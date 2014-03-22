#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <QDebug>
#include "../TDA/listpointert.h"

using namespace std;

template <class K>
class Edge;

template <class J>
class Vertex{
public:
    J data;
    Vertex<J> *next;
    Edge<J>* firstEdge;
    int count;
    Vertex(){
        next = NULL;
        firstEdge = NULL;
        count = 0;
    }
    Vertex(J d): data(d), next(NULL), firstEdge(NULL), count(0){}

    void addEdge(Vertex<J>* where, int value=0){
        if(where == NULL)
            return;
        addEdge(new Edge<J>(where,value));
    }

    void addEdge(Edge<J>* param){
        if(firstEdge == NULL)
            firstEdge = param;
        else{
            Edge<J>* cursor = firstEdge;
            while(cursor->next != NULL){
                cursor = cursor->next;
            }
            cursor->next = param;
        }
        updateCount();
    }

    bool hasAdyacencyWith(Vertex<J>* w){
        Edge<J>* cursor = firstEdge;
        bool found = false;
        while(cursor != NULL){
            if(cursor->destin == w)
                found = true;
            cursor = cursor->next;
        }
        return found;
    }

    bool edgeExists(Vertex<J>* w, int cost){
        Edge<J>* cursor = firstEdge;
        bool found = false;
        while(cursor != NULL){
            if(cursor->destin == w && cursor->value == cost)
                found = true;
            cursor = cursor->next;
        }
        return found;
    }

    bool edgeExists(Edge<J> *param){
        Edge<J>* cursor = firstEdge;
        bool found = false;
        while(cursor != NULL){
            if(cursor == param)
                found = true;
            cursor = cursor->next;
        }
        return found;
    }

    int indexOfEdge(Vertex<J>* w){
        Edge<J>* cursor = firstEdge;
        bool index = 0;
        while(cursor != NULL){
            if(cursor->destin == w)
                return index;
            cursor = cursor->next;
            index++;
        }
        return -1;
    }

    Edge<J>* getEdge(Vertex<J>* w){
        Edge<J>* cursor = firstEdge;
        while(cursor != NULL){
            if(cursor->destin == w)
                return cursor;
            cursor = cursor->next;
        }
        return NULL;
    }

    Edge<J>* getVertex(int index){
        Edge<J>* cursor = firstEdge;
        int current = 0;
        while(cursor != NULL){
            if(current == index)
                return cursor;
            cursor = cursor->next;
            current++;
        }
        return NULL;
    }

    void removeEdge(Edge<J>* target){
        if(target == NULL)
            return;
        if(count && edgeExists(target) ){
            if(target == firstEdge){
                firstEdge = target->next;
                target->next = NULL;
            }else{
                Edge<J>* auxBefore = firstEdge;
                while(auxBefore->next != NULL){
                    if(auxBefore->next == target){
                        auxBefore->next = target->next;
                        target->next = NULL;
                        break;
                    }
                    auxBefore = auxBefore->next;
                }
            }
        }
        updateCount();
    }

    void removeAdyaceny(Vertex<J>* with){
        removeEdge(getEdge(with));
    }

    void updateCount(){
        Edge<J>* cursor = firstEdge;
        count = 0;
        while(cursor != NULL){
            count++;
            cursor = cursor->next;
        }
    }

    void printEdgeList(){
        qDebug() << "\n" << data << "Edges count: " << count;
        Edge<J>* cursor = firstEdge;
        int i = 0;
        while(cursor != NULL){
            i++;
            qDebug() << "Edge" << i << "to Vertex:" << cursor->destin->data << " with cost:" << cursor->value;
            cursor = cursor->next;
        }
    }
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
    Edge(Vertex<K>* dest, int cost): destin(dest), next(NULL), value(cost){}
};

template <class T>
class Graph{
public:
    Vertex<T>* firstVertex;
    int count;

    Graph(){
        firstVertex = NULL;
        count = 0;
    }

    void addVertex(T data){
        if(firstVertex == NULL)
            firstVertex = new Vertex<T>(data);
        else{
            Vertex<T>* cursor = firstVertex;
            while(cursor->next != NULL){
                cursor = cursor->next;
            }
            cursor->next = new Vertex<T>(data);
        }
        updateCount();
    }

    void addConnection(T fromV, T toV, int cost){
        if(!count || !vertexExists(fromV) || !vertexExists(toV))
            return;
        getVertex(fromV)->addEdge(getVertex(toV), cost);
    }

    void removeConnection(T fromV, T with){
        if(!count || !vertexExists(fromV) || !vertexExists(with))
            return;
        getVertex(fromV)->removeAdyaceny(getVertex(with));
    }

    bool vertexExists(T data){
        Vertex<T>* cursor = firstVertex;
        bool found = false;
        while(cursor != NULL){
            if(cursor->data == data)
                found = true;
            cursor = cursor->next;
        }
        return found;
    }

    ListPointerT<T> getAllBut(T except){
        ListPointerT<T> result;
        Vertex<T>* cursor = firstVertex;
        while(cursor){
            if(cursor->data != except)
                result.insert(cursor->data);
            cursor = cursor->next;
        }
        return result;
    }

    void removeVertex(T data){
        removeVertex(getVertex(data));
    }

    void removeVertex(Vertex<T>* target){
        if(target == NULL)
            return;
        if(count && vertexExists(target->data) ){
            if(target == firstVertex){
                firstVertex = target->next;
                target->next = NULL;
            }else{
                Vertex<T>* auxBefore = firstVertex;
                while(auxBefore->next != NULL){
                    if(auxBefore->next == target){
                        auxBefore->next = target->next;
                        target->next = NULL;
                        break;
                    }
                    auxBefore = auxBefore->next;
                }
            }
        }
        updateCount();
    }

    int indexOfVertex(T data){
        Vertex<T>* cursor = firstVertex;
        bool index = 0;
        while(cursor != NULL){
            if(cursor->data == data)
                return index;
            cursor = cursor->next;
            index++;
        }
        return -1;
    }

    Vertex<T>* getVertex(T data){
        Vertex<T>* cursor = firstVertex;
        while(cursor != NULL){
            if(cursor->data == data)
                return cursor;
            cursor = cursor->next;
        }
        return NULL;
    }

    Vertex<T>* getVertex(int index){
        Vertex<T>* cursor = firstVertex;
        int current = 0;
        while(cursor != NULL){
            if(current == index)
                return cursor;
            cursor = cursor->next;
            current++;
        }
        return NULL;
    }

    void updateCount(){
        Vertex<T>* cursor = firstVertex;
        count = 0;
        while(cursor != NULL){
            count++;
            cursor = cursor->next;
        }
    }

    void printVertexList(){
        qDebug() << "\nVertex count: " << count;
        Vertex<T>* cursor = firstVertex;
        int i = 0;
        while(cursor != NULL){
            i++;
            qDebug() << "\tVertex" << i << ":" << cursor->data;
            cursor->printEdgeList();
            cursor = cursor->next;
        }
    }
};

#endif // GRAFO_H
