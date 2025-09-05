#pragma once
#include <string.h>
#include "tier0/color.h"

enum e_font_draw_type
{
	font_draw_default = 0,
	font_draw_nonadditive,
	font_draw_additive,
	font_draw_type_count = 2,
};

enum e_font_flags
{
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

typedef unsigned long h_font;
typedef unsigned int vpanel;

struct int_rect
{
	int x0;
	int y0;
	int x1;
	int y1;
};


class i_surface
{
public:
	void set_drawing_color(int r, int g, int b, int a = 255)
	{
		using fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(fn**)this)[15](this, r, g, b, a);
	}

	void set_drawing_color(color color)
	{
		set_drawing_color((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	}

	void set_text_font(unsigned long font)
	{
		using fn = void(__thiscall*)(i_surface*, unsigned long);
		return (*(fn**)this)[21](this, font);
	}

	void set_text_color(color color)
	{
		set_text_color((int)color.r, (int)color.g, (int)color.b, (int)color.a);
	}

	void set_text_color(int r, int g, int b, unsigned int a = 0)
	{
		using fn = void(__thiscall*)(i_surface*, int, int, int, unsigned int);
		return (*(fn**)this)[23](this, r, g, b, a);
	}

	vpanel get_embedded_panel()
	{
		using fn = vpanel(__thiscall*)(i_surface*);
		return (*(fn**)this)[36](this);
	}
};