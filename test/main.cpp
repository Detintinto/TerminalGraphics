#include <iostream>
#include <cstdint>
#include <string>

#include "TerminalScreen.hpp"

int main(){
	
	TerminalScreen TS(60,30);
	
	TerminalWindow* win = TS.CreateWindow(10,10);
	
	win->RasterString("▓", 1, 1);
	win->RasterBorder(DefaultBorderType::SINGLE_LINE);
	TS.RenderWindow();
	return 0;
}
