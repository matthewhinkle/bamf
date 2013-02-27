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

	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite, &r);
	
	bamf::Rectangle bounds(0, 0, 1096, 200);
	bamf::Sprite red("Resources/green.png", &bounds);
	red.load(man);
	red.setHotspot(red.getBounds().getCenter());
	bamf::SpriteObject redSprite(&red, &r2);
	
	
	
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
	
	/**
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, 1000 * 0.016, 0, gameLoop->.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -1000 * 0.016, 0, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, 1000 * 0.016, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -1000 * 0.016, graphicsModule.getCamera()));
	*/
	
    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);
	
	// Collision Circle Test
    bamf::CollisionCircle c1(glm::vec2(0,2), 2);
    bamf::CollisionCircle c2(glm::vec2(1,50), 100);
    c1.checkCollision(c2);
    c2.checkCollision(c1);
	r.setForce(glm::vec2(0, -1));
    c2.setRigidBody(&r);
    bamf::PhysicsWorld pw(1);
	
    bamf::CollisionRectangle rectangle(glm::vec2(-548,-200),glm::vec2(548,-400));
	
    rectangle.setRigidBody(&r2);
	r2.setPositon(glm::vec2(0, -200));
    pw.addObject(c2);
    pw.addObject(rectangle);
	
	bamf::CollisionModule collisionModule;
	
	gameLoop->addModule(&pw);
	gameLoop->addModule(&collisionModule);
	
	gameLoop->start();
	
	return 0;
}
