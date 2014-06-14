#ifndef __STDLIB__H
#define __STDLIB__H

#include <types.h>

#define IsDigit(c) 		(c >= '0' && c <= '9')
#define IsHexDigit(c) 	( (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') )
#define IsUpper(c) 		(c >= 'A' && c <= 'Z')
#define IsLower(c) 		(c >= 'a' && c <= 'z')

#define IsAlpha(c) 		(IsLower(c) || IsUpper(c))
#define IsAlphaNum(c) 	(IsAlpha(c) || IsDigit(c))

#define ToLower(c) ((IsUpper(c)) ? (c - 'A' + 'a') : c)
#define ToUpper(c) ((IsLower(c)) ? (c - 'a' + 'A') : c)

#define Max(a,b) ((a > b) ? (a) : (b))
#define Min(a,b) ((a < b) ? (a) : (b))
#define Abs(a)   ((a < 0) ? (a * -1) : (a))

/***************************************************
 * String operations: len, cmp, cpy                *
 ***************************************************/
extern uint32 strlen (string s);
extern int32  strcmp (string a, string b);
extern int32  strncmp (string a, string b, uint32 n);
extern int32  strcasecmp (string a, string b);
extern string strcpy (string s1, const string s2);
extern char*  strchr (string s, int c);
extern char*  strrchr (string s, int c);

/***************************************************
 * Number operations: len                          *
 ***************************************************/
extern uint32 numlen  (int32 number, int32 base);
extern uint32 unumlen (uint32 number, int32 base);

/***************************************************
 * Memory operations: cpy, cmp, set                *
 ***************************************************/
void* memcpy (void *dest, const void *src, uint32 count);
int32 memcmp (const void *s1, const void *s2, uint32 count);
void* memset (void *dest, uint8 val, uint32 count);

/***************************************************
 * Conversion operations: num-str/str-num          *
 ***************************************************/
extern int32 	ConvertIntToString 		(string buffer, int32 number, int32 base);
extern uint32 	ConvertUIntToString 	(string buffer, uint32 number, int32 base);
extern int32 	ConvertStringToInt 		(string buffer);
extern uint32	ConvertStringToUInt 	(string buffer);
extern uint32 	ConvertStringToIntHex 	(string buffer);


#endif
