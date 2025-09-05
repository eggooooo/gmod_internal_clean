#include "interfaces.h"

void interfaces::initialize() {
	engine = memory::capture_interface<c_engine_client>(xorstr("engine.dll"), xorstr("VEngineClient015"));
	if (!engine)
		throw;

	panel = memory::capture_interface<i_panel>(xorstr("vgui2.dll"), xorstr("VGUI_Panel009"));
	if (!panel)
		throw;

	hl_client = memory::capture_interface<c_hl_client>(xorstr("client.dll"), xorstr("VClient017"));
	if (!hl_client)
		throw;

	engine_vgui = memory::capture_interface<c_engine_vgui>(xorstr("engine.dll"), xorstr("VEngineVGui001"));
	if (!engine_vgui)
		throw;

	surface = memory::capture_interface<i_surface>(xorstr("vguimatsurface.dll"), xorstr("VGUI_Surface030"));
	if (!surface)
		throw;

	material_system = memory::capture_interface<c_material_system>(xorstr("materialsystem.dll"), xorstr("VMaterialSystem080"));
	if (!material_system)
		throw;

	window = FindWindowW(xorstr(L"Valve001"), NULL);
	if (!window)
		throw;
}