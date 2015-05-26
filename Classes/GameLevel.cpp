#include "GameLevel.h"

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::setBoss(Boss* levelBoss)
{
	this->levelBoss = levelBoss;
}

void GameLevel::setBackground(ParallaxBackground* levelBackground)
{
	this->levelBackground = levelBackground;
	this->addChild(levelBackground);
}

void GameLevel::setPlayer(Player* mainCharacter)
{
	this->mainCharacter = mainCharacter;
	this->addChild(mainCharacter);
}

void GameLevel::setDistanceToBoss(long long distance)
{
	this->distance = distance;
}

void GameLevel::setAudioEngine(CocosDenshion::SimpleAudioEngine* audioEngine)
{
	this->audioEngine = audioEngine;
}

void GameLevel::setMusic(string backgroundMusic)
{
	this->backgroundMusic = backgroundMusic;
}

void GameLevel::addObjectFactory(InteractiveObjectFactory* objectFactory)
{
	this->addChild(objectFactory);
	this->objectFactories.push_back(objectFactory);
}

GameLevel* GameLevel::create()
{
	GameLevel* gameLevel = GameLevel::createWithPhysics();
	gameLevel->getPhysicsWorld()->setGravity(Vect(0.0f, -700.0f));
	gameLevel->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	gameLevel->getPhysicsWorld()->setSpeed(2.0f);
	gameLevel->scheduleUpdate();


	Label* scoreLabel = Label::createWithTTF("Score: 0", "font.ttf", 15);
	scoreLabel->setPosition(70, Director::getInstance()->getWinSize().height - 20);
	gameLevel->setScoreLabel(scoreLabel);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size finalSize;
	finalSize.width = visibleSize.width * 2;
	finalSize.height = visibleSize.height / GROUND_PERCENTAGE_FOR_BOX;

	PhysicsBody* edgeBody = PhysicsBody::createEdgeBox(finalSize, PhysicsMaterial(0.1f, 0.0f, 0.5f), 3);
	Node* edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	gameLevel->addChild(edgeNode);



	ParticleSystemQuad* particle = ParticleSystemQuad::create("particle.plist");
	particle->setPosition(0, 300);
	auto spriteBody = PhysicsBody::createBox(particle->boundingBox().size, PhysicsMaterial(1.0f, 0.5f, 0.5f));
	spriteBody->setGravityEnable(false);
	spriteBody->applyImpulse(Vect(25, 0));
	particle->setPhysicsBody(spriteBody);


	gameLevel->addChild(particle,534);





	return gameLevel;
}

GameLevel* GameLevel::createWithPhysics()
{
	GameLevel *ret = new (std::nothrow) GameLevel();
	if (ret && ret->initWithPhysics())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

void GameLevel::update(float delta)
{
	for (int i = 0; i < objectFactories.size(); i++)
	{
		objectFactories.at(i)->createObject();
	}


	if (this->distance == this->mainCharacter->getDistanceTravelled())
	{
		this->levelBackground->slowlyStop();
		this->mainCharacter->setBossMode(true);
	}

	updateScore();
	

}

void GameLevel::updateScore()
{
	int score = mainCharacter->getScore();

	this->scoreLabel->setString("Score: " + to_string(score));
}

void GameLevel::setScoreLabel(Label* label)
{
	this->scoreLabel = label;
	this->addChild(label,100);
}
