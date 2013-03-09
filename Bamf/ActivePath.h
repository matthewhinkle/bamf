//
//  ActivePath.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/7/13.
//
//

#ifndef __Bamf__ActivePath__
#define __Bamf__ActivePath__

#include "Graph.h"

namespace bamf {

template<typename T>
class ActivePath {
public:

	ActivePath(Path<T> * path);
	virtual ~ActivePath();

	void resetProgress();
	
	void advanceNode();
	
	inline T getGlobalSource() const { return this->globalSource->value; }
	inline T getGlobalGoal() const { return this->globalGoal->value; }
	inline T getLocalSource() const { return this->localSource->value; }
	inline T getLocalGoal() const { return this->localGoal->value; }
	
	/**
		modifying the active path's underlying path
		results in undefined behavior
	 */
	inline Path<T> * getPath() { return this->path; }

private:
	Path<T> * findGlobalGoal();

	Path<T> * path;
	
	Path<T> * globalSource;
	Path<T> * globalGoal;
	Path<T> * localSource;
	Path<T> * localGoal;

	ActivePath(const ActivePath &);
	ActivePath & operator=(const ActivePath &);
};

template<typename T>
ActivePath<T>::ActivePath(Path<T> * path)
	:
	path(path),
	globalSource(path ? path : NULL),
	globalGoal(path ? findGlobalGoal() : NULL),
	localSource(path ? path : NULL),
	localGoal(path ? path->next : NULL)
{ }

template<typename T>
ActivePath<T>::~ActivePath() { }

template<typename T>
void ActivePath<T>::resetProgress()
{
	this->localSource = this->globalSource;
}

template<typename T>
void ActivePath<T>::advanceNode()
{
	this->localSource = this->localGoal;
	
	if(this->localSource == this->globalGoal) {
		/**
			leave the localSource the same as the localGoal as we
			have reached our destination
		 */
		return;
	}
	
	this->localGoal = this->localSource->next;
}

template<typename T>
Path<T> * ActivePath<T>::findGlobalGoal()
{
	for(Path<T> * p = this->path; p; p = p->next) {
		if(!(p->next)) {
			return p;
		}
	}
	
	return NULL;
}
	
}

#endif /* defined(__Bamf__ActivePath__) */
