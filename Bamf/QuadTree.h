//
//  QuadTree.h
//  Bamf
//
//  Created by Matthew Hinkle on 3/9/13.
//
//

#ifndef __Bamf__QuadTree__
#define __Bamf__QuadTree__

#include <cassert>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Aabb.h"

namespace bamf {

enum {
	kQuadTreeNW = 0,
	kQuadTreeNE,
	kQuadTreeSW,
	kQuadTreeSE
};

enum {
	kQuadTreeDefaultCapacity = 5,
	kQuadTreeChildrenCount = 4
};

template<
	typename T,
	typename R = float,
	typename Hash = std::hash<T>
> class QuadTree {
public:

	explicit QuadTree(const Aabb<R> & aabb, unsigned capacity = kQuadTreeDefaultCapacity);
	virtual ~QuadTree();
	
	inline unsigned getCapacity() const { return this->capacity; }
	
	unsigned getObjectsIntersectingAabb(const Aabb<R> & aabb, std::unordered_set<T, Hash> & out);
	
	void resize(const Aabb<R> & aabb, unsigned capacity = kQuadTreeDefaultCapacity);
	
	void insert(T object, const Aabb<R> & aabb);
	void remove(T object);
	void update(T object, const Aabb<R> & aabb);

private:
	void divide();
	void collapse();
	void populateWithIntersections(QuadTree<T, R, Hash> * t);
	
	unsigned getObjectPairsIntersectingAabb(const Aabb<R> & aabb, std::vector<std::pair<T, Aabb<R>>> & out);
	
	inline Aabb<R> * aabbByObject(T object) {
		typename std::unordered_map<T, R, Hash>::const_iterator i = this->objects.find(object);
		
		return i == this->objects.end() ? NULL : &i->second;
	}

	Aabb<R> aabb;
	std::unordered_map<T, Aabb<R>, Hash> objects;
	unsigned capacity;
	
	QuadTree<T, R, Hash> * children[kQuadTreeChildrenCount] = { NULL };

	QuadTree(const QuadTree<T, R, Hash> &);
	QuadTree<T, R, Hash> & operator=(const QuadTree<T, R, Hash> &);
};

template<
	typename T,
	typename R,
	typename Hash
> QuadTree<T, R, Hash>::QuadTree(const Aabb<R> & aabb, unsigned capacity)
	:
	aabb(aabb),
	objects(),
	capacity(capacity)
{ }

template<
	typename T,
	typename R,
	typename Hash
> QuadTree<T, R, Hash>::~QuadTree()
{
	for(QuadTree<T, R, Hash> *& t : this->children) {
		if(t) {
			delete t;
			t = NULL;
		}
	}
}

template<
	typename T,
	typename R,
	typename Hash
> unsigned QuadTree<T, R, Hash>::getObjectsIntersectingAabb(const Aabb<R> & aabb, std::unordered_set<T, Hash> & out)
{
	if(!(this->aabb.intersects(aabb))) {
		return 0;
	}
	
	if(!(this->children[kQuadTreeNW])) {
		assert(!(this->children[kQuadTreeNE] || this->children[kQuadTreeSW] || this->children[kQuadTreeSE]));
		
		unsigned int insertions = 0;
		for(std::pair<T, Aabb<R>> p : this->objects) {
			if(p.second.intersects(aabb)) {
				out.insert(p.first);
				insertions++;
			}
		}
		
		return insertions;
	}
	
	std::unordered_set<T, Hash> objects;
	for(QuadTree<T, R, Hash> * t : this->children) {
		assert(t);
		t->getObjectsIntersectingAabb(aabb, objects);
	}
	
	for(T object : objects) {
		out.insert(object);
	}
	
	return static_cast<unsigned>(objects.size());
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::resize(const Aabb<R> & aabb, unsigned capacity)
{
	std::vector<std::pair<T, Aabb<R>>> pairs;
	this->getObjectPairsIntersectingAabb(aabb, pairs);
	
	for(QuadTree<T, R, Hash> *& t : this->children) {
		if(t) {
			delete t;
			t = NULL;
		}
	}
	
	this->objects.clear();
	
	this->aabb = aabb;
	this->capacity = capacity;
	
	for(std::pair<T, Aabb<R>> p : pairs) {
		this->insert(p.first, p.second);
	}
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::insert(T object, const Aabb<R> & aabb)
{
	if(!(this->aabb.intersects(aabb))) {
		return;
	}
	
	if(!(this->children[kQuadTreeNW])) {
		assert(!(this->children[kQuadTreeNE] || this->children[kQuadTreeSW] || this->children[kQuadTreeSE]));
		
		this->objects.insert(std::pair<T, Aabb<R>>(object, aabb));
		if(this->objects.size() >= this->capacity) {
			this->divide();
		}
	} else {
		for(QuadTree<T, R, Hash> * t : this->children) {
			assert(t);
			t->insert(object, aabb);
		}
	}
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::remove(T object)
{
	if(!(this->aabb.intersects(aabb))) {
		return;
	}

	if(!(this->children[kQuadTreeNW])) {
		assert(!(this->children[kQuadTreeNE] || this->children[kQuadTreeSW] || this->children[kQuadTreeSE]));
		
		this->objects.erase(object);
	} else {
		for(QuadTree<T, R, Hash> * t : this->children) {
			assert(t);
			t->remove(object);
		}
	}
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::update(T object, const Aabb<R> & aabb)
{	
	if(!(this->children[kQuadTreeNW])) {
		assert(!(this->children[kQuadTreeNE] || this->children[kQuadTreeSW] || this->children[kQuadTreeSE]));
		
		this->objects.erase(object);
		
		if(this->aabb.intersects(aabb)) {
			this->insert(object, aabb);
		}
	} else {
		for(QuadTree<T, R, Hash> * t : this->children) {
			assert(t);
			t->update(object, aabb);
		}
	}
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::divide()
{
	const std::pair<R, R> center(this->aabb.getCenter());
	
	const Aabb<R> nwAabb(
		this->aabb.xMin, center.second,
		center.first, this->aabb.yMax
	);
	this->children[kQuadTreeNW] = new QuadTree<T, R, Hash>(nwAabb, this->capacity);
	
	const Aabb<R> neAabb(
		center.first, center.second,
		this->aabb.xMax, this->aabb.yMax
	);
	this->children[kQuadTreeNE] = new QuadTree<T, R, Hash>(neAabb, this->capacity);
	
	const Aabb<R> swAabb(
		this->aabb.xMin, this->aabb.yMin,
		center.first, center.second
	);
	this->children[kQuadTreeSW] = new QuadTree<T, R, Hash>(swAabb, this->capacity);
	
	const Aabb<R> seAabb(
		center.first, this->aabb.yMin,
		this->aabb.xMax, center.second
	);
	this->children[kQuadTreeSE] = new QuadTree<T, R, Hash>(seAabb, this->capacity);
	
	for(QuadTree<T, R, Hash> * t : this->children) {
		this->populateWithIntersections(t);
	}
	
	this->objects.clear();
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::collapse()
{
	for(QuadTree * t : this->children) {
		this->objects.insert(t->objects.begin(), t->objects.end());
	}
}

template<
	typename T,
	typename R,
	typename Hash
> void QuadTree<T, R, Hash>::populateWithIntersections(QuadTree<T, R, Hash> * t)
{
	typename std::unordered_map<T, Aabb<R>, Hash>::const_iterator i;
	for(i = this->objects.begin(); i != this->objects.end(); i++) {
		if(t->aabb.intersects(i->second)) {
			t->objects.insert(*i);
		}
	}
}

template<
	typename T,
	typename R,
	typename Hash
> unsigned QuadTree<T, R, Hash>::getObjectPairsIntersectingAabb(const Aabb<R> & aabb, std::vector<std::pair<T, Aabb<R>>> & out)
{
	if(!(this->aabb.intersects(aabb))) {
		return 0;
	}
	
	if(!(this->children[kQuadTreeNW])) {
		assert(!(this->children[kQuadTreeNE] || this->children[kQuadTreeSW] || this->children[kQuadTreeSE]));
		
		for(std::pair<T, Aabb<R>> p : this->objects) {
			out.push_back(p);
		}
		
		return static_cast<unsigned>(this->objects.size());
	}
	
	unsigned sum = 0;
	std::vector<std::pair<T, Aabb<R>>> objects;
	for(QuadTree<T, R, Hash> * t : this->children) {
		assert(t);
		sum += t->getObjectPairsIntersectingAabb(aabb, objects);
	}
	
	for(std::pair<T, Aabb<R>> p : objects) {
		out.push_back(p);
	}
	
	return sum;
}

}

#endif /* defined(__Bamf__QuadTree__) */
