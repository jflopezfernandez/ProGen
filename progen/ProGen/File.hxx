#ifndef PROGEN_FILE_HXX_
#define PROGEN_FILE_HXX_

#ifndef WINDOWS_HEADER_INCLUDED
#define WINDOWS_HEADER_INCLUDED
#include <Windows.h>
#endif // WINDOWS_HEADER_INCLUDED

#ifndef STDLIB_FILESYSTEM_INCLUDED
#define STDLIB_FILESYSTEM_INCLUDED
#include <filesystem>
#endif // STDLIB_FILESYSTEM_INCLUDED

#ifndef STDLIB_FSTREAM_INCLUDED
#define STDLIB_FSTREAM_INCLUDED
#include <fstream>
#endif // STDLIB_FSTREAM_INCLUDED

#ifndef STDLIB_STRING_INCLUDED
#define STDLIB_STRING_INCLUDED
#include <string>
#endif // STDLIB_STRING_INCLUDED

#ifndef STDLIB_STRING_VIEW_INCLUDED
#define STDLIB_STRING_VIEW_INCLUDED
#include <string_view>
#endif //STDLIB_STRING_VIEW_INCLUDED

namespace FileIO {
	DWORD FileAttributes(const std::string& filename) noexcept;

	bool FileExists(const std::string& filename) noexcept;
} // End namespace FileIO

class File {
	std::string filename;

	std::string path;

	std::fstream stream;

public:
	File();

	File(const std::string& filename);

	File(const std::string_view& filename);

	void open(const std::ios::openmode& mode);

	void close();

	static bool exists(const std::string& filename) noexcept {
		if (FileIO::FileExists(filename)) {
			return true;
		}

		return false;
	}

	std::string name() const noexcept;

	std::string fullPathName() const noexcept;

	/** Function: std::fstream& handle()
	 *
	 *  Example Usage:
	 *
	 *  File outputFile;
	 *  outputFile.changeName("test-file.txt");
	 *  outputFile.open(std::ios::out);
	 *
	 *  for (auto i = 0; i < 10; i++) {
	 *  	for (auto j = 0; j < 10; j++) {
	 *		outputFile.handle() << j << ' ';
	 *	}
	 *  
	 *  outputFile.handle() << '\n';
	 *  
	 *  }
	 *
	 *  outputFile.handle() << '\n';
	 *  outputFile.close();
	 *
	 */

	std::fstream& handle();

	void changeName(const std::string& newFilename);

	void changePath(const std::string& newPath);

}; // End class File

#endif // PROGEN_FILE_HXX_
