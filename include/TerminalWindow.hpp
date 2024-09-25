#ifndef TERMINAL_WINDOW
#define TERMINAL_WINDOW

#include <cstdint>
#include <string>

/* 
 * In TerminalGraphics, a TerminalWindow is equivalent
 * to a window found inside a monitor.
 * Each individual window has its own data, this being
 * position and a glyph buffer.
 *
 * Methods in a TerminalWindow serve to affect the
 * above mentioned data.
 * */

/*
 * A UTF-8 character's data is stored in a Glyph struct.
 * */
struct Glyph{
	uint32_t Ch; // 0x HH HH HH HH 
};

enum class DefaultBorderType{
	DOUBLE_LINE,
	SINGLE_LINE
};

class TerminalWindow{
public:
	uint8_t width, height;
	uint8_t xpos, ypos;
	Glyph* buffer;
	
	// TerminalWindow requires a width and a height for the constructor to be called.
	TerminalWindow(uint8_t,uint8_t);
	~TerminalWindow();
	
	// RasterBorder will assume glyphBuffer has a size of 8 elements, which it will use in making TLcorner clockwise. The left and right, as well as the top and bottom sides of the square can differ, hence a size of 8.
	void RasterBorder(Glyph*);
	void RasterBorder(DefaultBorderType);
	
	void RasterString(std::string,uint8_t,uint8_t);

	// Little Endian
	uint32_t utf8_to_uint32(const char*, uint8_t&);
	uint32_t utf8_to_uint32(const char*);

};

#endif
