#ifndef __TIME__H
#define __TIME__H

#include <types.h>

// User friendly time structure
struct _Time
{
	int32 Year;
	uint8 Month, WeekDay, Day; 	// Day starts monday
	uint8 Hour, Minute, Second;
	uint16 Milisecond;
} __attribute__((packed));

// System time structure
struct  _TimeSystem {
	uint32 Date, Time;
} __attribute__((packed));

typedef struct _Time Time;
typedef struct _TimeSystem TimeSystem;


extern TimeSystem	ConvertTimeToTimeSystem (Time t);
extern Time			ConvertTimeSystemToTime (TimeSystem InternalTime);
extern uint16		TimeCalculateWeekday (Time t);

extern TimeSystem	TimeGetInternalTime();
extern uint32		TimeGetInternalFrequency ();

extern void	TimeSetInternalTime(TimeSystem t);
extern void	TimeSetInternalFrequency (uint32 f);

extern void TimerStart (uint32 ms);
extern uint8 TimerIsDone ();

#endif
