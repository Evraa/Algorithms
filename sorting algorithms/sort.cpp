#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>
#include <chrono> 
#include <cmath>
using namespace std;
using namespace std::chrono;
//Any Global variables
//Total size of the array that's being sorted
int Data_Size;


//Auxiliary functions
//Takes two pointers of the desired (to swap) variables and swaps their values
void swap_ptrs(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
//Generates a random number within the range [min:max)
int random(int min, int max) //range : [min, max)
{
	if (min == max)
		return min;
	if (min > max)
	{
		int temp = max;
		max = min;
		min = temp;
	}
	int range = max - min + 1;
	return rand() % range + min;
}

//For debuging function to print out vector's data

void printVector(vector<int> arr)
{
	int size = Data_Size;
	if (size == 0)
		return;
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	return;
}


//Selection Sort
//findMin function traverse the whole vector and returns a POINTER with the minimum values
//if start was NULL that means the vector has no initially minimum values, and is being called for the first time
int* findMin(vector<int> &arr,  int n , int* start = NULL)
{
	int size = n;
	if (size == 0)
		return NULL;
	int* min_ptr;
	if (!start)
		min_ptr = &arr[0];
	else
		min_ptr = start;

	int min = *min_ptr;
	int* end = &arr[size - 1];
	int* itr = min_ptr + 1;
	for (itr; itr <= end; itr++)
	{
		if (*itr < min)
		{
			min_ptr = itr;
			min = *min_ptr;
		}
	}
	return min_ptr;
}
//The main selection algorithm function
//
void Selection_sort(vector<int> &arr, int n=0)
{
	int size;
	if (n == 0)
		size = Data_Size; //Called for regular selection sort
	else
		size = n; //called for spesific selection sort

	if (size <= 1)
	{
		if (size == 0)
		{
			cout << "Error: Empty array of data recieved." << endl;
		}
		return;
	}
	//This call is done once, just to detect the VERY first element with the minimum value
	int* minimum_ptr = findMin(arr, size,NULL);
	int* ptr = &arr[0];
	if (!minimum_ptr)
		return;
	if (minimum_ptr != ptr)
		swap_ptrs(minimum_ptr, ptr);
	
	//Untill that point any vector has it's first index as the minimum

	int* end = &arr[size - 1];
	while (ptr <end) 
	{
		ptr++;
		int* minInArray = findMin(arr, size,ptr);
		if (!minInArray)
			return;
		if (minInArray != ptr)
			swap_ptrs(minInArray, ptr);
	}
}

//Insertion Sort
//Only one function, that starts at a 'moving' place takes its value and swap it at its place then returns to the 'next' number and traverse

void InsertionSort(vector<int> &arr)
{
	int size = Data_Size;
	if (size <= 1)
	{
		if (size == 0)
			cout << "Error: Empty array of data recieved." << endl;
		return;
	}

	int *moving, *next;
	//Assuming the first element is at its place
	//So we start at the second element
	moving = &arr[1];
	next = moving;
	const int *end = &arr[size - 1];
	while (next <= end)
	{
		//That's why next was pointing at moving, because we want to increase it before we traverse not after
		//another solution whould be do-while loops
		next++;
		while ( (moving != &arr[0]) && *moving < *(moving - 1))
		{
			swap_ptrs(moving, moving - 1);
			moving--;
		}
		moving = next;

	}
}


//Merge Sort

void merge(vector<int>& arr, int L, int M, int R)
{
	//Initializations
	int size1 = M - L + 1;
	int size2 = R - M;

	//Create Two arrays for left and right lists
	int *left = new int[size1];
	int *right = new int[size2];

	//Fill these two arrays with the data
	for (int i = 0; i < size1; i++)
		left[i] = arr[L + i];
	for (int i = 0; i < size2; i++)
		right[i] = arr[M + i + 1];

	//Iterative integers
	int i = 0, j = 0, k = L;
	//Compare and fill the main array untill one subarray is done
	while (i < size1 && j < size2)
	{
		//The equal sign here to make the algorithm STABLE
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	//Fill the main array with any remaining values in any of the two other arrays
	while (i < size1)
	{
		arr[k] = left[i];
		k++;
		i++;
	}
	while (j < size2)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
	return;
}
void MergeSort(vector<int>& arr, int L, int R)
{
	if (L < R)
	{
		int M = L + (R - L) / 2;
		MergeSort(arr, L, M);
		MergeSort(arr, M + 1, R);

		merge(arr, L, M, R);
	}
}
void CallMergeSort(vector<int>& arr)
{
	MergeSort(arr, 0, Data_Size - 1);
}


//Quick Sort
int partition (vector<int>& arr, int L, int R)
{
	//Assign a variable (first/last/random/median..)
	//I choose random
	//Partition index
	int pi = random(L,R);
	int pivot = arr[pi];

	int i = L - 1;
	for (int j = L; j < R ; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			swap_ptrs(&arr[i], &arr[j]);
		}
		//else: Do nothing
	}
	swap_ptrs(&arr[i+1],&arr[pi]);
	return i + 1;//Our PI
}
void quickSort(vector<int>& arr, int L, int R)
{
	if (L < R)
	{
		int pi = partition(arr, L, R);
		quickSort(arr, L, pi - 1);
		quickSort(arr, pi + 1, R);
	}
}
void callQuickSort(vector <int>& arr)
{
	quickSort(arr, 0, Data_Size - 1);
	return;
}


//Additional algorithm
void CountingSort(vector<int>& arr, int size, int maxElement)
{
	int accArraySize = maxElement + 1;
	//The array range from 0:max
	int* accumulate = new int[accArraySize];
	for (int i = 0; i < accArraySize; i++)
		accumulate[i] = 0;
	int x;
	for (int i=0; i<size; i++)
		accumulate[arr[i]]++;

	//int* Sorted = new int[mainArraySize];
	int place = 0;
	for (int i = 0; i < accArraySize; i++)
	{
		int occurrs = accumulate[i];
		for(int j = 0; j < occurrs; j++)
		{
			arr[place] = i;
			place++;
		}
	}
}

//Modified the selection sort to work with Merge-modified
//My modification was to take a sub-vector of the main vector and operate selection sort at
//Some modifications would be:
		//instead of findMin function I'ld have used a binary search function
		//instead of taking the sub vector and storing it in another one then sorting and finally returning it back
			//I could've take two opinters (start and end) and apply selection sort at their range
void SelectionSortModified(vector<int>& arr, int lower,int upper)
{
	vector<int> temp;
	int size = upper - lower + 1;
	for (int i = lower; i <= upper; i++)
		temp.push_back(arr[i]);

	Selection_sort(temp,size);

	int k = 0;
	for (int i = lower; i <= upper; i++)
		arr[i] = temp[k++];
	return;
}
void mergeSortModified(vector<int>& arr, int L, int R,int size)
{
	if (L < R)
	{
		int M = L + (R - L) / 2;
		size = ceil(size / 2.0);
		if (size < 200)
		{
			SelectionSortModified(arr, L,M);
			SelectionSortModified(arr, M+1, R);
		}
		else
		{
			mergeSortModified(arr, L, M,size);
			mergeSortModified(arr, M + 1, R,size);
		}
		merge(arr, L, M, R);
	}
}
//Hybird Sort
//consists of 2 algorithms (Merge, Insertion)
//First for data greater than 100 elements applyung Merge sort
//then for less than 100 elements, applying Insertion Sort

void HybirdSort(vector<int>&arr)
{
	int size = Data_Size;
	mergeSortModified(arr, 0, size - 1, size);
	return;
}



//Heap Sort algorithm
void Heapify(vector<int>&vec, int size, int i)
{
	int largest = i;
	int left =( 2 * i )+1;
	int right = left + 1;
	if (left<size && vec[left]>vec[largest])
		largest = left;

	if (right<size && vec[right]>vec[largest])
		largest = right;

	//If largest is not ROOT
	if (largest != i)
	{
		swap(vec[i], vec[largest]);
		Heapify(vec, size, largest);
	}
	return;
}

void callHeapSort(vector<int>& vec)
{
	int size = Data_Size;
	//Build Max-Heap, TOP-Bottom
	for (int i = size/2 - 1; i >=0; i--)
		Heapify(vec, size, i);

	//One by one extract elemetns from the array, then heapify
	for (int i = size - 1; i >= 0; i--)
	{
		//vec[0] is the MAX (root)
		swap_ptrs(&vec[0], &vec[i]);
		Heapify(vec, i, 0);
	}
	return;
}


int main(int argc, char* argv[])
{
	
	//argc is an integer number for # of elemnts inserted
	//argv[1]:argv[4] contains the input strings
	string algoName = argv[4];
	string inputFile = argv[2];
	string outputFile = argv[3];
	int algorithmNumber = stoi(argv[1]);
	string state =" "; //If the data file is sorted or not !

	if (algorithmNumber < 0 || algorithmNumber > 4)
	{
		cout << "An incorrect number of algorithm was entered, please make sure to insert a number between 0:4" << endl;
		return 0;
	}

	//Reading data from the file
	ifstream myfile(inputFile);
	vector<int> test;
	int c = 0;
	if (myfile.is_open())
	{
		cout << "Reading the data from file at: " << inputFile << endl;
		int x;
		while (myfile >> x)
		{	
			test.push_back(x);
			c++;
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file at: " << inputFile<< endl;
		return 0;
	}
	Data_Size = c;
	
	//Applying the algorithm stated	
	auto start = high_resolution_clock::now();
	switch (algorithmNumber)
	{
	case 0: {
		cout << "Applying the sorting algorithm: Selection" << endl;
		Selection_sort(test);
	}break;
	case 1: {
		cout << "Applying the sorting algorithm: Insertion" << endl;
		InsertionSort(test);
	}break;
	case 2: {
		cout << "Applying the sorting algorithm: Merge" << endl;
		CallMergeSort(test);
	}break;
	case 3: {
		cout << "Applying the sorting algorithm: Quick" << endl;
		callQuickSort(test);
	}break;
	case 4: {
		cout << "Applying the sorting algorithm: Hybird" << endl;
		HybirdSort(test);
  case 5: {
  cout << "Applying the sorting algorithm: Heap" << endl;
  callHeapSort(test);
	}break;

	}
	auto stop = high_resolution_clock::now();
	auto time = duration_cast<microseconds>(stop - start);
	//Time in MILLISECONDS
	double duration = time.count() / (pow(10, 3)); 
	
	//Typing the Sorted array
	ofstream outFile;
	ofstream outFile_Sorted;
	cout << "Outputing the sorted data at: " << outputFile << endl;
	outFile_Sorted.open (outputFile);

	for (int i = 0; i < Data_Size; i++)
	{
		outFile_Sorted << test[i] << " ";
	}
	outFile_Sorted.close();	
	
	cout << "Typing its performance at: " << algoName << endl;
	//Depending on what algorithm we are applying
	outFile.open(algoName,ios::app);
	outFile <<Data_Size<< " Unsorted data   "<< "Time in millis: " << duration << endl;
	outFile.close();



	cout << "Sorting the sorted data with algorithm: " << algoName << endl;
	auto start2 = high_resolution_clock::now();
	switch (algorithmNumber)
	{
	case 0: {
		cout << "Applying the sorting algorithm: Selection" << endl;
		Selection_sort(test);
	}break;
	case 1: {
		cout << "Applying the sorting algorithm: Insertion" << endl;
		InsertionSort(test);
	}break;
	case 2: {
		cout << "Applying the sorting algorithm: Merge" << endl;
		CallMergeSort(test);
	}break;
	case 3: {
		cout << "Applying the sorting algorithm: Quick" << endl;
		callQuickSort(test);
	}break;
	case 4: {
		cout << "Applying the sorting algorithm: Hybird" << endl;
		HybirdSort(test);
  case 5: {
  cout << "Applying the sorting algorithm: Heap" << endl;
  callHeapSort(test);
	}break;
	}

	auto stop2 = high_resolution_clock::now();
	auto time2 = duration_cast<microseconds>(stop2 - start2);
	//Time in MILLISECONDS
	double duration2 = time2.count() / (pow(10, 3));

	cout << "Typing its performance at: " << algoName << endl;
	//Depending on what algorithm we are applying
	outFile.open(algoName, ios::app);
	outFile << Data_Size << " Sorted data   " << "Time in millis: " << duration2 << endl;
	outFile.close();

	cout << "Finished" << endl;
	return 0;
}
