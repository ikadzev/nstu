import random
import math

L = 10.0         # Длина области
p_abs = 0.3      # Вероятность поглощения
N = 1000000     # Количество нейтронов

transmitted = 0
reflected = 0
absorbed = 0

for _ in range(N):
    x = 0.0
    mu = 1.0
    alive = True

    while alive:
        r = random.random()
        lambda_val = -math.log(r + 1e-10)  # Добавлен сдвиг, как и в C++ коде
        x_next = x + lambda_val * mu

        if x_next >= L:
            transmitted += 1
            alive = False
        elif x_next < 0:
            reflected += 1
            alive = False
        else:
            gamma = random.random()
            if gamma < p_abs:
                absorbed += 1
                alive = False
            else:
                x = x_next
                mu = 2.0 * random.random() - 1.0  # Случайное направление в [-1, 1]

print(f"Simulated {N} neutron trajectories:")
print(f"Transmitted:  {transmitted} ({100.0 * transmitted / N:.2f}%)")
print(f"Reflected:    {reflected} ({100.0 * reflected / N:.2f}%)")
print(f"Absorbed:     {absorbed} ({100.0 * absorbed / N:.2f}%)")
