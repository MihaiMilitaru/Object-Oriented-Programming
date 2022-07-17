#include <bits/stdc++.h>

#include "util/IoBase.h"


using namespace std;

class Picture:public IoBase{
protected:
    double latime;
    double ratio;

public:
    Picture():latime(0),ratio(0){}
    Picture(double latime, double ratio) : latime(latime), ratio(ratio) {}

    virtual double calculeazaInaltime()=0;

    virtual double calculeazaAria()=0;

    virtual double cantitateUlei()=0;
};

class SmallPicture: public Picture{
public:
    SmallPicture():Picture(){}
    SmallPicture(double _latime, double _ratio):Picture(_latime,_ratio){
        if(_ratio>3 or _ratio<1)
            throw string("Invalid ratio for given picture.\n");
        if(_latime>10)
            throw string("Invalid width for given picture.\n");
    }

    double calculeazaInaltime() override{
        return ratio*latime;
    }
    double calculeazaAria() override{
        return latime*calculeazaInaltime();
    }

    double cantitateUlei() override {
        return calculeazaAria()*0.1;
    }

    istream &read(istream &is) override {
        IoBase::read(is);
        return is;
    }

};


class MediumPicture: public Picture{
public:
    MediumPicture():Picture(){}
    MediumPicture(double _latime, double _ratio):Picture(_latime,_ratio){
        if(_ratio > 1.618 or _ratio < 0.618){
            throw string("Invalid ratio for given picture.\n");
        }
        if(_latime > 57 or _latime < 19){
            throw string("Invalid width for given picture.\n");
        }
    }

    double calculeazaInaltime() override{
        return ratio*latime;
    }
    double calculeazaAria() override{
        return latime*calculeazaInaltime();
    }

    double cantitateUlei() override {
        return calculeazaAria()*0.1;
    }
};

class WallPicture: public Picture{
public:
    WallPicture():Picture(){}
    WallPicture(double _latime, double _ratio):Picture(_latime,_ratio){
        if(_ratio > 10 or _ratio < 1){
            throw string("Invalid ratio for given picture.\n");
        }
        if(_latime > 1000 or _latime < 100){
            throw string("Invalid width for given picture.\n");
        }
    }

    double calculeazaInaltime() override{
        return ratio*latime;
    }
    double calculeazaAria() override{
        return latime*calculeazaInaltime();
    }

    double cantitateUlei() override {
        return calculeazaAria()*0.1;
    }
};


int main() {
    try {
        SmallPicture pic1(2.5, 3.4);
        cout << pic1.calculeazaInaltime() << " " << pic1.calculeazaAria() << " " << pic1.cantitateUlei() << "\n";
    }
    catch (string& s){
        cout<<s;
    }

    try {
         MediumPicture pic2(18, 10);
         cout<<pic2.calculeazaInaltime()<<" "<<pic2.calculeazaAria()<<" "<<pic2.cantitateUlei()<<"\n";
    }
    catch (string& s){
        cout<<s;
    }

    try {
        WallPicture pic3(20, 10);
        cout << pic3.calculeazaInaltime() << " " << pic3.calculeazaAria() << " " << pic3.cantitateUlei() << "\n";
    }
    catch (string& s){
        cout<<s;
    }
    cout<<"\n";
    try {
        SmallPicture pic4(2.5,2);
        cout<<pic4.calculeazaInaltime()<<" "<<pic4.calculeazaAria()<<" "<<pic4.cantitateUlei()<<"\n";
    }
    catch (string& s){
        cout<<s;
    }
    return 0;
}
