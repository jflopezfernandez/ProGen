
#ifndef PROGEN_FILE_HXX_
#include <ProGen/File.hxx>
#endif // PROGEN_FILE_HXX_

namespace FileIO {
	DWORD FileAttributes(const std::string& filename) noexcept {
		const auto fileAttributes = GetFileAttributes(filename.c_str());

		if (fileAttributes == INVALID_FILE_ATTRIBUTES) {
			// TODO: Handle error

			exit(EXIT_FAILURE);
		}

		return fileAttributes;
	}

	bool FileExists(const std::string& filename) noexcept {
		const auto fileAttributes = FileAttributes(filename);

		if (fileAttributes == 0xFFFFFFFF)
			return false;

		return true;
	}
} // End namespace FileIO

File::File(const std::string& filename)
	: filename(filename), path { "./" } {
}

File::File(const std::string_view& filename)
	: filename(filename), path { "./" } {
}

void File::open(const std::ios::openmode& mode) {
	handle.open(filename, mode);
}

void File::close() {
	handle.close();
}

std::string File::name() const noexcept {
	return filename;
}

std::string File::fullPathName() const noexcept {
	return path + filename;
}
