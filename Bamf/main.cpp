//
//  main.m
//  Bamf
//
//  Created by Matthew Hinkle on 1/31/13.
//
//

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
#include "CollisionModule.h"
#include "PhysicsWorld.h"

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

int main(int argc, char *argv[])
{
	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite);

	bamf::Scene scene;
	scene.addObjectWithZValue(&spriteSprite, bamf::Scene::kForegroundMidLayer);
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
    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);
	
	
	/* Collision Circle Test */
    bamf::CollisionCircle c1(glm::vec2(0,2), 2);
    bamf::CollisionCircle c2(glm::vec2(0,5), 1);
    c1.checkCollision(c2);
    c2.checkCollision(c1);
    bamf::RigidBody r;
    r.setForce(glm::vec2(0,1));
    c2.setRigidBody(r);
    bamf::PhysicsWorld pw(1);
    pw.addObject(c2);
	
	bamf::CollisionModule collisionModule;
	
	gameLoop->addModule(&pw);
	gameLoop->addModule(&collisionModule);
	
	gameLoop->start();
	
	return 0;
}
