#ifndef TERMINAL_SCREEN
#define TERMINAL_SCREEN 

#include <cstdint>
#include <vector>
#include <string>

#include "TerminalWindow.hpp"

/*
 * In TerminalGraphics, a TerminalScreen is equivalent to
 * a monitor.
 * It manages the TerminalWindow's by being responsible
 * for creating, destroying, and rendering them.
 * */

class TerminalScreen{
	uint8_t width, height;
	std::vector<TerminalWindow*> windowBuffer;
	std::string printBuffer;
	public:
	std::string ChangeCursorPos(uint8_t, uint8_t);

public:

	TerminalScreen(uint8_t, uint8_t);
	~TerminalScreen();

	TerminalWindow* CreateWindow(uint8_t, uint8_t);
	void DestroyWindow(TerminalWindow*);

	void RenderWindow();
};

#endif
