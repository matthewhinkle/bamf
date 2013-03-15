//
//  Graph.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/25/13.
//
//

#ifndef __Bamf__Graph__
#define __Bamf__Graph__

#include <unordered_map>
#include <vector>

namespace bamf {

template<
	typename T,
	typename R
> struct Edge {
public:

	Edge(T value, R weight)
		:
		value(value),
		weight(weight)
	{ }
	
	virtual ~Edge() { }

	T value;
	R weight;
};

template<typename T> struct Path {
public:

	Path(T value, Path<T> * previous = NULL, Path<T> * next = NULL)
		:
		value(value),
		previous(previous),
		next(next)
	{ }
	
	virtual ~Path() {
		Path * p = this->previous;
		while(p) {
			Path * tmp = p;
			p = p->previous;
			delete tmp;
			tmp = NULL;
		}

		p = this->next;
		while(p) {
			Path * tmp = p;
			p = p->next;
			delete tmp;
			tmp = NULL;
		}
	}

	T value;
	Path * previous;
	Path * next;
};

template<
	typename T,
	typename R,
	typename Hash
> class Graph {
public:

	Graph();
	virtual ~Graph();

	void addEdge(T v, T u, R weight);

	std::pair<
		typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator,
		typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator
	> getEdges(T v);
	
	inline void clear() { this->edges.clear(); }
	
	void foreachEdge(std::function<void (T, Edge<T, R> *)> & doFunc);

private:
	std::unordered_multimap<T, Edge<T, R>, Hash> edges;

	Graph(const Graph &);
	Graph & operator=(const Graph &);
};

template<
	typename T,
	typename R,
	typename Hash
> Graph<T, R, Hash>::Graph()
	:
	edges()
{ }

template<
	typename T,
	typename R,
	typename Hash
> Graph<T, R, Hash>::~Graph()
{
	this->edges.clear();
}

template<
	typename T,
	typename R,
	typename Hash
> void Graph<T, R, Hash>::addEdge(T v, T u, R weight)
{
	Edge<T, R> edge(u, weight);
	this->edges.insert(std::pair<T, Edge<T, R>>(v, edge));
}

template<
	typename T,
	typename R,
	typename Hash
> std::pair<
		typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator,
		typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator
> Graph<T, R, Hash>::getEdges(T v)
{
	return this->edges.equal_range(v);
}

template <
	typename T,
	typename R,
	typename Hash
> void Graph<T, R, Hash>::foreachEdge(std::function<void (T, Edge<T, R> *)> & doFunc)
{
	typename std::unordered_multimap<T, Edge<T, R>, Hash>::iterator i;
	for(i = this->edges.begin(); i != this->edges.end(); i++) {
		doFunc(i->first, &i->second);
	}
}

}

#endif /* defined(__Bamf__Graph__) */
