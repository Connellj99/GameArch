#pragma once

class GraphicsSystem
{
public:
	GraphicsSystem();
	virtual ~GraphicsSystem();

	void initCheck();

private:
	int mHeight;
	int mWidth;

};

void initCheck(bool test, const char* description);

void setHeight();
void getHeight();

void setWidth();
void getWidth();


