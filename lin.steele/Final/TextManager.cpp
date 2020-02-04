#include "TextManager.h"


// This is the default constructor of the class
TextManager::TextManager()
{
}





// This is the destructor of the class
TextManager::~TextManager()
{
	removeAllTexts();
}





// This function gets a Text from a given key
Text * TextManager::getText(string nameOfText) 
{
	// The following code checks if the given key matches a text name.
	// If it does, return the text. If it goes through the whole text
	// without finding a match, return null
	for (int i = 0, max = mTexts.size(); i < max; i++) 
	{
		if (mTexts[i]->getName() == nameOfText) 
		{
			return mTexts[i];
		}
	}

	return nullptr;
}





// This function adds a text object to the texts vector based on given inputs
void TextManager::addText(string newName, string fontPath, int newFontSize, Color newColor, string newMessage, Vector2 newPosition) 
{
	mTexts.push_back(new Text(newName, fontPath, newFontSize, newColor, newMessage, newPosition));
}





// This function removes all of the Text objects from the text vector
void TextManager::removeAllTexts() 
{
	for (int i = 0, max = mTexts.size(); i < max; i++) 
	{
		delete mTexts[i];
	}
}





// This function removes a Text from the text vector from a given key
void TextManager::removeText(string nameOfTextToBeRemoved) 
{
	for (int i = 0, max = mTexts.size(); i < max; i++) 
	{
		if (mTexts[i]->getName() == nameOfTextToBeRemoved) 
		{
			delete mTexts[i];
			mTexts.erase(mTexts.begin() + i);
		}
	}
}





// This function is the draw function for this manager class
void TextManager::draw() 
{
	for (int i = 0, max = mTexts.size(); i < max; i++) 
	{
		mTexts[i]->drawText();
	}
}