def brute_force_lis(seq, res_seq):
  def _lis(_seq):
    n = len(_seq)
    if n == 1:
      return 1
    
    # maxEndingHere is the length of LIS ending with arr[n-1]
    maxEndingHere = 1
 
    """Recursively get all LIS ending with arr[0], arr[1]..arr[n-2]
       IF arr[i-1] is smaller than arr[n-1], and max ending with
       arr[n-1] needs to be updated, then update it"""
    for i in range(1, n):
      res = _lis(_seq)
      if _seq[i-1] < _seq[n-1] and res+1 > maxEndingHere:
        maxEndingHere = res + 1
 
    # Compare maxEndingHere with overall maximum. And
    # update the overall maximum if needed
    maximum = max(maximum, maxEndingHere)
 
    return maxEndingHere

if __name__ == '__main__':
  sequence = [int(x) for x in input("Enter a sequence: ")]

  print(brute_force_lis(sequence))