#pragma once
#include <cmath>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector3.hpp>

float clamp(float v, float min, float max) {
	//In debug mode might want to assert on max < min
	return std::max(min, std::min(v, max));
}

float clampAngle(float a) {
	if (!std::isnormal(a)) {
		return 0.0f;
	}
	while (a < 0.0f) {
		a += 360.0f;
	}
	while (a >= 360.0f) {
		a -= 360.0f;
	}
	return a;
}

struct HSV_Color {
	float h;
	float s;
	float v;

	HSV_Color() : h(0.0f), s(0.0f), v(0.0f) {

	}
	HSV_Color(float h, float s, float v)
		: h(clampAngle(h)), s(clamp(s, 0.0f, 1.0f)), v(clamp(v, 0.0f, 1.0f)) {

	}
};

HSV_Color shiftHSV(HSV_Color in, float hs, float ss, float vs) {
	return (HSV_Color(in.h + hs, in.s + ss, in.v + vs));
}

//Adapted from https://stackoverflow.com/a/6930407
HSV_Color rgb2hsv(sf::Color color)
{
	HSV_Color         out;
	sf::Vector3f in;
	in.x = color.r / 255.0f;
	in.y = color.g / 255.0f;
	in.z = color.b / 255.0f;
	float      min, max, delta;
	
	min = in.x < in.y ? in.x : in.y;
	min = min  < in.z ? min : in.z;

	max = in.x > in.y ? in.x : in.y;
	max = max  > in.z ? max : in.z;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0f;
		out.h = (float)NAN;                            // its now undefined
		return out;
	}
	if (in.x >= max) {                        // > is bogus, just keeps compilor happy
		out.h = (in.y - in.z) / delta;        // between yellow & magenta
	} else {
		if (in.y >= max) {
			out.h = 2.0f + (in.z - in.x) / delta;  // between cyan & yellow
		} else {
			out.h = 4.0f + (in.x - in.y) / delta;  // between magenta & cyan
		}
	}
	out.h *= 60.0f;                              // degrees

	if (out.h < 0.0f) {
		out.h += 360.0f;
	}

	return out;
}


sf::Color hsv2rgb(HSV_Color in)
{
	float      hh, p, q, t, ff;
	long        i;
	sf::Vector3f  out;

	if (in.s <= 0.0f) {       // < is bogus, just shuts up warnings
		out.x = in.v;
		out.y = in.v;
		out.z = in.v;
		return sf::Color((sf::Uint8)(out.x * 255), (sf::Uint8)(out.y * 255), (sf::Uint8)(out.z * 255), 255);
	}
	hh = in.h;
	if (hh >= 360.0f) {
		hh = 0.0f;
	}
	hh /= 60.0f;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0f - in.s);
	q = in.v * (1.0f - (in.s * ff));
	t = in.v * (1.0f - (in.s * (1.0f - ff)));

	switch (i) {
	case 0:
		out.x = in.v;
		out.y = t;
		out.z = p;
		break;
	case 1:
		out.x = q;
		out.y = in.v;
		out.z = p;
		break;
	case 2:
		out.x = p;
		out.y = in.v;
		out.z = t;
		break;

	case 3:
		out.x = p;
		out.y = q;
		out.z = in.v;
		break;
	case 4:
		out.x = t;
		out.y = p;
		out.z = in.v;
		break;
	case 5:
	default:
		out.x = in.v;
		out.y = p;
		out.z = q;
		break;
	}
	return sf::Color((sf::Uint8)(out.x * 255), (sf::Uint8)(out.y * 255), (sf::Uint8)(out.z * 255), 255);
}