
#ifndef STDLIB_CSTDLIB_INCLUDED
#define STDLIB_CSTDLIB_INCLUDED
#include <stdlib.h>
#endif // STDLIB_CSTDLIB_INCLUDED

#ifndef STDLIB_IOSTREAM_INCLUDED
#define STDLIB_IOSTREAM_INCLUDED
#include <iostream>
#endif // STDLIB_IOSTREAM_INCLUDED

#ifndef PROGEN_FILE_HXX_
#include <ProGen/File.hxx>
#endif // PROGEN_FILE_HXX_

void ValidateCmdLineParameters(const int argc, char *argv[]) {
	if (argc == 1) {
		// TODO: Let user know or something

		exit(EXIT_FAILURE);
	}

	// TODO: Validate argv somehow
}

int main(int argc, char *argv[])
{
	ValidateCmdLineParameters(argc, argv);

	if (File::exists(argv[1])) {
		std::cout << "File exists.\n";
	} else {
		std::cout << "File does not exist.\n";
	}

	return EXIT_SUCCESS;
}