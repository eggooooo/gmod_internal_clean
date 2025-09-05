void hooks::handles::paint_traverse(i_panel* panel, v_panel v_panel, bool force_repaint, bool allow_force) {
	if (!strcmp(interfaces::panel->get_name(v_panel), xorstr("GameConsole")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("CompletionList"))	||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("OptionsDialog")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("CServerBrowserDialog")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("OptionsSubVideoAdvancedDlg")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("FileOpenDialog")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("DemoUIPanel")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("DemoSmootherPanel")) ||
		!strcmp(interfaces::panel->get_name(v_panel), xorstr("LoadingDialog"))) {

		globals::apply_panel_colors = globals::override_panel_colors;
		globals::apply_text_colors = globals::override_text_colors;
		originals::paint_traverse(panel, v_panel, force_repaint, allow_force);
		globals::apply_panel_colors = false;
		globals::apply_text_colors = false;
		return;
	}

	if (!strcmp(interfaces::panel->get_name(v_panel), xorstr("OverlayPopupPanel"))) {
		interfaces::panel->set_key_board_input_enabled(v_panel, globals::menu_open);
		interfaces::panel->set_mouse_input_enabled(v_panel, globals::menu_open);
	}

	originals::paint_traverse(panel, v_panel, force_repaint, allow_force);
}