#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "Trackable.h"
#include "Vector2D.h"
#include "GraphicsBufferManager.h"
#include "BoxCollider2D.h"
#include <string>

class GameData : public Trackable
{
public:
	GameData() {}
	~GameData() {}

	void read(const std::string& configFilepath);

	// game
	Vector2D getDisplayDimensions() const { return mDisplayDimesions; }
	float getTargetFrameRate() const { return mTargetFrameRate; }
	std::string getAssetPath() const { return mAssetPath; }
	Color getBackgroundColor() const { return mBackgroundColor; }

	// player
	BufferKey getPlayerReadyBufferKey() const { return mPlayerReadyBufferKey; }
	std::string getPlayerReadyBufferFilename() const { return mPlayerReadyBufferFilename; }
	BufferKey getPlayerReloadBufferKey() const { return mPlayerReloadBufferKey; }
	std::string getPlayerReloadBufferFilename() const { return mPlayerReloadBufferFilename; }
	Vector2D getPlayerSpriteDimensions() const { return mPlayerSpriteDimensions; }
	float getPlayerAnimSpeed() const { return mPlayerAnimSpeed; }
	Vector2D getPlayerScale() const { return mPlayerScale; }
	Tag getPlayerTag() const { return mPlayerTag; }
	int getInitPlayerLives() const { return mInitPlayerLives; }
	int getPointsForExtraLife() const { return mPointsForExtraLife; }
	float getPlayerMoveSpeed() const { return mPlayerMoveSpeed; }
	float getPlayerMoveRangeY() const { return mPlayerMoveRangeY; }

	// bullet
	BufferKey getBulletBufferKey() const { return mBulletBufferKey; }
	std::string getBulletBufferFilename() const { return mBulletBufferFilename; }
	Vector2D getBulletSpriteDimensions() const { return mBulletSpriteDimensions; }
	float getBulletAnimSpeed() const { return mBulletAnimSpeed; }
	Vector2D getBulletScale() const { return mBulletScale; }
	Tag getBulletTag() const { return mBulletTag; }
	float getBulletMoveSpeed() const { return mBulletMoveSpeed; }

	// mushroom
	BufferKey getMushroomBufferKey() const { return mMushroomBufferKey; }
	std::string getMushroomBuffferFilename() const { return mMushroomBufferFilename; }
	Vector2D getMushroomSpriteDimesions() const { return mMushroomSpriteDimesions; }
	Vector2D getMushroomScale() const { return mMushroomScale; }
	Tag getMushroomTag() const { return mMushroomTag; }
	int getNumInitMushrooms() const { return mNumInitMushrooms; }
	int getMushroomDestroyPoints() const { return mMushroomDestroyPoints; }
	int getMushroomHitPoints() const { return mMushroomHitPoints; }

	// centipede
	BufferKey getCentipedeBodyBufferKey() const { return mCentipedeBodyBufferKey; }
	std::string getCentipedeBodyBufferFilename() const { return mCentipedeBodyBufferFilename; }
	BufferKey getCentipedeHeadBufferKey() const { return mCentipedeHeadBufferKey; }
	std::string getCentipedeHeadBufferFilename() const { return mCentipedeHeadBufferFilename; }
	Vector2D getCentipedeSpriteDimensions() const { return mCentipedeSpriteDimensions; }
	float getCentipedeAnimSpeed() const { return mCentipedeAnimSpeed; }
	Vector2D getCentipedeScale() const { return mCentipedeScale; }
	Tag getCentipedeTag() const { return mCentipedeTag; }
	int getInitialCentipedeLength() const { return mInitialCentipedeLength; }
	float getCentipedeMoveSpeedIncPerLevel() const { return mCentipedeMoveSpeedIncPerLevel; }
	float getCentipedeInitSetback() const { return mCentipedeInitSetback; }
	float getCentipedeInitMoveSpeed() const { return mCentipedeInitMoveSpeed; }
	float getCentipedeMoveSpeedIncPerSplit() const { return mCentipedeMoveSpeedIncPerSplit; }

	// font
	std::string getFontFilename() const { return mFontFilename; }
	Color getMenuFontColor() const { return mMenuFontColor; }
	int getMenuFontSize() const { return mMenuFontSize; }
	Color getHudFontColor() const { return mHudFontColor; }
	int getHudFontSize() const { return mHudFontSize; }

