#include <iostream>

using namespace std;
class figure{
    protected:
    double x, y;
    public:
    figure(){
        x = 0;
        y = 0;
    }
    figure(double nx, double ny){
        x = nx;
        y = ny;
    }
    void print(){
        cout << "(" << x << ", " << y << ")" << endl;
    }
};
 class circle : public figure {
    protected:
    double r;
    public:
    circle(double nx, double ny, double nr){
        x = nx;
        y = ny;
        r = nr;
    }
    double area(){
        return 0;
    }
    double lenth(){
        return 0;
    }

 };

 int main(){
    figure *p, *p2;
    circle *c;
    p = new figure(2, 3);
    p -> print();
    p2 = new figure;
    p2->print();
    c = new circle(2, 3, 4);
    c->print();
    delete p, p2, c;
    return 0;
 }