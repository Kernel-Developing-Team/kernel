/*
 * settings.h
 *
 *  Created on: Aug 16, 2011
 *      Author: Tiberiu
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

// OS info
#define OS_STRING "lux"
#define OS_VERSION "0.1 [pre-Alpha]"
#define OS_BUILD_DATE __DATE__
#define OS_BUILD_TIME __TIME__

#include <version.h>

// Logger
#define LOGGER_ALLOW 1
#define LOGGER_ALLOW_ERROR 1
#define LOGGER_ALLOW_PANIC 1


// Clock
#define PIT_FREQUENCY 100

// Console
#define CONSOLE_MAX_PARAMS 32
#define CONSOLE_DEFAULT_COLOR 0x7

// Memory manager
#define KERNEL_HEAP_START 0xC0000000
#define KERNEL_HEAP_INITIAL_SIZE 0x100000
#define KERNEL_HEAP_END (KERNEL_HEAP_START + KERNEL_HEAP_INITIAL_SIZE)


#endif /* SETTINGS_H_ */
