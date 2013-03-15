//
//  Astar.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/25/13.
//
//

#ifndef Bamf_Astar_h
#define Bamf_Astar_h

#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "Graph.h"

namespace bamf {

template<
	typename T,
	typename R
> struct VertexInfo {
public:
	VertexInfo(T & value, R h, R g, VertexInfo<T, R> * parent = NULL)
		:
		value(value),
		h(h),
		g(g),
		parent(parent)
	{ }

	VertexInfo<T, R> * parent;
	
	T value;
	R h;
	R g;
};

template<typename T> class VertexCmp;

template<
	typename T,
	typename R
> class VertexCmp<VertexInfo<T, R> *> {
public:
	bool operator()(const VertexInfo<T, R> * v1, const VertexInfo<T, R> * v2) { return (v1->h + v1->g) == (v2->h + v2->g); }
};

template<
	typename T,
	typename R,
	typename Hash
> class Astar {
public:

	explicit Astar(Graph<T, R, Hash> * g);
	virtual ~Astar();

	inline Graph<T, R, Hash> * getGraph() const { return this->graph; }

	bool search(T start, T goal, std::function< R(T, T) > & dist, std::stack<T> & path);

private:
	Graph<T, R, Hash> * graph;
	std::unordered_map<T, VertexInfo<T, R> *, Hash> infos;
	
	R g(T v);
	R h(T v);
	R f(T v);
	
	void insert(T v, VertexInfo<T, R> * info);
	VertexInfo<T, R> * find(T v);
	bool makePath(VertexInfo<T, R> * info, std::stack<T> & path);

	Astar(const Astar &);
	Astar & operator=(const Astar &);
};

template<
	typename T,
	typename R,
	typename Hash
> Astar<T, R, Hash>::Astar(Graph<T, R, Hash> * g)
	:
	graph(g)
{ }

template<
	typename T,
	typename R,
	typename Hash
> Astar<T, R, Hash>::~Astar()
{
	std::for_each(this->infos.begin(), this->infos.end(),
		[=](std::pair<T, VertexInfo<T, R> *> i) {
			if(i.second) {
				delete i.second;
				i.second = NULL;
			}
		}
	);
	
	this->infos.clear();
}

template<
	typename T,
	typename R,
	typename Hash
> bool Astar<T, R, Hash>::search(T start, T goal, std::function< R(T, T) > & dist, std::stack<T> & path)
{
	if(!(this->graph)) return false;

	std::priority_queue<VertexInfo<T, R> *, std::vector<VertexInfo<T, R> *>, VertexCmp<VertexInfo<T, R> *>> open;

	VertexInfo<T, R> * startInfo = new VertexInfo<T, R>(start, dist(start, goal), dist(start, start));
	this->insert(start, startInfo);
	open.push(startInfo);
	
	while(!(open.empty())) {
		VertexInfo<T, R> * parentInfo = open.top();
		open.pop();
		
		T v = parentInfo->value;
		
		if(v == goal) {
			return this->makePath(parentInfo, path);
		}
		
		std::pair<
			typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator,
			typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator
		> edges = this->graph->getEdges(v);
		
		typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator i;
		
		for(i = edges.first; i != edges.second; i++) {
			Edge<T, R> e = i->second;
			T u = e.value;
			
			R g = this->g(v) + e.weight;
			R h = dist(u, goal);
			
			VertexInfo<T, R> * info = this->find(u);
			if(info && g + h < info->g + info->h) {
				info->parent = parentInfo;
				info->g = g;
				info->h = h;
			} else if(!(info)) {
				VertexInfo<T, R> * newInfo = new VertexInfo<T, R>(u, h, g, parentInfo);
				open.push(newInfo);
				this->insert(u, newInfo);
			}
		}
	}

	return false;
}

template<
	typename T,
	typename R,
	typename Hash
> bool Astar<T, R, Hash>::makePath(VertexInfo<T, R> * info, std::stack<T> & path)
{
	if(!(info)) return false;
	
	for(; info; info = info->parent) {
		path.push(info->value);
	}
	
	return true;
}

template<
	typename T,
	typename R,
	typename Hash
> R Astar<T, R, Hash>::g(T v)
{
	VertexInfo<T, R> * info = this->find(v);
	
	return info->g;
}

template<
	typename T,
	typename R,
	typename Hash
> R Astar<T, R, Hash>::h(T v)
{
	VertexInfo<T, R> * info = this->find(v);
	
	return info->h;
}

template<
	typename T,
	typename R,
	typename Hash
> R Astar<T, R, Hash>::f(T v)
{
	return this->g(v) + this->h(v);
}

template<
	typename T,
	typename R,
	typename Hash
> void Astar<T, R, Hash>::insert(T v, VertexInfo<T, R> * info)
{
	this->infos.insert(std::pair<T, VertexInfo<T, R> *>(v, info));
}

template<
	typename T,
	typename R,
	typename Hash
> VertexInfo<T, R> * Astar<T, R, Hash>::find(T v)
{
	typename std::unordered_map<T, VertexInfo<T, R> *, Hash>::iterator i = this->infos.find(v);
	if(i == this->infos.end()) {
		return NULL;
	}
	
	return i->second;
}

}

#endif
