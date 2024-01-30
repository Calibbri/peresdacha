#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

class   MyArray {
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
            for (int i = 0; i < n; i++) ms[i] = random()%100-50;
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
        
        void min()
        {
            int min = ms[0];
            for (int i = 0; i < n; i++)
            {
                if (ms[i]<min) min = ms[i];
            }
            cout << min << endl;
        }
        
        void max()
        {
            int max = ms[0];
            for (int i = 0; i < n; i++)
            {
                if (ms[i]>max) max = ms[i];
            }
            cout << max << endl;
        }
        
        int get(int k){
            return ms[k];
        }
        
        void random(int left, int right){
            srand(time(0));
            for (int i=0;i<n;i++) ms[i]=rand()%(right-left)+left;
        }
        
        int insertElm(int r){
            int i, t;
            int *tmp = new int[n+1];
            
            for(i=0; i<n;i++) tmp[i] = ms[i];
            tmp[n] = r;
            n++;
            delete ms;
            ms = tmp;
        }
        

        ~MyArray() 
        {
		    delete[] ms;
        }
};

int main()
{
    srand(time(NULL));
    MyArray *a,*b,*c;
    int k;
    a= new MyArray;
    b= new MyArray;
    c= new MyArray;
    
    cin >> k;
    a->init(k);
    b->init(0);
    c->init(0);
    a->random(-20,20);
    
    for(int i=0; i<a->lenght();i++){
        if (a->get(i)>0) b->insertElm(a->get(i));
        if (a->get(i)<0) c->insertElm(a->get(i));
    }
    a->print();
    b->print();
    c->print();
    delete a;
    delete b;
    delete c;
    return 0;
    // m.init(20);
    // m.print();
    // m.min();
    // m.max();
    // m.removeElem(10);
    // m.print();

    // MyArray* A = new MyArray;
    // A->init(10);
    // A->print();
    // delete A;

    // return 0;
}