#include "ramDisc.h"

ramDisc::ramDisc(){
	this.files = new RFile[2];
	this.numFiles = 2;
	this.lastWrittenIndex = 0;
}

void ramDisc::addFile(const RFile& rFile){
	if(this.lastWrittenIndex == (this.numFiles - 1)){
		Rfile temp = new RFile[this.numFiles];
		for(int i = 0; i < numFiles; i++){
			temp[i] = files[i];
		}
		numFiles *= 2;
		this.files = new RFile[numFiles]
		for(int i = 0; i < (numFiles/2); i++){
			files[i] = temp[i];
		}
	}
	files[++lastWrittenIndex] = rfile;
}

RFile* ramDisc::getFile(const std::string& filename, const UserID& owner){
	return NULL; //For now
}
