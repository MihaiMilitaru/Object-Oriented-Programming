#include <bits/stdc++.h>
using namespace std;

class IoBase {
private:
public:
    // metoda citire
    virtual istream &read(istream &is) { // nu este nevoie de obiectul citit, pt ca avem this
        return is; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // metoda scriere
    virtual ostream &write(ostream &os) const { // nu este nevoie de obiectul citit, pt ca avem this
        return os; // vom vedea ca in interfete deseori nu avem functionalitati
    }

    // ...
    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};

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
        os << var << " " ;
    }
    os << ']';

    return os;
}

//Final Template.uri

class Masina: public IoBase{

protected:
    int an_productie;
    string nume;
    int viteza;
    double greutate;

public:
    Masina(){
        an_productie=0;
        viteza=0;
        greutate=0;
        nume="unkown";
    }

    Masina(int anProductie, const string &nume, int viteza, double greutate) : an_productie(anProductie), nume(nume),viteza(viteza), greutate(greutate) {}

    virtual double autonomie(){};

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"An fabricatie: ";
        cin>>an_productie;
        cin.get();
        cout<<"Model: ";
        getline(cin, nume);
        cout<<"Viteza: ";
        cin>>viteza;
        cout<<"Greutate: ";
        cin>>greutate;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"An fabricatie: "<<an_productie<<"\n";
        cout<<"Model: "<<nume<<"\n";
        cout<<"Viteza: "<<viteza<<"\n";
        cout<<"Greutate: "<<greutate<<"\n";
        return os;
    }

};

class MasinaFosil:public virtual Masina{
protected:
    string combustibil;
    double capacitate;

public:
    MasinaFosil(){
        Masina();
        combustibil="unknown";
        capacitate=0;
    }

    MasinaFosil(int anProductie, const string &nume, int viteza, double greutate, const string &combustibil, double capacitate) : Masina(anProductie, nume, viteza, greutate), combustibil(combustibil),capacitate(capacitate) {}

    double autonomie() override {
        return capacitate/ sqrt(greutate);
    }

    istream &read(istream &is) override {
        Masina::read(is);
        cout<<"Combustibil: ";
        cin>>combustibil;
        cout<<"Capacitate: ";
        cin>>capacitate;
        return is;
    }

    ostream &write(ostream &os) const override {
        Masina::write(os);
        cout<<"Combustibil: "<<combustibil<<"\n";
        cout<<"Capacitate: "<<capacitate<<"\n";
        return os;
    }
};

class MasinaElectrica:public virtual Masina{
protected:
    double capacitate_baterie;

public:
    MasinaElectrica(){
        Masina();
        capacitate_baterie=0;
    }

    MasinaElectrica(int anProductie, const string &nume, int viteza, double greutate, double capacitateBaterie): Masina(anProductie, nume, viteza, greutate), capacitate_baterie(capacitateBaterie) {}

    double autonomie() override {
        return capacitate_baterie/(greutate*greutate);
    }

    istream &read(istream &is) override {
        Masina::read(is);
        cout<<"Capacitate baterie: ";
        cin>>capacitate_baterie;
        return is;
    }

    ostream &write(ostream &os) const override {
        Masina::write(os);
        cout<<"Capacitate baterie: "<<capacitate_baterie<<"\n";
        return os;
    }

};


class MasinaHibrid:public virtual MasinaFosil, public virtual MasinaElectrica{
public:
    MasinaHibrid(){
        MasinaFosil();
        capacitate_baterie=0;
    }

    MasinaHibrid(int anProductie, const string &nume, int viteza, double greutate, const string &combustibil, double capacitate, int anProductie1, const string &nume1, int viteza1, double greutate1,double capacitateBaterie) : MasinaFosil(anProductie, nume, viteza, greutate, combustibil, capacitate),MasinaElectrica(anProductie1, nume1, viteza1, greutate1,capacitateBaterie) {}

    double autonomie() override {
        return MasinaFosil::autonomie() + MasinaElectrica::autonomie();
    }

    istream &read(istream &is) override {
        MasinaFosil::read(is);
        cout<<"Capacitate baterie: ";
        cin>>capacitate_baterie;
        return is;

    }

    ostream &write(ostream &os) const override {
        MasinaFosil::write(os);
        cout<<"Capacitate baterie: "<<capacitate_baterie<<"\n";
        return os;
    }

};

