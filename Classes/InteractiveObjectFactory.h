#pragma once
#include "cocos2d.h"
#include "InteractiveObject.h"
class GameLevel;

USING_NS_CC;
using namespace std;

class InteractiveObjectFactory: public Node
{
public:
	static InteractiveObjectFactory* create(int resourceIndex, bool isAnimated, bool canBeFiredAt = false, bool canHitPlayer = false, bool gravityAffected = true);
	void setSpeed(Vec2 speed);
	void setSpawnFrequency(int frequency);
	void setGravityAffected(bool gravityAffected);
	void setPositionInterval(Vec2 interval);
	void setIsAnimated(bool isAnimated);
	void setParent(GameLevel* parent);
	void setCanBeFiredAt(bool canBeFiredAt);
	void setCanHitPlayer(bool canHitPlayer);
	void setResource(int resource);
	void createObject();

	//TODO: remove obsolete occurrences

	void update(float delta) override;
private:
	int resourceIndex;

	bool isAnimated;
	bool canBeFiredAt;
	bool canHitPlayer;
	bool gravityAffected;

	Vec2 speed;
	Vec2 spawnInterval;

	GameLevel* parent;
	int frequency;
	~InteractiveObjectFactory();
	InteractiveObjectFactory();
	vector<InteractiveObject*> objects;
};
