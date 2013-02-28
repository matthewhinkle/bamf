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

int main(int argc, char *argv[])
{
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
	bamf::RigidBody r;
	bamf::RigidBody r2;
	
	bamf::CollisionRectangle rectangle(glm::vec2(0.0f,300.0f),100.0f,350.0f);
	
	bamf::CollisionRectangle rectangle2(glm::vec2(0.0f,-300.0f),1000.0f,100.0f);

	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite, &rectangle);
	
	bamf::Rectangle bounds(0, 0, 1000, 100);
	bamf::Sprite red("Resources/green.png", &bounds);
	red.load(man);
	red.setHotspot(red.getBounds().getCenter());
	bamf::SpriteObject redSprite(&red, &rectangle2);
	
	bamf::Scene scene;
	scene.addObjectWithZValue(&spriteSprite, bamf::Scene::kForegroundMidLayer);
	scene.addObjectWithZValue(&redSprite, bamf::Scene::kForegroundMidLayer);
	//scene.addObjectWithZValue(&chSprite, bamf::Scene::kForegroundNearLayer);
	//scene.addObjectWithZValue(&bgSprite, bamf::Scene::kBackgroundLayer);
	
	bamf::SynchronousGameLoop * gameLoop = new bamf::SynchronousGameLoop();
	
	bamf::CoreModule * core = gameLoop->getCoreModule();
	bamf::SceneManager * sm = core->getSceneManager();
	
	sm->pushScene(&scene);
	
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
	
	spriteSprite.setCollisionShape(&rectangle);
	redSprite.setCollisionShape(&rectangle2);

    r.setPositon(rectangle.getPosition());
    r.setForce(glm::vec2(0,-.005));
    r2.setPositon(rectangle2.getPosition());
    rectangle.setRigidBody(&r);
    rectangle2.setRigidBody(&r2);
    pw.addObject(&rectangle);
    pw.addObject(&rectangle2);

	bamf::CollisionModule collisionModule;
    
	//collisionModule.addCollidable(rectangle);
    //collisionModule.addCollidable(rectangle2);

	gameLoop->addModule(&pw);
	gameLoop->addModule(&collisionModule);
	
	gameLoop->start();
	
	return 0;
}
