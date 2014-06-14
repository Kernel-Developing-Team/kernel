/*
 * storage.h
 *
 *  Created on: Aug 23, 2011
 *      Author: Tiberiu
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include <types.h>

extern void ConvertLbaToChs(uint32 SectorsPerTrack, uint32 lba, uint32 *cyl, uint32 *head, uint32 *sector);

#endif /* STORAGE_H_ */
