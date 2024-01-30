#include <iostream>
using namespace std;

class myString
{
private:
    char* Str;
public:
    myString()
    {
        Str = NULL;
    }
    
    void test()
    {
        Str = new char(10);
        char c = 'a';
        for (int i = 0; i <10; i++)
        {
            Str[i] = c++;
        }
        Str[9] = '\0';
        cout << Str;
    }
    
    void print(){
        
    }
    
    ~myString()
    {
        if (Str){delete Str;}
    }
    
    friend ostream& operator<< (ostream &out, const myString &Str);
    friend istream& operator>> (istream &in, const Matrix &Str);
};

ostream& operator<< (ostream &out, const myString &s)
{
    out << s.Str;
    return out;
}

friend istream& operator>> (istream &in, const Matrix &s)
{
    char bufer[10000], t;
    int i, k = 0;
    t = in.get();
    while ((int)(t)!=10){
        bufer[k++]=t;
        t = in.get();
    }
    if (s.Str) {delete s.Str;}
}

int myString:: length(){
    if (!Str) return 0;
    int k = 0;
    while(Str[k++]);
    Str = new char[k];
    
}


int main()
{
    cout << "Hello World";
    char H[100];
    gets(H);
    cout << H;
    
    myString s;
    s.test();
    cout << endl << s << endl;

    return 0;
}
