#ifndef TEXT_H
#define TEXT_H

// Graphics-Lib includes
#include <Font.h>
#include <Color.h>
#include <Vector2.h>

class Text
{
public:

	// Friends
	friend class TextManager;

	// Mutators
	void drawText();
	int checkDigits(string amountToCheck);//This function essentially takes in a string of numbers and checks how many digits it is.
	void changeMessage(string newMessage);
	void addScore(int amountAdd);
	void setTextPosition(Vector2 newPos);
	void changeFontSize(int newSize);
	void setTextToActive();
	void setTextToInactive();

	// Acessors
	string getName();
	Color * getCurrentColor();

private:

	// Constructors
	Text();
	Text(string newName, string fontPath, int newFontSize, Color newColor, string newMessage, Vector2 newPosition);

	// Destructors
	~Text();

	// Fonts
	Font * mFont;

	// Integers
	int mFontSize;
	int mHealth;
	int mTimer;

	// Booleans
	bool mIsActive;

	// Strings
	string mMessage;
	string mName;
	string mLevel;
	string mScore;

	// Colors
	Color * mTextColor;

	// Vector2's
	Vector2 mTextPosition;

};

#endif // !TEXT_H

