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
            for (int i = 0; i < n; i++) ms[i] = 0;
        }

        void print() 
        {
            for (int i = 0; i < n; i++) cout << ms[i] << " ";
            cout << endl;
        }

        void removeElem(int index)
        {
            int* newMs = new int[n - 1];
            for (int i = 0; i < index; i++) newMs[i] = ms[i];
            for (int i = index; i < n; i++) newMs[i] = ms[i+1];
            n--;
            delete[] ms;
            ms = newMs;
        }
        
        void minElem()
        {
            int min=ms[0];
            for(int i = 0; i < 20; i++)
            {
                if(ms[i] < min)
                {
                    min = ms[i];
                }
            }
        }
        
        void maxElem()
        {
          int max=ms[0];
          for(int i = 0; i < 20; i++)
            {
                if(ms[i] > max)
                {
                    max = ms[i];
                }
            }
        }

        ~MyArray() 
        {
            // cout << "destructor";
        }
};



int main()
{

    MyArray m;
    m.init(20);
    m.print();



    MyArray* A = new MyArray;
    A->init(10);
    A->print();
    delete A;

    return 0;
}