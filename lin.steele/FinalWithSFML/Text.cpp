#include "Text.h"
#include "Game.h"



// This function is the default constructor for this class
Text::Text()
{
	mFont = nullptr;
	//mTextColor = nullptr;
	mFontSize = 0;
	mMessage = "";
	mTextPosition = Vector2(0, 0);
	mIsActive = false;
}


//
//
//
//// This function initializes all values with given inputs
//// for each individual value (except for font, it is taken in as a file path)
//Text::Text( string newName, string fontPath, int newFontSize, Color newColor, string newMessage, Vector2 newPosition )
//{
//	mName = newName;
//	mFont = new Font(fontPath, newFontSize);
//	mTextColor = new Color(newColor);
//	mMessage = newMessage;
//	mTextPosition = newPosition;
//	mIsActive = false;
//}
//
//



// This function is the destructor for this class
Text::~Text()
{
	delete mFont;
	//delete mTextColor;
}





// This function draws the text to the screen
void Text::drawText() 
{
	if (mIsActive) 
	{
		//Game::getStaticInstance()->getCurrentSystem()->getGraphicsSystem().drawText(mTextPosition, *mFont, *mTextColor, mMessage);
	}
}





// This function changes the message of the text a given input
void Text::changeMessage(string newMessage) 
{
	mMessage = newMessage;
}





// This function returns the name of the text
string Text::getName() 
{
	return mName;
}





// This function sets the text to active
void Text::setTextToActive() 
{
	mIsActive = true;
}





// This function sets the text to active
void Text::setTextToInactive() 
{
	mIsActive = false;
}





// This function changes the positioning the Text is at
void Text::setTextPosition( Vector2 newPos ) 
{
	mTextPosition = newPos;
}





// This function changes the Font size of the Text
void Text::changeFontSize(int newSize) 
{
	mFontSize = newSize;
	mFont->setSize(newSize);
}




//
//// This function gets the current color of the text
//Color * Text::getCurrentColor() 
//{
//	return mTextColor;
//}