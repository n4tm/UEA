import math


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
  @staticmethod
  def ReadDataFromInput() -> CompressibleData:
    symbols: list[Symbol] = []
    data_amount = int(input())
    for _ in range(data_amount):
      symbol_input = input().split()
      symbol_key = symbol_input[0]
      symbol_probability = float(symbol_input[1])
      symbol = Symbol(symbol_key, symbol_probability)
      symbols.append(symbol)

    return CompressibleData(symbols)


data = InputHandler.ReadDataFromInput()
data.compress()

print(data.compression_result)
