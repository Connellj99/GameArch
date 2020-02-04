/*********************************************************************
**		Author:	Nick DaCosta										**
**		Class: 310 <Section 01>										**
**		Assignment: pa 5											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
*********************************************************************/

#pragma once

/// <summary>
///		A pointer to a specific part of a <see cref="GraphicsBuffer" />.
/// </summary>
/// <seealso cref="Trackable" />
class Sprite :
	public Trackable
{
public:
	// Default constructor.
	Sprite();

	// Copy constructor.
	Sprite(Sprite& _oldSprite);

	// Create a sprite with the given specifications.
	Sprite(GraphicsBuffer* _pBuffer, int _sourceX, int _sourceY, int _width, int _height);

	// Clean up the sprite instance.
	~Sprite();

	// Get the source x location on the buffer.
	int getSourceX();

	// Get the source y location on the buffer.
	int getSourceY();

	// Get the width.
	int getWidth();

	// Get the height.
	int getHeight();

	// Get the buffer associated with this sprite.
	GraphicsBuffer* getBuffer();

private:
	// Graphics buffer associated with this sprite.
	GraphicsBuffer* mpBuffer;

	// Source x location of the sprite on the buffer.
	int mSourceX = 0;

	// Source y location of the sprite on the buffer.
	int mSourceY = 0;

	// Width of the sprite.
	int mWidth = 0;

	// Height of the sprite.
	int mHeight = 0;
};