struct Data{
    int zi,luna,an;
    Data() {
       zi=an=luna=0;
    }

    Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}
};

class Tranzactie: public IoBase{
private:
    string client;
    Data data;
    vector <shared_ptr<Masina>> masini;
public:
    Tranzactie()= default;

    Tranzactie(const string &client, const Data &data, const vector<shared_ptr<Masina>> &masini) : client(client),data(data),masini(masini) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Nume client: ";
        getline(cin, client);
        cout<<"Data tranzactiei: ";
        cin>>data.zi>>data.luna>>data.an;
        cout<<"Introduceti masinile acum.\n";
        cout<<"Introduceti numarul de masini pe care vreti sa-l adaugati.\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"1. Masina carburant fosil\n2. Masina Electrica\n3. Masina Hibrid\n";
            int tip;
            cin>>tip;
            while(tip!=1 and tip!=2 and tip!=3){
                cout<<"Tip gresit. Reintroduceti tipul.\n";
                cin>>tip;
            }
            if(tip==1){
                MasinaFosil m;
                cin>>m;
                masini.push_back(make_shared<Masina>(m));
            }

            if(tip==2){
                MasinaElectrica m;
                cin>>m;
                masini.push_back(make_shared<Masina>(m));
            }

            if(tip==3){
                MasinaHibrid m;
                cin>>m;
                masini.push_back(make_shared<Masina>(m));
            }

        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Nume client: "<<client<<"\n";
        cout<<"Data tranzactiei: "<<data.zi<<" "<<data.luna<<" "<<data.an<<"\n";
        for(const auto & i : masini){
            auto *fosil=dynamic_cast< MasinaFosil*>(i.get());
            auto *electric=dynamic_cast< MasinaElectrica*>(i.get());
            auto *hibrid=dynamic_cast< MasinaHibrid*>(i.get());

            if(fosil){
                cout<<*fosil;
            }
            if(electric){
                cout<<*electric;
            }
            if(hibrid){
                cout<<*hibrid;
            }
        }
        return os;

    }

};

class BaseMenu {
public:
    virtual void listOptions() = 0;

    virtual int chooseOption(int first, int last) = 0;

    virtual void mainLoop() = 0;


};

class Menu : public BaseMenu {
private:
    Menu() = default;

    static Menu *menu;
    vector<shared_ptr<Masina>> masini;
    vector<shared_ptr<Tranzactie>> tranzactii;


public:

    static Menu *getMenu() {
        if (menu != nullptr) {
            return menu;
        }
        menu = new Menu();
        return menu;
    }


    void listOptions() override {
        cout<<"1. Adauga Masina noua.\n";
        cout<<"2. Adauga tranzactie.\n";
        cout<<"3. Afiseaza cel mai vandut model.\n";
        cout<<"4. Afiseaza modelul cu autonomia cea mai mare.\n";
        cout<<"4. Mareste performanta unui model, crescandu-i viteza cu un anumit procent.\n";
        cout<<"4. Exit.\n";
    }

    void option1(){
        cout<<"1. Masina carburant fosil\n2. Masina Electrica\n3. Masina Hibrid\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip!=2 and tip!=3){
            cout<<"Tip gresit. Reintroduceti tipul.\n";
            cin>>tip;
        }
        if(tip==1){
            MasinaFosil m;
            cin>>m;
            masini.push_back(make_shared<Masina>(m));
        }

        if(tip==2){
            MasinaElectrica m;
            cin>>m;
            masini.push_back(make_shared<Masina>(m));
        }

        if(tip==3){
            MasinaHibrid m;
            cin>>m;
            masini.push_back(make_shared<Masina>(m));
        }

    }

    void option2(){
        Tranzactie t;
        cin>>t;
    }

    void option3(){

    }

    int chooseOption(int first, int last) override {
        int option = -1;
        while (option < first || option > last) {
            cout << '\n';
            cout << "Pentru a rula comanda, alegeti un numar intre " << first << " si " << last << '\n';
            listOptions();
            cout << "Alegere:";
            cin >> option;
        }
        return option;
    }



    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 6);
            if(option==1){
                option1();
            }
            if(option==1){
                option1();
            }
            if(option==2){
                option2();
            }
            if(option==3){
                option3();
            }
            if(option==6){
                break;
            }

        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }



};

Menu *Menu::menu = nullptr;


int main(){
    MasinaFosil m;
    cout<<m;

}