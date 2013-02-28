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

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

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

#include "Graph.h"
#include "Astar.h"

#include "NetworkingModule.h"

class MoveCameraAction : public bamf::Action
{
protected:
    float _x;
    float _y;
    bamf::Camera * _camera;
public:
    MoveCameraAction(float x, float y, bamf::Camera * camera);
    void executeAction();
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
    this->_object->getRigidBody()->setLinearVeloctiy(glm::vec2(this->_x, this->_y));
}

template<class T> class Hashit;

template<>
class Hashit<glm::vec2> {
public:
	size_t operator()(glm::vec2 v) const {
		return std::hash<float>()(v.x) ^ std::hash<float>()(v.y);
	}
};

float weight(glm::vec2 v1, glm::vec2 v2) {
	return glm::distance(v1, v2);
}

float dist(glm::vec2 v1, glm::vec2 v2) {
	return glm::distance(v1, v2);
}

static bamf::Scene * createScene(bamf::ResourceManager & man) {
	bamf::Scene * scene = new bamf::Scene();

	bamf::Sprite * ground = new bamf::Sprite("Resources/art/ground.png");
	ground->load(man);
	for(int i = -544; i < -540; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(i, -418));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	}
	
	bamf::Sprite * water = new bamf::Sprite("Resources/art/water.png");
	water->load(man);
	for(int i = -476; i < -340; i += water->getBounds().width - 1) {
		bamf::SpriteObject * waterObject = new bamf::SpriteObject(water);
		waterObject->setPosition(glm::vec2(i, -392));
		scene->addObjectWithZValue(waterObject, bamf::Scene::kForegroundMidLayer);
	}
	
	for(int i = -338; i < 140; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(i, -418));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	}
	
	bamf::Sprite * spikes = new bamf::Sprite("Resources/art/spikes.png");
	spikes->load(man);
	bamf::SpriteObject * spikesObject = new bamf::SpriteObject(spikes);
	spikesObject->setPosition(glm::vec2(146, -386));
	scene->addObjectWithZValue(spikesObject, bamf::Scene::kForegroundMidLayer);
	
	bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
	groundObject->setPosition(glm::vec2(216, -418));
	scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	
	spikesObject = new bamf::SpriteObject(spikes);
	spikesObject->setPosition(glm::vec2(286, -386));
	scene->addObjectWithZValue(spikesObject, bamf::Scene::kForegroundMidLayer);
	
	for(int i = 358; i < 400; i += ground->getBounds().width - 1) {
		bamf::SpriteObject * groundObject = new bamf::SpriteObject(ground);
		groundObject->setPosition(glm::vec2(i, -418));
		scene->addObjectWithZValue(groundObject, bamf::Scene::kForegroundMidLayer);
	}
	
	bamf::Sprite * fence = new bamf::Sprite("Resources/art/fence.png");
	fence->load(man);
	for(int i = -554; i < -500; i+= fence->getBounds().width) {
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
	
	bamf::Sprite * bonus = new bamf::Sprite("Resources/art/bonus.png");
	bonus->load(man);
	bamf::SpriteObject * bonusObject = new bamf::SpriteObject(bonus);
	bonusObject->setPosition(glm::vec2(390, -140));
	scene->addObjectWithZValue(bonusObject, bamf::Scene::kForegroundNearLayer);
	
	blockObject = new bamf::SpriteObject(block);
	blockObject->setPosition(glm::vec2(460, -140));
	scene->addObjectWithZValue(blockObject, bamf::Scene::kForegroundNearLayer);
	
	blockObject = new bamf::SpriteObject(block);
	blockObject->setPosition(glm::vec2(146, -256));
	scene->addObjectWithZValue(blockObject, bamf::Scene::kForegroundNearLayer);
	
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
	scene->addObjectWithZValue(crateObject, bamf::Scene::kForegroundFarLayer);
	
	grassObject = new bamf::SpriteObject(grass);
	grassObject->setPosition(glm::vec2(90, -354));
	scene->addObjectWithZValue(grassObject, bamf::Scene::kForegroundNearLayer);
	
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
	
	bamf::Sprite * background = new bamf::Sprite("Resources/art/background.png");
	background->load(man);
	background->setHotspot(background->getBounds().getCenter());
	bamf::SpriteObject * backgroundObject = new bamf::SpriteObject(background);
	backgroundObject->setPosition(glm::vec2(0, 0));
	//scene->addObjectWithZValue(backgroundObject, bamf::Scene::kBackgroundLayer);
	
	return scene;
}