	// text
	Vector2D getMenuTextLoc() const { return mMenuTextLoc; }
	Vector2D getEndTextLoc() const { return mEndTextLoc; }
	Vector2D getPlayAgainTextLoc() const { return mPlayAgainTextLoc; }
	Vector2D getLevelTextLoc() const { return mLevelTextLoc; }
	Vector2D getScoreTextLoc() const { return mScoreTextLoc; }
	Vector2D getLivesTextLoc() const { return mLivesTextLoc; }
	Vector2D getFpsTextLoc() const { return mFpsTextLoc; }
private:
	// game
	Vector2D mDisplayDimesions = Vector2D(800, 600);
	float mTargetFrameRate = 60;
	std::string mAssetPath = "..\\..\\clarke.adam\\midterm\\assets\\";
	Color mBackgroundColor = Color(0, 0, 0, 255);

	// player
	BufferKey mPlayerReadyBufferKey = "PLAYER_READY";
	std::string mPlayerReadyBufferFilename = "player_ready.png";
	BufferKey mPlayerReloadBufferKey = "PLAYER_RELOAD";
	std::string mPlayerReloadBufferFilename = "player_reload.png";
	Vector2D mPlayerSpriteDimensions = Vector2D(7, 10);
	float mPlayerAnimSpeed = 1;
	Vector2D mPlayerScale = Vector2D(4, 4);
	Tag mPlayerTag = "PLAYER";
	int mInitPlayerLives = 3;
	int mPointsForExtraLife = 5000;
	float mPlayerMoveSpeed = 10.0f;
	float mPlayerMoveRangeY = 120;

	// bullet
	BufferKey mBulletBufferKey = "BULLET";
	std::string mBulletBufferFilename = "bullet.png";
	Vector2D mBulletSpriteDimensions = Vector2D(1, 6);
	float mBulletAnimSpeed = 1;
	Vector2D mBulletScale = Vector2D(5, 5);
	Tag mBulletTag = "BULLET";
	float mBulletMoveSpeed = 20.0f;

	// mushroom
	BufferKey mMushroomBufferKey = "MUSHROOM";
	std::string mMushroomBufferFilename = "mushroom.png";
	Vector2D mMushroomSpriteDimesions = Vector2D(8, 8);
	Vector2D mMushroomScale = Vector2D(4, 4);
	Tag mMushroomTag = "MUSHROOM";
	int mNumInitMushrooms = 15;
	int mMushroomDestroyPoints = 1;
	int mMushroomHitPoints = 4;

	// centipede
	BufferKey mCentipedeBodyBufferKey = "CENTIPEDE_BODY";
	std::string mCentipedeBodyBufferFilename = "centipede_body.png";
	BufferKey mCentipedeHeadBufferKey = "CENTIPEDE_HEAD";
	std::string mCentipedeHeadBufferFilename = "centipede_head.png";
	Vector2D mCentipedeSpriteDimensions = Vector2D(7, 8);
	float mCentipedeAnimSpeed = 1.0f;
	Vector2D mCentipedeScale = Vector2D(4, 4);
	Tag mCentipedeTag = "CENTIPEDE";
	int mInitialCentipedeLength = 10;
	float mCentipedeMoveSpeedIncPerLevel = 1.0f;
	int mCentipedeInitSetback = -500;
	float mCentipedeInitMoveSpeed = 2;
	float mCentipedeMoveSpeedIncPerSplit = 0.5f;

	// font
	std::string mFontFilename = "cour.ttf";
	Color mMenuFontColor = Color(255, 0, 0, 255);
	int mMenuFontSize = 30;
	Color mHudFontColor = Color(255, 0, 0, 255);
	int mHudFontSize = 30;

	// text
	Vector2D mMenuTextLoc = Vector2D(300, 400);
	Vector2D mEndTextLoc = Vector2D(300, 400);
	Vector2D mPlayAgainTextLoc = Vector2D(300, 550);
	Vector2D mLevelTextLoc = Vector2D(360, 20);
	Vector2D mScoreTextLoc = Vector2D(100, 20);
	Vector2D mLivesTextLoc = Vector2D(250, 20);
	Vector2D mFpsTextLoc = Vector2D(560, 20);
};
#endif