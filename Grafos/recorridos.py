from collections import deque

grafo = {
    "A": ["B","D"],
    "B": ["A","C","F"],
    "C": ["B","D"],
    "D": ["A","C"],
    "E": ["F","A"],
    "F": ["E","B"],
}

def dfs(grafo , nodo_inicio,visitados):
    vecinos = grafo[nodo_inicio]

    visitados.append(nodo_inicio)
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