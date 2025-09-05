void hooks::handles::set_text_color(i_surface* surface, int r, int g, int b, int a) {
	if (globals::apply_text_colors) {
		int new_r = min(255, r + globals::text_r);
		int new_g = min(255, g + globals::text_g);
		int new_b = min(255, b + globals::text_b);
		originals::set_text_color(surface, new_r, new_g, new_b, a);
		return;
	}

	originals::set_text_color(surface, r, g, b, a);
}