#ifndef FILEREADER_H
#define FILEREADER_H

// Standard Library includes
#include <string>

using namespace std;

class FileReader
{
public:

	// Constructors
	FileReader();

	// Destructors
	~FileReader();

	// Mutators
	void readFile(string fileName);
	void readUIFile(string fileName);

private:

};


#endif // !FILEREADER_H

