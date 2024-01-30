#include <iostream>
using namespace std;

void bubbleSort(int list[], int listLength)
{
	while(listLength--)
	{
		bool swapped = false;
		
		for(int i = 0; i < listLength; i++)
		{
			if(list[i] > list[i + 1])
			{
				swap(list[i], list[i + 1]);
				swapped = true;
			}
		}
		
		if(swapped == false)
			break;
	}
}

void insertionSort(int list[], int listLength)
{
	for(int i = 1; i < listLength; i++)
	{
		int j = i - 1;
		while(j >= 0 && list[j] > list[j + 1])
		{
			swap(list[j], list[j + 1]);
			
			j--;
		}
	}
}

int main()
{
	srand(time(0));
	int list[7] = {3,19,8,0,48,55,24};
	cout << "Input array ..." << endl;
	for(int i = 0; i < 7; i++)
		cout << list[i] << '\t';
	cout << endl;
	
	bubbleSort(list, 7);
	
	cout << "Sorted array ..." << endl;
	for(int i = 0; i < 7; i++)
		cout << list[i] << '\t';
	cout << endl;
	cout << "runtime = " << clock()/1000.0 << endl;
}