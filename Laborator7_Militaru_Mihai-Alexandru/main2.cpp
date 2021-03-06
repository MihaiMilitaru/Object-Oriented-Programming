#include <iostream>

using namespace std;

/*
 *  discutam despre metode virtual si object slicing pe un exemplu mai simplu
 *  pe care sigur il auziti si la seminar!
 *  .
 *  Avem clasa de baza CakeShape = o forma de tort despre care stim inaltimea,
 *   dar nu si baza (patrat, dreptunghi, etc)
 *  Chiar si asa, putem calcula volumul, cu ajutorul unei functii virtuale
 *   care va calcula aria bazei:
 */

/*
 *
 */
class CakeShape {
protected:
    double height;
public:
    // calculam volumul
    double volume() {
        return baseArea() * height;
    }

    // spunem ca aria bazei va fi calculata in copii,
    //  prin suprascrierea metodei virtuale:
    virtual double baseArea() {
        // returnam zero, deoarece nu stim forma:
        return 0;
    }

    // constructorii
    explicit CakeShape(double height) : height(height) {}

    CakeShape() : height(0) {}
};

//  Pentru fiecare dintre clasele de mai jos vom:
//      * adauga laturile/raza;
//      * genera constructorii cu parametrii;
//      * si vom calcula aria bazei, prin suprascriere.

class SquareCake : public CakeShape {
private:
    double side;
public:
    double baseArea() override {
        return side * side;
    }

    SquareCake(double height, double side) : CakeShape(height), side(side) {};
    SquareCake():CakeShape(), side(0) {};

};

class RectangleCake : public CakeShape {
private:
    double length;
    double width;

public:
    RectangleCake():CakeShape(),length(0),width(0){};

    RectangleCake(double height, double length, double width):CakeShape(height),length(length),width(width){};

    double baseArea() override {
        return width*length;
    }
};

static double pi=3.14159265359;
class CircleCake : public CakeShape {
private:
    double radius;

public:
    CircleCake():CakeShape(),radius(0){};
    CircleCake(double height, double radius):CakeShape(height),radius(radius){};

    double baseArea() override {
        return pi*radius*radius;
    }

};


int main() {
    // pentru prima clasa, dar si o clasa copil:
    CakeShape cake(4);
    SquareCake cube(2, 2);

    cout << cake.volume() << '\n'; // 0
    cout << cube.volume() << '\n'; // 8

    // pentru clasele derivate
    SquareCake squareCake(4, 5);
    RectangleCake rectangleCake(1, 5, 2);
    CircleCake circleCake(1, 5);

    cout << squareCake.volume() << '\n'; //     100
    cout << rectangleCake.volume() << '\n'; //  10
    cout << circleCake.volume() << '\n'; //     78.5398

    return 0;
}