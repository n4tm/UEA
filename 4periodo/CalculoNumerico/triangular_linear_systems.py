from random import randint


def printTriangularLinearSystem(zero_condition):
  for i in range(3):
    for j in range(3):
      if zero_condition(i, j):
        print(0, end=' ')
      else:
        print(randint(0, 9), end=' ')
    print()
    
print("Sistema Triangular Superior 3x3:")
printTriangularLinearSystem(lambda i, j: j < i)
print("\nSistema Triangular Inferior 3x3")
printTriangularLinearSystem(lambda i, j: j > i)