#include <system.h>


#include <stdio.h>
#include <keyboard.h>

#define KeybCmdWriteLED			0xed
#define KeybCmdEcho			0xee
#define KeybCmdSetScancodeSet		0xf0
#define KeybCmdGetID			0xf2
#define KeybCmdSetRepeatDelay		0xf3
#define KeybCmdEnable			0xf4
#define KeybCmdSetDefaultDisable	0xf5
#define KeybCmdSetDefault		0xf6
#define KeybCmdResend			0xfe
#define KeybCmdReset			0xff

volatile uint8 KeyState[16];
volatile uint8 KeyboardLastStatus;
volatile uint8 KeyboardLastScancode;

uint8	KeyboardScancodeSet = 2;

// Byte map:
// 0  If set, next code is break
// 1  'Gray' key
// 2  'Weird' key (Pause/Break)
// 3  Scroll
// 4  Num
// 5  Caps
// 6  If set, LEDs changed
uint8 KeyboardModifiers;

const char KeyboardMap[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\t', '`', 0,
	0, 0, 0, 0, 0, 'q', '1', 0, 0, 0, 'z', 's', 'a', 'w', '2', 0,
	0, 'c', 'x', 'd', 'e', '4', '3', 0, 0, ' ', 'v', 'f', 't', 'r', '5', 0,
	0, 'n', 'b', 'h', 'g', 'y', '6', 0, 0, 0, 'm', 'j', 'u', '7', '8', 0,
	0, ',', 'k', 'i', 'o', '0', '9', 0, 0, '.', '/', 'l', ';', 'p', '-', 0,
	0, 0, '\'', 0, '[', '=', 0, 0, 0, 0, '\n', ']', 0, '\\', 0, 0,
	0, 0, 0, 0, 0, 0, '\b', 0, 0, '1', '/', '4', '7', '\n', 0, 0,
	'0', '.', '2', '5', '6', '8', 0, 0, 0, '+', '3', '-', '*', '9', 0, 0
	};

const char KeyboardMapShift[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\t', '~', 0,
	0, 0, 0, 0, 0, 'Q', '!', 0, 0, 0, 'Z', 'S', 'A', 'W', '@', 0,
	0, 'C', 'X', 'D', 'E', '$', '#', 0, 0, ' ', 'V', 'F', 'T', 'R', '%', 0,
	0, 'N', 'B', 'H', 'G', 'Y', '^', 0, 0, 0, 'M', 'J', 'U', '&', '*', 0,
	0, '<', 'K', 'I', 'O', ')', '(', 0, 0, '>', '?', 'L', ':', 'P', '_', 0,
	0, 0, '\"', 0, '{', '+', 0, 0, 0, 0, '\n', '}', 0, '|', 0, 0,
	0, 0, 0, 0, 0, 0, '\b', 0, 0, '1', '/', '4', '7', '\n', 0, 0,
	'0', '.', '2', '5', '6', '8', 0, 0, 0, '+', '3', '-', '*', '9', 0, 0
	};


void KeyboardSetKeyStatus (uint8 scancode, uint8 status)
{
	int32 index = scancode>>3, pos = scancode & 0x7;

	if (status) KeyState[index] |= 1<<pos;
	else KeyState[index] &= ~(1<<pos);
}


uint8 KeyboardGetKeyStatus (uint8 scancode)
{
	int32 index = scancode>>3, pos = scancode & 0x7;

	return KeyState[index] & (1<<pos);
}



void _process_scancode(uint8 scancode)
{
	switch (scancode)
	{
	   // Messages from keyboard controller
		case 0x00:						// Error 0x00
		case 0xFC:						// Diagnostics failed (MF kb)
		case 0xFD:						// Diagnostics failed (AT kb)
		case 0xFF: KeyboardWaitOutport();
				outportb(0x60, KeybCmdEnable);
				return;				// Error 0xFF, reenable keyboard
		case 0xAA:						// BAT test successful.
		case 0xFA:						// ACKnowledge
		case 0xFE:						// Last command invalid or parity error
		case 0xEE: return;				// Echo response

	   // Break
		case 0xF0: KeyboardModifiers |= 1; return;

	   // Special character (gray, etc)
		case 0xE0: KeyboardModifiers |= 2; return;
		case 0xE1: KeyboardModifiers |= 4; return;

	   // Remap some characters:
		case 0x83: scancode = KeyboardKeyF7; break;

	   // LEDs
		case KeyboardKeyScrollLock:
			if ((KeyboardModifiers & 1) == 0) {
				KeyboardModifiers ^= 1<<3;
				KeyboardModifiers |= 1<<6;
			} break;
			
		case KeyboardKeyNumLock:
			if ((KeyboardModifiers & 1) == 0) {
				KeyboardModifiers ^= 1<<4;
				KeyboardModifiers |= 1<<6;
			} break;
		case KeyboardKeyCapsLock:
			if ((KeyboardModifiers & 1) == 0) {
				KeyboardModifiers ^= 1<<5;
				KeyboardModifiers |= 1<<6;
			} break;
	}

	// Remap most gray characters
	if (KeyboardModifiers & 2) switch (scancode)
	{
		case 0x10: scancode = KeyboardKeyMediaWebSearch; break;
		case 0x11: scancode = KeyboardKeyRightAlt; break;
		case 0x12: return;							// Fake shift, ignore
		case 0x14: scancode = KeyboardKeyRightCtrl; break;
		case 0x15: scancode = KeyboardKeyMediaPrevious; break;
		case 0x18: scancode = KeyboardKeyMediaWebFavorites; break;
		case 0x1F: scancode = KeyboardKeyLeftWin; break;
		case 0x20: scancode = KeyboardKeyMediaWebRefresh; break;
		case 0x21: scancode = KeyboardKeyMediaVolDown; break;
		case 0x23: scancode = KeyboardKeyMediaMute; break;
		case 0x27: scancode = KeyboardKeyRightWin; break;
		case 0x28: scancode = KeyboardKeyMediaWebStop; break;
		case 0x2B: scancode = KeyboardKeyMediaCalculator; break;
		case 0x2F: scancode = KeyboardKeyMenu; break;
		case 0x30: scancode = KeyboardKeyMediaWebForward; break;
		case 0x32: scancode = KeyboardKeyMediaVolUp; break;
		case 0x34: scancode = KeyboardKeyMediaPause; break;
		case 0x37: scancode = KeyboardKeyPower; break;
		case 0x38: scancode = KeyboardKeyMediaWebBack; break;
		case 0x3A: scancode = KeyboardKeyMediaWebHome; break;
		case 0x3B: scancode = KeyboardKeyMediaStop; break;
		case 0x3F: scancode = KeyboardKeySleep; break;
		case 0x40: scancode = KeyboardKeyMediaComputer; break;
		case 0x48: scancode = KeyboardKeyMediaEmail; break;
		case 0x4A: scancode = KeyboardKeyNumpadSlash; break;
		case 0x4D: scancode = KeyboardKeyMediaNext; break;
		case 0x50: scancode = KeyboardKeyMediaSelect; break;
		case 0x5A: scancode = KeyboardKeyNumpadEnter; break;
		case 0x5E: scancode = KeyboardKeyWake; break;
		case 0x69: scancode = KeyboardKeyEnd; break;
		case 0x6B: scancode = KeyboardKeyLeft; break;
		case 0x6C: scancode = KeyboardKeyHome; break;
		case 0x70: scancode = KeyboardKeyInsert; break;
		case 0x71: scancode = KeyboardKeyDelete; break;
		case 0x72: scancode = KeyboardKeyDown; break;
		case 0x74: scancode = KeyboardKeyRight; break;
		case 0x75: scancode = KeyboardKeyUp; break;
		case 0x7A: scancode = KeyboardKeyPageDown; break;
		case 0x7C: scancode = KeyboardKeyPrintScreen; break;
		case 0x7D: scancode = KeyboardKeyPageUp; break;
	}

	// Pause/break
	if (KeyboardModifiers & 4)
	{
		KeyboardSetKeyStatus(KeyboardKeyPause, 1 - (KeyboardModifiers & 1));

		if (scancode == 0x77) KeyboardModifiers = 0;
		return;
	}

	KeyboardSetKeyStatus(scancode, 1 - (KeyboardModifiers & 1));

	// Give functions something to wait for :P
	KeyboardLastScancode = scancode;
	KeyboardLastStatus = KeyboardModifiers;
	KeyboardModifiers &= ~7;
}





void KeyboardHandler (_RegsStack32* UNUSED(r))
{
	// Get scancode from keyboard
	uint8 scancode = inportb(0x60);

	// Process scancode
	_process_scancode(scancode);

	// LED update
	if (KeyboardModifiers & (1<<6))
	{
		KeyboardSetLEDs(KeyboardModifiers & (1<<3), KeyboardModifiers & (1<<4), KeyboardModifiers & (1<<5));
		KeyboardModifiers &= ~(1<<6);
	}

}


void KeyboardSetLEDs (uint8 scroll, uint8 num, uint8 caps)
{
	uint8 status = 0;
	status |= (scroll > 0);
	status |= (num > 0) << 1;
	status |= (caps > 0) << 2;

	KeyboardWaitOutport();
	outportb (0x60, KeybCmdWriteLED);

	KeyboardWaitOutport();
	outportb (0x60, status);
}


/***************************************
 *	 Set repeat rate/delay	   *
 ***************************************
 Values for inter-character delay (bits 4-0)
 (characters per second; default is 10.9)
     |  0 |  1 |  2 |  3 |  4 |  5 |  6 |  7
 ----+----+----+----+----+----+----+----+----
  0  |30.0|26.7|24.0|21.8|20.0|18.5|17.1|16.0
  8  |15.0|13.3|12.0|10.9|10.0|9.2 |8.6 |8.0
  16 |7.5 |6.7 |6.0 |5.5 |5.0 |4.6 |4.3 |4.0
  24 |3.7 |3.3 |3.0 |2.7 |2.5 |2.3 |2.1 |2.0

 Values for delay:
 (miliseconds; default is 500)
    0 |   1 |   2 |   3
 -----+-----+-----+-----
  250 | 500 | 750 | 1000

 ***************************************/
void KeyboardSetRepeatRate(uint8 rate, uint8 delay)
{
	if (rate>3 || delay>31) return;

	uint8 out = rate<<5 | delay;
	
	KeyboardWaitOutport();
	outportb(0x60, KeybCmdSetRepeatDelay);
	
	KeyboardWaitOutport();
	outportb(0x60, out);
}

/***************************************
 *	 Set scancode set		  *
 ***************************************
	1  Set to scancode set 1
	2  Set to scancode set 2
	3  Set to scancode set 3
 ***************************************/
void KeyboardSetScancodeSet(uint8 set)
{
    if (set>3 || set <= 0) return;

    KeyboardWaitOutport();
    outportb (0x60, KeybCmdSetScancodeSet);

    KeyboardWaitOutport();
    outportb (0x60, set);

    KeyboardScancodeSet = set;
}


void KeyboardWaitOutport()
{
	int fail_safe=200000;
	while ((inportb(0x64)&2)!=0 && fail_safe>0) fail_safe--;
}

void KeyboardWaitInport()
{
	int fail_safe=200000;
	while ((inportb(0x64)&1)==0 && fail_safe>0) fail_safe--;
}


void KeyboardInstallA()
{
	KeyboardWaitOutport();
	outportb(0x60, KeybCmdReset);	   // Reset kb

	// Initialize variables
	KeyboardLastStatus = 0;
	KeyboardModifiers = 0;

	int32 i;
	for (i = 0; i < 16; i++)
		KeyState[i] = 0;
}


void KeyboardInstallB()
{
	// Wait for BAT test results
	KeyboardWaitInport();
	
	unsigned char temp;
	do temp = inportb(0x60);
	while (temp!=0xAA && temp!=0xFC);

	// Error
	if (temp == 0xFC) return;

	// Set new repeat rate
	KeyboardSetRepeatRate(1, 11);

	// Set scancode set 2
	KeyboardSetScancodeSet(2);  // Set new scancode set

	KeyboardWaitOutport();
	outportb(0x64, 0x20); // Get "Command unsigned char"

	do {  temp = inportb(0x60);
	} while (temp==0xFA || temp==0xAA);

	temp &= ~(1<<6); 	// Unset bit6: disable conversion
	KeyboardWaitOutport();
	outportb(0x64, 0x60); // Function to write cmd unsigned char
	
	KeyboardWaitOutport();
	outportb(0x60, temp); // Send it
}
