//
//  main.m
//  Bamf
//
//  Created by Matthew Hinkle on 1/31/13.
//
//

#include <functional>
#include <algorithm>
#include <iostream>

#include "ResourceManager.h"
#include "SynchronousGameLoop.h"

#include "Camera.h"

#include "InputManager.h"
#include "InputMapping.h"
#include "Action.h"

#include "Module.h"
#include "CoreModule.h"
#include "GraphicsModule.h"

#include "Scene.h"
#include "SpriteObject.h"

#include "CollisionCircle.h"
#include "CollisionShape.h"
#include "CollisionRectangle.h"
#include "CollisionModule.h"
#include "PhysicsWorld.h"

#include "ArtificialIntelligenceModule.h"
#include "Graph.h"
#include "Astar.h"

#include "NetworkingModule.h"
#include "UpdateExecutor.h"

#include "Event.h"
#include "EventPublisher.h"

#include "QuadTree.h"
#include "SMSPacket.h"

bamf::Scene * scene;

class MoveCameraAction : public bamf::Action
{
protected:
    float _x;
    float _y;
    bamf::Camera * _camera;
public:
    MoveCameraAction(float x, float y, bamf::Camera * camera);
    void executeAction();
    bamf::SMSPacket * packetForAction();
};

MoveCameraAction::MoveCameraAction(float x, float y, bamf::Camera * camera)
{
    _x = x;
    _y = y;
    _camera = camera;
}

void MoveCameraAction::executeAction()
{
    glm::vec2 position = _camera->getPosition();
    position.x += _x;
    position.y += _y;
    _camera->setPosition(position);
}

bamf::SMSPacket * MoveCameraAction::packetForAction()
{
    return NULL;
}

class MoveCameraButtons : public bamf::IKeyMapping
{
protected:
    int _keyCode;
    float _movesX;
    float _movesY;
    bamf::Camera * _cam;
public:
    MoveCameraButtons(int keyCode, float movesX, float movesY,  bamf::Camera * cam);
    bool appliesForInput(bamf::KeyPressType type, int keyCode, ...);
    bamf::Action * actionForInput();
};

MoveCameraButtons::MoveCameraButtons(int keyCode, float movesX, float movesY, bamf::Camera * cam)
{
    _keyCode = keyCode;
    _movesX = movesX;
    _movesY = movesY;
    _cam = cam;
}

bool MoveCameraButtons::appliesForInput(bamf::KeyPressType type, int keyCode, ...)
{
    if(keyCode == _keyCode && type == bamf::KEY_DOWN) {
        return true;
    }
    else {
        return false;
    }
}

bamf::Action * MoveCameraButtons::actionForInput()
{
    return new MoveCameraAction(_movesX, _movesY, _cam);
}

class MoveActorButtons : public bamf::IKeyMapping
{
protected:
    int _keyCode;
    bamf::BamfObject * _object;
    float _x;
    float _y;
public:
    MoveActorButtons(int keyCode, bamf::BamfObject * object, float x, float y);
    bool appliesForInput(bamf::KeyPressType type, int keyCode, ...);
    bamf::Action * actionForInput();
};

class MoveActorAction : public bamf::Action
{
protected:
    float _x;
    float _y;
    bamf::BamfObject * _object;
public:
    MoveActorAction(float x, float y, bamf::BamfObject * object);
    void executeAction();
    bamf::SMSPacket * packetForAction();
};


MoveActorButtons::MoveActorButtons(int keyCode, bamf::BamfObject * object, float x, float y)
{
    this->_keyCode = keyCode;
    this->_object = object;
    this->_x = x;
    this->_y = y;
}

bool MoveActorButtons::appliesForInput(bamf::KeyPressType type, int keyCode, ...)
{
    return keyCode == this->_keyCode && type == bamf::KEY_DOWN;
}

bamf::Action * MoveActorButtons::actionForInput()
{
    return new MoveActorAction(this->_x, this->_y, this->_object);
}

MoveActorAction::MoveActorAction(float x, float y, bamf::BamfObject * object) {
    this->_x = x;
    this->_y = y;
    this->_object = object;
}

