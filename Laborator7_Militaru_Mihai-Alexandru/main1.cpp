#include <iostream>
#include "util/IoBase.h"

using namespace std;

class Fraction : public IoBase {
protected:
    int a, b;
public:
    // constructori
    Fraction(int a, int b) : a(a), b(b) {};

    Fraction():a(0),b(0){};

    // IoBase - overrided functions
    istream &read(istream &is) override {
        IoBase::read(is);
        cout << "a: ";
        is >> a;
        cout << "b: ";
        is >> b;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout << "a: " << a;
        cout << ", b: " << b;
        return os;
    }

    int getA() const {
        return a;
    }

    int getB() const {
        return b;
    }
};

class IrrationalFraction : public Fraction {
private:
    // adaugam si radicalul dintr-un numar real
    double underSqrt;
public:

    // constructori:

    IrrationalFraction():Fraction(),underSqrt(0.0) {};
    IrrationalFraction(int a, int b, double underSqrt):Fraction(a,b),underSqrt(underSqrt){};

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

    friend bool operator<(const Fraction &f1, const IrrationalFraction &f2);

    friend IrrationalFraction operator*(const Fraction &f1, const IrrationalFraction &f2);


    // IoBase - overrided functions

};

bool operator<(const Fraction &f1, const IrrationalFraction &f2) {
    double numarator_f2 = f2.a * f2.a * f2.underSqrt;
    double numitor_f2 = f2.b * f2.b;

    double numarator_f1=f1.getA() * f1.getA();
    double numitor_f1=f1.getB() * f1.getB();

    numarator_f1 *= numitor_f2;
    numarator_f2 *= numitor_f1;

    if(numarator_f1<numarator_f2)
        return true;
    else
        return false;
}

istream &IrrationalFraction::read(istream &is) {
    cout << "a: ";
    is >> a;
    cout << "b: ";
    is >> b;
    cout<<"undersqrt: ";
    is>>underSqrt;
    return is;

}

ostream &IrrationalFraction::write(ostream &os) const {
    cout << "a: " << a;
    cout << ", b: " << b;
    cout<< ", undersqrt: "<<underSqrt;
    return os;
}



IrrationalFraction operator*(const Fraction &f1, const IrrationalFraction &f2) {
    return {f1.getA()*f2.a, f1.getB()*f2.b, f2.underSqrt};
}



// Vom implementa cele doua clase
// Vom implementa <
/*
Exemplu input:

2 3         -> citim fractia 2/3
1 2 2       -> citim fractia 1/2*sqrt(2)

Ca indiciu, vom avea 2/3 < 1/2*sqrt(2).
*/

// functie catre clasa de baza:
// testati ce se intampla daca eliminati ampersand-ul
void show(const Fraction &f) {
    cout << "Fractia este: " << f << '\n';
}

int main() {
    // level 0: constructori si operatori de afisare
    Fraction f1(2,3);
    IrrationalFraction f2(1,2,2);

//    //  Level 1: operator de citire


//    cin >> f1;
//    cin >> f2;
//    cout << f1 << " si " << f2;

//    //  level 2: Operator supraincarcat cu clase diferite
    if (f1 < f2) {
        cout << f1 << " < " << f2 << '\n';
    } else {
        cout << f2 << " < " << f1 << '\n';
    }

//    //  Level 3: operatori si metode
   cout << f1 * f2 << '\n';


    // Aveti deja implementata functia globala show(Fraction f).
    // Ce se intampla cand urmatoarele 2 linii de cod?
    cout<<f1*f2<<"\n";
    show(f1);
    show(f2);
    //  daca adaugam & la parametrul din show?
}