#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <chrono> 
using namespace std;
using namespace std::chrono;

//Global Variables
//Map of Combinations
//Gets all the nC2 of the nudes, used later
map<int, int> combinations;
int v;
int e;
int* arr1;
int* arr2;
int validEdges;


// function to convert decimal to binary 
vector<int> decToBinary(int n)
{
	// vector to store binary number 
	vector<int> binaryNum;

	// counter for binary array 
	int i = 0;
	while (n > 0) {

		// storing remainder in binary vector 
		int num = n % 2;
		binaryNum.push_back(num);
		n = n / 2;
		i++;
	}

	return binaryNum;
}
int* getBinary(long int itr, int v)
{
	//First get the binary sequence
	vector<int> binary = decToBinary(itr);

	int size = binary.size();
	//Then add zeros on the left till we get v
	if (size == v)
	{
		int k = size - 1;
		int* combinations = new int[v];
		for (int i = 0; i < v; i++)
		{
			combinations[i] = binary[k];
			k--;
		}
		return combinations;
	}
	else {
		int difference = v - size;
		int* combinations = new int[v];
		int i = 0;
		for (i; i < difference; i++)
		{
			combinations[i] = 0;
		}
		int k = size - 1;
		for (i; i < v; i++)
		{
			combinations[i] = binary[k];
			k--;
		}


		return combinations;
	}
}


//Gets count of ones in an array
int numbersOfOnes(int* arr, int size)
{
	int num = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == 1)
			num++;
	}
	return num;
}

//Converts the 0-1 array to its indecies values
int* convert(int* comb, int v)
{
	int* returned = new int[v];
	int l = 0;
	for (int i = 0; i < v; i++)
	{
		if (comb[i] == 1)
		{
			returned[l] = i;
			l++;
		}
		else {
			returned[l] = -1;
			l++;
		}

	}
	return returned;
}

int checkMaxPath(int oldPath, int newPath)
{
	if (newPath > oldPath)
		return newPath;
	return oldPath;
}

int matchThis(int*arr1, int*arr2, int* comb, int size, int edgesRequired, int totalEdges, int nudes)
{
	int edgesCollected = 0;
	int path = 0;
	if (edgesRequired == 2)
		edgesRequired = 1;
	if (edgesRequired > totalEdges)
		return 0;
	int p1;
	int p2;
	for (int i = 0; i < totalEdges; i++)
	{
		p1 = arr1[i];
		p2 = arr2[i];
		int ev = 0;
		for (int k = 0; k < size; k++)
		{
			if (comb[k] == p1 || comb[k] == p2)
				ev++;
			if (ev == 2)
			{
				edgesCollected++;
				break;
			}
		}
	}

	if (edgesRequired == 1 && edgesCollected == 1)
		return 2;

	if (edgesCollected == edgesRequired)
		return nudes;
	return 0;
}

void combinationsCalculation()
{
	combinations.insert({ 2,1 });
	for (int i = 3; i < v + 1; i++)
	{
		auto ptr = combinations.end();
		ptr--;
		int start = ptr->first;
		int end = ptr->second;
		combinations.insert({ i,(end + start) });
	}

}

void solve()
{
	//Total size of combinations
	int iterations = pow(2, v);
	iterations--;
	int* comb = new int[v];
	int* numberedCombinations = new int[v];
	int path = 0;
	int maxPath = 0;
	int numb;
	//Main loop:
	while (iterations > 0)
	{
		comb = getBinary(iterations, v);
		numberedCombinations = convert(comb, v);
		numb = numbersOfOnes(comb, v);

		while (numb > 0)
		{
			int rquiredEdges;
			if (numb == 1)
			{
				rquiredEdges = 0;
				maxPath = checkMaxPath(maxPath, 1);
				numb = 0;
			}
			else {
				if (numb == 2)
					rquiredEdges = 2;
				else
				{
					auto ptr = combinations.find(numb);
					rquiredEdges = ptr->second;
				}
				if (rquiredEdges != 0)
					path = matchThis(arr1, arr2, numberedCombinations, v, rquiredEdges, validEdges, numb);

				//check on path, and print the first one got
				if (path > 0)
				{
					maxPath = checkMaxPath(maxPath, path);
				}
				numb = 0;
			}
		}


		//cout <<"Itr: "<<iterations<<"  max: "<< maxPath << endl;
		iterations--;
	}

	//Gets here only if path == 0
//	cout << maxPath << endl;
	return;
}
int main()
{
	ofstream fout_v,fout_time;
	fout_v.open("vertices.txt");
	fout_time.open("time.txt");
	for (int i = 2; i < 30; i++)
	{
		v = i;
		fout_v << v << endl;
		combinationsCalculation();
		e = combinations[v];
		validEdges = e;
		//cout << "Vertices: " << v << "  Edges: " << e << endl;
		arr1 = new int[e];
		arr2 = new int[e];
		int p1 = 0;
		for (int j = 0; j < v; j++)
		{
			for (int l = j+1; l < v; l++)
			{
				arr1[p1] = j;
				arr2[p1] = l;
				p1++;
				//cout << j << " " << l << endl;
			}
		}
		//Now data is ready
		//cout << "answer: ";
		auto start = high_resolution_clock::now();
			solve();
		auto stop = high_resolution_clock::now();
		auto time = duration_cast<microseconds>(stop - start);
		//cout << endl;
		fout_time << time.count()/(pow(10,6)) << endl;

	}


	return 0;
}