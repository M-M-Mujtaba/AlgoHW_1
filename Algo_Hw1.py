import random
import sys

import matplotlib.pyplot as plt
import numpy as np


def insertionSort(A):
    global counter
    for index in range(1, len(A)):
        key = A[index]
        j = index
        while key < A[j - 1] and j > 0:
            counter += 1
            A[j] = A[j - 1]
            j = j - 1

        A[j] = key
    return A


def insertionSort_Limit(left, right):  # combines left and right array then
    # performs insertion sort
    temp_counter = 0
    A = []
    A.extend(left)
    A.extend(right)
    for index in range(len(left), len(A)):
        key = A[index]
        j = index
        while key < A[j - 1] and j > 0:
            temp_counter += 1
            A[j] = A[j - 1]
            j = j - 1

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
    right = merge_sort(right)

    A, temp_Counter = insertionSort_Limit(left, right)
    counter += temp_Counter

    return list(A)


counter = 0


def sortPloter():
    global counter
    result = np.zeros((992,), int)
    for N in range(8, 1000):
        A = []
        for i in range(0, N):
            x = random.randint(0, 10000)
            if x not in A:
                A.append(x)
        # for i in range(N, 0, -1):
        #     A.append(i)
        largest_Dec_lgN(A)
        result[N - 10] = counter
        counter = 0

    plt.plot([i * 2 for i in range(8, 1000)], 'r', [i for i in range(8, 1000)], result, 'b',
             [i for i in range(8, 1000)], [np.log2(i) for i in range(8, 1000)], 'r')
    plt.ylabel('Step Count')
    plt.xlabel("array sizes")
    plt.show()


# sortPloter()
#
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
    global counter
    while len(A) > 0:
        x = A.pop()
        for i in range(0, len(A)):
            counter += 1
            if abs(x - A[i]) > largest_decline:
                largest_decline = abs(x - A[i])

    # print(largest_decline)


def largest_Dec_N(A):
    largest_dec = -(sys.maxsize * 2 + 1) - 1
    max = -(sys.maxsize * 2 + 1) - 1
    max_ind = 0
    min_ind = 0
    f_max_ind = 0
    global counter
    for i in range(len(A)):
        if A[i] > max:
            max = A[i]
            max_ind = i
            counter += 1
        else:
            dec = max - A[i]
            if dec > largest_dec:
                largest_dec = dec
                min_ind = i
                f_max_ind = max_ind
            counter += 1

    print("Dif = {}, position max = {} and position min = {}".format(largest_dec, f_max_ind, min_ind))


def find_min_max_ind(A, min, max):
    min_ind = 0
    max_ind = 0
    for i in range(len(A)):
        if A[i] == min:
            min_ind = i
        elif A[i] == max:
            max_ind = i
    return max_ind, min_ind


def merge_dec(r, lmax, dec_max):
    min_ = 0
    f_max = lmax
    global counter
    for i in r:
        if i > lmax:
            lmax = i
        else:
            if (lmax - i) > dec_max:
                dec_max = lmax - i
                min_ = i
                f_max = lmax
        counter += 1
    return lmax, f_max, min_, dec_max


def largest_Dec_lgN(A):
    global counter
    if len(A) == 1:
        return A[0], A[0], A[0], 0
    else:
        l = A[:len(A) // 2]
        r = A[len(A) // 2:]
        counter += 1
        max, min, maxr, dec = largest_Dec_lgN(l)
        max, maxr, min, dec = merge_dec(r, max, dec)
    return max, maxr, min, dec


# Q10
def merge_score(A, l_score, r_score, l, r, m):
    counter = 0
    l_val = A[m]
    r_val = A[m + 1]
    for i in range(m + 1, r + 1):
        if A[i] > l_val:
            r_score[m] = A[i]
            i = r
    for i in range(m, -1, -1):
        if A[i] > r_val:
            l_score[m + 1] = A[i]
            break
    return counter


def score_left_right(A, l_score, r_score, l, r):
    global counter
    temp_Counter = 0
    middle = 0
    if l < r:
        middle = (l + r) // 2
        score_left_right(A, l_score, r_score, l, middle)
        score_left_right(A, l_score, r_score, middle + 1, r)
        temp_Counter = merge_score(A, l_score, r_score, l, r, middle)
        counter += temp_Counter
    return list(A)


# print(A)
# max, maxr ,min, dec = largest_Dec_lgN(A)
# max, min = find_min_max_ind(A,min, maxr)
# print("Dif = {}, position max = {} and position min = {}".format(dec, max, min))


# A = [random.randint(3, 25) for i in range(10)]
#
# print(A)
# min, max = largest_Dec_lgN(A)
# print(find_min_max_ind(A,min, max ))
# min_in , max_in = largest_Dec_lgN(A)
# print(max_in - min_in)

# sortPloter()
# # Q9
# np.random.seed(647534)
# z = np.random.random_integers(0, 25, (4, 4))
# x, y = z[:, 0], z[:, 1]
# color = ['b', 'g', 'r', 'm', 'c', 'y', 'k', 'w']
# for i in range(len(x)):
#     plt.plot(x[i], y[i], '{}+'.format(color[i]))
# plt.show()
# r = np.sqrt(x ** 2 + y ** 2)
# t = np.arctan2(y, x)
# for i in range(len(x)):
#     plt.polar(r[i], t[i], '{}+'.format(color[i]))
# plt.show()
# print(r)
# print(t)
# Q11
#
# def Mul(i, a):
#     if i == 0:
#         return a
#     else:
#         a_up= a[:len(a)//2]
#         a_down = a[len(a)//2: ]
#
#         a1 = Mul(i-1, a_up)
#         a2 = Mul(i-1, a_down)
#         Up = np.add(a1, a2)
#         Du = np.subtract(a1, a2)
#         return np.concatenate((Up, Du), axis = 0)
#
# np.random.seed(65464)
# A = np.zeros(4, int)
#
# for i in range(0, 4):
#     x = np.random.random_integers(1, 100, (1))[0]
#     if x not in A:
#         A[i] =x
# print(A)
# A = Mul(2,A)
# print(A)

from dataclasses import dataclass


@dataclass
class p:  # used in state grid for to store cost , depth and parent information
    x: int  # the cost to reach this state
    y: int  # to store the level of the node
    color: str

z = np.random.random_integers(0, 25, (2, 10))
Points = [p(z[0][i], z[1][i], 'r') for i in range(10)]
print(z)
print(Points)
sorted_points_x = sorted(Points, key = lambda e: e.x)
max_y = -10000000
for i in range(len(sorted_points_x)-1, -1, -1):
    if sorted_points_x[i].y > max_y:
        max_y = sorted_points_x[i].y
    else:
        sorted_points_x[i].color = 'b'


for p in Points:
    plt.plot(p.x, p.y, '{}+'.format(p.color))
plt.show()