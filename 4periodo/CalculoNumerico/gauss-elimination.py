var_quantity = int(input("System variables quantity (2-4): "))

print(f"Enter the {var_quantity} variables system:")

matrix = [[int(x) for x in input().split()] for _ in range(var_quantity)]

columns_list = [[row[i] for row in matrix] for i in range(var_quantity+1)]

is_triangular = False

tries_count = 0

def is_triangular(m: list) -> bool:
  for i in range(1, var_quantity):
    for j in range(i-1):
      if m[i][j] != 0:
        return False
  return True

def multiply_row_and_sum_with_another(r1_index: int, r2_index: int) -> None:
  scaled_row = [r1_index*x for x in matrix[r1_index]] # Fix here to actually multiply
  matrix[r2_index] = [x + y for x, y in zip(scaled_row, matrix[r2_index])]

def choose_best_indexes(columns_lst: list) -> tuple:
  for i in range(var_quantity):
    for j in range(var_quantity):
      if columns_lst[i][j] == 0:
        continue
      for k in range(j+1, var_quantity):
        if columns_lst[i][k] == 0:
          continue
        if columns_lst[i][j] % columns_lst[i][k] == 0:
          return j, k
        elif columns_lst[i][k] % columns_lst[i][j] == 0:
          return k, j

def print_answer():
  for i in range(var_quantity):
    print(f"x{i} = {matrix[i][var_quantity-1]}")

while not is_triangular(matrix):
  chosen_indexes = choose_best_indexes(columns_list)
  multiply_row_and_sum_with_another(chosen_indexes[0], chosen_indexes[1])

print_answer()

