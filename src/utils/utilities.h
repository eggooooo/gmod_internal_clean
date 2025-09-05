#pragma once
#include "../sdk/interfaces.h"
#include "../settings.h"

namespace utilities {
	static i_texture* rt = nullptr;
	static IDirect3DStateBlock9* pixel_state = nullptr;
	inline ImDrawList* draw_list;

	bool game_is_fully_loaded();
	void attach_console();
	void detach_console();
	void run_javascript(void* html_panel, const char* script);
	void disconnect(const char* msg);
	void config_handler(int mode);
	void setup_imgui(IDirect3DDevice9* device);
	void shutdown();

	void start_render();
	void end_render();

	void setup_states(IDirect3DDevice9* device);
	void backup_states(IDirect3DDevice9* device);
}