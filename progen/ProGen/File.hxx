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

	std::fstream handle;

public:
	File() = delete;

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
}; // End class File

#endif // PROGEN_FILE_HXX_
