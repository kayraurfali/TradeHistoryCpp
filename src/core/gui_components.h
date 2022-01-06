#pragma once

#include <graphics/color.h>
#include <graphics/font.h>
#include <util/types.h>
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

	struct component_base {};

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
	static u32 s_component_id_counter = 0;

	struct rectangle
	{
		static u32 component_id;

		s_position position;
		int width, height;
	};

	struct circle
	{
		static u32 component_id;

		s_position pos;
		int radius;
	};

	// === STYLE AND EDIT COMPONENTS === //

	struct style
	{
		static u32 component_id;

		color *text_color;
		color *background_color;

		const char* text;
		font text_font;
		text_alignment alignment;
	};
	
	using click_callback = void(*)();
	struct clickable
	{
		static u32 component_id;

		click_callback on_click;
	};
}