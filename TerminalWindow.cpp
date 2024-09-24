#include "TerminalWindow.hpp"

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
	switch(b){
		case DefaultBorderType::TYPE1:
			Glyph* border = new Glyph[8];
			border[0].Ch = 0x00E29594;
			border[1].Ch = 0x00E29590;
			border[2].Ch = 0x00E29597;
			border[3].Ch = 0x00E29591;
			border[4].Ch = 0x00E2959D;
			border[5].Ch = 0x00E29590;
			border[6].Ch = 0x00E2959A;
			border[7].Ch = 0x00E29591;
			RasterBorder(border);
			delete[] border;
			break;
	}	
}
