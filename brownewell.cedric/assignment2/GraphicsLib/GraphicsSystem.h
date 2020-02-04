#pragma once



class GraphicsSystem
{
public:
	GraphicsSystem() {}
	~GraphicsSystem() {}


	int getScreenHeight() { return screenHeight; }
	int getScreenWidth() { return screenWidth; }

	void flipScreen();

private:

	int screenHeight = 800;
	int screenWidth = 600;





};
