import  random
import sys

import matplotlib.pyplot as plt
import numpy as np





def insertionSort(A):
    global counter
    for index in range(1 , len(A)):
        key = A[index]
        j = index
        while key < A[ j -1] and j > 0:
            counter += 1
            A[j] = A[ j -1]
            j = j- 1

        A[j] = key
    return A
def insertionSort_Limit(left, right):
    temp_counter = 0
    A = []
    A.extend(left)
    A.extend(right)
    for index in range(1 , len(A)):
        key = A[index]
        j = index
        while key < A[j -1] and j > 0:
            temp_counter += 1
            A[j] = A[ j -1]
            j = j- 1

        A[j] = key
    return A, temp_counter


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
    return result, counter


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

    A, temp_Counter = insertionSort_Limit(left, right)
    counter+= temp_Counter

    return list(A)




counter = 0

def sortPloter ():
    global counter
    result = np.zeros((990,), int)
    for N in range(10, 1000):
        A = []
        # for i in range(0, N + 1):
        #     x = random.randint(0, 100000)
        #     if x not in A:
        #         A.append(x)
        for i in range(N, 0, -1):
            A.append(i)
        A = merge_sort(A)
        result[N-10] = counter
        counter = 0

    plt.plot([i for i in range(10, 1000)], result, 'b',[i for i in range(10, 1000)], [3 * i * i // 4 for i in range(10, 1000)], 'r' )
    plt.ylabel('Step Count')
    plt.xlabel("array size")
    plt.show()

#sortPloter()

# N = 100
# A = []
# A_worst = []
# x = 0
# for i in range(0, N+1):
#     x = random.randint(0, 100000)
#     if x not in A:
#         A.append(x)
#
# for i in range(N, 0, -1):
#     A_worst.append(i)
# print(A)
# A = merge_sort(A)
# #insertionSort(A_worst)
# print("\n\nSorted array is")
# print(counter)
# print(A)


def largest_Dec_N2(A):
    largest_decline = 0
    while len(A) > 0:
        x = A.pop()
        for i in range(0, len(A)):
            if abs(x - A[i]) > largest_decline:
                largest_decline = abs(x - A[i])

    print(largest_decline)

def largest_Dec_N(A):
    min = sys.maxsize * 2 + 1
    max = -(sys.maxsize * 2 + 1) - 1
    for i in A:
        if i < min:
            min = i
        elif i > max:
            max = i

    print(max - min)

def largest_Dec_lgN(A):

    if len(A) == 1:
        minu = maxu = A[0]
    else:
        middle = len(A) // 2
        left = A[:middle]
        right = A[middle:]
        lmin, lmax = largest_Dec_lgN(left)
        rmin, rmax = largest_Dec_lgN(right)
        minu = lmin if lmin < rmin else rmin
        maxu = lmax if lmax > rmax   else rmax
    return minu, maxu


A = [random.randint(3, 25) for i in range(10)]
print(A)
min_in , max_in = largest_Dec_lgN(A)
print(max_in - min_in)

