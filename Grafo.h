#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
using namespace std;

template <class J>
class Vertex{
public:
    J data;
    Vertex<J> *next;
    Edge<J>* firstEdge;
    Vertexe(){
        next = NULL;
        firstEdge = NULL;
    }
    Vertex(J d): data(d), next(NULL), firstEdge(NULL){}
};

template <class K>
class Edge{
public:
    Vertex<K> *destin;
    Edge<K>* next;
    int value;
    Edge(){
        destin = NULL;
        next = NULL;
    }
};

template <class T>
class Graph{
    Vertex<T>* firstVertex;

    void addVertex(T data){
        if(firstVertex == NULL){
            firstVertex = new Vertex<T>(data);
        }
    }
};

#endif // GRAFO_H
