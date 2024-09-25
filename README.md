# TerminalGUI
A library for ease in doing terminal GUI.

The two important classes are TerminalScreen and TerminalWindow.
The TerminalScreen acts like the monitor, while the TerminalWindow acts like windows inside the monitor.

Instantiate a TerminalScreen, and you will be allowed to create and destroy TerminalWindows, as well as render them.

Once a TerminalWindow is created, you can, by yourself, change the uint32_t buffer, which holds the UTF8 glyphs, or you can use the Render--- methods to streamline the process.
