class DecimalConverter:
  @staticmethod
  def decimal_to_binary(n: str) -> str:
    n = int(n)
    result = ''
    while True:
      result += str(n%2)
      if n <= 1:
        break
      n //= 2
    return result[::-1]

  @staticmethod
  def decimal_fraction_to_binary(n: str, max_digits: int = 6) -> str:
    parcels = n.split('.')
    frac_n = float('0' + '.' + parcels[1])
    frac_result = ''
    while frac_n > 0 or len(frac_result) >= max_digits:
      frac_n *= 2
      if frac_n >= 1:
        frac_n -= 1
        frac_result += '1'
      else:
        frac_result += '0'
    return parcels[0] + '.' + frac_result

  @staticmethod
  def binary_to_decimal(n: str) -> int:
    i = len(n)-1
    result = 0
    for d in n:
      result += int(d) << i
      i-=1
    return result

def read_catching_exception(from_base: str, to_base: str, try_func):
  result = ''
  while True:
    result = input(f'Enter a {from_base} number to find out its value in {to_base} base: ')
    try:
      try_func(result)
    except ValueError:
      max_dig = '1' if from_base == 'binary' else '9'
      print(f'{from_base.capitalize()} digits 0-{max_dig} only allowed.')
    else:
      break
  return result

binary_num = read_catching_exception(from_base='binary', to_base='decimal', try_func=lambda x: int(x, 2))
decimal_num = read_catching_exception(from_base='decimal', to_base='binary', try_func=int)
decimal_fraction_num = read_catching_exception(from_base='decimal fraction', to_base='binary', try_func=float)

print('--------')
print(f'The binary number {binary_num} in decimal base is: {DecimalConverter.binary_to_decimal(binary_num)}')
print(f'The decimal number {decimal_num} in binary base is: {DecimalConverter.decimal_to_binary(decimal_num)}')
print(f'The decimal fraction number {decimal_fraction_num} in binary base is: {DecimalConverter.decimal_fraction_to_binary(decimal_fraction_num)}')
