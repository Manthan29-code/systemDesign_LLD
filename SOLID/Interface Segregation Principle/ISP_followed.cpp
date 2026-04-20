#include<iostream>

using namespace std ;

class TwoDimensionalShape {

    public :
        virtual double area() = 0 ;

};

class ThreeDimensionalShape
{

public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Square : public TwoDimensionalShape {
    private :
        double side ;
    public :
        Square ( double s ) : side(s) {} 

        double area() override {
            return side * side ;
        }
};

class Cube : public ThreeDimensionalShape
{
private:
    double side;

public:
    Cube(double s) : side(s) {}

    double area() override
    {
        return 6 * side * side;
    }

    double volume() override
    {
        return side * side * side;
    }
};

int main()
{
    TwoDimensionalShape *square = new Square(5);
    ThreeDimensionalShape *cube = new Cube(3);

    cout << "Square Area: " << square->area() << endl;
    cout << "Cube Area: " << cube->area() << endl;
    cout << "Cube Volume: " << cube->volume() << endl;

    return 0;
}