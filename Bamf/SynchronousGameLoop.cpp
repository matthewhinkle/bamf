//
//  SynchronousGameLoop.cpp
//  Bamf
//
//  Created by Matthew Hinkle on 2/1/13.
//
//

#include "SynchronousGameLoop.h"

#include "Lerp.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "SpriteStream.h"
#include "GraphicsModule.h"
#include "CollisionCircle.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"

glm::vec2 prev;
bamf::Sprite sprite("/bamf/mage.png");
bamf::Sprite crosshair("/bamf/crosshair.png");

namespace bamf {

SynchronousGameLoop::SynchronousGameLoop(GraphicsModule * graphicsModule)
	:
	running(false),
	suspended(false),
	suspendMutex(SDL_CreateMutex()),
	suspendCond(SDL_CreateCond()),
	graphicsModule(graphicsModule),
	dt(0.016),
	maxDtFrame(60),
	time(0)
{ }

SynchronousGameLoop::~SynchronousGameLoop()
{
	if(this->suspendMutex) {
		SDL_DestroyMutex(this->suspendMutex);
		this->suspendMutex = NULL;
	}
	
	if(this->suspendCond) {
		SDL_DestroyCond(this->suspendCond);
		this->suspendCond = NULL;
	}
}

void SynchronousGameLoop::removeModule(Module * module)
{
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		if(*modIt == module) {
			this->modules.erase(modIt);
			
			return;
		}
	}
}

void SynchronousGameLoop::restart()
{
	this->stop();
	this->start();
}

void SynchronousGameLoop::start()
{
	if(__sync_bool_compare_and_swap(&this->running, false, true)) {
		this->run();
	} else if(this->suspended) {
		this->suspended = false;
		SDL_CondSignal(this->suspendCond);
	}
}

void SynchronousGameLoop::stop()
{
	if(!(__sync_bool_compare_and_swap(&this->running, true, false))) {
		/* game loop is not currently running */
		return;
	}
}

void SynchronousGameLoop::suspend()
{
	this->suspended = true;
}
	
float SynchronousGameLoop::update(float epoch)
{
	for(; epoch >= this->dt; epoch -= this->dt, this->time += this->dt) {
		std::vector<Module *>::iterator modIt;
		for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
			(*modIt)->update(this->dt);
			prev = this->graphicsModule->getCamera()->getPosition();
		}
	}
		
	return epoch > 0.0f ? epoch : 0.0f;
}

void SynchronousGameLoop::draw(unsigned delta) {
	/* temp draw code */
	SpriteStream * ss = this->graphicsModule->getSpriteStream();
	
	this->graphicsModule->update(delta);
	
	ss->begin(this->graphicsModule->getCamera()->computeTransform(), bamf::kSpriteStreamClipEdges | bamf::kSpriteStreamEnforceDrawOrder);
	for(int i = 0; i < 300; i++) {
		for(int j = 0; j < 200; j++) {
			ss->draw(&sprite, glm::vec2(i * 200, j * 300));
		}
	}
	ss->draw(&crosshair, this->graphicsModule->getCamera()->getPosition());
	ss->end();
}

int SynchronousGameLoop::run()
{
	/* temp development code */
	ResourceManager man;
	sprite.load(man);
	sprite.setHotspot(sprite.getBounds().getCenter());
	
	crosshair.load(man);
	crosshair.setHotspot(crosshair.getBounds().getCenter());
	
    /* Collision Circle Test */
    /*CollisionCircle c1(glm::vec2(0,2), 2);
    CollisionCircle c2(glm::vec2(0,5), 1);    
    c1.checkCollision(c2);
    c2.checkCollision(c1);
    RigidBody r;
    r.setForce(glm::vec2(0,1));
    c2.setRigidBody(r);
    PhysicsWorld pw(0);
    pw.addObject(c2);*/
    
	/* actual code */
	std::vector<Module *>::iterator modIt;
	for(modIt = this->modules.begin(); modIt != this->modules.end(); modIt++) {
		(*modIt)->init();
	}
	
	Camera * cam = graphicsModule->getCamera();
	prev = graphicsModule->getCamera()->getPosition();
	
	unsigned timeLastTicked = SDL_GetTicks();
	float epoch = 0;
	while(this->running) {
		while(this->running && this->suspended) {
			SDL_CondWait(this->suspendCond, this->suspendMutex);
		}
			
		if(!(this->running)) {
			/* do not execute another iteration if we stopped while suspended */
			continue;
		}
		
		//cam->setPosition(glm::vec2(cam->getPosition().x + 5, cam->getPosition().y + 5));
		
		unsigned time = SDL_GetTicks();
		
		printf("fps = %f\n", 1000.0f / (time - timeLastTicked));
		
		unsigned dtFrame = glm::min(time - timeLastTicked, maxDtFrame);
		timeLastTicked = time;

		/* interpolate */
		//pw.update();
		
		epoch += dtFrame / 1000.0f;
		epoch = this->update(epoch);
		
		glm::vec2 pos = Lerp::lerp(prev, cam->getPosition(), epoch, dt);
		
		//printf("new = %f, %f\n", pos.x, pos.y);
		//prev = pos;
		//cam->setPosition(pos);
		
		this->draw(this->dt);
	}
		return 0;
}

}
