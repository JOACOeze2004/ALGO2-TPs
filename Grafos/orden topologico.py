from collections import deque

grafo = {
    "CBC": ["AM2","FUNDA", "F1"],
    "AM2": ["AM3"],
    "FUNDA": ["ALGO2"],
    "F1": ["TDA"],
    "AM3": ["ALGO3"],
    "ALGO2": ["ALGO3"],
    "TDA": ["M2"],
    "ALGO3": ["M2"],
    "M2": ["FIN"],
    "FIN": []
}

grafo2 = {
    "A": ["B", "C", "D", "E"],
    "B": ["C", "F"],
    "C": ["E"],
    "D": ["F"],
    "E": [],
    "F": []
}


def topo (grafo):
    incidencias = {nodo: 0 for nodo in grafo}

    for nodo in grafo:
        for vecino in grafo[nodo]:      #grafo[nodo] seria como decir diccionario[i] y ves los coso asociados a ese vertice
            incidencias[vecino] += 1

    cola = deque([nodo for nodo in grafo if incidencias[nodo] == 0])
    orden = []

    while len(cola) > 0:
        nodo = cola.popleft()
        orden.append(nodo)
        for vecino in grafo[nodo]:
            incidencias[vecino] -= 1
            if incidencias[vecino] == 0:
                cola.append(vecino)
    return orden

print("Orden topológico:", topo(grafo2))

a = 13%8
print(a)