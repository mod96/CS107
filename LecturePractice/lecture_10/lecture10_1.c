#include "inc.h"

int main(int argc, char *argv[])
{
				Fraction f = {1, 2};
				return f.numer;
}

/*
Steps
-Preprocessor (gcc -E)
	-Input: binky.c (C source code)
	-Output: binky.i (C source code)
	-Purpose: hndles #include, #defines
-Compiler (gcc -S)
	-Input: binky.i (C code)
	-Output: binky.s (Assembly code, text)
	-Purpose: Translate C to assembly
-Assembler (gcc -c)
	-Input: binky.s (Assembly)
	-Output: binky.o (Machine code, binary, "object file", 
										info: readelf -h ~.o / disassemble: dumpobj -d ~.o )
	-Purpose: 
-Linker (gcc [no flag])
	-Input: binky.o, winky.o, libdinky.a (multiple object files, libraries)
	-Output: binky (executable program)
	-Purpose: resolve symbols, set address layout


.o file vs executable
	: .o file has small addresses, undefined symbols

	: to see, >>nm ~.o

	: binky.o, winky.o, ... has only their own defined functions.
	If a function is not defined in there, it's Undefined. The Linker
	will connect each definition(function address).

Errors
-Preprocessor
	Not handle syntax errors in #define
	non-existent #include file
-Compiler
	syntax errors, undeclared variables
	all type checking
	prototype problem if no prototype
-Assembler
	None (as long as compiler generated good assembly)
-Linker
	Undefined reference to symbols
	WILL NOT detect prototype mismatch
			|_ ex. int a(int x, int y) vs a(int x)


*/

