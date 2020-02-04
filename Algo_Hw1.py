


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


def Merge(arr, l, r, m):
    leftArr = arr[l: m+1]
    rightArr = arr[m+1: r+1]

    # merge sort : copy data back with comparision
    li = 0  # Initial index of left array
    ri = 0  # Initial index of rogjt subarray
    ai = l  # Initial index of sorting array

    while li < len(leftArr) and ri < len(rightArr):
        if leftArr[li] <= rightArr[ri]:
            arr[ai] = leftArr[li]
            li += 1
        else:
            arr[ai] = rightArr[ri]
            ri += 1
        ai += 1

    # Copy the remaining elements of L[], if there
    # are any
    while li <len(leftArr):
        arr[ai] = leftArr[li]
        li += 1
        ai += 1

    # Copy the remaining elements of R[], if there
    # are any
    while ri < len(rightArr):
        arr[ai] = rightArr[ri]
        ri += 1
        ai += 1

counter = 0
# Recursive function that sorts the input array by breaking it into sub problems and then merging them intelligently
def mergeSort(A, l, r): # l is the left index and r is the right index
    global counter
    if l < r:
        mid = (l + r) // 2
        counter += 1
        mergeSort(A, l, mid)
        counter += 1
        mergeSort(A, mid + 1, r)

        Merge(A, l, r, mid)


import  random

N = 10000
A = []
x = 0
for i in range(0, N):
    x = random.randint(0, 10000000)
    if x not in A:
        A.append(x)
print(A)
#mergeSort(A, 0, N - 1)
insertionSort(A)
print("\n\nSorted array is")
print(counter)
print(A)