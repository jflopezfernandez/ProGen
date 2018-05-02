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

	struct NewFileDefaultConfiguration {
	private:
		DWORD defaultAccess_ = GENERIC_READ | GENERIC_WRITE;
		DWORD defaultShareMode_ = FILE_SHARE_READ | FILE_SHARE_DELETE;
		LPSECURITY_ATTRIBUTES defaultSecurityAttributes_ = NULL;
		DWORD defaultCreationDisposition_ = OPEN_ALWAYS;
		DWORD defaultAttributes_ = NULL;
		HANDLE defaultTemplateFile_ = NULL;

	public:
		DWORD defaultAccess() const noexcept { return defaultAccess_; }
		DWORD defaultShareMode() const noexcept { return defaultShareMode_; }
		LPSECURITY_ATTRIBUTES defaultSecurityAttributes() const noexcept { return defaultSecurityAttributes_; }
		DWORD defaultCreationDisposition() const noexcept { return defaultCreationDisposition_; }
		DWORD defaultAttributes() const noexcept { return defaultAttributes_; }
		HANDLE defaultTemplateFile() const noexcept { return defaultTemplateFile_; }

		void changeDefaultAccess(const DWORD access) { defaultAccess_ = access; }
		void changeDefaultShareMode(const DWORD shareMode) { defaultShareMode_ = shareMode; }
		void changeDefaultSecurityAttributes(const LPSECURITY_ATTRIBUTES attributes) { defaultSecurityAttributes_ = attributes; }
		void changeDefaultCreationDisposition(const DWORD disposition) { defaultCreationDisposition_ = disposition; }
		void changeDefaultAttributes(const DWORD attributes) { defaultAttributes_ = attributes; }
		void changeDefaultTemplateFile(const HANDLE file) { defaultTemplateFile_ = file; }
	};

	HANDLE newFile(const std::string& filename) noexcept;

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
	 *		    outputFile.handle() << j << ' ';
	 *	    }
	 *  
	 *      outputFile.handle() << '\n';
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
