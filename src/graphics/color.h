#pragma once

namespace trade_history
{
	struct color
	{
	public:
		static color *make_color(int r, int g, int b, int a)
		{
			return new color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}
	private:
		color(float r, float g, float b, float a);
		float r, g, b, a;
	};

	static const color *black = color::make_color(0, 0, 0, 255);
	static const color *white = color::make_color(255, 255, 255, 255);
	
	static const color *light_grey = color::make_color(64, 64, 64, 255);
	static const color *grey = color::make_color(127, 127, 127, 255);
	static const color *dark_grey = color::make_color(192, 192, 192, 255);

	static const color *red = color::make_color(255, 0, 0, 255);
	static const color *blue = color::make_color(0, 255, 0, 255);
	static const color *green = color::make_color(0, 0, 255, 255);
}