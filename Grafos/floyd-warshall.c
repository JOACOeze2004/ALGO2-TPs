#include <stdio.h>
#define INF 99999
#define V 4     


void printMatrix(int dist[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("\t%s\t", "INF");
            else
                printf("\t%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int grafo[V][V]) {
    int dist[V][V];
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = grafo[i][j];
        }
    }

    for (int k = 0; k < V; k++) {       //K seria nodo intermedio
        for (int i = 0; i < V; i++) {   // I seria mi V1
            for (int j = 0; j < V; j++) {   //Y J mi V2
                if (dist[i][k] != INF && dist[k][j] != INF &&       //verificamos que haya camino posible desde I --> K y desde K-->J y V1-->V2 > V1--->V0--->V2
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];           //cambias esa distancia ( la de la matriz posta) sumando la distancia de  V1--->V0 y V0---->V2 
                }
            }
        }
    }

    printf("Matriz de distancias más cortas entre todos los pares de vértices:\n");
    printMatrix(dist);
}

int main() {
    int grafo[V][V] = {
        {0, 2, INF, 2},
        {7, 0, 9, 2},
        {INF, 1, 0, INF},
        {8, INF, 3, 0}
    };

    floydWarshall(grafo);
    return 0;
}