#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <vector>
using namespace std;

unsigned long ccount = 0;
bool lt(int a, int b) 
{
	ccount++;
	return (a < b);
}
double executeAndTime(void (*func)(vector<int>&, int, int), vector<int>& a, int left, int right, int tu = 1) 
{
	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	func(a, left, right);
	chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	if (tu == 3)
		return chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	else if (tu == 6)
		return chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	else if (tu == 9)
		return chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
	else
		return chrono::duration_cast<std::chrono::seconds>(end - begin).count();
}
class Node
{
public:
	string num;
	Node* next;
};
class List
{
public:
	Node* head;
	Node* tail;
	Node* temp;
	bool isEmpty()
	{
		return head == NULL;
	}
	List()
	{
		head = NULL;
		tail = NULL;
	}

	void insert(string x)
	{
		temp = new Node;
		temp->num = x;
		if (isEmpty())
		{
			temp->next = NULL;
			tail = temp;
		}
		else
			temp->next = head;
		head = temp;
	}

	void insertAtEnd(string x)
	{
		temp = new Node;
		temp->num= x;
		temp->next = NULL;
		if (isEmpty())
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}

	void remove(string x)
	{
		temp = head;
		Node* prev;
		while (temp->next != NULL && temp->num != x)
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp->num == x)
		{
			prev->next = temp->next;
			delete temp;
		}
		else if (temp->next == NULL)
		{
			cout << "Error: Number Not found..." << endl;
		}
	}

	void find(string x)
	{
		int i;
		for (i = 1, temp = head; temp->next != NULL && temp->num != x; temp = temp->next, i++);
		if (temp->num == x)
		{
			cout << "Found at position:" << i << endl;
		}
		else if (temp->next == NULL)
		{
			cout << "Error: Number Not found..." << endl;
		}
	}

	void display()
	{
		if (!isEmpty())
		{
			for (temp = head; temp != NULL; temp = temp->next)
				cout << temp->num << " ";
			cout << endl;
		}
		else
		{
			cout << "List is Empty!" << endl;
		}
	}
	/* Given a reference (pointer to pointer) to the head of a list
   and a position, deletes the node at the given position */
	void deleteNode(Node** head_ref, int position) //src: geeks4geeks
	{
		// If linked list is empty 
		if (*head_ref == NULL)
			return;

		// Store head node 
		Node* temp = *head_ref;

		// If head needs to be removed 
		if (position == 0)
		{
			*head_ref = temp->next;   // Change head 
			free(temp);               // free old head 
			return;
		}

		// Find previous node of the node to be deleted 
		for (int i = 0; temp != NULL && i < position - 1; i++)
			temp = temp->next;

		// If position is more than number of ndoes 
		if (temp == NULL || temp->next == NULL)
			return;

		// Node temp->next is the node to be deleted 
		// Store pointer to the next of node to be deleted 
		Node* next = temp->next->next;

		// Unlink the node from linked list 
		free(temp->next);  // Free memory 

		temp->next = next;  // Unlink the deleted node from list 
	}
}; //src https://gist.github.com/harish-r/873ce92a91bb7b685b81
void delNodesWith1(List ls)
{
	// delete nodes with 1
}
void delNodesWith0(List ls)
{
	//delete nodes with 0
}
int retNum(string num) //converts a string number to its int representation
{
	int retVal = 0;
	int len = num.length();
	int power = pow(2, len - 1);
	for (int i = 0; i < len; i++)
	{
		if (num[i] == '1')
		{
			retVal += power;
		}
		power /= 2;
	}
	return retVal;
}
void Q6a()
{
	Node *a = new Node();
	Node *b = new Node(); 
	//Node *c = new Node(); 
	Node *d = new Node();
	a->next = b;
	b->next = d;
	//c->next = d;
	d->next = nullptr; //linked the nodes
	a->num = "10";
	b->num = "00";
	d->num = "11";

	int uCount = pow(2, a->num.length()) - 1; // total sum;
	int totalSum = 0;
	for (int j = uCount; j > 0; j--)
	{
		totalSum += j;
	}
	cout << "Total sum: " << totalSum << endl;
	//lets say a is the head node
	Node* n = a;
	while (n != NULL) {
		cout << n->num << endl;
		totalSum -= retNum(n->num);
		n = n->next;
	}
	cout << "The missing number is: " << totalSum << endl;
}
void Q6b()
{
	List ls;

	ls.insertAtEnd("000");
	ls.insertAtEnd("001");
	//ls.insertAtEnd("010"); the missing node
	ls.insertAtEnd("011");
	ls.insertAtEnd("100");
	ls.insertAtEnd("101"); 
	ls.insertAtEnd("110");
	ls.insertAtEnd("111");
	//ls.display(); // insertion done

	int countI = ls.head->num.length();
	countI = pow(2, countI);
	countI /= 2; // countI = 4
	char missingChar;
	int counter = 0;
	string res;
	for (int i = 0; i < ls.head->num.length(); i++)
	{
		counter = countI;
		if (!ls.isEmpty())
		{
			for (ls.temp = ls.head; ls.temp != NULL; ls.temp = ls.temp->next)
			{
				//cout << ls.temp->num[i] << " ";
				if (ls.temp->num[i] == '0')
				{
					counter--;
				}
			}
			if (counter == 0)
			{
				res.append("1");
				//delNodesWith0(ls);
				// i have to check
				// if ith position == 0 
				// remove
				int refcount = 0;
				Node* t;
				bool done = false;
				for (t = ls.head; t != NULL; t = t->next)
				{
					if (t->num[i] == '0')
					{
						ls.deleteNode(&ls.head, refcount);
						refcount = 0;
						done = true;
					}
					if (!done)
						refcount++;
					else
						done = false;
				}
			}
			else
			{
				res.append("0");
				int refcount = 0;
				Node* t;
				bool done = false;
				for (t = ls.head; t != NULL; t = t->next)
				{
					if (t->num[i] == '1')
					{
						ls.deleteNode(&ls.head, refcount);
						refcount = 0;
						done = true;
					}
					if (!done)
						refcount++;
					else
						done = false;
				}
			}
		}
		countI /= 2; //after nodes deletion
	}
	cout << res << endl;
}
void Q4b()
{
	const int Sz = 5;
	int arr[] = { 2,4,1,3,5 };
	int retCount = 0;
	for (int i = 0; i < Sz; i++)
	{
		for (int j = i; j < Sz; j++)
		{
			if (arr[i] > arr[j])
			{
				retCount++;
			}
		}
	}
	cout << retCount << endl;
}
int countCrossInversions(int arr[], int temp[], int left, int mid, int right)
{
	int i, j, k;
	int inv_count = 0;

	i = left; /* i is index for left subarray*/
	j = mid; /* j is index for right subarray*/
	k = left; /* k is index for resultant merged subarray*/
	while ((i <= mid - 1) && (j <= right)) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {
			temp[k++] = arr[j++];
			inv_count = inv_count + (mid - i);
		}
	}
	while (i <= mid - 1)
		temp[k++] = arr[i++];
	while (j <= right)
		temp[k++] = arr[j++];
	for (i = left; i <= right; i++)
		arr[i] = temp[i];
	//cout << inv_count << " ";
	return inv_count;
}
int countInversions(int* A, int * t, int left, int right)
{
	int mid, x = 0, y = 0, z = 0;
	if (left < right)
	{
		mid = (left + right) / 2;
		x = countInversions(A, t, left, mid);
		y = countInversions(A, t, mid + 1, right);
		z = countCrossInversions(A, t, left, mid + 1, right);
		//cout << x << " " << y << " " << z << endl;	
	}
	return x + y + z;
}
void Q4c()
{
	int arr[] = { 5,6,8,0,1 };
	int t[5];
	cout << "no. of inversions " << countInversions(arr, t, 0, 4);
}
void merge4d(int* array,int * p, int l, int m, int r) {
	int i, j, k, nl, nr;
	//size of left and right sub-arrays
	nl = m - l + 1; nr = r - m;
	int* larr = new int[nl];
	int* rarr = new int[nr];

	int* plarr = new int[nl];
	int* prarr = new int[nr];
	//fill left and right sub-arrays
	for (i = 0; i < nl; i++)
	{
		larr[i] = array[l + i];
		plarr[i] = p[l + i];
	}
	for (j = 0; j < nr; j++)
	{
		rarr[j] = array[m + 1 + j];
		prarr[j] = p[m + 1 + j];
	}
	i = 0; j = 0; k = l;
	//marge temp arrays to real array
	while (i < nl && j < nr) {
		if (larr[i] <= rarr[j]) {
			p[k] = plarr[i];
			array[k] = larr[i];
			i++;
		}
		else {
			p[m] = prarr[j];
			array[k] = rarr[j];
			j++;
		}
		k++;
	}
	while (i < nl) {       //extra element in left array
		array[k] = larr[i];
		p[k] = plarr[i];
		i++; k++;
	}
	while (j < nr) {     //extra element in right array
		array[k] = rarr[j];
		p[k] = prarr[j];
		j++; k++;
	}
	delete larr, rarr;
}
void mergeSort4d(int* array,int * p, int l, int r) {
	int m;
	if (l < r) {
		int m = l + (r - l) / 2;
		// Sort first and second arrays
		mergeSort4d(array,p, l, m);
		mergeSort4d(array,p, m + 1, r);
		merge4d(array,p, l, m, r);
	}
}
int countIntersections(int* P, int* Q, int left, int right)
{
	mergeSort4d(Q, P, 0, 4);
	//create another array with same arr size for reusability of the 
	//count inversions code;
	int temp[5];
	return countInversions(P, temp, 0, 4);
}
void Q4d()
{
	int P[] = { 1,3,2,6,4 };
	int Q[] = { 16,12,13,10,5 };
	cout << "no. of intersections " << countIntersections(P, Q, 0, 4);
}
//courtesy of tutorialspoint
void merge(int* array, int l, int m, int r) {
	int i, j, k, nl, nr;
	//size of left and right sub-arrays
	nl = m - l + 1; nr = r - m;
	int * larr = new int[nl];
	int * rarr = new int[nr];
	//fill left and right sub-arrays
	for (i = 0; i < nl; i++)
		larr[i] = array[l + i];
	for (j = 0; j < nr; j++)
		rarr[j] = array[m + 1 + j];
	i = 0; j = 0; k = l;
	//marge temp arrays to real array
	while (i < nl && j < nr) {
		if (lt(larr[i] ,rarr[j])) {
			array[k] = larr[i];
			i++;
		}
		else {
			array[k] = rarr[j];
			j++;
		}
		k++;
	}
	while (i < nl) {       //extra element in left array
		array[k] = larr[i];
		i++; k++;
	}
	while (j < nr) {     //extra element in right array
		array[k] = rarr[j];
		j++; k++;
	}
	delete larr, rarr;
}
void mergeSort(int* array, int l, int r) {
	int m;
	if (lt(l , r)) {
		int m = l + (r - l) / 2;
		// Sort first and second arrays
		mergeSort(array, l, m);
		mergeSort(array, m + 1, r);
		merge(array, l, m, r);
	}
}

