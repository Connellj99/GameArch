#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

// Standard library includes
#include <vector>

// Local Project includes
#include "Text.h"


class TextManager
{
public:

	// Constructors
	TextManager();

	// Destructors
	~TextManager();

	// Acessors
	Text * getText(string nameOfText);

	// Mutators
	void addText(string newName, string fontPath, int newFontSize, Color newColor, string newMessage, Vector2 newPosition);
	void removeAllTexts();
	void removeText(string nameOfTextToBeRemoved);

	// Update functions
	void draw();

private:

	// Vectors
	vector<Text*> mTexts;

};

#endif // !TEXTMANAGER_H

