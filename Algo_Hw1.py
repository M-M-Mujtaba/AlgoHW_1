import  random
import matplotlib.pyplot as plt
import numpy as np





def insertionSort(A):
    global counter
    for index in range(1 , len(A)):
        key = A[index]
        j = index
        counter+= 1
        while key < A[ j -1] and j > 0:
            counter += 1
            A[j] = A[ j -1]
            j = j- 1

        A[j] = key
    return A


def merge(left, right):
    counter = 0
    result = []
    left_idx, right_idx = 0, 0
    while left_idx < len(left) and right_idx < len(right):
        # change the direction of this comparison to change the direction of the sort
        if left[left_idx] <= right[right_idx]:
            result.append(left[left_idx])
            left_idx += 1
        else:
            result.append(right[right_idx])
            right_idx += 1
        counter += 1


    if left:
        result.extend(left[left_idx:])
        counter += len(left[left_idx:])
    if right:
        result.extend(right[right_idx:])
        counter += len(right[right_idx:])
    return result, counter;

def merge_sort(m):
    global counter
    temp_Counter = 0

    if len(m) <= 1:
        return m

    middle = len(m) // 2
    left = m[:middle]
    right = m[middle:]

    left = merge_sort(left)
    right= merge_sort(right)

    A, temp_Counter = merge(left, right)
    counter+= temp_Counter

    return list(A)




counter = 0

def sortPloter ():
    global counter
    result = []
    for N in range(10, 10001):
        for i in range(0, N + 1):
            x = random.randint(0, 100000)
            if x not in A:
                A.append(x)
        A = merge_sort(A)
        result.append(counter)
        counter = 0



N = 100
A = []
A_worst = []
x = 0
for i in range(0, N+1):
    x = random.randint(0, 100000)
    if x not in A:
        A.append(x)

for i in range(N, 0, -1):
    A_worst.append(i)
print(A)
A = merge_sort(A)
#insertionSort(A_worst)
print("\n\nSorted array is")
print(counter)
print(A)