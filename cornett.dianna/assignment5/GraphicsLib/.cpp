#include "GraphicsSystem.h"


GraphicsSystem::GraphicsSystem() {
	mDisplay = NULL;
}
GraphicsSystem::~GraphicsSystem() {
	cleanup();
}


void GraphicsSystem::init(int width, int height) {
	if (!al_init())
	{
		std::cout << "error initting Allegro\n";
	}

	mDisplay = al_create_display(width, height);
}

void GraphicsSystem::cleanup() {
	//delete mDisplay;
	mDisplay = NULL;
}


void GraphicsSystem::clearToColor(Color color) {
	al_clear_to_color(al_map_rgb(color.r, color.g, color.b));
}



void GraphicsSystem::WriteText(Font font, int x, int y, Color color, std::string message) {
	font.write(x, y, color, message);
}

void GraphicsSystem::Filp() {
	al_flip_display();
}