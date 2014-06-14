/*
 * multiboot.h
 *
 *  Created on: Aug 17, 2011
 *      Author: Tiberiu
*/

#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

#include <types.h>

// Flags to be set in the 'flags' member of the multiboot info structure.
#define MultibootInfo_MEMORY                   0x00000001		// is there basic lower/upper memory information?
#define MultibootInfo_BOOTDEV                  0x00000002		// is there a boot device set?
#define MultibootInfo_CMDLINE                  0x00000004		// is the command-line defined?
#define MultibootInfo_MODS                     0x00000008		// are there modules to do something with?

// These next two are mutually exclusive
#define MultibootInfo_AOUT_SYMS                0x00000010		// is there a symbol table loaded?
#define MultibootInfo_ELF_SHDR                 0X00000020		// is there an ELF section header table?


#define MultibootInfo_MEM_MAP                  0x00000040		// is there a full memory map?
#define MultibootInfo_DRIVE_INFO               0x00000080		// Is there drive info?
#define MultibootInfo_CONFIG_TABLE             0x00000100		// Is there a config table?
#define MultibootInfo_BOOT_LOADER_NAME         0x00000200		// Is there a boot loader name?
#define MultibootInfo_APM_TABLE                0x00000400		// Is there a APM table?
#define MultibootInfo_VIDEO_INFO               0x00000800		// Is there video information?


// The symbol table for a.out.
typedef struct
{
	uint32 TableSize;
	uint32 StrSize;
	uint32 Address;
	uint32 Reserved;
} MultibootAoutSymbolTable;


// The section header table for ELF.
typedef struct
{
	uint32 Number;
	uint32 Size;
	uint32 Address;
	uint32 Shndx;
} MultibootElfSectionHeaderTable;


typedef struct
{
	uint32 Flags;					// Multiboot info version number

	uint32 MemoryLower;				// Available memory from BIOS
	uint32 MemoryUpper;

	uint32 BootDevice;				// "root" partition

	uint32 CommandLine;				// Kernel command line

	uint32 ModulesCount;			// Boot-Module list
	uint32 ModulesAddress;

	union
	{
		MultibootAoutSymbolTable AoutSymbols;
		MultibootElfSectionHeaderTable ElfSectionHeaderTable;
	} Symbols;

	uint32 MemoryMapLength;			// Memory Mapping buffer
	uint32 MemoryMapAddress;

	uint32 DrivesLength;			// Drive Info buffer
	uint32 DrivesAddress;

	uint32 ConfigurationTable;		// ROM configuration table

	uint32 BootLoaderName;			// Boot Loader Name

	uint32 ApmTable;				// APM table

	uint32 VbeControlInfo;	// Video
	uint32 VbeModeInfo;
	uint16 VbeMode;
	uint16 VbeInterfaceSegment;
	uint16 VbeInterfaceOffset;
	uint16 VbeInterfaceLength;
} MultibootInfo;


typedef struct
{
	uint32 Size;
	uint64 Address;
	uint64 Length;

	#define MULTIBOOT_MEMORY_AVAILABLE              1
	#define MULTIBOOT_MEMORY_RESERVED               2

	uint32 Type;
} __attribute__((packed)) MultibootMemoryMapEntry;

typedef struct
{
	// the memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive
	uint32 ModuleStart;
	uint32 ModuleEnd;

	// Module command line
	uint32 CommandLine;

	// padding to take it to 16 bytes (must be zero)
	uint32 _Padding;
} MultibootModule;


#endif
