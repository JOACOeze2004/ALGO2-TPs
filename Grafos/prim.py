import math


grafo = {
    "A": {
        "B": 2,
        "C": 5,
        "D" : 5,
    },
    "B" : {
        "A" : 2,
        "C" : 2,
        "D" : 7
    },
    "C" : {
        "A" : 5,
        "B" : 2,
        "D" : 4
    },
    "D" : {
        "A" : 5,
        "C" : 5,
        "B" : 7
    }
}

class AristaAsiNomas:
    def __init__(self,n1,n2,peso):
        self.n1 = n1
        self.n2 = n2
        self.peso = peso
    
    def __eq__(self, otro):
        return self.peso == otro.peso

    def __lt__(self,otro):
        return self.peso < otro.peso


    

#version en clase q no funciona xq no tenemos el heap q aparece en clase (el d python)
# def prim(grafo, nodo_inicial):
#     arbol = {nodo_inicial:{}}
#     visitados = set()

#     vecinos = grafo[nodo_inicial]
#     heap = heap()
#     for vecino,peso in grafo[nodo_inicial].items():
#         heap.push(AristaAsiNomas(nodo_inicial,vecino,peso))

#     visitados.add(nodo_inicial)

#     while heap:
#         siguiente = heap.pop()

#         if siguiente.n2 not in visitados:
#             visitados.add(siguiente.n2)
#             arbol[siguiente.n1][siguiente.n2] = siguiente.peso
#             arbol[siguiente.n2] = {siguiente.n1 : siguiente.peso}

#             for vecino,peso in grafo[siguiente.n2].items():
#                 if vecino not in visitados:
#                     heap.push(AristaAsiNomas(siguiente.n2,vecino,peso))


import heapq

def prim(grafo, nodo_inicio):
    mst = []  
    visitados = set()
    heap = []

    def add_edges(nodo):
        for vecino, peso in grafo[nodo]:
            if vecino not in visitados:
                heapq.heappush(heap, (peso, nodo, vecino))
    
    add_edges(nodo_inicio)
    visitados.add(nodo_inicio)
    
    while heap:
        peso, nodo_origen, nodo_destino = heapq.heappop(heap)
        
        if nodo_destino not in visitados:
            visitados.add(nodo_destino)
            mst.append((nodo_origen, nodo_destino, peso))
            add_edges(nodo_destino)
    
    return mst

grafo = {
    'A': [('B', 1), ('C', 4)],
    'B': [('A', 1), ('C', 2), ('D', 5)],
    'C': [('A', 4), ('B', 2), ('D', 1)],
    'D': [('B', 5), ('C', 1)],
}

nodo_inicio = 'A'
mst = prim(grafo, nodo_inicio)

print("Árbol de Expansión Mínima (MST):")
for nodo_origen, nodo_destino, peso in mst:
    print(f"{nodo_origen} - {nodo_destino}: {peso}")

