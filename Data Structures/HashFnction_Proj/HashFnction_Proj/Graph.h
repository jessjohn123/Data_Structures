#pragma once
#include "SLList.h"
#include "DynArray.h"
#include <queue>

template <typename Type>
class Graph
{
	
	public:
	struct Edge
	{
		unsigned int toVertex;
	};

	struct Vertex
	{
		Type element;
		SLList<Edge> edges;
		void addEdge(const unsigned int & toVertex)
		{
			Edge obj;
			obj.toVertex = toVertex;
			edges.addHead(obj);
		}
	};
private:
	DynArray<Vertex>arr_vertex;
public:
	unsigned int addVertex(const Type& value);
	Vertex& operator[] (const unsigned int& index);
	unsigned int size() const;
	void clear();
	void printBreadthFirst(const unsigned int& startVertex);
};

template <typename Type>
typename Graph<Type>::Vertex& Graph<Type>::operator[](const unsigned int& index)
{
	return arr_vertex[index];
}

template<typename Type>
unsigned int Graph<Type>::size() const
{
	return arr_vertex.size();
}

template<typename Type>
unsigned int Graph<Type>::addVertex(const Type& value)
{
	Vertex obj;
	obj.element = value;
	arr_vertex.append(obj);
	return(arr_vertex.size() - 1);
}

template<typename Type>
void Graph<Type>::clear()
{
	arr_vertex.clear();
}

template<typename Type>
void Graph<Type>::printBreadthFirst(const unsigned int& startVertex)
{
	queue<unsigned int> que;

	DynArray<unsigned int> obj;

	int *temp = new int[arr_vertex.size()];
	for (unsigned int i = 0; i < arr_vertex.size(); i++)
	{
		temp[i] = -1;
	}
	temp[startVertex] = 0;
	bool check = false;

	que.push(startVertex);
	obj.append(startVertex);

	while (!que.empty())
	{
		unsigned int tmp = que.front();
		//check[startVertex] = true;
		que.pop();
		SLLIter<Edge>iter(arr_vertex[tmp].edges);
		for (iter.begin(); !iter.end(); ++iter)
		{
			check = false;
			for (unsigned int j = 0; j < obj.size(); j++)
			{
				if (iter.current().toVertex == obj[j])
				{
					check = true;
				}
			}
			if (check == false)
			{
			que.push(iter.current().toVertex);
			obj.append(iter.current().toVertex);
			temp[iter.current().toVertex] = temp[tmp] + 1;
			}
		}
 		cout << arr_vertex[tmp].element << " : " << temp[tmp] << "\n";
	}
	delete[] temp;
}

