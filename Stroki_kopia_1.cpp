#include <iostream>
#include <cstring>
using namespace std;

class mString
{
private:
    char* st;
public:
    mString()
    {
        st = NULL;
    }

    void test()
    {
        st = new char(10);
        char c = 'a';

        for (int i = 0; i < 10; i++)
        {
            st[i] = c++;
        }
        st[0] = '\0';
        cout << st;
    }

    ~mString()
    {
        if (st) { delete st; }
    }
    void operator= (const mString& s);
    void operator= (const char *s);
    mString operator+ (const mString& s) const;
    mString operator+ (const char* s) const;
    friend mString operator+ (const char * s1, const mString &s);
    
    friend bool operator==(const mString& s1, mString &s2);
    friend bool operator>(const mString& s1, mString &s2);
    friend istream& operator >>(istream& in, mString& s);
    friend ostream& operator <<(ostream& on, const mString& s);
    
    int length();
    mString substr(int start, int count);
};

void mString::operator= (const mString& s) {
    if (st) delete st;
    int i, k = 0;
    while (s.st[k++]);
    st = new char[k];
    for (i = 0; i < k; i++) st[i] = s.st[i];

}

mString mString::operator+ (const mString& s) const {
    mString res;
    int i, k =0, k1=0, k2=0;
    while(st[k1++]);
    k1--;
    while(s.st[k2++]);
    k2--;
    res.st = new char[k1+k2+1];
    for (i=0;i<k1;i++) res.st[k++] = st[i];
    for (i=0;i<k2;i++) res.st[k++] = s.st[i];

    res.st[k] = '\0';
    return res;
}

bool operator==(const mString &s1, const mString &s2){
    int i, k=0, k1=0, k2=0;
    while(s1.st[k1++]);
    k--;
    while(s2.st[k2++]);
    if (k1 != k2) return 0;
    for (i=0; i <k1; i++) if (s1.st[i] != s2.st[i]) return 0;
    return 1;
}

bool operator>(const mString &s1, const mString &s1){
    int i, k=0, k1=0, k2=0;
    while(st[k1++]);
    k1--;
    while(s.st[k2++]);
    k2--;
    int l = k1;
    if (k2 < l) l = k2;

    for (i = 0; i <= l; i++) {
        if (s1.st[i] > s2.st[i]) return 1;
        if (s1.st[i] < s2.st[i]) return 0;
    }
    
}

int mString::length() {
    if (!st) return 0;
    int k = 0;
    while (st[k++]);
    return --k;

}

mString mString:: substr(int start, int count) {
    mString res;
    int i,k = start;
    res.st = new char[count+1];
    for (i=0; i < count; i++, k++){
        res.st[i] = st[k];
    }
    res.st[count+1]='\0';
    return res;
} 

ostream& operator << (ostream& out, const mString& data) {
    out << data.st;
    return out;

}
istream& operator >> (istream& in, mString& s) {
    char buf[10000], t;
    int i, k = 0;
    t = in.get();
    while ((int)(t) != 10) {
        buf[k++] = t;
        t = in.get();
    }
    if (s.st) delete s.st;
    s.st = new char[k + 1];
    for (i = 0; i < k; i++) s.st[i] = buf[i];
    s.st[i] = '\0';
    return in;
}


int main()
{
    mString s, p;
    s.test();
    cout << endl << s << endl;
    cin >> s;
    p = s;
    cout << p << " " << p.length() << endl;
    cin >> addition;
    cout << addition << " " << addittion == p << endl;

    return 0;
}
