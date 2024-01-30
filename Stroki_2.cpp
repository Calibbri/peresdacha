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

    
    ~myString()
    {
        if (Str){delete Str;}
    }
    void operator= (const myString &s);
    friend istream& operator >>(istream &in, myString &s);
    friend ostream& operator <<(ostream &on, const myString &s);
    int length();
};

void myString::operator= (const myString &s){
    if(Str) delete Str;
    int i, k=0;
    while(s.Str[k++]);
    Str = new char[k];
    for (i = 0; i < k; i++) Str[i]=s.Str[i];
    
}

int myString::length(){
        if(!Str) return 0;
        int k = 0;
        while(Str[k++]);
        return --k;
        
}

    ostream& operator << (ostream& out, const myString& data){
        out << data.Str;
        return out;
    
}
    istream& operator >> (istream& in, myString& s){
        char buf[10000], t;
        int i, k = 0;
        t = in.get();
        while ((int)(t) != 10){
            buf[k++] = t;
            t = in.get();
        }
        if (s.Str) delete s.Str;
        s.Str = new char[k+1];
        for (i = 0; i < k; i++) s.Str[i]=buf[i];
        s.Str[i]='\0';
        return in;
    }


int main()
{
    myString s, p;
    s.test();
    cout << endl << s << endl;
    cin >> s;
    p = s;
    cout << p << " " << p.length() << endl;
    
    return 0;
}
