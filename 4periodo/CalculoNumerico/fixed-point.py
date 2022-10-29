import math


def f_a(value):
    return math.cos(value) - value


def f_b(value):
    return pow(value, 2) + value - 6


def f_c(value):
    return pow(value, 3) - 9*value - 6


def fixed_point_algorithm(f, x0):
    x = f(x0)

    iteration = 0

    print('Iteration | x0 | x | f(x)')
    print(f'{iteration} | {x0} | {x} | {f(x)}')

    while iteration < 50:
        x = f(x)
        iteration += 1

        print(f'{iteration} | {x0} | {x} | {f(x)}')


if __name__ == '__main__':
    print('\nQuestion A')
    fixed_point_algorithm(f_a, 0.5)

    print('\nQuestion B')
    fixed_point_algorithm(f_b, 1.5)

    print('\nQuestion C')
    fixed_point_algorithm(f_c, 0.5)
