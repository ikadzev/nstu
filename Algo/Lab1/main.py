from math import log2

# 1. Реализовать функцию, которая на вход получает натуральное четное число и возвращает два простых числа, 
# которые в сумме составляют входное число (с подсчетом количества итераций).
# 2. Написать функцию, которая оценивает трудоемкость алгоритма из п. 1 для следующих значений: 
# 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096.

def numToSimples(inp):
    itr = 0
    for i in range(1, inp):
        simp, itr = isSimple(i, itr)
        if simp:
            simp, itr = isSimple(inp - i, itr)
            if simp:
                return itr

def isSimple(num, iterations):
    for i in range(2, num // 2 + 1):
        iterations += 1
        if num % i == 0:
            return False, iterations
    return True, iterations

def main():
    tests = [8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096]
    print("num     | Te1    | T1     | Te1/T1 ")
    print('-' * 35)
    for i in tests:
        print(f'{i:<8}|', end='')
        test = numToSimples(i)
        print(f' {test:<7}|', end='')
        print(f' {(i)//2:<7}|', end='')
        print(f' {test/((i)//2)}')


if __name__ == '__main__':
    main()