void MoveActorAction::executeAction()
{
	bamf::CollisionObject * collisionObject = scene->getCollisionLayer()->getObjectById(this->_object->getId());
	collisionObject->getRigidBody()->setLinearVeloctiy(glm::vec2(this->_x, this->_y));
}

bamf::SMSPacket * MoveActorAction::packetForAction()
{
    return bamf::UpdateExecutor::toPacket(scene, this->_object);
}

float weight(glm::vec2 v1, glm::vec2 v2) {
	return glm::distance(v1, v2);
}

float dist(glm::vec2 v1, glm::vec2 v2) {
	return glm::distance(v1, v2);
}

void onPublish(bamf::Event<bamf::BamfObject *, glm::vec2> * e) {
	//std::cout << "received: " << e->getMessage().x << ", " << e->getMessage().y << std::endl;
}

static bamf::Scene * createScene(bamf::ResourceManager & man, bamf::PhysicsWorld * pw) {
	bamf::Scene * scene = new bamf::Scene();

	bamf::Sprite * ground = new bamf::Sprite("Resources/art/ground.png");
	ground->load(man);
	/*for(int i = -544; i < -540; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(i, -418));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
        pw->addObject(groundObject->getCollisionShape());
	}
	
	bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
	groundObject->setPosition(glm::vec2(-544, -418));
	scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	pw->addObject(groundObject->getCollisionShape());
	
	groundObject = new bamf::SpriteObject(ground);
	groundObject->setPosition(glm::vec2(564, -418));
	scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	pw->addObject(groundObject->getCollisionShape());
	
	bamf::Sprite * water = new bamf::Sprite("Resources/art/water.png");
	water->load(man);
	for(int i = -476; i < -340; i += water->getBounds().width - 1) {
		bamf::SpriteObject * waterObject = new bamf::SpriteObject(water);
		waterObject->setPosition(glm::vec2(i, -392));
		scene->addObjectWithZValue(waterObject, bamf::Scene::kForegroundMidLayer);
	}*/
	
	//for(int i = -338; i < 140; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(-ground->getBounds().width/2,-300));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	//}
	
	/*bamf::Sprite * spikes = new bamf::Sprite("Resources/art/spikes.png");
	spikes->load(man);
	bamf::SpriteObject * spikesObject = new bamf::SpriteObject(spikes);
	spikesObject->setPosition(glm::vec2(146, -386));
	scene->addObjectWithZValue(spikesObject, bamf::Scene::kForegroundMidLayer);
    pw->addObject(spikesObject->getCollisionShape());
	
	groundObject = new bamf::SpriteObject(ground);
	groundObject->setPosition(glm::vec2(216, -418));
	scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
    pw->addObject(groundObject->getCollisionShape());
	
	spikesObject = new bamf::SpriteObject(spikes);
	spikesObject->setPosition(glm::vec2(286, -386));
	scene->addObjectWithZValue(spikesObject, bamf::Scene::kForegroundMidLayer);
    pw->addObject(spikesObject->getCollisionShape());
	
	for(int i = 358; i < 400; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(i, -418));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
        pw->addObject(groundObject->getCollisionShape());
	}
	
	bamf::Sprite * fence = new bamf::Sprite("Resources/art/fence.png");
	fence->load(man);
	for(int i = -768; i < -500; i+= fence->getBounds().width) {
		bamf::SpriteObject * fenceObject = new bamf::SpriteObject(fence);
		fenceObject->setPosition(glm::vec2(i, -354));
		scene->addObjectWithZValue(fenceObject, bamf::Scene::kForegroundFarLayer);
	}
	
	bamf::Sprite * brokenFence = new bamf::Sprite("Resources/art/fence_broken.png");
	brokenFence->load(man);
	bamf::SpriteObject * brokenFenceObject = new bamf::SpriteObject(brokenFence);
	brokenFenceObject->setPosition(glm::vec2(-326, -354));
	scene->addObjectWithZValue(brokenFenceObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::Sprite * grass = new bamf::Sprite("Resources/art/grass.png");
	grass->load(man);
	bamf::SpriteObject * grassObject = new bamf::SpriteObject(grass);
	grassObject->setPosition(glm::vec2(-290, -354));
	scene->addObjectWithZValue(grassObject, bamf::Scene::kForegroundFarLayer);
	
	grassObject = new bamf::SpriteObject(grass);
	grassObject->setPosition(glm::vec2(-270, -354));
	scene->addObjectWithZValue(grassObject, bamf::Scene::kForegroundMidLayer);
	
	bamf::Sprite * block = new bamf::Sprite("Resources/art/block.png");
	block->load(man);
	bamf::SpriteObject * blockObject = new bamf::SpriteObject(block);
	blockObject->setPosition(glm::vec2(320, -140));
	scene->addObjectWithZValue(blockObject, bamf::Scene::kForegroundNearLayer);
    pw->addObject(blockObject->getCollisionShape());
	
	bamf::Sprite * bonus = new bamf::Sprite("Resources/art/bonus.png");
	bonus->load(man);
	bamf::SpriteObject * bonusObject = new bamf::SpriteObject(bonus);
	bonusObject->setPosition(glm::vec2(390, -140));
	scene->addObjectWithZValue(bonusObject, bamf::Scene::kForegroundNearLayer);
    pw->addObject(bonusObject->getCollisionShape());
	
	blockObject = new bamf::SpriteObject(block);
	blockObject->setPosition(glm::vec2(460, -140));
	scene->addObjectWithZValue(blockObject, bamf::Scene::kForegroundNearLayer);
    pw->addObject(blockObject->getCollisionShape());
	
	blockObject = new bamf::SpriteObject(block);
	blockObject->setPosition(glm::vec2(146, -256));
	scene->addObjectWithZValue(blockObject, bamf::Scene::kForegroundNearLayer);
    pw->addObject(blockObject->getCollisionShape());
	
	bamf::Sprite * shortHill = new bamf::Sprite("Resources/art/hill_short.png");
	shortHill->load(man);
	bamf::SpriteObject * shortHillObject = new bamf::SpriteObject(shortHill);
	shortHillObject->setPosition(glm::vec2(-120, -354));
	scene->addObjectWithZValue(shortHillObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::Sprite * longHill = new bamf::Sprite("Resources/art/hill_long.png");
	longHill->load(man);
	bamf::SpriteObject * longHillObject = new bamf::SpriteObject(longHill);
	longHillObject->setPosition(glm::vec2(-180, -354));
	scene->addObjectWithZValue(longHillObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::Sprite * crate = new bamf::Sprite("Resources/art/crate.png");
	crate->load(man);
	bamf::SpriteObject * crateObject = new bamf::SpriteObject(crate);
	crateObject->setPosition(glm::vec2(40, -354));
	scene->addObjectWithZValue(crateObject, bamf::Scene::kForegroundFarLayer - 0.1);
    pw->addObject(crateObject->getCollisionShape());
	
	grassObject = new bamf::SpriteObject(grass);
	grassObject->setPosition(glm::vec2(90, -354));
	scene->addObjectWithZValue(grassObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::Sprite * shroom = new bamf::Sprite("Resources/art/shroom.png");
	shroom->load(man);
	bamf::SpriteObject * shroomObject = new bamf::SpriteObject(shroom);
	shroomObject->setPosition(glm::vec2(0, -350));
	scene->addObjectWithZValue(shroomObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::SpriteObject * waterObject = new bamf::SpriteObject(water);
	waterObject->setPosition(glm::vec2(426, -392));
	scene->addObjectWithZValue(waterObject, bamf::Scene::kForegroundMidLayer);

	waterObject = new bamf::SpriteObject(water);
	waterObject->setPosition(glm::vec2(495, -392));
	scene->addObjectWithZValue(waterObject, bamf::Scene::kForegroundNearLayer);
	
	bamf::Sprite * bush = new bamf::Sprite("Resources/art/bush.png");
	bush->load(man);
	bamf::SpriteObject * bushObject = new bamf::SpriteObject(bush);
	bushObject->setPosition(glm::vec2(340, -76));
	scene->addObjectWithZValue(bushObject, bamf::Scene::kForegroundMidLayer);
		
	shortHillObject = new bamf::SpriteObject(shortHill);
	shortHillObject->setPosition(glm::vec2(380, -76));
	scene->addObjectWithZValue(shortHillObject, bamf::Scene::kForegroundFarLayer);
	
	bamf::Sprite * background = new bamf::Sprite("Resources/art/background_leveled.png");
	background->load(man);
	background->setHotspot(background->getBounds().getCenter());
	bamf::SpriteObject * backgroundObject = new bamf::SpriteObject(background);
	scene->addObjectWithZValue(backgroundObject, bamf::Scene::kBackgroundLayer);*/
	
	return scene;
}