int main(int argc, char *argv[])
{
    float f = 2342398347593;
    std::cout << sizeof(f);
/**
	glm::vec2 o(0, 0);
	glm::vec2 a(10, 10);
	glm::vec2 b(-10, -10);
	glm::vec2 g(-11, -11);
	
	bamf::Graph<glm::vec2, float, Hashit<glm::vec2>> graph;

	graph.addEdge(o, a, (float) glm::distance(o, a));
	graph.addEdge(o, b, (float) glm::distance(o, b));
	graph.addEdge(a, g, (float) glm::distance(a, g));
	graph.addEdge(b, g, (float) glm::distance(b, g));
	
	bamf::Astar<glm::vec2, float, Hashit<glm::vec2>> astar(&graph);
	
	std::function< float(glm::vec2, glm::vec2) > f(dist);
	
	bamf::Path<glm::vec2> * p = astar.search(o, g, f);
	
	assert(p->value == o);
	assert(p->next->value == b);
	assert(p->next->next->value == g);
	
	return 0;
*/	
	bamf::CollisionRectangle rectangle(glm::vec2(0.0f,300.0f),100.0f,350.0f);
	bamf::CollisionRectangle rectangle2(glm::vec2(0.0f,-300.0f),1000.0f,100.0f);

	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/art/character/front.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite);
	
	bamf::Rectangle bounds(0, 0, 1000, 100);
	bamf::Sprite red("Resources/art/ground.png");
	red.load(man);
	red.setHotspot(red.getBounds().getCenter());
	bamf::SpriteObject redSprite(&red);
	
	bamf::Scene * scene = createScene(man);
	//scene.addObjectWithZValue(&redSprite, bamf::Scene::kForegroundMidLayer);
	scene->addObjectWithZValue(&spriteSprite, bamf::Scene::kForegroundMidLayer);
	//scene.addObjectWithZValue(&chSprite, bamf::Scene::kForegroundNearLayer);
	//scene.addObjectWithZValue(&bgSprite, bamf::Scene::kBackgroundLayer);
	
	redSprite.setPosition(glm::vec2(0, -300));
	
	bamf::SynchronousGameLoop * gameLoop = new bamf::SynchronousGameLoop();
	
	bamf::CoreModule * core = gameLoop->getCoreModule();
	bamf::SceneManager * sm = core->getSceneManager();
	
	sm->pushScene(scene);
	
	bamf::InputManager inputManager;
	bamf::InputMapping inputMapping;

#if 0
	inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, 1000 * 0.016, 0, gameLoop->.getCamera()));
	inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -1000 * 0.016, 0, graphicsModule.getCamera()));
	inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, 1000 * 0.016, graphicsModule.getCamera()));
	inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -1000 * 0.016, graphicsModule.getCamera()));
#endif

    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_w, &spriteSprite, 0, 1));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_d, &spriteSprite, 1, 0));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_s, &spriteSprite, 0, -1));
    inputMapping.addKeyMapping(new MoveActorButtons(SDLK_a, &spriteSprite, -1, 0));

    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);

	/* Collision Circle Test */
    bamf::PhysicsWorld pw;
#if 0
    r.setPositon(rectangle.getPosition());
    r.setForce(glm::vec2(0,-.005));
    r2.setPositon(rectangle2.getPosition());
    rectangle.setRigidBody(&r);
    rectangle2.setRigidBody(&r2);
    pw.addObject(&rectangle);
    pw.addObject(&rectangle2);
#endif
	bamf::CollisionModule collisionModule;
    
	//collisionModule.addCollidable(rectangle);
    //collisionModule.addCollidable(rectangle2);

	gameLoop->addModule(&pw);
	gameLoop->addModule(&collisionModule);
    
    gameLoop->addModule(new bamf::NetworkingModule());
	
	gameLoop->start();
	
	return 0;
}
