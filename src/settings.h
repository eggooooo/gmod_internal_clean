#pragma once
#include "sdk/interfaces.h"

namespace globals {
    inline void* menu_panel = nullptr;
	inline bool menu_open = false;
	inline bool apply_panel_colors = false;
	inline bool apply_text_colors = false;

	inline bool override_panel_colors = false;
	inline int panel_r = 255;
	inline int panel_g = 255;
	inline int panel_b = 255;

	inline bool override_text_colors = false;
	inline int text_r = 255;
	inline int text_g = 255;
	inline int text_b = 255;

	inline std::string disconnect_msg = "";
	inline std::string menu_bg_url = "";
	inline std::string load_url = "";
}