#ifndef __CTYPE_H
#define __CTYPE_H

extern unsigned char _ctype[];

#define _CTYPE_ISCONTROL    0x01  // 0000 0001
#define _CTYPE_ISSPACE      0x02  // 0000 0010
#define _CTYPE_ISBLANK      0x04  // 0000 0100 etc.
#define _CTYPE_ISPUNCT      0x08
#define _CTYPE_ISDIGIT      0x10
#define _CTYPE_ISHEX        0x20
#define _CTYPE_ISUPPER        0x40
#define _CTYPE_ISLOWER        0x80

#define isalnum(c) (_ctype[(int)c+1] & (_CTYPE_ISLOWER | _CTYPE_ISUPPER | _CTYPE_ISDIGIT))
#define isalpha(c) (_ctype[(int)c+1] & (_CTYPE_ISLOWER | _CTYPE_ISUPPER))
#define isblank(c) (_ctype[(int)c+1] & (_CTYPE_ISBLANK))
#define iscntrl(c) (_ctype[(int)c+1] & (_CTYPE_ISCONTROL))
#define isdigit(c) (_ctype[(int)c+1] & (_CTYPE_ISDIGIT))
#define isgraph(c) (_ctype[(int)c+1] & (_CTYPE_ISLOWER | _CTYPE_ISUPPER | _CTYPE_ISDIGIT | _CTYPE_ISPUNCT))
#define islower(c) (_ctype[(int)c+1] & (_CTYPE_ISLOWER))
#define isprint(c) (_ctype[(int)c+1] & (_CTYPE_ISLOWER | _CTYPE_ISUPPER | _CTYPE_ISDIGIT | _CTYPE_ISPUNCT | _CTYPE_ISBLANK))
#define ispunct(c) (_ctype[(int)c+1] & (_CTYPE_ISPUNCT))
#define isspace(c) (_ctype[(int)c+1] & (_CTYPE_ISSPACE))
#define isupper(c) (_ctype[(int)c+1] & (_CTYPE_ISUPPER))
#define isxdigit(c) (_ctype[(int)c+1] & (_CTYPE_ISHEX))

extern int toupper(int c);
extern int tolower(int c);

#endif