void merge(vector<int>& arr, int left, int right, int mid)
{
	int* leftArray = new int[mid - left + 1];
	int* rightArray = new int[right - mid];


	for (int i = 0; i < (mid - left + 1); i++)
	{
		leftArray[i] = arr[left + i];
	}

	for (int j = 0; j < (right - mid); j++)
	{
		rightArray[j] = arr[mid + 1 + j];
	}

	int k = 0;
	int l = 0;
	int m = left;

	while ((k < mid - left + 1) && (l < right - mid))
	{
		if (lt(leftArray[k], rightArray[l]))
		{
			arr[m] = leftArray[k];
			m++;
			k++;
		}
		else
		{
			arr[m] = rightArray[l];
			m++;
			l++;
		}
	}
	while (k < mid - left + 1)
	{
		arr[m] = leftArray[k];
		m++;
		k++;
	}
	while (l < right - mid)
	{
		arr[m] = rightArray[l];
		m++;
		l++;
	}
}
void mergeSort(vector<int>& arr, int left, int right)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, right, mid);
	}
}
//courtesy of geeks4geeks
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l<n && lt(arr[largest],arr[l]))
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && lt( arr[largest], arr[r]))
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}
}
void heapify(vector<int>& arr, int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;


	if (l < n && lt(arr[largest], arr[l]))
		largest = l;


	if (r < n && lt(arr[largest], arr[r]))
		largest = r;


	if (largest != i)
	{
		swap(arr[i], arr[largest]);


		heapify(arr, n, largest);
	}
}
void heapSort(vector<int>& arr, int left, int n)
{

	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);


	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);

		heapify(arr, i, 0);
	}
}
void Q5b()
{
	const int aSize = 1000000, aCount = 10;
	int** arr = new int* [aCount];
	for (int i = 0; i < aCount; i++)
	{
		arr[i] = new int[aSize];
		for (int j = 0; j < aSize; j++)
		{
			arr[i][j] = rand() % aSize;
		}
	}
	long int count = 0;
	cout << "Heap Sort" << endl;
	for (int i = 0; i < aCount; i++) //there seems to be an error here
	{
		ccount = 0;
		heapSort(arr[i], aSize);
		count += ccount;
		cout << ccount << endl;
	} // heap sort
	count /= 10;
	cout << "AVG" << count << endl;
	for (int i = 0; i < aCount; i++)
	{
		for (int j = 0; j < aSize; j++)
		{
			arr[i][j] = rand() % aSize;
		}
	}
	count = 0;
	//now test for merge sort
	cout << "Merge Sort" << endl;
	for (int i = 0; i < aCount; i++)
	{
		ccount = 0;
		mergeSort(arr[i], 0, aSize);
		count += ccount;
		cout << ccount << endl;
	}
	count /= 10;
	cout << "AVG" << count << endl;
}
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && lt(key,arr[j])) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
void insertionSort(vector<int>& arr, int left, int right)
{
	int i, key, j;
	for (i = left; i <= right; i++)
	{

		key = arr[i];
		j = i - 1;

		while (j >= 0 && lt(key, arr[j]))
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}
void Q5c()
{
	int arrCount = 10;
	int arrSize1 = 100000;
	int arrSize2 = 8;
	int** a;
	int** b;
	a = new int* [arrCount];
	b = new int* [arrCount];
	for (int i = 0; i < arrCount; i++)
	{
		a[i] = new int[arrSize1];
		b[i] = new int[arrSize1];
	}
	for (int i = 0; i < arrCount; i++)
	{
		for (int j = 0; j < arrSize1; j++)
		{
			a[i][j] = rand() % arrSize1;
			b[i][j] = rand() % arrSize1;
		}
	}
	long count = 0;
	for (int i = 0; i < arrCount; i++)
	{
		ccount = 0;
		insertionSort(a[i], arrSize1);
		count += ccount;
		cout << ccount << endl;
	}
	count /= 10;
	cout << "AVG: " << count << endl;

	count = 0;
	for (int i = 0; i < arrCount; i++)
	{
		ccount = 0;
		mergeSort(b[i],0,arrSize1-1);
		count += ccount;
		cout << ccount << endl;
	}
	count /= 10;
	cout << "AVG: " << count << endl;
}
void Q5d()
{
	int C[] = { 4,5,-2,0,11,25,6,20};
	vector<int> vnum(C, C + 8);//or push_back random values
	for (int i = 0; i < 1000000; i++)
	{
		vnum.push_back(rand() % 1000);
	}
	ccount = 0;
	sort(vnum.begin(), vnum.end(), lt);//lt is function pointer
	cout << "Number of comparisons: " << ccount << endl;
}
void printArr(int* arr, int size)
{
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}
void sort(vector<int>& v, int l, int r)
{
	sort(v.begin(), v.end(), lt);
}
void Q8()
{
	//(a)
	vector<int> v;
	int tccount = 0;
	double tTime = 0;
	int* arr1;
	int n = 0;
	int size = 1000000;
	double time = 0;

	for (int i = 0; i < 10; i++)
	{
		v.clear();
		for (int j = 0; j < size; j++)
		{
			v.push_back(rand());
		}
		ccount = 0;
		time = executeAndTime(insertionSort, v, 0, size - 1, 3);
		cout << i + 1 << "Sort:" << endl;
		cout << "#comparisons: " << ccount << endl;
		cout << "Time: " << time << " secs" << endl;
		tTime += time;
		tccount += ccount;


	}
	cout << "avg time: " << tTime / 10 << endl;
	cout << "avg comparisons " << tccount / 10 << endl;

}

int main()
{
	//srand(time(NULL));
	Q6b();

	
	return 0;
}