#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class MyArray {
    private:
        int n, *ms;
    public:
        MyArray() {
            n = 0;
            ms = NULL;
            //cout << "construct";
    }

    void init(int k)
    {
        if (ms == NULL)
        {
            ms = new int[k];
            n = k;
        }
        for (int i = 0; i < n; i++) ms[i] = rand() % 100 - 50;
    }


    void print(){
        //{
        for (int i = 0; i < n; i++) cout << ms[i] << " ";
    cout << endl;
}

void removeElem(int index)
{
    int *newMs = new int[n - 1];
    for (int i = 0; i < index; i++) newMs[i] = ms[i];
    for (int i = index; i < n; i++) newMs[i] = ms[i + 1];
    n--;
    delete[] ms;
    ms = newMs;
}



void maxEl()
{
    int max = ms[0];
    for (int i = 0; i < n; i++)
    {
        if (ms[i] > max)
        {
            max = ms[i];
        }
    }
    cout << max << endl;
}
void minEl()
{
    int min = ms[0];
    for (int i = 0; i < n; i++)
    {
        if (ms[i] < min)
        {
            min = ms[i];
        }
    }
    cout << min << endl;
}

int length()
{
    return n;
}

~MyArray()
{
    delete[] ms;
    // cout << "destructor";
}
// метод, который возвращает элемент
int get(int index)
{
    return ms[index];
}
// метод, который добавляет элемент
void addEl(int el)
{
    int *newMs = new int[n + 1];
    for (int i = 0; i < n; i++) newMs[i] = ms[i];
    newMs[n] = el;
    n++;
    delete[] ms;
    ms = newMs;
}
void bubbleSort()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (ms[j] > ms[j + 1])
            {
                int tmp = ms[j];
                ms[j] = ms[j + 1];
                ms[j + 1] = tmp;
            }
        }
    }
}

void insertionSort()
{
	for(int i = 1; i < n; i++)
	{
		int j = i - 1;
		while(j >= 0 && ms[j] > ms[j + 1])
		{
			swap(ms[j], ms[j + 1]);
			
			j--;
		}
	}
}

};


int main()
{
    srand(time(0));
    MyArray m;
    m.init(27);
    cout << "This is array m: ";
    m.print();

    MyArray *A = new MyArray;
    A->init(22);
    cout << "This is array A: ";
    A->print();

    MyArray *positive = new MyArray;
    positive->init(0);
    MyArray *negative = new MyArray;
    negative->init(0);
    for (int i = 0; i < A->length(); i++)
    {
        if (A->get(i) > 0) positive->addEl(A->get(i));
        if (A->get(i) < 0) negative->addEl(A->get(i));
    }

    cout << endl << "This is a positive integers:";
    positive->print();
    cout << "This is a negative integers:";
    negative->print();

    cout << endl << "This is a insertionSort principe A:";
    A->insertionSort();
    A->print();
    cout << "runtime = " << clock()/1000.0 << endl;
    delete A;


    return 0;

    // 1. сделать так, что бы создавалось два объекта положительных и отрицательных чисел
    // 2. добавлять элемент так, чтобы сохранялся порядок возрастания
    // 3. реализовать два метода сортировки массива
    // 4. засеч время работы на двух разных алгоритмах сортироввки
}
