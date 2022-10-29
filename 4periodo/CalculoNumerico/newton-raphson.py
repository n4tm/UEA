import math


def f_a(value):
    return math.cos(value) - value

def df_a(value):
    return -math.sin(value) - 1

def f_b(value):
    return pow(value, 2) + value - 6

def df_b(value):
    return 2*value + 1

def f_c(value):
    return pow(value, 3) - 9*value - 6

def df_c(value):
    return 3*pow(value, 2) - 9


def newton_raphston_algorithm(f, df, x0):
    f_x0 = f(x0)

    iteration = 0
    x = x0

    print('Iteration | x | f(x)')
    print(f'{iteration} | {x} | {f_x0}')

    while iteration < 50:
        f_x = f(x)
        df_x = df(x)
        
        x -= f_x/df_x

        iteration += 1

        print(f'{iteration} | {x} | {f_x}')


if __name__ == '__main__':
    print('\nQuestion A')
    newton_raphston_algorithm(f_a, df_a, 0.5)

    print('\nQuestion B')
    newton_raphston_algorithm(f_b, df_b, 1.5)

    print('\nQuestion C')
    newton_raphston_algorithm(f_c, df_c, 0.5)
