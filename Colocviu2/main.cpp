#include <bits/stdc++.h>
#include "util/functions.h"
#include "util/IoBase.h"
using namespace std;

//Template.uri

template<typename T>
istream &operator>>(istream &is, vector<T> &vec) {
    // empty vector:
    vec.clear();
    // read length:
    int n;
    cout << "n: ";
    cin >> n;
    // read items
    for (int i = 0; i < n; ++i) {
        T var;
        cin >> var;
        vec.push_back(var);
    }
    return is;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &vec) {
    os << "[ ";
    for(auto& var : vec) {
        os << var << ' ';
    }
    os << ']';

    return os;
}

struct Data{
    int zi;
    int luna;
    int an;
};

class Produs: public IoBase{
    protected:
        string denumire;
        int cantitate_disponibila;
        float pret;
        vector<string> sponsori;
        int cod;
        Data data_expirare;

    public:
        Produs()=default;

        Produs(const string &denumire, int cantitateDisponibila, float pret, const vector<string> &sponsori, int cod,
               const Data &dataExpirare) : denumire(denumire), cantitate_disponibila(cantitateDisponibila), pret(pret),
                                           sponsori(sponsori), cod(cod), data_expirare(dataExpirare) {}


    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Denumire produs: ";
        getline(cin, denumire);
        cout<<"Cantitate: ";
        cin>>cantitate_disponibila;
        cout<<"Pret: ";
        cin>>pret;
        cout<<"Sponsori: ";
        cin>>sponsori;
        cout<<"Cod produs: ";
        cin>>cod;
        cout<<"Introduceti tasta 1 daca produsul are data expirare, altfel apasati tasta 2.\n";
        int tasta;
        cin>>tasta;
        while(tasta!=1 and tasta !=2){
            cout<<"Introduceti tasta 1 daca produsul are data expirare, altfel apasati tasta 2.\n";
            cin>>tasta;
        }
        if(tasta==1){
            cout<<"Data expirarii: ";
            cin>>data_expirare.zi>>data_expirare.luna>>data_expirare.an;
        }else{
            data_expirare.zi=data_expirare.luna=data_expirare.an=-1;
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Denumire produs: "<<denumire<<"\n";
        cout<<"Cantitate: "<<cantitate_disponibila<<"\n";
        cout<<"Pret: "<<pret<<"\n";
        cout<<"Sponsori: "<<sponsori<<"\n";
        cout<<"Cod: "<<cod<<"\n";
        if(data_expirare.an==-1){
            cout<<"Acest produs nu are data de expirare.\n";
        }else{
            cout<<"Data expirare: "<<data_expirare.zi<<" "<<data_expirare.luna<<" "<<data_expirare.an<<"\n";
        }
    }
};

class ProdusCopil: public virtual Produs{
private:

};










