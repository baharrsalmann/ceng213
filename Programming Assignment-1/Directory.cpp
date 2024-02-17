#include "Directory.h"

File Directory::getFile(int index) const
{
	/* TODO */
	if (index<0 || index>files.size()-1) {
		File empty_file;
		return empty_file;
	}
	return files[index];
}

size_t Directory::directorySize() const
{
	/* TODO */
	if(!numFiles()) return 0;

	size_t result=files[0].fileSize();
	for(int i=1;i<numFiles();i++){
	result+=files[i].fileSize();
	}
	return result;
}

bool Directory::isEmpty() const
{
	/* TODO */
	return files.empty();
}

size_t Directory::numFiles() const
{
	/* TODO */
	return files.size();
}

void Directory::newFile(const File &file)
{
	/* TODO */
	files.push_back(file);
}

void Directory::removeFile(int index)
{
	/* TODO */
	if (index<0 || index>files.size()-1) return;
	files.erase(files.begin()+index);
}

void Directory::removeFile(File &file)
{
	/* TODO */
	for(int i=0;i<numFiles();i++){
		if(files[i]==file){
			removeFile(i);
			return;
			}
		}
	return;
}

void Directory::removeBiggestFile()
{
	/* TODO */
	if(isEmpty()) return;
	File biggest_file=files[0];
	for(int i=0;i<numFiles();i++){
		if(biggest_file.fileSize()<files[i].fileSize()) {
			biggest_file=files[i];
		}
	}
	removeFile(biggest_file);
}