#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

#include "Trackable.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"

// The class which creates and maintains the display
class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	// init allegro addons and create display
	void init(const Vector2D& dimensions);
	// destroy display and shutdown allegro addons
	void cleanup();

	int getDisplayHeight() const { return al_get_display_height(mpDisplay); }
	int getDisplayWidth() const { return al_get_display_width(mpDisplay); }
	Vector2D getDisplayDimensions() const { return Vector2D(al_get_display_width(mpDisplay), 
		al_get_display_height(mpDisplay)); }
	GraphicsBuffer* getBackBuffer() const { return mpBackBuffer; }

	// display what is in the Back Buffer
	void flip() { al_flip_display(); }
	// clear backbuffer to color
	void clearToColor(const Color& color);
	// draw to current backbuffer
	void draw(const Vector2D& loc, const Sprite& sprite, const Vector2D& scale = Vector2D(1, 1), bool flipHoriztonal = false);
	// draw to given GraphicsBuffer
	void draw(const GraphicsBuffer& buffer, const Vector2D& loc, const Sprite& sprite, const Vector2D& scale = Vector2D(1, 1));
	// write to current BackBuffer
	void writeText(const Vector2D& loc, const Font& font, const Color& color, const std::string& text);
	// write to given GraphicsBuffer
	void writeText(const GraphicsBuffer& buffer, const Vector2D& loc, const Font& font, const Color& color, const std::string& text);
	// save the contents of a GraphicsBuffer to a file
	void saveBuffer(const GraphicsBuffer& buffer, const std::string& filename);
	// wait for restTime seconds
	void rest(float restTime);
private:
	GraphicsSystem(const GraphicsSystem&) = delete;
	void operator=(const GraphicsSystem&) = delete;

	bool mIsInitted = false;

	ALLEGRO_DISPLAY* mpDisplay;
	GraphicsBuffer* mpBackBuffer;
};
#endif