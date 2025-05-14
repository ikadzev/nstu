import random
import numpy as np

class Rand():
    def __init__(self, mean, stddev):
        self.mean = mean
        self.stddev = stddev

    def rand(self):
        return max(1, int(round(np.random.normal(self.mean, self.stddev))))

def synchronous_pipeline(stages, elements, rand):
    total_time = 0
    for _ in range(elements):
        total_time += max([rand.rand() for _ in range(stages)])
    return total_time

def asynchronous_pipeline(stages, elements, rand):
    buffer = [rand.rand() for _ in range(stages)]
    time = 0
    processed = 0

    while processed < elements:
        for i in reversed(range(stages)):
            if buffer[i] > 0:
                buffer[i] -= 1
                if buffer[i] == 0 and i == stages - 1:
                    processed += 1
                    buffer[i] = -1 

        for i in reversed(range(1, stages)):
            if buffer[i] == -1 and buffer[i - 1] == 0:
                buffer[i] = rand.rand()
                buffer[i - 1] = -1

        if buffer[0] == -1:
            buffer[0] = rand.rand()

        time += 1

    return time

def main():
    stages = 5
    mean = 5.0
    stddev = 2.0
    rand = Rand(mean, stddev)

    print(f"{'num':<10}{'syn':<20}{'asyn':<20}{'a/s':<15}")
    print('-' * 54)

    for elements in range(100, 2001, 100):
        sync_time = synchronous_pipeline(stages, elements, rand)
        async_time = asynchronous_pipeline(stages, elements, rand)
        ratio = async_time / sync_time

        print(f"{elements:<10}{sync_time:<20}{async_time:<20}{ratio:<15.2f}")

if __name__ == "__main__":
    main()
