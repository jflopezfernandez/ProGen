
#ifndef WINDOWS_HEADER_INCLUDED
#define WINDOWS_HEADER_INCLUDED
#include <Windows.h>
#endif // WINDOWS_HEADER_INCLUDED

#ifndef STDLIB_IOSTREAM_INCLUDED
#define STDLIB_IOSTREAM_INCLUDED
#include <iostream>
#endif // STDLIB_IOSTREAM_INCLUDED

#ifndef PROGEN_FILE_HXX_
#include <ProGen/File.hxx>
#endif // PROGEN_FILE_HXX_


int main(int argc, char *argv[])
{
	if (argc == 1) {
		return EXIT_FAILURE;
	}

	const auto fileAttributes = GetFileAttributes(argv[1]);
}