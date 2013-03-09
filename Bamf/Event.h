//
//  Event.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#ifndef Bamf_Event_h
#define Bamf_Event_h

#include "SDL2/SDL.h"

namespace bamf {

template<
	typename Sender,
	typename Message
> class Event {
public:

	Event(Sender sender, Message message)
		:
		message(message),
		sender(sender),
		timestamp(SDL_GetTicks())
	{ }
	
	virtual ~Event() { }
	
	inline Sender getSender() const { return this->sender; }
	inline Message getMessage() const { return this->message; }

private:
	Sender sender;
	Message message;
	unsigned timestamp;

	Event(const Event &);
	Event & operator=(const Event &);
};

}

#endif
