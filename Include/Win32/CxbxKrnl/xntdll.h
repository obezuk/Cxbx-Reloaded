// ******************************************************************
// *
// *    .,-:::::    .,::      .::::::::.    .,::      .:
// *  ,;;;'````'    `;;;,  .,;;  ;;;'';;'   `;;;,  .,;; 
// *  [[[             '[[,,[['   [[[__[[\.    '[[,,[['  
// *  $$$              Y$$$P     $$""""Y$$     Y$$$P    
// *  `88bo,__,o,    oP"``"Yo,  _88o,,od8P   oP"``"Yo,  
// *    "YUMMMMMP",m"       "Mm,""YUMMMP" ,m"       "Mm,
// *
// *   Cxbx->Win32->CxbxKrnl->xntdll.h
// *
// *  This file is part of the Cxbx project.
// *
// *  Cxbx and Cxbe are free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef XNTDLL_H
#define XNTDLL_H

#if defined(__cplusplus)
extern "C"
{
#endif

// ******************************************************************
// * dll import/export
// ******************************************************************
#define DECLSPEC_IMPORT __declspec(dllimport)
#define DECLSPEC_EXPORT __declspec(dllexport)

// ******************************************************************
// * cxbx_krnl exports, others import
// ******************************************************************
#define NTSYSAPI     DECLSPEC_IMPORT

// ******************************************************************
// * CONST
// ******************************************************************
#define CONST               const

// ******************************************************************
// * Basic types
// ******************************************************************
typedef char                CHAR;
typedef short               SHORT;
typedef long                LONG;
typedef unsigned char       UCHAR;
typedef unsigned char       BYTE;
typedef unsigned char       BOOLEAN;
typedef unsigned short      USHORT;
typedef	unsigned short		WORD;
typedef unsigned long       ULONG;
typedef	unsigned long       DWORD;
typedef unsigned long       SIZE_T, *PSIZE_T;
typedef unsigned long       ACCESS_MASK;
typedef unsigned long       PHYSICAL_ADDRESS;
typedef long                INT_PTR;

// ******************************************************************
// * Pointer types
// ******************************************************************
typedef CHAR               *PCHAR;
typedef CHAR               *PCSZ;
typedef BYTE               *PBYTE;
typedef BOOLEAN            *PBOOLEAN;
typedef UCHAR              *PUCHAR;
typedef USHORT             *PUSHORT;
typedef ULONG              *PULONG;
typedef ULONG              *ULONG_PTR;
typedef ACCESS_MASK        *PACCESS_MASK;
typedef LONG               *LONG_PTR;
typedef INT_PTR            *PINT_PTR;
typedef void                VOID;
typedef VOID               *PVOID;
typedef void               *HANDLE;
typedef HANDLE             *PHANDLE;
typedef wchar_t             WCHAR, *PWCHAR;
typedef WCHAR              *LPWCH, *PWCH;
typedef CONST WCHAR        *LPCWCH, *PCWCH;
typedef WCHAR              *NWPSTR;
typedef WCHAR              *LPWSTR, *PWSTR;
typedef CONST WCHAR        *LPCWSTR, *PCWSTR;

// ******************************************************************
// * NTSTATUS
// ******************************************************************
typedef long                            NTSTATUS;
typedef unsigned __int64                ULONGLONG;

#define NT_SUCCESS(Status)              ((NTSTATUS) (Status) >= 0)

// ******************************************************************
// * calling conventions
// ******************************************************************
#define NTAPI               __stdcall
#define CDECL               __cdecl
#define INLINE              __inline
#define DECLSPEC_NORETURN   __declspec(noreturn)

// ******************************************************************
// * documentation purposes only
// ******************************************************************
#define EXPORTNUM(a)
#define UNALIGNED
#define OPTIONAL
#define IN
#define OUT

// ******************************************************************
// * LDT_ENTRY
// ******************************************************************
typedef struct _LDT_ENTRY
{
    WORD    LimitLow;
    WORD    BaseLow;

    union
    {
        struct
        {
            BYTE    BaseMid;
            BYTE    Flags1;     // Declare as bytes to avoid alignment
            BYTE    Flags2;     // Problems.
            BYTE    BaseHi;
        }
        Bytes;

        struct
        {
            DWORD   BaseMid : 8;
            DWORD   Type : 5;
            DWORD   Dpl : 2;
            DWORD   Pres : 1;
            DWORD   LimitHi : 4;
            DWORD   Sys : 1;
            DWORD   Reserved_0 : 1;
            DWORD   Default_Big : 1;
            DWORD   Granularity : 1;
            DWORD   BaseHi : 8;
        }
        Bits;

    }
    HighWord;
}
LDT_ENTRY, *PLDT_ENTRY;

// ******************************************************************
// * NtSetLdtEntries
// ******************************************************************
NTSYSAPI NTSTATUS NTAPI NtSetLdtEntries
(
    IN USHORT       Selector1,
    IN LDT_ENTRY    Descriptor1,
    IN USHORT       Selector2,
    IN LDT_ENTRY    Descriptor2
);

// ******************************************************************
// * Valid values for the Attributes field
// ******************************************************************
#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_VALID_ATTRIBUTES    0x000003F2L

// ******************************************************************
// * UNICODE_STRING
// ******************************************************************
typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
#ifdef MIDL_PASS
    [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
#else // MIDL_PASS
    PWSTR  Buffer;
#endif // MIDL_PASS
}
UNICODE_STRING, *PUNICODE_STRING;

typedef const UNICODE_STRING *PCUNICODE_STRING;

#define UNICODE_NULL ((WCHAR)0) // winnt

// ******************************************************************
// * OBJECT_ATTRIBUTES
// ******************************************************************
typedef struct _OBJECT_ATTRIBUTES
{
    ULONG           Length;
    HANDLE          RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG           Attributes;
    PVOID           SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID           SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
}
OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

// ******************************************************************
// * InitializeObjectAttributes
// * 
// * VOID
// * InitializeObjectAttributes(
// *     OUT POBJECT_ATTRIBUTES p,
// *     IN PUNICODE_STRING n,
// *     IN ULONG a,
// *     IN HANDLE r,
// *     IN PSECURITY_DESCRIPTOR s
// *     )
// * 
// ******************************************************************
#define InitializeObjectAttributes( p, n, a, r, s )     \
{                                                       \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
}

// ******************************************************************
// * IO_STATUS_BLOCK
// ******************************************************************
typedef struct _IO_STATUS_BLOCK
{
    union
    {
        NTSTATUS Status;
        PVOID    Pointer;
    };

    ULONG_PTR Information;
}
IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

// ******************************************************************
// * NtSetLdtEntries
// ******************************************************************
NTSYSAPI NTSTATUS NTAPI ZwOpenFile
(
    OUT PHANDLE             FileHandle,
    IN  ACCESS_MASK         DesiredAccess,
    IN  POBJECT_ATTRIBUTES  ObjectAttributes,
    OUT PIO_STATUS_BLOCK    IoStatusBlock,
    IN  ULONG               ShareAccess,
    IN  ULONG               OpenOptions
);

#if defined(__cplusplus)
}
#endif

#endif