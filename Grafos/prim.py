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

grafo2 = {
    'A': [('C', 2), ('D', 4)],
    'B': [('E', 7), ('D', 2), ('H', 2)],
    'C': [('A', 2), ('E', 1), ('F', 1)],
    'D': [('A', 4), ('B', 5), ('G', 5)],
    'E': [('B', 7), ('C', 1), ('H', 4)],
    'F': [('C', 1), ('I', 5), ('G', 8)],
    'G': [('I', 2), ('F', 8), ('D', 5)],
    'H': [('E', 4), ('B', 2)],
    'I': [('F', 5), ('G', 2)]
}

grafo3 = {
    'A': [('G', 1), ('B', 1), ('E', 1), ('F', 9)],
    'B': [('C', 4), ('F', 5), ('A', 1)],
    'C': [('B', 4), ('F', 4), ('G', 3)],
    'D': [('E', 6), ('F', 6), ('G', 5)],
    'E': [('G', 2), ('A', 1), ('D', 6)],
    'F': [('B', 5), ('C', 4), ('D', 6), ('A', 9)],
    'G': [('E', 2), ('A', 1), ('D', 5), ('C', 3)],
}

grafo4 = {
    'A': [('B', 2), ('C', 5), ('D', 1), ('F', 8)],
    'B': [('A', 2), ('H', 4)],
    'C': [('A', 5), ('I', 2), ('F', 3), ('E', 1)],
    'D': [('A', 1), ('G', 6), ('H', 5)],
    'E': [('C', 1), ('H', 8)],
    'F': [('A', 8), ('C', 3), ('I', 1), ('G', 1)],
    'G': [('D', 6), ('F', 1), ('I', 3)],
    'H': [('B', 4), ('D', 5), ('E', 8)],
    'I': [('C', 2), ('F', 1), ('G', 3)]
}

grafo5 = {
    'A': [('C', 3), ('D', 1)],
    'B': [('D', 5), ('H', 7), ('E', 1)],
    'C': [('A', 3), ('F', 2), ('E', 7)],
    'D': [('B', 5), ('G', 9), ('A', 1)],
    'E': [('C', 7), ('H', 4), ('B', 1)],
    'F': [('C', 2), ('G', 2), ('I', 4)],
    'G': [('D', 9), ('F', 2), ('I', 1)],
    'H': [('B', 7), ('E', 4)],
    'I': [('F', 4), ('G', 1)]
}

grafo6 = {
    'A': [('B', 2), ('C', 5), ('F', 8), ('D', 1)],
    'B': [('A', 2), ('H', 4)],
    'C': [('A', 5), ('I', 2), ('F', 3), ('E', 1)],
    'D': [('G', 6), ('H', 5), ('A', 1)],
    'E': [('H', 8), ('C', 1)],
    'F': [('A', 8), ('I', 1), ('C', 3), ('G', 1)],
    'G': [('I', 3), ('F', 1), ('D', 6)],
    'H': [('E', 8), ('B', 4), ('D', 5)],
    'I': [('F', 1), ('C', 2), ('G', 3)]
}

nodo_inicio = 'E'
mst = prim(grafo6, nodo_inicio)

print("Árbol de Expansión Mínima (MST):")
for nodo_origen, nodo_destino, peso in mst:
    print(f"{nodo_origen} - {nodo_destino}: {peso}")

