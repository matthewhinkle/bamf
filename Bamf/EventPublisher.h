//
//  EventPublisher.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/8/13.
//
//

#ifndef Bamf_EventPublisher_h
#define Bamf_EventPublisher_h

#include <unordered_map>

#include "Event.h"

namespace bamf {

template <
	typename Sender,
	typename Message
> class EventPublisher {
public:

	EventPublisher(Sender sender);
	virtual ~EventPublisher();
	
	uint64_t subscribe(const std::function<void (Event<Sender, Message> *)> & onPublish);
	
	void unsubscribe(uint64_t subscriberId);
	
	void publish(Message message);

private:
	Sender sender;
	std::unordered_map<uint64_t, std::function<void (Event<Sender, Message> *)>> subscriberById;

	uint64_t nextSubscriberId;

	EventPublisher(const EventPublisher &);
	EventPublisher & operator=(const EventPublisher &);
};

template <
	typename Sender,
	typename Message
> EventPublisher<Sender, Message>::EventPublisher(Sender sender)
	:
	sender(sender),
	subscriberById(),
	nextSubscriberId(0)
{ }

template <
	typename Sender,
	typename Message
> EventPublisher<Sender, Message>::~EventPublisher() { }

template <
	typename Sender,
	typename Message
> uint64_t EventPublisher<Sender, Message>::subscribe(const std::function<void (Event<Sender, Message> *)> & onPublish)
{
	uint64_t id = __sync_fetch_and_add(&this->nextSubscriberId, 1);
	this->subscriberById.insert(std::pair<uint64_t, std::function<void (Event<Sender, Message> *)>>(id, onPublish));
	
	return id;
}

template <
	typename Sender,
	typename Message
> void EventPublisher<Sender, Message>::unsubscribe(uint64_t subscriberId)
{
	typename std::unordered_map<uint64_t, std::function<void (Event<Sender, Message> *)>>::const_iterator i = this->subscriberById.find(subscriberId);
	if(i != this->subscriberById.end()) {
		this->subscriberById.erase(i);
	}
}

template <
	typename Sender,
	typename Message
> void EventPublisher<Sender, Message>::publish(Message message)
{
	Event<Sender, Message> event(this->sender, message);
	Event<Sender, Message> * e = &event;
	typename std::unordered_map<uint64_t, std::function<void (Event<Sender, Message> *)>>::iterator i;
	for(i = this->subscriberById.begin(); i != this->subscriberById.end(); i++) {
		i->second(e);
	}
}

}

#endif
