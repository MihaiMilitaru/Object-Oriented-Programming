#include <bits/stdc++.h>
#include <memory>
#include "IoBase.h"

class Fruit: public IoBase{
private:
    string nume;
    string soi;

public:
    Fruit()=default;

    Fruit(const string &nume, const string &soi) : nume(nume), soi(soi) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cin>>nume>>soi;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Nume fruct: "<<nume<<"\n";
        cout<<"Soi fruct: "<<soi<<"\n";
        return os;
    }

};

class Juice: public IoBase{
protected:
    int cantitate;

public:
    Juice()=default;

    Juice(int cantitate) : cantitate(cantitate) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cin>>cantitate;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Cantitate suc: "<<cantitate<<"\n";
        return os;
    }

    virtual int quantity();
};

int Juice::quantity() {
    return cantitate;
}

class SimpleJuice:public Juice{
private:
    Fruit fruct;

public:
    SimpleJuice()=default;
    SimpleJuice(int cantitate, Fruit fruit){
        this->cantitate=cantitate;
        this->fruct=fruit;
    }

    istream &read(istream &is) override {
        Juice::read(is);
        cin>>fruct>>cantitate;
        return is;
    }

    ostream &write(ostream &os) const override {
        Juice::write(os);
        cout<<"Fructul folosit: "<<fruct<<"\n";
        cout<<"Cantitatea: "<<cantitate<<"\n";
        return os;
    }

    int quantity() override {
        return Juice::quantity();
    }
};

class MixedJuice:public Juice{
private:
    vector<Fruit> fructe;

public:
    MixedJuice()=default;
    MixedJuice(int cantitate, vector<Fruit> fructe){
        this->cantitate=cantitate;
        this->fructe=fructe;
    }

    istream &read(istream &is) override {
        Juice::read(is);
        int nr_fructe;
        cin>>nr_fructe;
        fructe.resize(nr_fructe);
        for(int i=0;i<fructe.size();i++){
            cin>>fructe[i];
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        Juice::write(os);
        cout<<"Fructele folosite:\n";
        for(int i=0;i<fructe.size();i++){
            cout<<fructe[i]<<" ";
        }
        cout<<"\n";
        cout<<"Cantitate: "<<cantitate<<"\n";
        return os;
    }

    int quantity() override {
        return Juice::quantity();
    }
};


class IcedJuice:public Juice{
private:
    vector<Fruit> fructe;
    int cantitate_gheata;

public:
    IcedJuice()=default;
    IcedJuice(int cantitate, vector<Fruit> fructe, int cantitate_gheata){
        this->cantitate=cantitate;
        this->fructe=fructe;
        this->cantitate_gheata=cantitate_gheata;

    }

    istream &read(istream &is) override {
        Juice::read(is);
        int nr_fructe;
        cin>>nr_fructe;
        fructe.resize(nr_fructe);
        for(int i=0;i<nr_fructe;i++){
            cin>>fructe[i];
        }
        cin>>cantitate_gheata;
        return is;
    }

    ostream &write(ostream &os) const override {
        Juice::write(os);
        cout << "Fructele folosite:\n";
        for (int i = 0; i < fructe.size(); i++) {
            cout << fructe[i] << " ";
        }
        cout << "\n";
        cout << "Cantitate gheata: " << cantitate_gheata << "\n";
        cout << "\n";
    }
    int quantity() override {
        return cantitate_gheata+cantitate;
    }
};

int main(){
    vector<shared_ptr<Juice> > stock = {
            make_shared<SimpleJuice>(
                    SimpleJuice(550, Fruit("Apple", "Granny Smith"))
            ),
            make_shared<MixedJuice>(
                    MixedJuice(
                            560,
                            {
                                    Fruit("Apple", "Granny Smith"),
                                    Fruit("Banana", "Musa balbisiana"),
                            }
                    )
            ),
            make_shared<IcedJuice>(
                    IcedJuice(
                            560,
                            {
                                    Fruit("Apple", "Granny Smith"),
                                    Fruit("Banana", "Musa balbisiana"),
                            },
                            150
                    )
            ),
    };

    for (auto juice : stock) {
        cout << juice->quantity()<<" ";
    }

     MixedJuice j;
     cin>>j;
     cout<<j;

}