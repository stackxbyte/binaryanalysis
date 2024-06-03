ELF binaries really consist of only four types of components: an executable header, a series of (optional) program headers, a number of sections, and a series of (optional) section headers, one per section

-- HEADER ORDER --
------------------
Executable Header
Program Header
Section
Section Header 
------------------


# Executable Header
-------------------

Every ELF file starts with an executable header, which is just a structured series of bytes telling you that it’s an ELF file, what kind of ELF file it is, and where in the file to find all the other contents.

ELF64_Ehdr in /usr/include/elf.h

typedef struct {
unsigned char e_ident[16]; 	/* Magic number and other info	     /*
uint16_t    e_type;		    /* Object file type		             /*
uint32_t    e_version;		/* Object file version		         /*
uint64_t    e_entry;		/* Entry point virtual address	     /*
uint64_t    e_phoff;		/* Program header table file offset  /*
uint64_t    e_shoff;		/* Section header table file offset  /*
uint32_t    e_flags;		/* Processor-specific flags	         /*
uint16_t    e_ehsize;		/* ELF header size in bytes	         /*
uint16_t    e_phentsize;	/* Program header table entry size   /*
uint16_t    e_phnum;		/* Program header table entry count  /*
uint16_t    e_shentsize;	/* Section header table entry size   /*
uint16_t    e_shnum;		/* Section header table entry count  /*
uint16_t    e_shstrndx;		/* Section header string table index /*
} Elf64_Ehdr;


# e_ident Array
----------------
The executable header (and the ELF file) starts with a 16-byte array called e_ident. The e_ident array always starts with a 4-byte “magic value” identifying the file as an ELF binary. The magic value consists of the hexadecimal number 0x7f, followed by the ASCII character codes for the letters E, L, and F

The indexes for these bytes (indexes 4 through 15 in the e_ident array) are symbolically referred to as EI_CLASS, EI_DATA, EI_VERSION, EI_OSABI, EI_ABIVERSION, and EI_PAD, respectively

EI_PAD field actually contains multiple bytes, namely, indexes 9 through 15 in e_ident. All of these bytes are currently designated as padding; they are reserved for possible future use but currently set to zero

EI_CLASS byte denotes what the ELF specification refers to as the binary’s “class.” The byte is set to the constant ELFCLASS32 (which is equal to 1), while in the latter case, it’s set to ELFCLASS64 (equal to 2).

The EI_DATA byte indicates the endianness of the binary. A value of ELFDATA2LSB (equal to 1) indicates little-endian, while ELFDATA2MSB (equal to 2) means big-endian

EI_VERSION, indicates the version of the ELF specification used when creating the binary. Currently, the only valid value is EV_CURRENT, which is defined to be equal to 1

EI_OSABI and EI_ABIVERSION bytes denote information regarding the application binary interface (ABI) and operating system (OS) for which the binary was compiled. If the EI_OSABI byte is set to nonzero, it means that some ABI- or OS-specific extensions are used in the ELF file. The default value of zero indicates that the binary targets the UNIX System V ABI. The EI_ABIVERSION byte denotes the specific version of the ABI You’ll usually see this set to zero because it’s not necessary to specify any version information when the default EI_OSABI is used.

ELF Header:
Magic: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
Class:					            ELF64
Data:					            2's complement, little endian
Version:				            1 (current)
OS/ABI:					            UNIX - System V
ABI Version:				        0
Type:					            EXEC (Executable file)
Machine:				            Advanced Micro Devices X86-64
Version:				            0x1
Entry point address:			    0x400430
Start of program headers:		    64 (bytes into file)
Start of section headers:		    6632 (bytes into file)
Flags:					            0x0
Size of this header:			    64 (bytes)
Size of program headers:		    56 (bytes)
Number of program headers:		    9
Size of section headers:		    64 (bytes)
Number of section headers:		    31
Section header string table index: 	28


