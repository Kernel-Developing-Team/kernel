/*
 * tasking.h
 *
 *  Created on: Sep 8, 2011
 *      Author: Tiberiu
 */

#ifndef TASKING_H_
#define TASKING_H_

#include <types.h>
#include <memory-add.h>

typedef struct _Task {
	uint32 Pid;
	uint32 Eip, Esp, Ebp;
	PageDirectory* Pd;
	uint32 StackLowerBase;
	uint32 StackUpperBase;
	uint8 Initialized;
	struct _Task* Next;
} Task;

extern void TaskInitialize();
extern void TaskSwitch ();
extern void TaskCreate (void (*func)());

#endif /* TASKING_H_ */
