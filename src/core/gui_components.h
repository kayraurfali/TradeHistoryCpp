#pragma once

#include <color.h>
#include <string>

namespace trade_history
{
	enum text_alignment
	{
		MIDDLE_CENTER,

		LEFT_CENTER,
		RIGHT_CENTER,
		TOP_CENTER,
		BOTTOM_CENTER,

		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};
	/*
		These 2 should not be used as a component as they are the base components.
	*/
	struct s_padding // internal padding for texts
	{
		int top, left, right, bottom;
	};

	struct s_position
	{
		int x, y;
		s_padding padding;
	};

	// === SHAPE COMPONENTS === //

	struct rectangle
	{
		s_position position;
		int width, height;
	};

	struct circle
	{
		s_position pos;
		int radius;
	};

	// === STYLE AND EDIT COMPONENTS === //

	struct style
	{
		color *text_color;
		color *background_color;

		std::string text;
		
		text_alignment alignment;
	};
}