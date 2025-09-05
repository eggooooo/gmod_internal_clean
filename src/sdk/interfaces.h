#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include <direct.h>
#include <algorithm>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <intrin.h>
#include <mutex>

#include "../dependencies/xorstr/xorstr.h"
#include "../dependencies/memory/memory.h"
#include "../dependencies/minhook/min_hook.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/imgui_impl_dx9.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

#include "source-sdk/tier0/color.h"
#include "source-sdk/tier0/platform.h"
#include "source-sdk/tier1/c_utl_memory.h"
#include "source-sdk/tier1/c_utl_vector.h"
#include "source-sdk/vgui/i_panel.h"
#include "source-sdk/vgui/c_engine_vgui.h"
#include "source-sdk/engine/c_net_channel.h"
#include "source-sdk/client/c_hl_client.h"
#include "source-sdk/c_engine_client.h"
#include "source-sdk/i_surface.h"
#include "source-sdk/materialsystem/i_material.h"
#include "source-sdk/materialsystem/i_texture.h"
#include "source-sdk/materialsystem/c_material_system.h"

#include "../utils/utilities.h"
#include "../utils/menu.h"
#include "../settings.h"

namespace interfaces {
	void initialize();

	inline c_engine_client*			engine;
	inline i_panel*					panel;
	inline c_hl_client*				hl_client;
	inline c_engine_vgui*			engine_vgui;
	inline i_surface*				surface;
	inline c_material_system*		material_system;
	inline HWND						window;
}