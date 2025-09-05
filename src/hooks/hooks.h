#pragma once
#pragma comment(lib, "Winmm.lib")

#include "../sdk/interfaces.h"

#include "../utils/utilities.h"
#include "../settings.h"

namespace hooks {
	void initialize();
	void shutdown();

	namespace handles {
		LRESULT CALLBACK			wndproc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
		HRESULT APIENTRY			present(IDirect3DDevice9* device, CONST RECT* src, CONST RECT* dest, HWND wnd_override, CONST RGNDATA* dirty_region);
		HRESULT APIENTRY			reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters);
		void __fastcall				html_panel_load_url(void* html_panel, const char* url);
		int __fastcall				html_panel_paint(void* html_panel);
		int __fastcall				send_datagram(c_net_channel* net_channel, void* datagram);
		void						paint_traverse(i_panel* panel, v_panel v_panel, bool force_repaint, bool allow_force);
		void 						set_draw_color(i_surface* surface, int r, int g, int b, int a);
		void 						set_text_color(i_surface* surface, int r, int g, int b, int a);

		namespace originals {
			inline WNDPROC wndproc = nullptr;
			inline HRESULT(APIENTRY* reset) (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			inline HRESULT(APIENTRY* present) (IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
			inline void(__thiscall* html_panel_load_url)(void*, const char*);
			inline int(__thiscall* html_panel_paint)(void*);
			inline int(__thiscall* send_datagram)(c_net_channel*, void*);
			inline void(__fastcall* paint_traverse)(i_panel*, v_panel, bool, bool);
			inline void(__fastcall* set_draw_color)(i_surface*, int, int, int, int);
			inline void(__fastcall* set_text_color)(i_surface*, int, int, int, int);
		}
	}
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);