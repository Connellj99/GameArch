#include "Sprite.h"

Sprite::Sprite(GraphicsBuffer* currentBuffer, int x, int y, int width, int height) {
	buffer = currentBuffer;
	sourceX = x;
	sourceY = y;
	sourceWidth = width;
	sourceHeight = height;
}

GraphicsBuffer* Sprite::getBuffer() {
	return this->buffer;
}

double Sprite::GetWidth() {
	return this->sourceWidth;
}

double Sprite::GetHeight() {
	return this->sourceHeight;
}

double Sprite::GetX() {
	return this->sourceX;
}

double Sprite::GetY() {
	return this->sourceY;
}

Sprite::~Sprite() {
	buffer->~GraphicsBuffer();
}