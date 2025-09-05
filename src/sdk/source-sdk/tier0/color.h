#pragma once
#include <cstdint>
#include <d3d9.h>
#include <cmath>
#include <Windows.h>

struct color {
	int a, r, g, b;
	color() = default;
	color(const int r, const int g, const int b, const int a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	explicit color(const uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}

	static color from_uint(const uint32_t uint) {
		return color(uint);
	}

	static D3DCOLOR from_color(const color col) {
		return D3DCOLOR_ARGB(col.a, col.r, col.g, col.b);
	}

	static color black(const int a = 255) { return { 0, 0, 0, a }; }
	static color white(const int a = 255) { return { 255, 255, 255, a }; }
	static color red(const int   a = 255) { return { 255, 0, 0, a }; }
	static color green(const int a = 255) { return { 0, 255, 0, a }; }
	static color blue(const int  a = 255) { return { 0, 150, 255, a }; }
	static color yellow(const int  a = 255) { return { 255, 255, 0, a }; }
	static color turquoise(const int  a = 255) { return { 120, 255, 255, a }; }
	static color rainbow(float speed = 1.f, const int alpha = 255) {
		float time = fmodf(static_cast<float>(GetTickCount64()) / 1000.0f * (1.f / speed), 1.0f);

		float h = time * 360.0f;
		float s = 1.0f;
		float v = 1.0f;

		float c = v * s;
		float x = c * (1 - fabsf(fmodf(h / 60.0f, 2) - 1));
		float m = v - c;

		float r_, g_, b_;

		if (h < 60) { r_ = c; g_ = x; b_ = 0; }
		else if (h < 120) { r_ = x; g_ = c; b_ = 0; }
		else if (h < 180) { r_ = 0; g_ = c; b_ = x; }
		else if (h < 240) { r_ = 0; g_ = x; b_ = c; }
		else if (h < 300) { r_ = x; g_ = 0; b_ = c; }
		else { r_ = c; g_ = 0; b_ = x; }

		int r = static_cast<int>((r_ + m) * 255);
		int g = static_cast<int>((g_ + m) * 255);
		int b = static_cast<int>((b_ + m) * 255);

		return color(r, g, b, alpha);
	}
	static color green_red_fade(int source, float min = 0.f, float max = 5.f, const int alpha = 255) {
		if (source < min) source = static_cast<int>(min);
		if (source > max) source = static_cast<int>(max);

		float t = (static_cast<float>(source) - min) / (max - min);

		int r = static_cast<int>(255 * t);
		int g = static_cast<int>(255 * (1.f - t));
		int b = 0;

		return color(r, g, b, alpha);
	}
};