int main(int argc, char *argv[])
{
    /*bamf::CollisionRectangle rectangle(glm::vec2(0.0f,0.0f),10.0f,10.0f);
    bamf::CollisionRectangle rectangle2(glm::vec2(5.0f, 0.0f),10.0f,10.0f);
    glm::vec2 tmp = rectangle.checkCollision(&rectangle2);
    std:: cout << "collision: (" << tmp.x << ", " << tmp.y <<") \n";
    tmp = rectangle2.checkCollision(&rectangle);
    std:: cout << "collision2: (" << tmp.x << ", " << tmp.y <<") \n";*/
	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/art/character/front.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite);
    
    //std::cout << "Created man with oid: " << spriteSprite.getId() << "\n";
	
    bamf::PhysicsWorld pw;
    pw.setGravity(glm::vec2(0,-.0001));
    
	scene = createScene(man, &pw);
	scene->addObjectWithZValue(&spriteSprite, bamf::Scene::kForegroundMidLayer);
	bamf::CollisionObject * collisionObject = scene->getCollisionLayer()->getObjectById(spriteSprite.getId());
	collisionObject->getRigidBody()->setForce(glm::vec2(0, -0.0001));
	
	bamf::SynchronousGameLoop * gameLoop = new bamf::SynchronousGameLoop();
	bamf::CoreModule * core = gameLoop->getCoreModule();
	bamf::SceneManager * sm = core->getSceneManager();
	sm->pushScene(scene);
	
	bamf::InputMapping inputMapping;

    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_w, &spriteSprite, 0, .1));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_d, &spriteSprite, .1, 0));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_s, &spriteSprite, 0, -.1));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_a, &spriteSprite, -.1, 0));

        
	bamf::CollisionModule collisionModule;
	
	//collisionModule.addCollidable(rectangle);
    //collisionModule.addCollidable(rectangle2);

	gameLoop->addModule(&pw);
	gameLoop->addModule(&collisionModule);
	
	SDL_assert(scene->getObjectById(spriteSprite.getId()));
	
