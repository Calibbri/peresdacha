/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online. 
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cmath>


using namespace std;

class point{
    private: 
    double x,y;
    public:
    point(){
        x=0;
        y=0;
    }
    point(double nx,double ny){
        //перегрузка конструктора
        x=nx;
        y=ny;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    void setX(double nx){
        x=nx;
    }
    void setY(double ny){
        y=ny;
    }
    void printPoint(){
        cout<<"("<<x<<","<<y<<")";    
    }
};

class segment{
    private:
    point *P1,*P2;//динамическое использвоние одного класса в другом
    public:
    segment(){
        P1 = new point;
        P2 = new point;
    }
    segment(double x1,double y1,double x2,double y2){
        P1 = new point(x1,y1);
        P2 = new point(x2,y2);
    }
    ~segment(){//деструктов. обязательно разрушение используемых динамических объектов
        delete P1;
        delete P2;
    }   
    
    double length(){
        return sqrt(pow(P1->getX()-P2->getX(),2)+pow(P1->getY()-P2->getY(),2));
    }
    point * getFirstPoint(){//результаттом функции является указатель на объект типа point
        point *tmp = new point(P1->getX(),P1->getY());
        return tmp;
    }
    point * getSecondPoint(){
        point *tmp = new point(P2->getX(),P2->getY());
        return tmp;
    }   
    
    void print(){//печать координат начала и конца отрезка
        
    }
    
    point * getMeedle(){//реализовать метод получения точки, которая является серединой отрезка
        point *tmp = new point((P1->getX()+P2->getX())/2, (P1->getY()+P2->getY())/2);
    }
    
    bool pointOnLine(point *P){
        //возвращает true если точка P лежит на прямой, на которой лежит отрезок
        double m, n, m1, n1;
        m=P1->getX()-P2->getX();
        n=P1->getY()-P2->getY();
        m1=P1->getX()-P->getX();
        n1=P1->getY()-P->getY();
        return (m/m1) == (n/n1);
    }
    
    bool pointBelongs(point *P){
        //возвращает true если точка P принадлежит отрезку
        /*if (!pointOnLine(P))
            return 0;*/
            
    }

    
};
/*
Задание 1. Реализовать следующие функции
*/
bool isPerpendicular(segment *A, *B ){
    //возвращает true если отрезки лежат на перпендикулярнах прямых 
}

bool isPapallel(segment *A, *B ){
    //возвращает true если отрезки лежат на параллельных прямых прямых
}

bool isCros(segment *A, *B ){
    //возвращает true если отрезки пересекаются
}

point * getCrosPoint(segment *A, *B ){
    //возвращает указатель на объект с координатами точки пересечения
}

/*Задание 2
реализовать динамический массив Точек (статический с частичным использванием -10 к карме программиста)
реализовать ввод и вывод массива течер

реализовать функцию которая принимает указанный массив точек и возвращает длину соответствующей незамкнутой кривой
реализовать функцию которая принимает указанный массив точек и возвращает длину соответствующей замкнутой кривой
реализовать функцию которая принимает указанный массив точек и возвращает площадь соответствующей замкнутой кривой
реализовать функцию которая принимает указанный массив точек и возвращает true если соответствующая замкнута кривая является выпуклой

*/



int main()
{
    point P;
    P.printPoint();
    point P2(4,6);
    P2.printPoint();
    cout << endl;
    segment *AB = new segment(2,2,5,5);
    cout << AB->length();
    
    point *AB1 = AB->getFirstPoint();
    cout << endl;
    AB1->printPoint();
    
    
    
    return 0;
}
