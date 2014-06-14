#ifndef __DEBUGIO__H
#define __DEBUGIO__H

#include <types.h>
#include <stdarg.h>

enum Colors
{
	ColorBlack			=	0x0,
	ColorBlue			=	0x1,
	ColorGreen			=	0x2,
	ColorCyan			=	0x3,
	ColorRed			=	0x4,
	ColorMagenta		=	0x5,
	ColorBrown			=	0x6,
	ColorLightGray		=	0x7,
	ColorDarkGray		=	0x8,
	ColorLightBlue		=	0x9,
	ColorLightGreen		=	0xA,
	ColorLightCyan		=	0xB,
	ColorLightRed		=	0xC,
	ColorLightMagenta		=	0xD,
	ColorYellow			=	0xE,
	ColorWhite			=	0xF
};

extern uint8 Color (uint8 back, uint8 fore);

// Cursor position
extern Point ConsoleGetCursor();
extern void ConsoleSetCursor(Point p);
extern void ConsoleCursorGoto(Point p);

extern void ConsoleCursorIncreasePos (int32 delta);
extern void ConsoleCursorNewline();
extern void ConsoleCursorUpdateHardware();

// Get/set properties
extern void ConsoleSetDefaultColor(uint8 color);
extern uint8 ConsoleGetDefaultColor ();
extern UPoint ConsoleGetSize();

extern void ConsoleSetChar(Point pos, char c);
extern void ConsoleSetColor(Point pos, uint8 color);
extern char ConsoleGetChar(Point pos);
extern uint8 ConsoleGetColor (Point pos);


// Basic console operations
extern void ConsoleClear();
extern void ConsoleScroll (uint32 lines);

// Console write operations
extern void ConsoleWriteChar (char c);
extern void ConsoleWriteString (string s);
extern int32 ConsoleWrite (string format, ...);

// Console read operations
extern void ConsoleReadString (string s, int32 buffer_size, char end_char);

// Console main loop
extern void ConsoleMain();


// External test routines
extern void SystemPanic();
extern int32 LogWrite (uint8 error, string device, string format, ...);
extern void LogAssert (int32 condition, string file, int32 line);

// Debug print
#define Log(dev, ...) { LogWrite(0, dev, __VA_ARGS__); }
#define Error(dev, ...) { LogWrite(1, dev, __VA_ARGS__); }
#define Panic(dev, ...) { LogWrite(1, dev, __VA_ARGS__); SystemPanic();  }
#define Assert(c) { LogAssert(c, __FILE__, __LINE__); }

#endif
