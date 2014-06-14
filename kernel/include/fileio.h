/*
 * fileio.h
 *
 *  Created on: Aug 23, 2011
 *      Author: Tiberiu
 */

#ifndef FILEIO_H_
#define FILEIO_H_

#include <types.h>
#include <time.h>

#define MAX_FILENAME_LEN 256
#define MAX_MOUNTPOINTNAME_LEN 64

// Device routines, will read/write 'BlockSize' bytes per call
typedef uint32 (*DevReadRoutine)(uint32 offset, void* buffer);
typedef uint32 (*DevWriteRoutine)(uint32 offset, void* buffer);

enum FileFlags
{
	FileFile			= 0x1,
	FileDirectory		= 0x2,
	FileCharDevice		= 0x3,
	FileBlockDevice		= 0x4,
	FilePipe			= 0x5,
	FileSymbolLink		= 0x6,
	FileMountPoint		= 0x7,
	FileOwnerRead		= 0x8,
	FileOwnerWrite		= 0x10,
	FileOwnerExecute	= 0x20,
	FileGroupRead		= 0x40,
	FileGroupWrite		= 0x80,
	FileGroupExecute	= 0x100,
	FileOtherRead		= 0x200,
	FileOtherWrite		= 0x400,
	FileOtherExecute	= 0x800,
	FileHidden			= 0x1000,
};


typedef struct
{
	uint32 DeviceId;	// The VFS identifies the mounted device that uses this
	uint32 Id;			// The FS identifies files using this field
	char* Name;

	/*** Flags look like this:
	 *
	 *	bits 31 ... 13 |     12 | 11 10  9 | 8  7  6 | 5  4  3 | 2  1  0
	 *	    unassigned | Hidden |  x  w  r | x  w  r | x  w  r | file type (enum above)
	 *	                        |  others  |  group  |  owner  |
	 * Note: In windows FSs, the readonly and system attributes are set
	 * using permissions mask and owner id (0 = system) */
	uint32 Flags, OwnerId, GroupId;
	uint32 Size;

	// Useful for file systems
	void *BufStart, *BufPos, *BufEnd ;
	uint32 FsData[8];	// Can store info such as current cluster, etc

} FILE;


typedef struct _DirectoryEntry
{
	char Name[MAX_FILENAME_LEN];
	uint32 Flags, OwnerId, GroupId, Size;
	TimeSystem TimeCreated, TimeModified, TimeAccessed;

}  __attribute__((packed)) DirectoryEntry;


typedef struct {
	uint32 Id, FsId;
	char Name[MAX_MOUNTPOINTNAME_LEN];

	uint32 BlockSize;
	DevReadRoutine Read;
	DevWriteRoutine Write;

	uint32 FsData[8];
} MountPoint;


// File system routines
typedef uint32 			(*FsReadRoutine)	(MountPoint*, FILE*, uint32, uint32, uint8*);
typedef uint32 			(*FsWriteRoutine)	(MountPoint*, FILE*, uint32, uint32, uint8*);
typedef FILE* 			(*FsOpenRoutine)	(MountPoint*, FILE*, string);
typedef DirectoryEntry* (*FsTestRoutine)	(MountPoint*, string);	// Test if a file exists, and returns info
typedef FILE* 			(*FsCloseRoutine)	(MountPoint*, FILE*);
typedef DirectoryEntry* (*FsReadDirRoutine)	(MountPoint*, FILE*, uint32);

typedef uint32 			(*FsDetectRoutine) 	(MountPoint*);
typedef void 			(*FsMountRoutine) 	(MountPoint*);
typedef void 			(*FsUnmountRoutine) (MountPoint*, uint8 Forced); // If forced, the FS shouldn't try to write to device

// File system structure
typedef struct {
	uint32 Id;
	char Name[16];

	FsDetectRoutine Detect;			// Returns 0 if detection failed, something positive otherwise
	FsMountRoutine MountDevice; 	// Tells FS a device has to be mounted. This way, the FS can cache data for faster access
	FsUnmountRoutine UnmountDevice;	// Tells FS a device has been unmounted. This way, the FS can free cached data.

	FsOpenRoutine Open;
	FsCloseRoutine Close;
	FsReadRoutine Read;
	FsWriteRoutine Write;
	FsTestRoutine Test;				// See if file exists without having to open it
	FsReadDirRoutine ReadDirectory;
} FileSystem;


// Vfs routines
extern void			VfsInstall ();
extern void			VfsInstallFs (FileSystem* fs);
extern MountPoint* 	VfsMount (string devname, DevReadRoutine R, DevWriteRoutine W, uint32 bs);
extern void			VfsUnmount (uint32 dev_id);
extern FILE*		VfsOpen (FILE* file, string path);
extern DirectoryEntry* VfsTest (string path);
extern FILE*		VfsClose (FILE* file);
extern uint32		VfsRead (FILE* file, uint32 bsz, uint32 n, uint8* buffer);
extern uint32 		VfsWrite (FILE* file, uint32 bsz, uint32 n, uint8* buffer);
extern DirectoryEntry* VfsReadDirectory (FILE* handle, uint32 index);
extern MountPoint* 	VfsGetMountPoint (uint32 dev_id);

#endif /* FILEIO_H_ */
