/*
CS 340 Assignment 4
Chris Arnold
Due February 28, 2013


array*[] is for my gap sequence
array_shell*[] is for Shell's gap sequence
array_hibb*[] is for Hibbard's gap sequence
3 of each array will be created, all identical for testing.

Results of comparisons are printed to the screen.
Array's Pre and post sorted are outputed to the file output.txt

*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <fstream>


using namespace std;

void seed_array(int a[], int length); //seed array with values 1 - length
void print_array(int a[], int length); //print array 
void copy3array(int master[], int a1[], int a2[], int length); //sets a1 and a2 equal to master
//Sort functions return # of comparisons.
int ShellSort_Hibbard(int a[], int length);
int ShellSort(int a[], int length);
int ShellSort_Custom(int a[], int length);
ofstream file;

int main()
{
	file.open("output.txt");	
	int array[10], array_shell[10], array_hibb[10];
	int array1[100], array_shell1[100], array_hibb1[100];
	int array2[1000], array_shell2[1000], array_hibb2[1000];
	int result, result_shell, result_hibb;
	result = result_shell = result_hibb = 0;
	seed_array(array, 10);
	seed_array(array1, 100);
	seed_array(array2, 1000);
	random_shuffle(array, array + 10);
	random_shuffle(array1, array1 + 100);
	random_shuffle(array2, array2 + 1000);
	copy3array(array, array_shell, array_hibb, 10);
	copy3array(array1, array_shell1, array_hibb1, 100);
	copy3array(array2, array_shell2, array_hibb2, 1000);
	file << endl << "Size 10: " << endl;
	print_array(array, 10);
	file << endl << "Size 100: " << endl;
	print_array(array1, 100);
	file << endl << "Size 1000: " << endl;
	print_array(array2, 1000);

	file << endl << "Size 10, array_hibb: " << endl;
	print_array(array_hibb, 10);

	result_shell = ShellSort(array_shell, 10);

	result = ShellSort_Custom(array, 10);
	result_shell = ShellSort(array_shell, 10);
	result_hibb = ShellSort_Hibbard(array_hibb, 10);

	cout << "Results for array of size 10 in number of comparisons: " << endl
		<< "Shell Gap: " << result_shell << endl
		<< "Hibbard Gap: " << result_hibb << endl
		<< "My Gap: " << result << endl;

		result = ShellSort_Custom(array1, 100);
	result_shell = ShellSort(array_shell1, 100);
	result_hibb = ShellSort_Hibbard(array_hibb1, 100);
	cout << "Results for array of size 100 in number of comparisons: " << endl
		<< "Shell Gap: " << result_shell << endl
		<< "Hibbard Gap: " << result_hibb << endl
		<< "My Gap: " << result << endl;

		result = ShellSort_Custom(array2, 1000);
	result_shell = ShellSort(array_shell2, 1000);
	result_hibb = ShellSort_Hibbard(array_hibb2, 1000);
	cout << "Results for array of size 1000 in number of comparisons: " << endl
		<< "Shell Gap: " << result_shell << endl
		<< "Hibbard Gap: " << result_hibb << endl
		<< "My Gap: " << result << endl;



	file << endl << "Sorted Size 10 (Shell): " << endl;
	print_array(array_shell, 10);

	file << endl << "Sorted Size 10 (Hibbard): " << endl;
	print_array(array_hibb, 10);

	file << endl << "Sorted Size 10 (Custom): " << endl;
	print_array(array, 10);

		file << endl << "Sorted Size 100 (Shell): " << endl;
	print_array(array_shell1, 100);

	file << endl << "Sorted Size 100 (Hibbard): " << endl;
	print_array(array_hibb1, 100);

		file << endl << "Sorted Size 100 (Custom): " << endl;
	print_array(array1, 100);

	return 0;
}
int ShellSort_Custom(int a[], int length)
{
	int k = (int)(2*(log(length+6)/log(2)));
	int gap = pow(2,k/2)-6;
	int temp = 0;
	int j;
	int swap = 0;
	int comparisons = 0;
	while(gap >= 1)		//loop upto, and including gap of 1
	{
		for(int i = gap; i < length; i++)
		{
			temp = a[i];
			comparisons++;
			for(j = i; j >=gap && a[j-gap] > temp; j-=gap)
			{
				a[j] = a[j-gap];
				comparisons++;
			}
			a[j] = temp;
		}

		k--;
		if(k == 2)
			gap = 1;
		else
			gap = pow(2,k/2)-6;

	

	}
		return comparisons;
}

int ShellSort(int a[], int length)
{
	int gap = length/2;
	int temp = 0;
	int j;
	int comparisons = 0;
	while(gap >= 1)		//loop upto, and including gap of 1
	{
		for(int i = gap; i < length; i++)
		{
			temp = a[i];
			comparisons++;
			for(j = i; j >=gap && a[j-gap] > temp; j-=gap)
			{
				a[j] = a[j-gap];
				comparisons++;
			}
			a[j] = temp;
		}

		gap = gap/2;
	}
		return comparisons;
}

int ShellSort_Hibbard(int a[], int length)
{
	int k = (int)(log(length+1)/log(2));
	int gap = pow(2,k)-1;
	int temp = 0;
	int j;
	int comparisons = 0;
	while(gap >= 1)		//loop upto, and including gap of 1
	{
		for(int i = gap; i < length; i++)
		{
			temp = a[i];
			comparisons++;
			for(j = i; j >=gap && a[j-gap] > temp; j-=gap)
			{
				a[j] = a[j-gap];
				comparisons++;
			}
			a[j] = temp;
		}

		gap = gap/2;
	}
		return comparisons;
}

void copy3array(int master[], int a1[], int a2[], int length)
{
	for(int i = 0; i < length; i++)
		a2[i] = a1[i] = master[i];
}

void seed_array(int a[],int length)
{
	for(int i = 0; i < length; i++)
	{
		a[i] = i + 1;
	}
}

void print_array(int a[], int length)
{
	for(int i = 0; i < length; i++)
		file << a[i] << " " ;
	file << endl;
}
