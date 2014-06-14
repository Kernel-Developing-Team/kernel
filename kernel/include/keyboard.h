#ifndef __KEYBOARD__H
#define __KEYBOARD__H

#include <types.h>

extern const char KeyboardMap[0x80];
extern const char KeyboardMapShift[0x80];
extern volatile uint8 KeyboardLastStatus;
extern volatile uint8 KeyboardLastScancode;

extern void KeyboardSetKeyStatus (uint8 scancode, uint8 status);
extern uint8 KeyboardGetKeyStatus (uint8 scancode);
extern void KeyboardHandler (_RegsStack32 *r);
extern void KeyboardSetLEDs (uint8 scroll, uint8 num, uint8 caps);
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
extern void KeyboardSetRepeatRate(uint8 rate, uint8 delay);

/***************************************
 *	 Set scancode set		  *
 ***************************************
	1  Set to scancode set 1
	2  Set to scancode set 2
	3  Set to scancode set 3
 ***************************************/
extern void KeyboardSetScancodeSet(uint8 set);

extern void KeyboardWaitOutport();
extern void KeyboardWaitInport();

extern void KeyboardInstallA();
extern void KeyboardInstallB();

#endif

