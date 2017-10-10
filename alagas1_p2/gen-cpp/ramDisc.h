#ifndef RAMDISC_H
#define RAMDISC_H

#include <stdio.h>
#include "FileStore.h"

class ramDisc{
	public:
		ramDisc();
		void addFile(const RFile& rFile);
		RFile* getFile(const std::string& filename, const UserID& owner);

	private:
		RFile** files;
		uint32_t lastWrittenIndex;
		uint32_t numFiles;
}
#endif