#if 0
/*
	glm::vec2 startNode = spriteSprite.getPosition();
	glm::vec2 middleNode = glm::vec2(-100, -100);
	glm::vec2 fuckNode = glm::vec2(200, 200);
	glm::vec2 endNode = glm::vec2(-300, -500);
	
	bamf::Graph<glm::vec2, float, Hashit<glm::vec2>> graph;
	graph.addEdge(startNode, middleNode, 100);
	graph.addEdge(startNode, fuckNode, 101);
	graph.addEdge(middleNode, endNode, 100);
	
	std::function<void (bamf::Event<bamf::BamfObject *, glm::vec2> *)> f1(onPublish);
	
	bamf::Astar<glm::vec2, float, Hashit<glm::vec2>> astar(&graph);
	
	std::function< float(glm::vec2, glm::vec2) > f(dist);
	bamf::Path<glm::vec2> * path = astar.search(startNode, endNode, f);
	bamf::ActivePath<glm::vec2> * activePath = new bamf::ActivePath<glm::vec2>(path);
	//spriteSprite.getState()->activePath = activePath;
	
	bamf::ArticialIntelligenceModule aimodule;
	aimodule.addObject(&spriteSprite);
	gameLoop->addModule(&aimodule);
*/
#endif
    //std::cout << "bounds = " << scene->getBounds().x << "," << scene->getBounds().y << "," << scene->getBounds().width << "," << scene->getBounds().height << std::endl;
    
    bamf::NetworkingModule * networking = new bamf::NetworkingModule(core);
    bamf::InputManager inputManager(networking);
    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);
#if 0
    networking->initializeNetworkGame("localhost", 57109);
#endif
    gameLoop->addModule(networking);
    
    gameLoop->start();
	
	return 0;
}
