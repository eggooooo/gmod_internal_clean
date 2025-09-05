void hooks::handles::set_draw_color(i_surface* surface, int r, int g, int b, int a) {
	if (globals::apply_panel_colors) {
		int new_r = min(255, r + globals::panel_r);
		int new_g = min(255, g + globals::panel_g);
		int new_b = min(255, b + globals::panel_b);
		originals::set_draw_color(surface, new_r, new_g, new_b, a);
		return;
	}

	originals::set_draw_color(surface, r, g, b, a);
}