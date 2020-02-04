#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "Trackable.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"
#include "GraphicsBuffer.h"

// The class which creates and maintains the display
class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem(const Vector2D& dimensions);
	~GraphicsSystem();

	// init allegro addons and create display
	void init(const Vector2D& dimensions);
	// destroy display and shutdown allegro addons
	void cleanup();

	int getDisplayHeight() const { return al_get_display_height(mpDisplay); }
	int getDisplayWidth() const { return al_get_display_width(mpDisplay); }


	// display what is in the Back Buffer
	void flip() { al_flip_display(); }
	// draw to current backbuffer
	void draw(const Vector2D& loc, const Sprite& sprite, float scale = 1.0);
	// draw to given GraphicsBuffer
	void draw(const GraphicsBuffer& buffer, const Vector2D& loc, const Sprite& sprite, float scale = 1.0);
	// write to current BackBuffer
	void writeText(const Vector2D& loc, const Font& font, const Color& color, const std::string& text);
	// write to given GraphicsBuffer
	void writeText(const GraphicsBuffer& buffer, const Vector2D& loc, const Font& font, const Color& color, const std::string& text);
	// save the contents of the BackBuffer to a file
	void saveBuffer(const std::string& filename);
	// save the contents of a GraphicsBuffer to a file
	void saveBuffer(const GraphicsBuffer& buffer, const std::string& filename);
	// wait for restTime seconds
	void rest(float restTime);
private:
	ALLEGRO_DISPLAY* mpDisplay;
};
#endif