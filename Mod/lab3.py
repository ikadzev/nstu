import random
import matplotlib.pyplot as pp

def weighted_random_index(priorities):
    total_weight = sum(priorities)
    random_value = random.randint(0, total_weight - 1)
    cumulative_weight = 0

    for i in range(len(priorities)):
        cumulative_weight += priorities[i]
        if random_value < cumulative_weight:
            return i

def fill_priorities(size): return [random.randint(1, size) for _ in range(size)]

def main():
    size = 100
    file_size = 10
    write_chance = 10

    priorities = fill_priorities(size)
    save_priorities = priorities[:]
    values = [0] * size
    absolute_value = 0

    while absolute_value < size:
        temp = weighted_random_index(priorities)
        if temp == -1:
            break

        values[temp] += 1

        if values[temp] == file_size:
            absolute_value += 1
            priorities[temp] = 0

            if random.randint(0, write_chance - 1) == 0:
                print("Writing process started. Resetting all reading progress.")
                values = [0 if priorities[i] != 0 else values[i] for i in range(size)]
                file_size += 1

    print("--- Reading cycle completed ---")
    for i in range(size):
        print(f"Process {i} with priority {save_priorities[i]} read {values[i]} characters.")
    pp.plot(values, save_priorities, 'ro')
    pp.grid()
    pp.show()

if __name__ == "__main__":
    main()
