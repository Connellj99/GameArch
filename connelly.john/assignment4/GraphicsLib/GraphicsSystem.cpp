#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
	: mpDisplay(nullptr), mpBackBuffer(nullptr)
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

void GraphicsSystem::init(const Vector2D& dimensions)
{
	mIsInitted = true;

	mpDisplay = al_create_display(dimensions.getX(), dimensions.getY());
	mpBackBuffer = new GraphicsBuffer(al_get_backbuffer(mpDisplay), false);

	// clear to white at start
	al_clear_to_color(al_map_rgb(255, 255, 255));
}

void GraphicsSystem::cleanup()
{
	if (!mIsInitted) return;
	mIsInitted = false;

	delete mpBackBuffer;
	al_destroy_display(mpDisplay);
}

void GraphicsSystem::draw(const Vector2D& loc, const Sprite& sprite, const Vector2D& scale)
{
	al_draw_scaled_bitmap(sprite.getGraphicsBuffer()->mpBitmap,
		sprite.getSourceLocation().getX(), sprite.getSourceLocation().getY(),
		sprite.getDimensions().getX(), sprite.getDimensions().getY(), loc.getX(), loc.getY(),
		sprite.getDimensions().getX() * scale.getX(), sprite.getDimensions().getY() * scale.getY(), NULL);
}

void GraphicsSystem::draw(const GraphicsBuffer& buffer, const Vector2D& loc, const Sprite& sprite, const Vector2D& scale)
{
	const auto initTargetBitmap = al_get_target_bitmap();
	al_set_target_bitmap(buffer.mpBitmap);
	draw(loc, sprite, scale);
	al_set_target_bitmap(initTargetBitmap);
}

void GraphicsSystem::writeText(const Vector2D& loc, const Font& font, const Color& color, const std::string& text)
{
	al_draw_text(font.mpFont, color.getAllegroColor(), loc.getX(), loc.getY(), NULL, text.c_str());
}

void GraphicsSystem::writeText(const GraphicsBuffer& buffer, const Vector2D& loc, const Font& font, const Color& color, const std::string& text)
{
	const auto initTargetBitmap = al_get_target_bitmap();
	al_set_target_bitmap(buffer.mpBitmap);
	writeText(loc, font, color, text);
	al_set_target_bitmap(initTargetBitmap);
}

void GraphicsSystem::saveBuffer(const GraphicsBuffer& buffer, const std::string& filename)
{
	al_save_bitmap(filename.c_str(), buffer.mpBitmap);
}

void GraphicsSystem::rest(float restTime)
{
	al_rest(restTime);
}
