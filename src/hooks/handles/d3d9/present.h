#include <iostream>

HRESULT APIENTRY hooks::handles::present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region) {
	if (globals::menu_open) {
		utilities::setup_imgui(device);
		utilities::setup_states(device);
		utilities::start_render();
		menu::render();
		utilities::end_render();
		utilities::backup_states(device);
	}

	if (GetAsyncKeyState(VK_F11) & 1)
		globals::menu_open = !globals::menu_open;

	return originals::present(device, src, dest, wnd_override, dirty_region);
}