#pragma once

#include <ft2build.h>
#include <freetype/freetype.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

namespace trade_history
{
	class font
	{
		struct Character
		{
			unsigned int TextureID;  // ID handle of the glyph texture
			glm::ivec2   Size;       // Size of glyph
			glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
			unsigned int Advance;    // Offset to advance to next glyph
		};
	public:
		font();
		static font make_font();

		void load(const char *path, int32_t font_size);
		void draw(const std::string &text, float x, float y, float scale, const glm::vec3 &color);
	private:
		static bool is_library_initialized;

		FT_Library ft_library;
		FT_Face ft_face;

		uint32_t VBO, VAO;
		std::unordered_map<char, Character> Characters;
	};
}