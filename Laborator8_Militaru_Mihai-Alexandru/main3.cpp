#include <bits/stdc++.h>

#include <utility>

#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

class Building:public IoBase{
protected:
    string culoare,nume_propietar;
public:
    Building() = default;
    Building( string col, string nume_prop){
        culoare = move(col);
        nume_propietar = move(nume_prop);
    };

    istream &read(istream &is) override {
        cout << "Culoare cladire:";
        cin >> culoare;
        cin.get();
        cout<<"Nume propietar:";
        getline(cin, nume_propietar);
        return IoBase::read(is);
    }
    ostream &write(ostream &os) const override {
        cout << "Culoare cladire:" << culoare << "\n";
        cout<<"Nume propietar:" << nume_propietar << "\n";
        return IoBase::write(os);
    }
};


class House:public Building{
private:
    int cntFloors;
public:
    House();
    House(string cul, string nump, int cntfloor);

    ostream &write(ostream &os) const override;

    istream &read(istream &is) override;
};

House::House() {
    cntFloors = 0;
}

House::House(string cul, string nump, int cntfloor): Building(std::move(cul), std::move(nump)) {
    cntFloors = cntfloor;
}

istream &House::read(istream &is) {
    Building::read(is);
    cout<< "Nr etaje:";
    cin >> cntFloors;
    return is;
}

ostream &House::write(ostream &os) const {
    Building::write(os);
    cout<<"Nr etaje:" << cntFloors << "\n";
    return os;
}

class Apartament : public Building{
private:
    int floor;
public:
    Apartament();
    Apartament(string culoare , string num_p, int fl);

    ostream &write(ostream &os) const override;

    istream &read(istream &is) override;
};

Apartament::Apartament():Building(){
    floor = 0;
}

Apartament::Apartament(string culoare, string num_p, int fl):Building(std::move(culoare), std::move(num_p)) {
    floor = fl;
}

istream &Apartament::read(istream &is) {
    Building::read(is);
    cout<<"Introduceti  etajul:";
    cin >> floor;
    return is;
}

ostream &Apartament::write(ostream &os) const {
    Building::write(os);
    cout<<"Etajul : "<< floor<<"\n";
    return os;
}

class Owner:public IoBase{
private:
    string num;
public:
    explicit Owner(string num) : num(std::move(num)) {};

    istream &read(istream &is) override {
        cin >> num;
        return IoBase::read(is);
    }

    ostream &write(ostream &os) const override {
        cout << num;
        return IoBase::write(os);
    }

    Owner() = default;
};
shared_ptr<Building> citeste(){
    int opt;
    cout<<"Pt apartament tasteaza 1 iar pt House apasa 2:";
    cin >>opt;
    if(opt == 1) {
        House h;
        cin >> h;
        return make_shared<House>(h);
    }
    else if (opt == 2) {
        Apartament p;
        cin >> p;
        return make_shared<Apartament>(p);
    } else if(opt < 1 or opt > 2){
        cout<< "operatie gresita.Introdu operatia:";
        cin >> opt;
    }
}


shared_ptr<Owner> citesteo(){
    Owner h;
    cout<<"Introdu numele:";
    cin >> h;
    return make_shared<Owner>(h);
}

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};

class BuildingMenu : public BaseMenu {
private:
    vector<shared_ptr<Building>>b;
public:
    BuildingMenu()= default;

