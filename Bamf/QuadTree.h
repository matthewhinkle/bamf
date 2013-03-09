//
//  QuadTree.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#ifndef __Bamf__QuadTree__
#define __Bamf__QuadTree__

#include <utility>
#include <vector>

#include "Aabb.h"

namespace bamf {

template<
	typename T,
	typename R = float
> class QuadTree {
public:

	explicit QuadTree(const Aabb<R> & aabb, unsigned capacity = 5);
	virtual ~QuadTree();
	
	inline unsigned getCapacity() const { return this->capacity; }
	
	void getObjectsIntersectingAabb(const Aabb<R> & aabb, std::vector<T> & objects);
	
	void insert(T object, const Aabb<R> & aabb);

private:	
	void divide();
	void collapse();
	void populateWithIntersections(QuadTree<T, R> * t);

	Aabb<R> & aabb;
	std::vector<std::pair<T, Aabb<R>>> objects;
	unsigned capacity;
	
	QuadTree<T, R> * nw;
	QuadTree<T, R> * ne;
	QuadTree<T, R> * sw;
	QuadTree<T, R> * se;

	QuadTree(const QuadTree<T, R> &);
	QuadTree<T, R> & operator=(const QuadTree<T, R> &);
};

template<
	typename T,
	typename R
> QuadTree<T, R>::QuadTree(const Aabb<R> & aabb, unsigned capacity)
	:
	aabb(aabb),
	objects(),
	capacity(capacity),
	nw(NULL),
	ne(NULL),
	sw(NULL),
	se(NULL)
{ }

template<
	typename T,
	typename R
> QuadTree<T, R>::~QuadTree()
{
	if(this->nw) {
		delete this->nw;
		this->nw = NULL;
	}
	
	if(this->ne) {
		delete this->ne;
		this->ne = NULL;
	}
	
	if(this->sw) {
		delete this->sw;
		this->sw = NULL;
	}
	
	if(this->se) {
		delete this->se;
		this->se = NULL;
	}
}

template<
	typename T,
	typename R
> void QuadTree<T, R>::divide()
{
	const std::pair<R, R> center = this->aabb->getCenter();
	
	const Aabb<R> nwAabb(
		this->aabb.xMin, center.second,
		center.first, this->aabb.yMax
	);
	this->nw = new QuadTree<T, R>(nwAabb, this->capacity);
	this->populateWithIntersections(this->nw);
	
	const Aabb<R> neAabb(
		center.first, center.second,
		this->xMax, this->yMax
	);
	this->ne = new QuadTree<T, R>(neAabb, this->capacity);
	this->populateWithIntersections(this->ne);
	
	const Aabb<R> swAabb(
		this->xMin, this->yMin,
		center.first, center.second
	);
	this->sw = new QuadTree<T, R>(swAabb, this->capacity);
	this->populateWithIntersections(this->sw);
	
	const Aabb<R> seAabb(
		center.first, this->yMin,
		this->xMax, center.second
	);
	this->se = new QuadTree<T, R>(seAabb, this->capacity);
	this->populateWithIntersections(seAabb);
}

template<
	typename T,
	typename R
> void QuadTree<T, R>::collapse()
{
}

template<
	typename T,
	typename R
> void QuadTree<T, R>::populateWithIntersections(QuadTree<T, R> * t)
{
	typename std::vector<std::pair<T, Aabb<R>>>::const_iterator i;
	for(i = this->objects.begin(); i != this->objects.end(); i++) {
		if(t->aabb.intersects((*i)->second)) {
			t->objects.insert(i);
		}
	}
}

}

#endif /* defined(__Bamf__QuadTree__) */
