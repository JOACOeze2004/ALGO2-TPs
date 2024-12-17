from collections import deque

grafo = {
    'A': ['B', 'C', 'F', 'D'],
    'B': ['A', 'H'],
    'C': ['A', 'I', 'F', 'E'],
    'D': ['G', 'H', 'A'],
    'E': ['H', 'C'],
    'F': ['A', 'I', 'C', 'G'],
    'G': ['I', 'F', 'D'],
    'H': ['E', 'B', 'D'],
    'I': ['F', 'C', 'G']
}

def dfs(grafo , vertice,visitados):
    vecinos = grafo[vertice]

    visitados.append(vertice)
    for vecino in vecinos:
        if vecino not in visitados:
            dfs(grafo,vecino,visitados)


def bfs(grafo , nodo_inicial):
    cola = deque()
    visitados = set()

    cola.append(nodo_inicial)
    visitados.add(nodo_inicial)
    
    while len(cola) > 0:
        nodo_sacado = cola.popleft()
        print(nodo_sacado)

        vecinos = grafo[nodo_sacado]
        
        for vecino in vecinos:
            if vecino not in visitados:
                cola.append(vecino)
                visitados.add(vecino)

visitados = []

dfs(grafo, "F", visitados)

print("Nodos visitados en DFS:", visitados)

bfs(grafo,"A")