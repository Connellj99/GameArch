#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H

#include "Trackable.h"
#include <allegro5/allegro.h>
#include "Vector2D.h"
#include "Color.h"

// A class to hold a chunk of memory used to display something
class GraphicsBuffer : public Trackable
{
public:
	Vector2D getDimensions() const { return Vector2D(al_get_bitmap_width(mpBitmap), al_get_bitmap_height(mpBitmap)); }
private:
	GraphicsBuffer(const std::string& filename);
	GraphicsBuffer(const Vector2D& dimensions, const Color& color);
	~GraphicsBuffer();

	GraphicsBuffer(const GraphicsBuffer&) = delete;
	void operator=(const GraphicsBuffer&) = delete;

	ALLEGRO_BITMAP* mpBitmap;
	bool mIsMyBitmap;

	GraphicsBuffer(ALLEGRO_BITMAP* bitmap, bool isMyBitmap);

	friend class GraphicsSystem;
	friend class GraphicsBufferManager;
};
#endif