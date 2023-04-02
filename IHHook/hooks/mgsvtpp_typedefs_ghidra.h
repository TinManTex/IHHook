#pragma once
//Not generated (so dont delete and expect it to reappear)
//for ghidra builtin data type names > c++
//mostly just copied from what ghidra put in a 'export C header'
//shouldn't have to add much to this, 
//for more complex structs add to or include from mgsvtpp_func_typedefs_manual

typedef unsigned char		byte;
typedef unsigned int		dword;
typedef long long			longlong;
typedef unsigned long long  qword;
typedef unsigned char		uchar;
typedef unsigned int		uint;
typedef unsigned long long  uint16;
typedef unsigned long		ulong;
typedef unsigned long long  ulonglong;
typedef unsigned short		ushort;
//typedef short			wchar_t;//tex TODO:
typedef unsigned short		word;

//tex if you're being lazy, just want to thrash out a hook where you arent actually using the unknown params.
typedef unsigned char		undefined;
typedef unsigned char		undefined1;
typedef unsigned short		undefined2;
typedef unsigned int		undefined3;
typedef unsigned int		undefined4;
typedef unsigned long long	undefined6;
typedef unsigned long long	undefined8;