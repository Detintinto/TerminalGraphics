#include "TerminalScreen.hpp"

#include <iostream>

/*
 * Constructor and Destructor
 * */
TerminalScreen::TerminalScreen(uint8_t width, uint8_t height): width(width), height(height){
	windowBuffer.reserve(5);
}
TerminalScreen::~TerminalScreen(){
	for(auto i = windowBuffer.begin(); i != windowBuffer.end(); ++i){
		(*i)->~TerminalWindow();
	}
}

/*
 * Create and Destroy Window's
 * */
TerminalWindow* TerminalScreen::CreateWindow(uint8_t width, uint8_t height){
	TerminalWindow* TW = new TerminalWindow(width, height);
	windowBuffer.push_back(TW);
	return TW;
}
void TerminalScreen::DestroyWindow(TerminalWindow* windowToDestroy){
	for(auto i = windowBuffer.begin(); i != windowBuffer.end(); ++i){
		if(*i == windowToDestroy){
			(*i)->~TerminalWindow();
			windowBuffer.erase(i);
			continue;
		}
	}
}

/*
 * Ansi Escape Sequence Methods
 * */
std::string inline TerminalScreen::ChangeCursorPos(uint8_t xp, uint8_t yp){
	std::string buffer;
	buffer.clear();

	buffer += "\033[";
	buffer += std::to_string(yp);
	buffer += ";";
	buffer += std::to_string(xp);
	buffer += "H";
	
	return buffer;
}

/*
 * Render Window's
 * */
void TerminalScreen::RenderWindow(){
	uint8_t* byteAddress = 0;
	printBuffer.clear();

	for(auto w : windowBuffer){
		printBuffer += ChangeCursorPos(w->xpos+1,w->ypos+1);
		
		for(uint8_t y = 0; y < w->height; ++y){
			for(uint8_t x = 0; x < w->width; ++x){
				
				//
				// NEEDS CHANGING FOR WHEN THE WINDOWS GET CLIPPED BY THE SCREEN!!!
				//
				if(w->buffer[x+w->width*y].Ch == 0){
					if(x < w->width-1)
						printBuffer += "\033[C";
					continue;
				}

				byteAddress = reinterpret_cast<uint8_t*>( &(w->buffer[x+w->width*y].Ch) );
				byteAddress += 3; // Points to the last byte, which needs to be added first.
				for(uint8_t k = 0; k < 4; ++k){
					printBuffer += *byteAddress;
					byteAddress--;
				} 
			}
			if(y + 1 < w->height)
				printBuffer += ChangeCursorPos(w->xpos+1, w->ypos+1+y+1);
		}
	}
	std::cout << printBuffer;
}
