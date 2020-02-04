#ifndef FONT_H
#define FONT_H

#include <iostream>
#include <cassert>
#include <string>
#include <stdlib.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

using namespace std;


class Font : public Trackable
{
public:


	// Friends
	friend class GraphicsSystem;

	// Constructors
	Font();
	Font( string fontFilePath, int fontSize );
	Font( string fontFilePath );

	// Destructors
	~Font();

	// Accesors
	int getSize();

	// Mutators
	void setSize(int newSize);

private:

	// Strings
	string mFilePath;

	// Ints
	int mFontSize;

};

#endif