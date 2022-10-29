class Symbol:
  def __init__(self, key: str, probability: float):
    self.key = key
    self.probability = probability
    self.code = ''


class CompressibleData:
  def __init__(self, data: list[Symbol]):
    # Sort symbols by its probabilities in descending order
    self.data = data
    self.compression_result = ''

  def compress(self) -> None:
    if len(self.data) == 1:
      self.compression_result = '0'
      return

    def _compress(_data: list[Symbol], _r: int) -> list[Symbol]:
      # Stop spliting data when there is only 1 element in data
      if len(_data) == 1:
        return

      # Two pointers implementation based in proportional probability percentual
      _l = 0
      _r = len(_data)-1

      _data[_r].code += '1'
      _data[_l].code += '0'
      sum_r = _data[_r].probability
      sum_l = _data[_l].probability
      
      while _l < _r - 1:
        if sum_l >= sum_r:
          _r -= 1
          sum_r += _data[_r].probability
          _data[_r].code += '1'
        else:
          _l += 1
          sum_l += _data[_l].probability
          _data[_l].code += '0'

      left_part = _data[:_l+1]
      right_part = _data[_r:]

      return _compress(left_part, _l), _compress(right_part, _r)

    ordered_data = sorted(self.data, key=lambda x: x.probability, reverse=True)
    _compress(ordered_data, len(ordered_data)-1)

    # Update compression result:
    for symbol in self.data:
      self.compression_result += symbol.code

class InputHandler:
  symbols: list[Symbol] = []

  @staticmethod
  def ReadDataFromInput() -> CompressibleData:
    data_amount = int(input())
    for _ in range(data_amount):
      InputHandler._InternalReadData(input())

    return CompressibleData(InputHandler.symbols)

  @staticmethod
  def ReadDataFromFile(file_path: str) -> CompressibleData:
    with open(file_path) as f:
      jumped_first_line = False
      for line in f:
        if not jumped_first_line:
          jumped_first_line = True
          continue
        InputHandler._InternalReadData(line)

    return CompressibleData(InputHandler.symbols)

  @staticmethod
  def _InternalReadData(data: str) -> None:
      symbol_input = data.split()
      symbol_key = symbol_input[0]
      symbol_probability = float(symbol_input[1])
      symbol = Symbol(symbol_key, symbol_probability)
      InputHandler.symbols.append(symbol)


class OutputHandler:
  @staticmethod
  def GetDataFromFile(file_path: str) -> str:
    with open(file_path) as f:
      print(f)

  @staticmethod
  def PrintResultComparison(actual: str, expected_result_file_path: str) -> None:
    with open(expected_result_file_path) as f:
      expected = f.read()

    print(f"\nActual result:\n{actual}")
    print(f"Expected result:\n{expected}")
    print(f"\nVeredict: {'FAIL' if actual != expected else 'SUCCESS'}")

default_in_out_folder = 'in_out'
num = input("Which input? (1 / 2 / 3): ")
data = InputHandler.ReadDataFromFile(f'{default_in_out_folder}/{num}.in')
data.compress()

OutputHandler.PrintResultComparison(data.compression_result, f'{default_in_out_folder}/{num}.out')
