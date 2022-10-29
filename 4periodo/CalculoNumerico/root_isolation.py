f = lambda x: pow(x, 3) - 9*x + 3

x_column = range(-1000, 1001)
fx_column = [f(x) for x in x_column]

print("+---------+--------------+")
print("|    x    |     f(x)     |")
print("|---------+--------------|")

def table_spacement(num_str: str, max_str_len: int) -> str:
  num_str_len = len(num_str)
  if num_str_len > max_str_len:
    max_str_len = num_str_len
  return ' '*(max_str_len - num_str_len)

for i in range(len(x_column)):
  x_str = str(x_column[i])
  fx_str = str(fx_column[i])

  print("|  " + x_str + table_spacement(x_str, 5) + "  |  " + fx_str + table_spacement(fx_str, 10) + "  |")
