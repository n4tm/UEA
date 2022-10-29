from abc import ABC
from math import cos, log, radians
from tabulate import tabulate

class RootApproximationMethodData:
  def __init__(self, f, f_str: str, interval: tuple[int|float, int|float] = (0, 1), precision: float = 1e-3):
    self.f = f
    self.f_str = f_str
    self.interval = interval
    self.precision = precision

class RootApproximationMethod(ABC):
  def __init__(self, x_approximation_func, methodName: str):
    self.x_approximation_func = x_approximation_func
    self.methodName = methodName

  def find_root_approximation(self, data: RootApproximationMethodData) -> None:
    a, b = data.interval
    precision_validation_count = 20
    x, f_x = 0.0, 0.0
    table_rows = []
    while precision_validation_count > 0:
      f_a, f_b = data.f(a), data.f(b)
      x: float = self.x_approximation_func(a, b, f_a, f_b)
      f_x = data.f(x)

      table_rows.append([a, f_a, b, f_b, x, f_x])

      if f_a*f_x > 0:
        a = x
      else:
        b = x

      if abs(f_x) <= data.precision:
        precision_validation_count -= 1
    
    print(f"\n                             {self.methodName}")
    print("+----------------------------------------------------------------------------+")
    print(f"|                         {data.f_str} | [{data.interval[0]}, {data.interval[1]}]; e <= {data.precision}                      |")
    print(tabulate(table_rows, headers=['a', 'f(a)', 'b', 'f(b)', 'x', 'f(x)'], tablefmt='grid'))
    print(f"          x: {x}        f(x): {f_x}\n")

class BissectionMethod(RootApproximationMethod):
  def __init__(self):
    super().__init__(lambda a, b, f_a, f_b: (a + b)/2, "Bissection Method")


class FalsePositionMethod(RootApproximationMethod):
  def __init__(self):
    super().__init__(lambda a, b, f_a, f_b: (a*f_b - b*f_a)/(f_b - f_a), "False Position Method")

if __name__ == '__main__':
  data = [
    RootApproximationMethodData(lambda x: x**3 - 9*x + 3, "x³-9x+3"), # x³-9x+3 | [0, 1]; e <= 0,001
    RootApproximationMethodData(lambda x: cos(radians(x)) - x, "cos(x)-x"), # cos(x)-x | [0, 1]; e <= 0,001
    RootApproximationMethodData(lambda x: x**2 - 3, "x²-3", (1, 2)), # x²-3 | [1, 2]; e <= 0,001 
    RootApproximationMethodData(lambda x: x**2 + log(x), "x²+ln(x)", (0.5, 1)) # x²+ln(x) | [0.5, 1]; e <= 0,001
  ]

  bissectionMethod = BissectionMethod()
  falsePositionMethod = FalsePositionMethod()

  for d in data:
    bissectionMethod.find_root_approximation(d)
    falsePositionMethod.find_root_approximation(d)