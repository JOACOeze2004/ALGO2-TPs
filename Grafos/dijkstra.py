import heapq

# grafo = {
#     'A': {'C': 2, 'D' : 4},
#     'B': {'E': 7, 'D' : 2, 'H':2},
#     'C': {'A': 2, 'E': 1, 'F': 1},
#     'D': {'A': 4, 'B': 5, 'G': 5},
#     'E': {'B': 7, 'C': 1, 'H': 4},
#     'F': {'C': 1, 'I': 5, 'G': 8},
#     'G': {'I': 2, 'F':8,'D':5},
#     'H': {'E': 4, 'B':2},
#     'I': {'F':5,'G':2}
# }

# grafo = {
#     'D': {'E': 6, 'F': 6, 'G': 5},
#     'A': {'G': 1, 'B': 1, 'E': 1, 'F': 9},
#     'F': {'B': 5, 'C': 4, 'D':6, 'A': 9},
#     'G': {'E': 2, 'A': 1, 'D': 5, 'C':3},
#     'C': {'B': 4, 'F': 4, 'G': 3},
#     'E': {'G': 2, 'A': 1, 'D': 6},
#     'B': {'C': 4, 'F': 5, 'A': 1}
# }


grafo = {
    'A': {'B': 6, 'C': 2, 'F': 8, 'D': 4},
    'B': {'A': 6, 'H': 2},
    'C': {'A': 2, 'I': 6, 'F': 1, 'E': 1},
    'D': {'G': 4, 'H': 5, 'A': 4},
    'E': {'H': 8, 'C': 1},
    'F': {'A': 8, 'I': 4, 'C': 1, 'G': 2},
    'G': {'I': 2, 'F': 2,'D': 4},
    'H': {'E': 8, 'B': 2,'D': 5},
    'I': {'F': 4, 'C': 6,'G': 2}

}

# grafo = {
#     'A': {'C': 3, 'D': 4},
#     'B': {'D': 5, 'H': 2, 'E': 7},
#     'C': {'A': 4, 'F': 2, 'E': 1},
#     'D': {'B': 5, 'G': 5, 'A': 3, 'H': 4},
#     'E': {'C': 1, 'H': 1, 'B': 7},
#     'F': {'C': 2, 'G': 8, 'I': 5},
#     'G': {'D': 5, 'F': 8, 'I': 2},
#     'H': {'B': 2, 'E': 1, 'D': 4},
#     'I': {'F': 5, 'G': 2}
# } 

# grafo = {
#     'A': {'B': 1, 'C': 5, 'D' : 2},
#     'B': {'A': 1, 'E': 5},
#     'C': {'A': 5, 'E': 1, 'I': 5},
#     'D': {'A': 2, 'E': 3, 'H': 1},
#     'E': {'B': 5, 'D': 3, 'F': 2, 'C': 1},
#     'F': {'C': 1, 'E': 2, 'I': 5},
#     'G': {'H': 9, 'I': 1},
#     'H': {'D': 1, 'G': 9, 'F': 3},
#     'I': {'F': 8, 'G': 1, 'C': 5}
# }


# grafo = {
#     'A': {'B': 1, 'C': 5, 'D': 5},  # Nodo A con aristas a B, C, D
#     'B': {'A': 1, 'E': 5, 'D': 3},  # Nodo B con aristas a A, E, D
#     'C': {'A': 5, 'E': 3, 'I': 5},  # Nodo C con aristas a A, E, I
#     'D': {'A': 5, 'B': 3, 'E': 3, 'H' : 5},  # Nodo D con aristas a A, B, E
#     'E': {'B': 5, 'D': 4, 'C': 3},  # Nodo E con aristas a B, D, F, C
#     'F': {'G': 10, 'I': 8},  # Nodo F con aristas a E, G, H, I
#     'G': {'F': 10, 'H': 9, 'I': 1},  # Nodo G con aristas a F, H, I
#     'H': {'D': 1, 'G': 9},  # Nodo H con aristas a F, G
#     'I': {'C': 5, 'F': 8, 'G': 1}  # Nodo I con aristas a C, F, G
# }


# grafo = {
#     'A': {'C': 4, 'F': 8},  # Nodo A
#     'B': {'D': 1, 'C': 3, 'H': 5,'E':1},  # Nodo B
#     'C': {'A': 4, 'B': 3, 'F': 2, 'E': 7},  # Nodo C
#     'D': {'G': 2, 'B': 1},          # Nodo D
#     'E': {'B': 1, 'H': 2, 'C':7},                  # Nodo E
#     'F': {'A': 8, 'C': 2, 'G': 4, 'I': 5},  # Nodo F
#     'G': {'F': 4, 'I': 5,'D': 2},                  # Nodo G
#     'H': {'B': 5, 'E': 2},          # Nodo H
#     'I': {'F': 5, 'G': 5}           # Nodo I
# }

def dijkstra(grafo, inicio):
    distancias = {nodo: float('inf') for nodo in grafo}
    distancias[inicio] = 0

    cola_prioridad = [(0, inicio)]  # (distancia, nodo)

    predecesores = {nodo: None for nodo in grafo}

    while cola_prioridad:
        distancia_actual, nodo_actual = heapq.heappop(cola_prioridad)

        if distancia_actual > distancias[nodo_actual]:
            continue

        for vecino, peso in grafo[nodo_actual].items():
            distancia_nueva = distancia_actual + peso

            if distancia_nueva < distancias[vecino]:
                distancias[vecino] = distancia_nueva
                predecesores[vecino] = nodo_actual
                heapq.heappush(cola_prioridad, (distancia_nueva, vecino))

    return distancias, predecesores 


inicio = 'A'
distancias, predecesores = dijkstra(grafo, inicio)

print("Distancias mínimas desde A:")
for nodo, distancia in distancias.items():
    print(f"{nodo}: {distancia}")

print("\nRutas:")
for nodo, pred in predecesores.items():
    ruta = []
    actual = nodo
    while actual is not None:
        ruta.append(actual)
        actual = predecesores[actual]
    print(f"Ruta a {nodo}: {' -> '.join(reversed(ruta))}")

