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
#include "CollisionShape.h"
#include "CollisionRectangle.h"
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
	bamf::RigidBody r;
	bamf::RigidBody r2;

	bamf::ResourceManager man;
	bamf::Sprite sprite("Resources/mage.png");
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	bamf::SpriteObject spriteSprite(&sprite, &r);
	bamf::Rectangle bounds(0, 0, 1000, 100);
	bamf::Sprite red("Resources/bg.png", &bounds);
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
	
	#if 0
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_RIGHT, 1000 * 0.016, 0, gameLoop->.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_LEFT, -1000 * 0.016, 0, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_UP, 0, 1000 * 0.016, graphicsModule.getCamera()));
    inputMapping.addKeyMapping(new MoveCameraButtons(SDLK_DOWN, 0, -1000 * 0.016, graphicsModule.getCamera()));
    #endif
	
    inputManager.setInputMapping(&inputMapping);
	gameLoop->addModule(&inputManager);
	
	/* Collision Circle Test */
    
    bamf::PhysicsWorld pw;
    bamf::CollisionRectangle rectangle(glm::vec2(0.0f,300.0f),sprite.getBounds().width,sprite.getBounds().height);
	bamf::CollisionRectangle rectangle2(glm::vec2(0.0f,-300.0f),1000.0f,100.0f);
   // rectangle2.checkCollision(rectangle);
    r.setPositon(rectangle.getPosition());
    r.setForce(glm::vec2(0,-.005));
    r2.setPositon(rectangle2.getPosition());
    rectangle.setRigidBody(&r);
    rectangle2.setRigidBody(&r2);
    
   // std::cout << "collision: " << rectangle.checkCollision(rectangle2) << "\n";
    
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