    void setB(vector<shared_ptr<Building>> &bi) {
        b = bi;
    }
    void listOptions() override {
        cout << "1. Adauga o noua cladire." << '\n';
        cout << "2. Afiseaza toate cladirile." << '\n';
        cout << "3. Sterge o cladire existenta." << '\n';
        cout << "4. Modifica o cladire." << '\n';
        cout << "5. Iesire." << '\n';
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

    void option1(){
        shared_ptr<Building> nou;
        nou = citeste();
        b.push_back(nou);
        cout << "Am adaugat o nouă cladire." << '\n';
    }
    void option2(){
        cout<<"Toate cladirile sunt:\n\n";
        int nr_cld = 0;
        if(!b.empty()) {
            for (auto &x: b) {
                auto *asHouse = dynamic_cast<House *>(x.get());
                auto *asApartament = dynamic_cast<Apartament *>(x.get());
                if (asHouse) {
                    cout<<"House\n";
                    cout << "Cladire :" << nr_cld++ << "\n";
                    cout << *asHouse << "\n";
                } else if (asApartament) {
                    cout<<"Apartament\n";
                    cout << "Cladire :" << nr_cld++ << "\n";
                    cout << *asApartament<<"\n";
                }
            }
        }
        else cout<<"Nu exista cladiri";
    }
    void option3() {
        option2();
        int nr;
        cout<<"Numarul cladirii pe care vrem sa il stergem: ";
        cin >> nr;
        if(!b.empty()) {
            if(nr >= 0 and nr < b.size()) {
                b.erase(b.begin() + nr);
                cout << "Am sters cladirea " << nr  << '\n';
            }
            else cout<<"Nu avem cladirea "<< nr <<'\n';
        }
        else cout<<"Nu exista cladiri";
    }

    void option4() {
        option2();
        int nr;
        cout<<"Numarul cladirii pe care vrem sa o modificam: ";
        cin >> nr;
        if(!b.empty()) {
            if(nr >= 0 and nr < b.size()) {
                int opt;
                cout<<"Pt apartament tasteaza 1 iar pt House apasa 2:";
                cin >>opt;
                if(opt == 1) {
                    House h;
                    cin >> h;
                    b[nr] = make_shared<House>(h);
                }
                else if (opt == 2) {
                    Apartament p;
                    cin >> p;
                    b[nr]= make_shared<Apartament>(p);
                } else if(opt < 1 or opt > 2){
                    cout<< "operatie gresita.Introdu operatia:";
                    cin >> opt;
                }
                cout << "Am modificat datele cladirii " << nr  << '\n';
            }
            else cout<<"Nu avem cladirea "<< nr <<'\n';
        }
        else cout<<"Nu exista cladiri";
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            }else if(option == 5){
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Meniu Building inchis";
    }

};

class OwnerMenu : public BaseMenu {
private:
    vector<shared_ptr<Owner>>o;
public:
    void setO(vector<shared_ptr<Owner>> &ow) {
        o = ow;
    }

public:
    void listOptions() override {
        cout << "1. Adauga un owner." << '\n';
        cout << "2. Afiseaza toti ownerii." << '\n';
        cout << "3. Sterge un owner existent." << '\n';
        cout << "4. Modifica un owner." << '\n';
        cout << "5. Iesire." << '\n';
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

    void option1(){
        shared_ptr<Owner> nou;
        nou = citesteo();
        o.push_back(nou);
        cout << "Am adaugat un owner." << '\n';
    }
    void option2(){
        if(!o.empty()) {
            int i=0;
            cout<<"Toti owneri sunt:\n\n";
            for(const auto& x: o) {
                cout <<i++ <<" "<< *x<< "\n";
            }
        }
        else cout<<"Nu exista owneri\n";
    }
    void option3() {
        option2();
        int nr;
        cout<<"Numarul ownerului pe care vrem sa il stergem: ";
        cin >> nr;
        if(!o.empty()) {
            if(nr >= 0 and nr < o.size()) {
                o.erase(o.begin() + nr);
                cout << "Am sters ownerul " << nr  << '\n';
            }
            else cout<<"Nu avem ownerul "<< nr <<'\n';
        }
        else cout<<"Nu exista owneri\n";
    }

    void option4() {
        option2();
        int nr;
        cout<<"Numarul ownerului pe care vrem sa o modificam: ";
        cin >> nr;
        if(!o.empty()) {
            if(nr >= 0 and nr < o.size()) {
                Owner mod;
                cin >> mod;
                o[nr] = make_shared<Owner>(mod);
                cout << "Am modificat datele ownerului " << nr  << '\n';
            }
            else cout<<"Nu avem ownerul "<< nr <<'\n';
        }
        else cout<<"Nu exista owneri";
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 5);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                option4();
            }else if(option == 5){
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Meniul de Owner inchis";
    }

};

class ComposedMenu : public BaseMenu {
protected:
    vector<shared_ptr<Building>> b;
    vector< shared_ptr <Owner> > o;

public:
    ComposedMenu(const vector<shared_ptr<Building>> &b, const vector<shared_ptr<Owner>> &o) : b(b) , o(o) {};

    void listOptions() override {
        cout << "1.Building menu\n";
        cout << "2.OwnerMenu\n";
        cout << "3.Exit" << '\n';
    }

    int chooseOption(int first, int  last) override {
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
    void option1(){
        cout << "Am deschis meniul Building \n";
        BuildingMenu bi;
        bi.setB(b);
        bi.mainLoop();
    }
    void option2(){
        cout << "Am deschis meniul Owner \n";
        OwnerMenu ow;
        ow.setO(o);
        ow.mainLoop();
    }


    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 3);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Programul s-a incheiat cu success";
    }

};

int main() {
    vector<shared_ptr<Building>> b = {
            make_shared<Apartament>(
                    "rosu", "Alex Pop", 2
            ),
            make_shared<House>(
                    "rosu", "Alex Pop", 3
            ),
    };

    vector<shared_ptr<Owner> >on = {
            make_shared<Owner>("asa"),

    };
    ComposedMenu menu = ComposedMenu(b,on);
    menu.mainLoop();
}