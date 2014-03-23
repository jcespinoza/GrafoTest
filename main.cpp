#include "Grafo.h"

int main()
{
    Graph<QString> g;
    g.addVertex("algo");
    g.addVertex("nada");
    g.addVertex("some");
    g.printVertexList();
    g.addConnection("algo", "nada", 15);
    g.addConnection("some", "nada", 10);
    g.addConnection("some", "algo", 10);
    g.printVertexList();
    g.removeVertex("algo");
    g.printVertexList();
    g.removeConnection("some", "nada");
    g.printVertexList();

    return 0;
}
