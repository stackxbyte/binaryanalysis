## Executable Header

Every ELF file starts with an executable header, which is just a structured series of bytes telling you that it’s an ELF file, what kind of ELF file it is, and where in the file to find all the other contents.

![plot](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header)

ELF64_Ehdr in /usr/include/elf.h

```
typedef struct {
unsigned char e_ident[16]; 	/* Magic number and other info	    /*
uint16_t    e_type;		/* Object file type		            /*
uint16_t    e_machine;  /* Architecture                     /*
uint32_t    e_version;	/* Object file version		        /*
uint64_t    e_entry;	/* Entry point virtual address	    /*
uint64_t    e_phoff;	/* Program header table file offset /*
uint64_t    e_shoff;	/* Section header table file offset /*
uint32_t    e_flags;	/* Processor-specific flags	        /*
uint16_t    e_ehsize;    /* ELF header size in bytes	        /*
uint16_t    e_phentsize;    /* Program header table entry size  /*
uint16_t    e_phnum;	/* Program header table entry count /*
uint16_t    e_shentsize;	/* Section header table entry size  /*
uint16_t    e_shnum;	/* Section header table entry count /*
uint16_t    e_shstrndx;     /* Section header string table index/*
} Elf64_Ehdr;
```

## e_ident Array

The executable header (and the ELF file) starts with a 16-byte array called e_ident. The e_ident array always starts with a 4-byte “magic value” identifying the file as an ELF binary. The magic value consists of the hexadecimal number 0x7f, followed by the ASCII character codes for the letters E, L, and F

The indexes for these bytes (indexes 4 through 15 in the e_ident array) are symbolically referred to as EI_CLASS, EI_DATA, EI_VERSION, EI_OSABI, EI_ABIVERSION, and EI_PAD, respectively

**EI_PAD** field actually contains multiple bytes, namely, indexes 9 through 15 in e_ident. All of these bytes are currently designated as padding; they are reserved for possible future use but currently set to zero

**EI_CLASS** byte denotes what the ELF specification refers to as the binary’s “class.” The byte is set to the constant ELFCLASS32 (which is equal to 1), while in the latter case, it’s set to ELFCLASS64 (equal to 2).

**EI_DATA** byte indicates the endianness of the binary. A value of ELFDATA2LSB (equal to 1) indicates little-endian, while ELFDATA2MSB (equal to 2) means big-endian

**EI_VERSION**, indicates the version of the ELF specification used when creating the binary. Currently, the only valid value is EV_CURRENT, which is defined to be equal to 1

**EI_OSABI** and **EI_ABIVERSION** bytes denote information regarding the application binary interface (ABI) and operating system (OS) for which the binary was compiled. If the EI_OSABI byte is set to nonzero, it means that some ABI- or OS-specific extensions are used in the ELF file. The default value of zero indicates that the binary targets the UNIX System V ABI. The EI_ABIVERSION byte denotes the specific version of the ABI You’ll usually see this set to zero because it’s not necessary to specify any version information when the default EI_OSABI is used.


***Elf header of an example binary using elfread***

```
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
```


## e_type, e_machine, and e_version Fields

**e_type**, specifies the type of the binary. The most common values you’ll encounter here are ***ET_REL (indicating a relocatable object file), ET_EXEC (an executable binary), and ET_DYN (a dynamic library, also called a shared object file)***

**e_machine** field, which denotes the architecture that the binary is intended to run on the value usually be set to EM_X86_64 since you will mostly be working on 64-bit x86 binaries. Other values you’re likely to encounter include EM_386 (32-bit x86) and EM_ARM (for ARM binaries).

**e_version** field serves the same role as the EI_VERSION byte in the e_ident array. it indicates the version of the ELF specification that was used when creating the binary. As this field is 32 bits wide, the only possible value is 1 (EV_CURRENT) to indicate version 1 of the specification.

## e_entry Field

**e_entry** field denotes the entry point of the binary; this is the virtual address at which execution should start. This is where the interpreter (typically ld-linux.so) will transfer control after it finishes loading the binary into virtual memory

## e_phoff and e_shoff Fields

The program header and section header tables need not be located at any particular offset in the binary file. The only data structure that can be assumed to be at a fixed location in an ELF binary is the executable header, which is always at the beginning.

   How can you know where to find the program headers and section headers? For this, the executable header contains two dedicated fields, called e_phoff and e_shoff, that indicate the file offsets to the beginning of the program header table and the section header table. The offsets can also be set to zero to indicate that the file does not contain a program header or section header table.

## The e_flags Field

**e_flags** field provides room for flags specific to the architecture for
which the binary is compiled e_flags field to indicate additional details about the interface they expect (file format conventions, stack organization, and so on). For x86 binaries, e_flags is typically set to zero and thus not of interest.

## The e_ehsize Field

**e_ehsize** field specifies the size of the executable header, in bytes. For 64-bit x86 binaries the executable header size will be 64 bytes and 52 bytes for 32-bit x86 binaries.

## The e_*entsize and e_*num Fields

**e_phoff** and **e_shoff** fields point to the file offsets where the program header and section header tables begin. But for the linker or loader (or another program handling an ELF binary) to actually traverse these tables, additional information is needed. Specifically, they need to know the size of the individual program or section headers in the tables, as well as the number of headers in each table. This information is provided by the e_phentsize and e_phnum fields for the program header table and by the e_shentsize and e_shnum fields for the section header table

## The e_shstrndx Field

**e_shstrndx** field contains the index (in the section header table) of the header associated with a special string table section, called .shstrtab. This is a dedicated section that contains a table of null-terminated ASCII strings, which store the names of all the sections in the binary

