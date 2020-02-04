#ifndef Font_h
#define Font_h

#include "Trackable.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

class Font : public Trackable
{
	friend class GraphicsSystem;
public:
	Font();
	Font(std::string fontFileName, int fontSize);
	Font(int fontSize);
	~Font();
	int getSize()
	{
		return mFontSize;
	};
	void setFontFile(std::string fileName);
	void setFontSize(int size);
private:
	ALLEGRO_FONT* getFont()
	{
		return mFont;
	};
	//Allegro font
	ALLEGRO_FONT* mFont;
	//Font size
	std::string mFontFile;
	int mFontSize;
};
#endif // !"Font.h"
