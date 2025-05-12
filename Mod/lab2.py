import random
from time import time as t
from matplotlib import pyplot as pp
from queue import PriorityQueue

CITIES_MIN = 3
CITIES_MAX = 10

# def tsp(matr):
#     num = len(matr)
#     pq = PriorityQueue()
#     pq.put((0, [0]))
#     best_distance = float('inf')

#     while not pq.empty():
#         cost, path = pq.get()
#         if len(path) == num:
#             total_cost = cost + matr[path[-1]][path[0]]
#             if total_cost < best_distance:
#                 best_distance = total_cost
#             continue

#         for next_city in range(num):
#             if next_city not in path:
#                 new_cost = cost + matr[path[-1]][next_city]
#                 pq.put((new_cost, path + [next_city]))
#     return

def gen_matrix(n):
    matr = [[random.randint(2, 20) if i < j else 0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            matr[i][j] = matr[j][i]
    return matr

def gen_paths(cities, start, end, paths):
    if start == end:
        paths.append(cities[:])
        paths[-1].append(paths[0][0])  # Замыкаем путь
        return
    for i in range(start, end + 1):
        cities[start], cities[i] = cities[i], cities[start]
        gen_paths(cities, start + 1, end, paths)
        cities[start], cities[i] = cities[i], cities[start]

def dist(path, matr):
    distance = 0
    for i in range(len(path) - 1):
        distance += matr[path[i]][path[i + 1]]
    return distance + matr[path[-1]][path[0]]

def brute(matr):
    num = len(matr)
    cities = list(range(num))
    paths = []
    min_path = []

    gen_paths(cities, 0, num - 1, paths)

    min_distance = float('inf')

    for path in paths:
        distance = dist(path, matr)
        if distance < min_distance:
            min_distance = distance
            min_path = path

    return distance, min_path

def nearest_neighbor(matr):
    unvisited = set(range(len(matr)))
    path = [0]
    unvisited.remove(0)
    total_distance = 0
    
    while unvisited:
        last = path[-1]
        nearest = min(unvisited, key=lambda x: matr[last][x])
        path.append(nearest)
        unvisited.remove(nearest)
        total_distance += matr[last][nearest]
    
    # Возвращаемся в начальную точку
    total_distance += matr[path[-1]][path[0]]
    path.append(path[0])
    
    return total_distance, path

def main():
    for cities in range(CITIES_MIN, CITIES_MAX):
        matr = gen_matrix(cities)
        start = t()
        dist1, path1 = brute(matr)
        brute_time = t() - start
        start = t()
        dist2, path2 = nearest_neighbor(matr)
        tsp_time = t() - start
        print(f"{cities} {brute_time:.4f} {tsp_time:.4f}")#  {dist1} {dist2}  {path1} {path2}")

if __name__ == "__main__":
    main()

