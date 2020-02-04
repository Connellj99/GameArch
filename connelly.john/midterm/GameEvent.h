#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include "Event.h"
#include "Vector2D.h"
enum GameEventType
{
	INIT_SMURF_EVENT = NUM_EVENT_TYPES,
	DESTROY_SMURF_EVENT,
	SWAP_SMURF_ANIMATION_EVENT,
	TOGGLE_SMURF_ANIMATIONS_EVENT,MOVELEFT,MOVERIGHT,MOVEUP,MOVEDOWN,
	CREATE_WALL,CREATE_FOOD,DESTROY_FOOD, CREATE_SPEEDUP, DESTROY_SPEEDUP, CREATE_SLOWDOWN, DESTROY_SLOWDOWN,
	EXIT_GAME_EVENT
};

class CreateFoodEvent : public Event
{
public:
	CreateFoodEvent(const Vector2D&  spawnLoc) : Event(EventType(CREATE_FOOD)),
		mSpawnLoc(spawnLoc) {}
	~CreateFoodEvent() {}
	Vector2D getSpawnLoc() const { return mSpawnLoc; }
private:
	Vector2D mSpawnLoc;
};

class DestroyFoodEvent : public Event
{
public:
	DestroyFoodEvent(const Vector2D&  delLoc) : Event(EventType(DESTROY_FOOD)),
		mDeleteLoc(delLoc) {}
	~DestroyFoodEvent() {}

	Vector2D getDeleteLoc() const { return mDeleteLoc; }
private:
	Vector2D mDeleteLoc;
};

class CreateWallEvent : public Event
{
public:
	CreateWallEvent(const Vector2D&  spawnLoc) : Event(EventType(CREATE_WALL)),
		mSpawnLoc(spawnLoc) {}
	~CreateWallEvent() {}
	Vector2D getSpawnLoc() const { return mSpawnLoc; }
private:
	Vector2D mSpawnLoc;
};
class DestroySpeedUpEvent : public Event
{
public:
	DestroySpeedUpEvent(const Vector2D&  delLoc) : Event(EventType(DESTROY_SPEEDUP)),
		mDeleteLoc(delLoc) {}
	~DestroySpeedUpEvent() {}

	Vector2D getDeleteLoc() const { return mDeleteLoc; }
private:
	Vector2D mDeleteLoc;
};

class CreateSpeedUpEvent : public Event
{
public:
	CreateSpeedUpEvent(const Vector2D&  spawnLoc) : Event(EventType(CREATE_SPEEDUP)),
		mSpawnLoc(spawnLoc) {}
	~CreateSpeedUpEvent() {}
	Vector2D getSpawnLoc() const { return mSpawnLoc; }
private:
	Vector2D mSpawnLoc;
};
class DestroySlowDownEvent : public Event
{
public:
	DestroySlowDownEvent(const Vector2D&  delLoc) : Event(EventType(DESTROY_SLOWDOWN)),
		mDeleteLoc(delLoc) {}
	~DestroySlowDownEvent() {}

	Vector2D getDeleteLoc() const { return mDeleteLoc; }
private:
	Vector2D mDeleteLoc;
};

class CreateSlowDownEvent : public Event
{
public:
	CreateSlowDownEvent(const Vector2D&  spawnLoc) : Event(EventType(CREATE_SLOWDOWN)),
		mSpawnLoc(spawnLoc) {}
	~CreateSlowDownEvent() {}
	Vector2D getSpawnLoc() const { return mSpawnLoc; }
private:
	Vector2D mSpawnLoc;
};

#endif