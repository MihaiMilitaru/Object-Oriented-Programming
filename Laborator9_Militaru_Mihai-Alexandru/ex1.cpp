#include <bits/stdc++.h>

#include "util/IoBase.h"

using namespace std;

/**
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
    virtual double volume() {
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


class SquareCake : public CakeShape {
private:
    double side;
public:
    double baseArea() override {
        return side * side;
    }

    SquareCake(double height, double side) : CakeShape(height), side(side) {}
    SquareCake():CakeShape(),side(0){}

};

class RectangleCake : public CakeShape {
private:
    double length;
    double width;

public:
    RectangleCake():CakeShape(),length(0),width(0){}
    RectangleCake(double height, double length, double width):CakeShape(height),length(length),width(width){}

    double baseArea() override {
        return width*length;
    }

};

static double pi=3.14159265359;
class CircleCake : public virtual CakeShape {
protected:
    double radius;

public:
    CircleCake():CakeShape(),radius(0){}
    CircleCake(double height, double radius):CakeShape(height),radius(radius){}

    double baseArea() override {
        return pi*radius*radius;
    }

};


class ConeShape : public virtual CakeShape {
protected:
    double radius;

public:
    ConeShape():CakeShape(),radius(0){}
    ConeShape(double height, double radius):CakeShape(height),radius(radius){}

    double baseArea() override {
        return pi*radius*radius;
    }

    double volume() override {
        return (pi*radius*radius*height)/3;
    }

};


class SpecialShape : public virtual ConeShape, public virtual CircleCake {
private:
    double radius;
public:
    SpecialShape():ConeShape(),CircleCake(),radius(0){}
    SpecialShape(double height, double radius):ConeShape(height,radius),CircleCake(height,radius),radius(radius){}

    double baseArea() override {
        return pi*radius*radius;
    }

    double volume() override {
        return CircleCake(height, radius).volume() + ConeShape(height, radius).volume();
    }

};

int main(){
    SquareCake v(2,5);
    cout<<v.volume()<<"\n";
    RectangleCake r(1,4,5);
    cout<<r.volume()<<"\n";
    SpecialShape s(20,5);
    cout<<s.volume();
    return 0;
}