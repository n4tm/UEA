import sys
import time

ans = sys.maxsize

# Function to minimize the maximum number of pages
def minimum_number_of_pages(p_index, N, pages, A) :
  global ans
  
  max_students = max(students)

  if p_index == N :
    # If all books are included then find the maximum no of
    # pages for any student store minimum among the maximum
    ans = min(ans, max_students)
    return ans
  elif max_students > ans:
    return ans

  # ith book can go in any of the students
  for j in range(0, A) :
    # Include the book for jth student
    students[j] += pages[p_index]

    # Recursively call for the next book
    ans = minimum_number_of_pages(p_index + 1, N, pages, A)

    # If the ith book is not included for jth student
    students[j] -= pages[p_index]
  
  return ans

  # Function to minimize the maximum number of pages
def brute_force_minimum_number_of_pages(p_index, N, pages, A) :
  global ans
  
  if p_index == N :
    # If all books are included then find the maximum no of
    # pages for any student store minimum among the maximum
    ans = min(ans, max(students))
    return ans

  # ith book can go in any of the students
  for j in range(0, A) :
    # Include the book for jth student
    students[j] += pages[p_index]

    # Recursively call for the next book
    ans = minimum_number_of_pages(p_index + 1, N, pages, A)

    # If the ith book is not included for jth student
    students[j] -= pages[p_index]
  
  return ans

def func_execution_time(func, p_index, N, pages, A):
  start = time.perf_counter()
  func(p_index, N, pages, A)
  end = time.perf_counter()
  return end-start
  

if __name__ == '__main__':
  pages = [int(x) for x in input('numbers of pages: ').split()]
  A = int(input('number of students: '))
  students = [0] * A
  
  print('\nbrute force execution time:', func_execution_time(brute_force_minimum_number_of_pages, 0, len(pages), pages, A))
  ans = sys.maxsize
  print('backtracking execution time:', func_execution_time(minimum_number_of_pages, 0, len(pages), pages, A))