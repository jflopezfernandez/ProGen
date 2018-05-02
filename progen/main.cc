
#ifndef WINDOWS_HEADER_INCLUDED
#define WINDOWS_HEADER_INCLUDED
#include <Windows.h>
#endif // WINDOWS_HEADER_INCLUDED

#ifndef STDLIB_CASSERT_INCLUDED
#define STDLIB_CASSERT_INCLUDED
#include <assert.h>
#endif // STDLIB_CASSERT_INCLUDED

#ifndef STDLIB_CSTDLIB_INCLUDED
#define STDLIB_CSTDLIB_INCLUDED
#include <stdlib.h>
#endif // STDLIB_CSTDLIB_INCLUDED

#ifndef STDLIB_TCHAR_H_INCLUDED
#define STDLIB_TCHAR_H_INCLUDED
#include <tchar.h>
#endif // STDLIB_TCHAR_H_INCLUDED

#ifndef STDLIB_STDIO_H_INCLUDED
#define STDLIB_STDIO_H_INCLUDED
#include <stdio.h>
#endif // STDLIB_STDIO_H_INCLUDED

#ifndef STDLIB_STRSAFE_H_INCLUDED
#define STDLIB_STRSAFE_H_INCLUDED
#include <strsafe.h>
#endif // STDLIB_STRSAFE_H_INCLUDED

#ifndef STDLIB_WCHAR_H_INCLUDED
#define STDLIB_WCHAR_H_INCLUDED
#include <wchar.h>
#endif // STDLIB_WCHAR_H_INCLUDED

#ifndef STDLIB_IOSTREAM_INCLUDED
#define STDLIB_IOSTREAM_INCLUDED
#include <iostream>
#endif // STDLIB_IOSTREAM_INCLUDED

#ifndef PROGEN_FILE_HXX_
#include <ProGen/File.hxx>
#endif // PROGEN_FILE_HXX_

void DisplayErrorBox(LPCTSTR function);


int _tmain(int argc, TCHAR *argv[])
{
	WIN32_FIND_DATA findData;
	LARGE_INTEGER fileSize;
	TCHAR directory[MAX_PATH];
	std::size_t argLength;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD error = 0;

	// If the directory is not specified as a command-line argument, print usage

	if (argc != 2) {
		_tprintf(TEXT("\nUsage: %s <directory name>\n"), argv[0]);

		return EXIT_FAILURE;
	}

	// Check that the input path plus 3 is not longer than MAX_PATH. Three characters
	// are for the "\*" plus NULL appended below.

	StringCchLength(argv[1], MAX_PATH, &argLength);

	if (argLength > (MAX_PATH - 3)) {
		_tprintf(TEXT("\nDirectory path is too long.\n"));

		return EXIT_FAILURE;
	}

	_tprintf(TEXT("\nTarget directory is %s\n\n"), argv[1]);

	// Prepare string for use with FindFile functions. First, copy the string to a buffer
	// then append '\*' to the directory name.

	StringCchCopy(directory, MAX_PATH, argv[1]);
	StringCchCat(directory, MAX_PATH, TEXT("\\*"));

	// Find the first file in the directory

	hFind = FindFirstFile(directory, &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		DisplayErrorBox(TEXT("FindFirstFile"));

		return error;
	}

	// List all the files in the directory with some info about them.

	do {
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			_tprintf(TEXT("\t%s\t<DIR>\n"), findData.cFileName);
		} else {
			fileSize.LowPart = findData.nFileSizeLow;
			fileSize.HighPart = findData.nFileSizeHigh;

			_tprintf(TEXT("\t%s\t%ld bytes\n"), findData.cFileName, fileSize.QuadPart);
		}
	} while (FindNextFile(hFind, &findData));

	error = GetLastError();

	if (error != ERROR_NO_MORE_FILES) {
		DisplayErrorBox(TEXT("FindFirstFile"));
	}

	FindClose(hFind);
	return error;
}

void DisplayErrorBox(LPCTSTR function) {
	// Retreive the system error message for the last error code
	LPVOID messageBuffer;
	LPVOID displayBuffer;

	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &messageBuffer,
		0, NULL
	);

	// Display the error message and clean up

	displayBuffer = (LPVOID) LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR) messageBuffer) + lstrlen((LPCTSTR) function) + 40) * sizeof(TCHAR));

	StringCchPrintf((LPTSTR) displayBuffer, LocalSize(displayBuffer) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), function, dw, messageBuffer);

	MessageBox(NULL, (LPCTSTR) displayBuffer, TEXT("Error"), MB_OK);

	LocalFree(messageBuffer);
	LocalFree(displayBuffer);
}
