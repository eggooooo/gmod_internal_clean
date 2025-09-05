#include "utilities.h"
using namespace ImGui;

bool utilities::game_is_fully_loaded() {
	return GetModuleHandleA(xorstr("client.dll"))
		&& GetModuleHandleA(xorstr("engine.dll"))
		&& GetModuleHandleA(xorstr("menusystem.dll"))
		&& GetModuleHandleA(xorstr("gameoverlayrenderer64.dll"))
		&& GetModuleHandleA(xorstr("vgui2.dll"));
}

void utilities::attach_console() {
	AllocConsole();
	freopen(xorstr("conin$"), "r", stdin);
	freopen(xorstr("conout$"), "w", stdout);
	freopen(xorstr("conout$"), "w", stderr);
	SetConsoleTitleA(xorstr("gmod_internal"));
}

void utilities::detach_console() {
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	FreeConsole();
}

void utilities::run_javascript(void* html_panel, const char* script) {
	using run_javascript_fn = void(*)(void*, const char*);
	static run_javascript_fn run_javascript = (run_javascript_fn)memory::pattern_scanner(xorstr("menusystem.dll"), xorstr("48 8B 89 ? ? ? ? 48 8B 01 48 FF 60 68"));

	if (!run_javascript)
		throw;

	if (html_panel)
		run_javascript(html_panel, script);
}

void utilities::disconnect(const char* msg) {
	c_net_channel* net_channel = interfaces::engine->get_net_channel();
	if (!net_channel)
		return;

	if (net_channel) {
		net_channel->shutdown(msg);
		return;
	}
}

//1 = save, 2 = load
void utilities::config_handler(int mode) {
	char exe_path[MAX_PATH];
	GetModuleFileNameA(NULL, exe_path, MAX_PATH);
	char* last_slash = strrchr(exe_path, '\\');
	if (last_slash) *last_slash = '\0';

	std::string outdir = std::string(exe_path) + "\\gmod_internal";
	_mkdir(outdir.c_str());

	std::string file_str = outdir + "\\" + "config.cfg";

	auto save_config = [&]() {
		std::ofstream file(file_str);
		if (!file.is_open()) {
			std::cout << "Config save failed." << std::endl;
			return;
		}

		file << "override_panel_colors=" << globals::override_panel_colors << "\n";
		file << "panel_r=" << globals::panel_r << "\n";
		file << "panel_g=" << globals::panel_g << "\n";
		file << "panel_b=" << globals::panel_b << "\n";

		file << "override_text_colors=" << globals::override_text_colors << "\n";
		file << "text_r=" << globals::text_r << "\n";
		file << "text_g=" << globals::text_g << "\n";
		file << "text_b=" << globals::text_b << "\n";

		file << "disconnect_msg=\"" << globals::disconnect_msg << "\"\n";
		file << "menu_bg_url=\"" << globals::menu_bg_url << "\"\n";
		file << "load_url=\"" << globals::load_url << "\"\n";

		file.close();
		std::cout << "Config saved to: " << file_str << std::endl;
		};

	if (mode == 1) {
		save_config();
	}
	else if (mode == 2) {
		std::ifstream file(file_str);
		if (!file.is_open()) {
			std::cout << "Config not found. Creating config file." << std::endl;
			save_config();
			file.open(file_str);
			if (!file.is_open()) {
				std::cout << "Failed to create config file." << std::endl;
				return;
			}
		}

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string key, value;

			if (std::getline(iss, key, '=') && std::getline(iss, value)) {
				if (key == "override_panel_colors")
					globals::override_panel_colors = (value == "1");
				else if (key == "panel_r")
					globals::panel_r = std::stof(value);
				else if (key == "panel_g")
					globals::panel_g = std::stof(value);
				else if (key == "panel_b")
					globals::panel_b = std::stof(value);
				else if (key == "override_text_colors")
					globals::override_text_colors = (value == "1");
				else if (key == "text_r")
					globals::text_r = std::stof(value);
				else if (key == "text_g")
					globals::text_g = std::stof(value);
				else if (key == "text_b")
					globals::text_b = std::stof(value);
				else if (key == "disconnect_msg") {
					if (!value.empty() && value.front() == '"' && value.back() == '"')
						value = value.substr(1, value.length() - 2);

					globals::disconnect_msg = value;
				}
				else if (key == "menu_bg_url") {
					if (!value.empty() && value.front() == '"' && value.back() == '"')
						value = value.substr(1, value.length() - 2);

					globals::menu_bg_url = value;
				}
				else if (key == "load_url") {
					if (!value.empty() && value.front() == '"' && value.back() == '"')
						value = value.substr(1, value.length() - 2);

					globals::load_url = value;
				}
			}
		}

		file.close();
		std::cout << "Config loaded from: " << file_str << std::endl;
	}
}

void utilities::setup_imgui(IDirect3DDevice9* device) {
	static std::once_flag once;
	std::call_once(once, [&] {
		CreateContext();
		ImGui_ImplWin32_Init(interfaces::window);
		ImGui_ImplWin32_GetDpiScaleForHwnd(interfaces::window);
		ImGui_ImplDX9_Init(device);

		draw_list = new ImDrawList(GetDrawListSharedData());

		StyleColorsDark();

		ImGuiIO& io = GetIO();
		ImFontConfig cfg = {};

		cfg.PixelSnapH = true;
		cfg.OversampleH = cfg.OversampleV = 1;
	});
}

void utilities::shutdown() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	DestroyContext();
}

void utilities::start_render() {
	c_mat_render_context* ctx = interfaces::material_system->get_render_context();
	if (ctx)
	{
		ctx->begin_render();
		rt = ctx->get_render_target();
		ctx->set_render_target(nullptr);
		ctx->end_render();
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	NewFrame();
}

void utilities::end_render() {
	EndFrame();
	Render();

	if (interfaces::engine->is_in_game()) {
		ImDrawData draw_data;
		draw_data.Valid = true;
        draw_data.CmdLists.clear();
        draw_data.CmdLists.push_back(draw_list);
		draw_data.CmdListsCount = 1;
		draw_data.TotalVtxCount = draw_list->VtxBuffer.size();
		draw_data.TotalIdxCount = draw_list->IdxBuffer.size();

		draw_data.DisplayPos = GetMainViewport()->Pos;
		draw_data.DisplaySize = GetMainViewport()->Size;
		draw_data.FramebufferScale = ImVec2(1.0f, 1.0f);

		ImGui_ImplDX9_RenderDrawData(&draw_data);
	}

	ImGui_ImplDX9_RenderDrawData(GetDrawData());

	if (rt) {
		c_mat_render_context* ctx = interfaces::material_system->get_render_context();
		if (ctx) {
			ctx->begin_render();
			ctx->set_render_target(rt);
			ctx->end_render();
		}
	}

	rt = nullptr;
}

void utilities::setup_states(IDirect3DDevice9* device) {
	device->CreateStateBlock(D3DSBT_ALL, &pixel_state);

	pixel_state->Capture();

	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_FOGENABLE, FALSE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
	device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
}

void utilities::backup_states(IDirect3DDevice9* device) {
	pixel_state->Apply();
	pixel_state->Release();
}