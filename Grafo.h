#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <limits>
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

    void addEdge(Vertex<J>* where, double value=0){
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

    bool hasAdjacencyWith(Vertex<J>* w){
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

    Edge<J>* getEdge(int index){
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

    double getEdgeValue(int index){
        Edge<J>* cursor = getEdge(index);
        if(cursor != NULL)
            return cursor->value;
        return -1;
    }

    double getEdgeValue(Vertex<J>* who){
        Edge<J>* cursor = getEdge(who);
        if(cursor)
            return cursor->value;
        return -1;
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

    ListPointerT< Edge<J>* > getAllEdges(){
        ListPointerT< Edge<J>* > result;
        Edge<J>* cursor = firstEdge;
        while(cursor){
            result.insert(cursor);
            cursor = cursor->next;
        }
        return result;
    }

    ListPointerT<double> getEdgeValues(){
        ListPointerT<double> result;
        Edge<J>* cursor = firstEdge;
        while(cursor){
            result.insert(cursor->value);
            cursor = cursor->next;
        }
        return result;
    }

    void removeAdjaceny(Vertex<J>* with){
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
        qDebug() << data << "Edges count: " << count;
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
    double value;
    Edge(){
        destin = NULL;
        next = NULL;
    }
    Edge(Vertex<K>* dest, double cost): destin(dest), next(NULL), value(cost){}
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

    void addConnection(T fromV, T toV, double cost){
        if(!count || !vertexExists(fromV) || !vertexExists(toV))
            return;
        getVertex(fromV)->addEdge(getVertex(toV), cost);
    }

    Edge<T>* getConnection(T fromV, T toV){
        if(!count || !vertexExists(fromV) || !vertexExists(toV))
            return NULL;
        return getVertex(fromV)->getEdge(getVertex(toV));
    }

    void updateConnection(T fromV, T toV, double nValue){
        Edge<T> *edge = getConnection(fromV, toV);
        if(edge)
            edge->value = nValue;
    }

    void removeConnection(T fromV, T with){
        if(!count || !vertexExists(fromV) || !vertexExists(with))
            return;
        getVertex(fromV)->removeAdjaceny(getVertex(with));
    }

    bool connectionExists(T fromV, T toV){
        if(!count || !vertexExists(fromV) || !vertexExists(toV))
            return false;
        return getVertex(fromV)->hasAdjacencyWith(getVertex(toV));
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

    ListPointerT< Vertex<T>* > getLowesCostPath(Vertex<T>* originVertex, Vertex<T>* toV){
        ListPointerT< Vertex<T>* > shortesPath;
        if(!originVertex || !toV)
            return shortesPath;
        bool ok=false;
        ListPointerT< Vertex<T>* > unvisited = getAllVertices(ok);
        ListPointerT< Vertex<T>* > universe = getAllVertices(ok);
        ListPointerT< Vertex<T>* > visited;

        int dSize = universe.getCount();
        double D[dSize];
        Vertex<T>* predecesor[dSize];

        for(int i = 0; i < dSize; i++){
            Vertex<T>* current = universe.get(i);
            double dist = originVertex->getEdgeValue(current);
            predecesor[i] = NULL;
            if(originVertex == current){
                dist = 0;
                predecesor[i] = originVertex;
            }else if(dist == -1)
                dist = std::numeric_limits<double>::max();
            else
                predecesor[i] = originVertex;
            D[i] = dist;
        }

        visited.insert(unvisited.disconnect(originVertex)->value);
        Vertex<T>* actual;

        while (unvisited.getCount() > 0) {
            actual = unvisited.getFirst();
            int indexV = universe.getIndex(actual);
            visited.insert(unvisited.disconnect(actual)->value);

            ListPointerT< Edge<T>* > edges = actual->getAllEdges();

            for(int i = 0; i < edges.getCount(); i++){
                Edge<T>* edge = edges.get(i);
                int indexU = universe.getIndex(edge->destin);
                double N = D[indexV]+edge->value;
                if(D[indexU] > N){
                    D[indexU] = N;
                    predecesor[indexU] = actual;
                }
            }
        }
        int indexTo = universe.getIndex(toV);
        if(D[indexTo] != std::numeric_limits<double>::max()){
            int nextIndex = indexTo;
            bool reachedSource;
            shortesPath.insert(toV);
            while(!reachedSource){
                Vertex<T>* preVertex = predecesor[nextIndex];
                shortesPath.insert(0, preVertex);
                if(preVertex == originVertex)
                    reachedSource = true;
                nextIndex = universe.getIndex(preVertex);
            }
        }
        return shortesPath;
    }



    ListPointerT< Vertex<T>* > getLowesCostPath(T fromV, T toV){
        return getLowesCostPath(getVertex(fromV), getVertex(toV));
    }

    ListPointerT<T> getAllBut(T except){
        ListPointerT<T> result;
        Vertex<T>* cursor = firstVertex;
        while(cursor){
            if( !(cursor->data == except))
                result.insert(cursor->data);
            cursor = cursor->next;
        }
        return result;
    }

    ListPointerT< Vertex<T>* > getAllVertices(bool){
        ListPointerT< Vertex<T>* > result;
        Vertex<T>* cursor = firstVertex;
        while(cursor){
            result.insert(cursor);
            cursor = cursor->next;
        }
        return result;
    }

    ListPointerT<T> getAllVertices(){
        ListPointerT<T> result;
        Vertex<T>* cursor = firstVertex;
        while(cursor){
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
            //Remove adyacency with this vertex
            Vertex<T>* cursor = firstVertex;
            while(cursor != NULL){
                cursor->removeAdjaceny(target);
                cursor = cursor->next;
            }
            //Remove the vertex ifself
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
        return indexOfVertex(getVertex(data));
    }

    int indexOfVertex(Vertex<T>* target){
        if(!target) return -1;
        Vertex<T>* cursor = firstVertex;
        bool index = 0;
        while(cursor != NULL){
            if(cursor == target)
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

    T getVertexWith(T data, bool &ok){
        Vertex<T>* cursor = firstVertex;
        while(cursor != NULL){
            if(cursor->data == data){
                ok = true;
                return cursor->data;
            }
            cursor = cursor->next;
        }
        ok = false;
        return T();
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
