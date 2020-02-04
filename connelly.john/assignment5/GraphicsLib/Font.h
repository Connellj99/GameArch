#ifndef FONT_H
#define FONT_H

#include "Trackable.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font : public Trackable
{
public:
	Font(std::string filePath, int size);
	~Font();

	int getSize() const { return mSize; }

private:
	Font(const Font&);
	void operator=(const Font&);

	ALLEGRO_FONT* mpFont;
	const int mSize;

	friend class GraphicsSystem;
};
#endif