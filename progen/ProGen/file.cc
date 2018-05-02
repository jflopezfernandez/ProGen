
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

	HANDLE newFile(const std::string& filename) noexcept {
		static NewFileDefaultConfiguration NewFileDefaults;

		HANDLE newFile = CreateFile(filename.c_str(),
			NewFileDefaults.defaultAccess(),
			NewFileDefaults.defaultShareMode(),
			NewFileDefaults.defaultSecurityAttributes(),
			NewFileDefaults.defaultCreationDisposition(),
			NewFileDefaults.defaultAttributes(),
			NewFileDefaults.defaultTemplateFile()
		);

		if (newFile == INVALID_HANDLE_VALUE) {
			// TODO: Handle error

			exit(EXIT_FAILURE);
		}

		return newFile;
	}

} // End namespace FileIO

void File::setPath() {
	const auto DEFAULT_BUFFER_SIZE = 128;

	char pathBuffer[DEFAULT_BUFFER_SIZE] = { 0 };
	const auto bytesWritten = GetFullPathName(filename.c_str(), DEFAULT_BUFFER_SIZE, pathBuffer, NULL);

	if (!bytesWritten) {
		// TODO: Handle errors

		exit(EXIT_FAILURE);
	}
	
	changePath(pathBuffer);
}

File::File()
	: filename(""), path_ { "./" } {
}

File::File(const std::string& filename)
	: filename(filename), path_ { "./" } {

	setPath();
}

File::File(const std::string& filename, const std::string& filePath)
	: filename(filename), path_(filePath + filename) {

	setPath();
}

void File::open(const std::ios::openmode& mode) {
	stream.open(filename, mode);
}

void File::close() {
	stream.close();
}

std::string File::name() const noexcept {
	return filename;
}

std::string File::path() const noexcept {
	return path_;
}

std::fstream& File::handle() {
	return stream;
}

void File::changeName(const std::string& newFilename) {
	filename = newFilename;
}

void File::changePath(const std::string& newPath) {
	path_ = newPath;
}
