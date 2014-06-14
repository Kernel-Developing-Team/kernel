/*
 * array.h
 *
 *  Created on: Sep 3, 2011
 *      Author: Tiberiu
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <types.h>

/*******************************************
 * Dynamically expanding array             *
 *******************************************/
typedef struct {
	//   You can cast the Data to any type of array
	// because it contains the actual data, not pointers
	void* Data;
	uint32 ElemSize;
	uint32 Size;
	uint32 Allocated;
} DynamicArray;

extern void DynamicArrayCreate (uint32 ElemSize, DynamicArray* arr);
extern void DynamicArrayPush (void* item, DynamicArray* arr);
extern void DynamicArrayPop (DynamicArray* arr);
extern void DynamicArrayInsert (void* item, uint32 index, DynamicArray* arr);
extern void DynamicArrayRemove (uint32 index, DynamicArray* arr);
extern void DynamicArraySwap (uint32 a, uint32 b, DynamicArray* arr);
extern void DynamicArrayDispose (DynamicArray* arr);


/*******************************************
 * Ordered array                           *
 *******************************************/
typedef int (*ComparePredicate) (uint32, uint32);
typedef struct {
	uint32* Data;
	uint32 Size;
	uint32 SizeLimit;
	ComparePredicate Compare;
} OrderedArray;

extern OrderedArray OrderedArrayCreate 		(uint32 maxSize, ComparePredicate p);
extern OrderedArray OrderedArrayPlace 		(uint32 addr, uint32 maxSize, ComparePredicate p);
extern void 		OrderedArrayDispose 	(OrderedArray* arr);
extern uint32 		OrderedArraySearch 		(uint32 key, OrderedArray* arr, ComparePredicate predicate);
extern void 		OrderedArrayInsert 		(uint32 item, OrderedArray* arr);
extern uint32 		OrderedArrayLookup 		(uint32 index, OrderedArray* arr);
extern void 		OrderedArrayDeleteIndex (uint32 index, OrderedArray* arr);


#endif /* ARRAY_H_ */
