#ifndef __TYPES__H
#define __TYPES__H

// Get rid of annoying unused params warnings
#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

/****************************************
 *     NULL constant                    *
 ****************************************/
#define null 0
#define NULL 0

/****************************************
 *     Int definitions                  *
 ****************************************/
typedef signed char int8;
typedef unsigned char   uint8;
typedef short  int16;
typedef unsigned short  uint16;
typedef int  int32;
typedef unsigned   uint32;
typedef long long  int64;
typedef unsigned long long   uint64;


/****************************************
 *     Limits definitions               *
 ****************************************/
#define INT8_MIN (-128) 
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN  (-9223372036854775807LL - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 0xff /* 255U */
#define UINT16_MAX 0xffff /* 65535U */
#define UINT32_MAX 0xffffffff  /* 4294967295U */
#define UINT64_MAX 0xffffffffffffffffULL /* 18446744073709551615ULL */


/****************************************
 *     Registers                        *
 ****************************************/
// 32 bit registers
typedef struct {
    uint32 eax, ebx, ecx, edx, esi, edi, ebp, esp, eflags;
    uint8 cflag;
} _R32BIT;

// 16 bit registers
typedef struct {
    uint16 ax, bx, cx, dx, si, di, bp, sp, es, cs, ss, ds, flags;
    uint8 cflag;
} _R16BIT ;

// 16 bit registers expressed in 32 bit registers
typedef struct {
    uint16 ax, axh, bx, bxh, cx, cxh, dx, dxh;
	uint16 si, di, bp, sp, es, cs, ss, ds, flags;
	uint8 cflags;
} _R16BIT32 ;

// 8 bit registers
typedef struct {
    uint8 al, ah, bl, bh, cl, ch, dl, dh;
} _R8BIT;

// 8 bit registers expressed in 32 bit registers
typedef struct {
    uint8 al, ah; uint16 axh; 
	uint8 bl, bh; uint16 bxh; 
	uint8 cl, ch; uint16 cxh; 
	uint8 dl, dh; uint16 dxh; 
} _R8BIT32;

// 8 and 16 bit registers union
typedef union {
     _R16BIT x;
     _R8BIT h;
}_INTR16;

// 32 bit, 16 bit and 8 bit registers union
typedef union {
	 _R32BIT x;
	 _R16BIT32 l;
	 _R8BIT32 h;
} _INTR32;

/* This defines what the stack looks like after an ISR was running */
typedef struct
{
    uint32 gs, fs, es, ds;      /* pushed the segs last */
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    uint32 int_no, err_code;    /* our 'push byte #' and ecodes do this */
    uint32 eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
} _RegsStack32;


/****************************************
 *     Keyboard data types              *
 ****************************************/
enum KeyboardKeys {

	KeyboardKeyF9			=	0x01,
	KeyboardKeyF7			=	0x02,
	KeyboardKeyF5			=	0x03,
	KeyboardKeyF3			=	0x04,
	KeyboardKeyF1			=	0x05,
	KeyboardKeyF2			=	0x06,
	KeyboardKeyF12			=	0x07,
	KeyboardKeyMediaNext		=	0x08,
	KeyboardKeyF10			=	0x09,
	KeyboardKeyF8			=	0x0A,
	KeyboardKeyF6			=	0x0B,
	KeyboardKeyF4			=	0x0C,
	KeyboardKeyTab			=	0x0D,
	KeyboardKeyTilda			=	0x0E,
	KeyboardKeyMediaPrevious	=	0x0F,
	KeyboardKeyMediaStop		=	0x10,
	KeyboardKeyLeftAlt		=	0x11,
	KeyboardKeyLeftShift		=	0x12,
	KeyboardKeyMediaPause		=	0x13,
	KeyboardKeyLeftCtrl		=	0x14,
	KeyboardKeyQ			=	0x15,
	KeyboardKey1			=	0x16,
	KeyboardKeyMediaVolUp		=	0x17,
	KeyboardKeyMediaVolDown		=	0x18,
	KeyboardKeyMediaSelect		=	0x19,
	KeyboardKeyZ			=	0x1A,
	KeyboardKeyS			=	0x1B,
	KeyboardKeyA			=	0x1C,
	KeyboardKeyW			=	0x1D,
	KeyboardKey2			=	0x1E,
	KeyboardKeyLeftWin		=	0x1F,
	KeyboardKeyMediaEmail		=	0x20,
	KeyboardKeyC			=	0x21,
	KeyboardKeyX			=	0x22,
	KeyboardKeyD			=	0x23,
	KeyboardKeyE			=	0x24,
	KeyboardKey4			=	0x25,
	KeyboardKey3			=	0x26,
	KeyboardKeyRightWin		=	0x27,
	KeyboardKeyMediaCalculator	=	0x28,
	KeyboardKeySpace			=	0x29,
	KeyboardKeyV			=	0x2A,
	KeyboardKeyF			=	0x2B,
	KeyboardKeyT			=	0x2C,
	KeyboardKeyR			=	0x2D,
	KeyboardKey5			=	0x2E,
	KeyboardKeyMenu			=	0x2F,
	KeyboardKeyMediaComputer	=	0x30,
	KeyboardKeyN			=	0x31,
	KeyboardKeyB			=	0x32,
	KeyboardKeyH			=	0x33,
	KeyboardKeyG			=	0x34,
	KeyboardKeyY			=	0x35,
	KeyboardKey6			=	0x36,
	KeyboardKeyPower			=	0x37,
	KeyboardKeyMediaWebSearch	=	0x38,
	KeyboardKeyMediaWebHome		=	0x39,
	KeyboardKeyM			=	0x3A,
	KeyboardKeyJ			=	0x3B,
	KeyboardKeyU			=	0x3C,
	KeyboardKey7			=	0x3D,
	KeyboardKey8			=	0x3E,
	KeyboardKeySleep			=	0x3F,
	KeyboardKeyWake			=	0x40,
	KeyboardKeyComma			=	0x41,
	KeyboardKeyK			=	0x42,
	KeyboardKeyI			=	0x43,
	KeyboardKeyO			=	0x44,
	KeyboardKey0			=	0x45,
	KeyboardKey9			=	0x46,
	KeyboardKeyMediaWebBack		=	0x47,
	KeyboardKeyMediaWebForward	=	0x48,
	KeyboardKeyPeriod			=	0x49,
	KeyboardKeySlash			=	0x4A,
	KeyboardKeyL			=	0x4B,
	KeyboardKeySemicolon		=	0x4C,
	KeyboardKeyP			=	0x4D,
	KeyboardKeyDash			=	0x4E,
	KeyboardKeyMediaWebStop		=	0x4F,
	KeyboardKeyMediaWebRefresh	=	0x50,
	KeyboardKeyMediaWebFavorites	=	0x51,
	KeyboardKeyApostrophe		=	0x52,
	KeyboardKeyRightAlt		=	0x53,
	KeyboardKeyLeftBracket		=	0x54,
	KeyboardKeyEqual			=	0x55,
	KeyboardKeyPrintScreen		=	0x56,
	KeyboardKeyPause			=	0x57,
	KeyboardKeyCapsLock		=	0x58,
	KeyboardKeyRightShift		=	0x59,
	KeyboardKeyReturn			=	0x5A,
	KeyboardKeyRightBracket		=	0x5B,
	KeyboardKeyRightCtrl		=	0x5C,
	KeyboardKeyBackSlash		=	0x5D,
	KeyboardKeyInsert			=	0x5E,
	KeyboardKeyDelete			=	0x5F,
	KeyboardKeyHome			=	0x60,
	KeyboardKeyEnd			=	0x61,
	KeyboardKeyPageUp			=	0x62,
	KeyboardKeyPageDown		=	0x63,
	KeyboardKeyLeft			=	0x64,
	KeyboardKeyDown			=	0x65,
	KeyboardKeyBackspace		=	0x66,
	KeyboardKeyRight			=	0x67,
	KeyboardKeyUp			=	0x68,
	KeyboardKeyNumpad1		=	0x69,
	KeyboardKeyNumpadSlash		=	0x6A,
	KeyboardKeyNumpad4		=	0x6B,
	KeyboardKeyNumpad7		=	0x6C,
	KeyboardKeyNumpadEnter		=	0x6D,
	KeyboardKeyMediaMute		=	0x6E,
	KeyboardKeyNumpad0		=	0x70,
	KeyboardKeyNumpadColon		=	0x71,
	KeyboardKeyNumpad2		=	0x72,
	KeyboardKeyNumpad5		=	0x73,
	KeyboardKeyNumpad6		=	0x74,
	KeyboardKeyNumpad8		=	0x75,
	KeyboardKeyEscape			=	0x76,
	KeyboardKeyNumLock		=	0x77,
	KeyboardKeyF11			=	0x78,
	KeyboardKeyNumpadPlus		=	0x79,
	KeyboardKeyNumpad3		=	0x7A,
	KeyboardKeyNumpadMinus		=	0x7B,
	KeyboardKeyNumpadAsterisk	=	0x7C,
	KeyboardKeyNumpad9		=	0x7D,
	KeyboardKeyScrollLock		=	0x7E
};

typedef struct {
	char Character;
	uint8 Scancode;
} Key;

typedef struct {
	uint8 Pressed;
	char Character;
	uint8 Scancode;
} KeyEvent;

/****************************************
 *     Other data types                 *
 ****************************************/
typedef struct {
    int32 X, Y;
} Point;

typedef struct
{
    uint32 X, Y;
} UPoint;

typedef char* string;

#endif
