#include "TerminalWindow.hpp"
#include <iostream>

/*
 * Constructor and Destructor
 * */
TerminalWindow::TerminalWindow(uint8_t width, uint8_t height) : width(width), height(height){
	xpos = 0;
	ypos = 0;

	buffer = new Glyph[width*height];
	for(int i = 0; i < width*height; i++)
		buffer[i].Ch = 0;
}
TerminalWindow::~TerminalWindow(){
	delete[] buffer;
}

/*
 * Raster Methods
 * */
void TerminalWindow::RasterBorder(Glyph* glyphBuffer){
	for(int y = 1; y<height-1;y++){
		buffer[0+width*y].Ch = glyphBuffer[7].Ch;	
		buffer[(width-1)+width*y].Ch = glyphBuffer[3].Ch;
	}
	for(int x = 1; x<width-1;x++){
		buffer[x+width*0].Ch = glyphBuffer[1].Ch;	
		buffer[x+width*(height-1)].Ch = glyphBuffer[5].Ch;
	}
	buffer[0+width*0].Ch = glyphBuffer[0].Ch;
	buffer[width-1+width*0].Ch = glyphBuffer[2].Ch;
	buffer[width-1+width*(height-1)].Ch = glyphBuffer[4].Ch;
	buffer[0+width*(height-1)].Ch = glyphBuffer[6].Ch;
}
void TerminalWindow::RasterBorder(DefaultBorderType b){
	Glyph* border = new Glyph[8];
	switch(b){
		case DefaultBorderType::DOUBLE_LINE:
			border[0].Ch = utf8_to_uint32("╔");
			border[1].Ch = utf8_to_uint32("═");
			border[2].Ch = utf8_to_uint32("╗");
			border[3].Ch = utf8_to_uint32("║");
			border[4].Ch = utf8_to_uint32("╝");
			border[5].Ch = utf8_to_uint32("═");
			border[6].Ch = utf8_to_uint32("╚");
			border[7].Ch = utf8_to_uint32("║");
			RasterBorder(border);
			break;
		case DefaultBorderType::SINGLE_LINE:
			border[0].Ch = utf8_to_uint32("┌");
			border[1].Ch = utf8_to_uint32("─");
			border[2].Ch = utf8_to_uint32("┐");
			border[3].Ch = utf8_to_uint32("│");
			border[4].Ch = utf8_to_uint32("┘");
			border[5].Ch = utf8_to_uint32("─");
			border[6].Ch = utf8_to_uint32("└");
			border[7].Ch = utf8_to_uint32("│");
			RasterBorder(border);
			break;
	}
	delete[] border;
}

void TerminalWindow::RasterString(std::string text, uint8_t xpos, uint8_t ypos){
	uint8_t count = text.size();
	uint8_t readUtf8Size = 0;
	uint8_t temp;
	for(uint8_t x = xpos; x < width; ++x){
			if(count == 0)
				return;
			buffer[x+width*ypos].Ch = utf8_to_uint32(text.c_str() + readUtf8Size, temp);
			readUtf8Size += temp;
			count--;
		} 
	for(uint8_t y = ypos+1; y < height; ++y){
		for(uint8_t x = 0; x < width; ++x){
			if(count == 0)
				return;
			buffer[x+width*y].Ch = utf8_to_uint32(text.c_str() + readUtf8Size, temp);
			readUtf8Size += temp;
			count--;
		}
	}	
}

/*
 * UTF8 Helper Methods
 * */

uint32_t TerminalWindow::utf8_to_uint32(const char* utf8, uint8_t& utf8Size){
	const uint8_t* f = reinterpret_cast<const uint8_t*>(utf8);
	uint32_t num = 0;
	if((f[0] >> 7) == 0b0){
		utf8Size = 1;
		return f[0];	
	}
	else if((f[0] >> 3) == 0b11110){
		num = ((((((num | f[0]) << 8) | f[1]) << 8) | f[2]) << 8) | f[3]; 
		utf8Size = 4;
		return num;
	}
	else if((f[0] >> 4) == 0b1110){
		num = ((((num | f[0]) << 8) | f[1]) << 8) | f[2];
		utf8Size = 3;
		return num;
	}
	else if((f[0] >> 5) == 0b110){
		num = ((num | f[0]) << 8) | f[1];
		utf8Size = 2;
		return num;
	}
	utf8Size = 0;
	return num;
}
uint32_t TerminalWindow::utf8_to_uint32(const char* utf8){
	const uint8_t* f = reinterpret_cast<const uint8_t*>(utf8);
	uint32_t num = 0;
	if((f[0] >> 7) == 0b0){
		return f[0];	
	}
	else if((f[0] >> 3) == 0b11110){
		num = ((((((num | f[0]) << 8) | f[1]) << 8) | f[2]) << 8) | f[3]; 
		return num;
	}
	else if((f[0] >> 4) == 0b1110){
		num = ((((num | f[0]) << 8) | f[1]) << 8) | f[2];
		return num;
	}
	else if((f[0] >> 5) == 0b110){
		num = ((num | f[0]) << 8) | f[1];
		return num;
	}
	return num;
}
