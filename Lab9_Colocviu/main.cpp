#include <utility>
#include <bits/stdc++.h>
#include "util/IoBase.h"
#include "util/functions.h"
using namespace std;

class Jucarie:public IoBase{
protected:
    string denumire;
    double dimensiune;
    string tip;

public:
    Jucarie()=default;
    Jucarie(const string &denumire, double dimensiune, const string &tip) : denumire(denumire), dimensiune(dimensiune),
                                                                            tip(tip) {}

    istream &read(istream &is) override {
        cout<<"Denumire jucarie: ";
        cin>>denumire;
        cout<<"Dimensiune jucarie: ";
        cin>>dimensiune;
        cout<<"Tip jucarie: ";
        cin>>tip;
        return IoBase::read(is);
    }

    ostream &write(ostream &os) const override {
        cout<<"Denumire jucarie: "<<denumire<<"\n";
        cout<<"Dimensiune jucarie: "<<dimensiune<<"\n";
        cout<<"Tip jucarie: "<<tip<<"\n";
        return IoBase::write(os);
    }
};

class JucarieClasica:public Jucarie{
private:
    string material;
    string culoare;

public:
    JucarieClasica()=default;
    JucarieClasica(const string &denumire, double dimensiune, const string &tip, const string &material,
                   const string &culoare) : Jucarie(denumire, dimensiune, tip), material(material), culoare(culoare) {}

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout<<"Material: ";
        cin>>material;
        cout<<"Culoare: ";
        cin>>culoare;
        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        cout<<"Material: "<<material<<"\n";
        cout<<"Culoare: "<<culoare<<"\n";
        return os;
    }

};

class JucarieEducativa:public virtual Jucarie{
protected:
    string abilitate_dezvoltata;

public:
    JucarieEducativa()=default;
    JucarieEducativa(const string &denumire, double dimensiune, const string &tip, const string &abilitateDezvoltata)
            : Jucarie(denumire, dimensiune, tip), abilitate_dezvoltata(abilitateDezvoltata) {}

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout<<"Abilitate dezvoltata: ";
        cin>>abilitate_dezvoltata;
        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        cout<<"Abilitate dezvoltata: "<<abilitate_dezvoltata<<"\n";
    }
};

class JucarieElectronica:public virtual Jucarie{
protected:
    int numar_baterii;

public:
    JucarieElectronica()=default;

    JucarieElectronica(const string &denumire, double dimensiune, const string &tip, int numarBaterii) : Jucarie(
            denumire, dimensiune, tip), numar_baterii(numarBaterii) {}

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout<<"Numar baterii: ";
        cin>>numar_baterii;
        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        cout<<"Numar baterii: "<<numar_baterii<<"\n";
        return os;
    }
};

class JucarieModerna:public virtual JucarieElectronica, public virtual JucarieEducativa{
private:
    string brand;
    string model;
public:
    JucarieModerna(){
        numar_baterii=1;
        abilitate_dezvoltata="generala";
    }
    JucarieModerna(const string &denumire, double dimensiune, const string &tip,string brand,string  model):Jucarie(denumire,dimensiune,tip),brand(std::move(brand)),model(std::move(model)){
        numar_baterii=1;
        abilitate_dezvoltata="generala";
    };

    istream &read(istream &is) override {
        Jucarie::read(is);
        return is;
    }

    ostream &write(ostream &os) const override {
        JucarieElectronica::write(os);
        cout<<"Abilitate dezvoltata: "<<abilitate_dezvoltata<<"\n";
        return os;
    }

};


class Copil:public IoBase{
protected:
    static int id_increment;
    int id;
    string nume;
    string prenume;
    string adresa;
    int varsta;
    int numar_fapte_bune;
    vector <shared_ptr<Jucarie>> jucarii;

public:
    Copil() {
        id=++id_increment;
    }

    Copil(const string &nume, const string &prenume, const string &adresa, int varsta, int numarFapteBune,
          const vector<shared_ptr<Jucarie>> &jucarii);

    int getId();

    const string &getNume() const;

    void setNume(const string &nume);

    const string &getPrenume() const;

    void setPrenume(const string &prenume);

    const string &getAdresa() const;

    void setAdresa(const string &adresa);

    int getVarsta() const;

    void setVarsta(int varsta);

    int getNumarFapteBune() const;

    void setNumarFapteBune(int numarFapteBune);

    const vector<shared_ptr<Jucarie>> &getJucarii() const;

    void setJucarii(const vector<shared_ptr<Jucarie>> &jucarii);

    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;

};

int Copil::id_increment=0;

Copil::Copil(const string &nume, const string &prenume, const string &adresa, int varsta, int numarFapteBune,
             const vector<shared_ptr<Jucarie>> &jucarii) : nume(nume), prenume(prenume), adresa(adresa), varsta(varsta),
                                                           numar_fapte_bune(numarFapteBune), jucarii(jucarii) {

    id=++id_increment;
//    if(numarFapteBune!=jucarii.size()){
//        throw string("Numarul de fapte bune nu corespunde cu numarul de jucarii.\n");
//    }
}


const string &Copil::getNume() const {
    return nume;
}

void Copil::setNume(const string &nume) {
    Copil::nume = nume;
}

const string &Copil::getPrenume() const {
    return prenume;
}

void Copil::setPrenume(const string &prenume) {
    Copil::prenume = prenume;
}

const string &Copil::getAdresa() const {
    return adresa;
}

void Copil::setAdresa(const string &adresa) {
    Copil::adresa = adresa;
}

int Copil::getVarsta() const {
    return varsta;
}

void Copil::setVarsta(int varsta) {
    Copil::varsta = varsta;
}

int Copil::getNumarFapteBune() const {
    return numar_fapte_bune;
}

void Copil::setNumarFapteBune(int numarFapteBune) {
    numar_fapte_bune = numarFapteBune;
}

const vector<shared_ptr<Jucarie>> &Copil::getJucarii() const {
    return jucarii;
}

void Copil::setJucarii(const vector<shared_ptr<Jucarie>> &jucarii) {
    Copil::jucarii = jucarii;
}

istream &Copil::read(istream &is) {
    cout<<"Nume: ";
    cin>>nume;
    cout<<"Prenume: ";
    cin>>prenume;
    cin.get();
    cout<<"Adresa: ";
    getline(cin, adresa);
    cout<<"Numar fapte bune: ";
    cin>>numar_fapte_bune;
    cout<<"Introduceti jucariile copilului citit.\n";
    for(int i=0;i<numar_fapte_bune;i++){
        cout<<"Introduceti:\n"<<"1. Jucarie clasica\n"<<"2. Jucarie educativa\n"<<"3. Jucarie electronica\n"<<"4. Jucarie moderna\n";
        int tip_jucarie;

        cin>>tip_jucarie;
        while(tip_jucarie!=1 and tip_jucarie!=2 and tip_jucarie!=3 and tip_jucarie!=4){
            cout<<"Tipul jucariei a fost introdus gresit. Reintrodu tipul jucariei.\n";
            cin>>tip_jucarie;
        }
        if(tip_jucarie==1){
            JucarieClasica jucarie;
            cin>>jucarie;
            jucarii.push_back(make_shared<JucarieClasica>(jucarie));

        }else if(tip_jucarie==2){
            JucarieEducativa jucarie;
            cin>>jucarie;
            jucarii.push_back(make_shared<JucarieEducativa>(jucarie));

        }else if(tip_jucarie==3){
            JucarieElectronica jucarie;
            cin>>jucarie;
            jucarii.push_back(make_shared<JucarieElectronica>(jucarie));

        }else if(tip_jucarie==4){
            JucarieModerna jucarie;
            cin>>jucarie;
            jucarii.push_back(make_shared<JucarieModerna>(jucarie));
        }
    }
    return is;
}

ostream &Copil::write(ostream &os) const {
    cout<<"ID: "<<id<<"\n";
    cout<<"Nume: "<<nume<<"\n";
    cout<<"Prenume: "<<prenume<<"\n";
    cout<<"Adresa: "<<adresa<<"\n";
    cout<<"Numar fapte bune: "<<numar_fapte_bune<<"\n";
    cout<<"Jucariile sunt:\n";
    for(const auto & i : jucarii){
        auto *asJucarieClasica = dynamic_cast<JucarieClasica *>(i.get());
        auto *asJucarieEducativa = dynamic_cast<JucarieEducativa *>(i.get());
        auto *asJucarieElectronica = dynamic_cast<JucarieElectronica *>(i.get());
        auto *asJucarieModerna = dynamic_cast<JucarieModerna *>(i.get());

        if(asJucarieClasica){
            cout<<*asJucarieClasica;
        }else if(asJucarieEducativa){
            cout<<*asJucarieEducativa;
        }else if(asJucarieElectronica){
            cout<<*asJucarieElectronica;
        }else if(asJucarieModerna){
            cout<<*asJucarieModerna;
        }
    }
    return os;
}

class CopilCuminte:public Copil{
private:
    int numar_dulciuri;

public:
    CopilCuminte()=default;

    CopilCuminte(const string &nume, const string &prenume, const string &adresa, int varsta, int numarFapteBune,
                 const vector<shared_ptr<Jucarie>> &jucarii, int numarDulciuri) : Copil(nume, prenume, adresa, varsta,
                                                                                        numarFapteBune, jucarii),
                                                                                  numar_dulciuri(numarDulciuri) {}

    istream &read(istream &is) override {
        Copil::read(is);
        cout<<"Numar dulciuri: ";
        cin>>numar_dulciuri;
        return is;
    }

    ostream &write(ostream &os) const override {
        Copil::write(os);
        cout<<"Numar dulciuri: "<<numar_dulciuri<<"\n";
        return os;
    }

};

class CopilNeastamparat:public Copil{
private:
    int numar_carbuni;

public:
    CopilNeastamparat()=default;

    CopilNeastamparat(const string &nume, const string &prenume, const string &adresa, int varsta, int numarFapteBune,
                      const vector<shared_ptr<Jucarie>> &jucarii, int numarCarbuni) : Copil(nume, prenume, adresa,
                                                                                            varsta, numarFapteBune,
                                                                                            jucarii),
                                                                                      numar_carbuni(numarCarbuni) {}

    istream &read(istream &is) override {
        Copil::read(is);
        cout<<"Numar carbuni: ";
        cin>>numar_carbuni;
        return is;
    }

    ostream &write(ostream &os) const override {
        Copil::write(os);
        cout<<"Numar carbuni: "<<numar_carbuni<<"\n";
        return os;
    }
};


class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, int last) {}

    virtual void mainLoop() {}
};


class CopiiMenu:public BaseMenu{
private:
    vector <shared_ptr<Copil>> copii;

public:
    CopiiMenu()=default;

    void setCopii(const vector<shared_ptr<Copil>> &copii) {
        CopiiMenu::copii = copii;
    }

    void listOptions() override {
        cout << "1. Adauga n copii." << '\n';
        cout << "2. Afiseaza copii din aplicatie." << '\n';
        cout << "3. Iesire." << '\n';
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
          cout<<"Introdu numarul de copii pe care vrei sa.i adaugi: ";
          int nr_copii;
          cin>>nr_copii;
          for(int i=0;i<nr_copii;i++){
              cout<<"Introdu 1 pentru copil cuminte si 2 pentru copil neastamparat.\n";
              int tip_copil;
              cin>>tip_copil;
              while(tip_copil!=1 and tip_copil!=2){
                  cout<<"Tip de date introdus gresit. Introdu 1 pentru copil cuminte si 2 pentru copil neastamparat.\n";
                  cin>>tip_copil;
              }
              if(tip_copil==1){
                  CopilCuminte copil_cuminte;
                  cin>>copil_cuminte;
                  while(copil_cuminte.getNumarFapteBune()!=copil_cuminte.getJucarii().size()){
                      cout<<"Numarul de fapte bune nu corespunde cu numarul de jucarii. Reintrodu datele despre copilul citit.\n";
                      cin>>copil_cuminte;
                  }
//                  while(copil_cuminte.getNumarFapteBune()<10){
//                      cout<<"Un copil cuminte are cel putin 10 fapte bune. Reintrodu datele despre copilul citit.\n";
//                      cin>>copil_cuminte;
//                  }
                  copii.emplace_back(make_shared<CopilCuminte>(copil_cuminte));

              }else if(tip_copil==2){
                  CopilNeastamparat copil_neastamparat;
                  cin>>copil_neastamparat;
//                  while(copil_neastamparat.getNumarFapteBune()!=copil_neastamparat.getJucarii().size()){
//                      cout<<"Numarul de fapte bune nu corespunde cu numarul de jucarii. Reintrodu datele despre copilul citit.\n";
//                      cin>>copil_neastamparat;
//                  }
                  copii.emplace_back(make_shared<CopilNeastamparat>(copil_neastamparat));
              }

          }
    }

    void option2(){
//        cout<<copii.size();
        if(copii.size()){
            cout<<"Copiii din aplicatia lui Mos Craciun sunt:\n";
            for(auto & i : copii){
                auto *asCopilCuminte = dynamic_cast<CopilCuminte *>(i.get());
                auto *asCopilNeastamparat = dynamic_cast<CopilNeastamparat *>(i.get());

                if(asCopilCuminte){
                    cout<<*asCopilCuminte;
                }else if(asCopilNeastamparat){
                    cout<<*asCopilNeastamparat;
                }
            }
        }else{
            cout<<"Nu exista copii in aplicatie introdusi.\n";
        }
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 3);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            }else if(option == 3){
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Meniu Copii inchis";
    }
};




class JucariiMenu:public BaseMenu{
private:
    vector <shared_ptr<Copil>> copii;

public:
    JucariiMenu()=default;

    void setCopii(const vector<shared_ptr<Copil>> &copii) {
        JucariiMenu::copii = copii;
    }

    void listOptions() override {
        cout << "1. Adauga m jucarii unui copil." << '\n';
        cout << "2. Afiseaza jucariile unui copil." << '\n';
        cout << "3. Iesire." << '\n';
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
        cout<<"Introdu ID-ul copilului caruia vrei sa.i adaugi jucarii.\n";
        int id_introdus;
        cin>>id_introdus;

        cout<<"Introdu numarul de jucarii pe care vrei sa le adaugi: ";
        int m;
        cin>>m;
        for(int i=0;i<m;i++){
            cout<<"Introduceti:\n"<<"1. Jucarie clasica\n"<<"2. Jucarie educativa\n"<<"3. Jucarie electronica\n"<<"4. Jucarie moderna\n";
            int tip_jucarie;

            cin>>tip_jucarie;
            while(tip_jucarie!=1 and tip_jucarie!=2 and tip_jucarie!=3 and tip_jucarie!=4){
                cout<<"Tipul jucariei a fost introdus gresit. Reintrodu tipul jucariei.\n";
                cin>>tip_jucarie;
            }
            if(tip_jucarie==1){
                JucarieClasica jucarie;
                cin>>jucarie;
                vector <shared_ptr<Jucarie>> toys=copii[id_introdus-1]->getJucarii();
                toys.emplace_back(make_shared<JucarieClasica>(jucarie));
                copii[id_introdus-1]->setJucarii(toys);

            }else if(tip_jucarie==2){
                JucarieEducativa jucarie;
                cin>>jucarie;
                vector <shared_ptr<Jucarie>> toys=copii[id_introdus-1]->getJucarii();
                toys.emplace_back(make_shared<JucarieEducativa>(jucarie));
                copii[id_introdus-1]->setJucarii(toys);

            }else if(tip_jucarie==3){
                JucarieElectronica jucarie;
                cin>>jucarie;
                vector <shared_ptr<Jucarie>> toys=copii[id_introdus-1]->getJucarii();
                toys.emplace_back(make_shared<JucarieElectronica>(jucarie));
                copii[id_introdus-1]->setJucarii(toys);

            }else if(tip_jucarie==4){
                JucarieModerna jucarie;
                cin>>jucarie;
                vector <shared_ptr<Jucarie>> toys=copii[id_introdus-1]->getJucarii();
                toys.emplace_back(make_shared<JucarieModerna>(jucarie));
                copii[id_introdus-1]->setJucarii(toys);
            }

        }
    }

    void option2(){

        if(copii.size()){
            cout<<"Introdu ID-ul copilului caruia vrei sa.i afisezi jucariile.\n";
            int id_introdus;
            cin>>id_introdus;
            while(id_introdus>copii.size()){
                cout<<"Id introdus gresit.\n";
                cin>>id_introdus;
            }
            cout<<"Jucariile sunt:\n";
            for(const auto & i : copii[id_introdus-1]->getJucarii()){
                auto *asJucarieClasica = dynamic_cast<JucarieClasica *>(i.get());
                auto *asJucarieEducativa = dynamic_cast<JucarieEducativa *>(i.get());
                auto *asJucarieElectronica = dynamic_cast<JucarieElectronica *>(i.get());
                auto *asJucarieModerna = dynamic_cast<JucarieModerna *>(i.get());

                if(asJucarieClasica){
                    cout<<*asJucarieClasica;
                }else if(asJucarieEducativa){
                    cout<<*asJucarieEducativa;
                }else if(asJucarieElectronica){
                    cout<<*asJucarieElectronica;
                }else if(asJucarieModerna){
                    cout<<*asJucarieModerna;
                }
            }
        }else{
            cout<<"Nu exista copii in aplicatie introdusi.\n";
        }
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, 3);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            }else if(option == 3){
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Meniu Copii inchis";
    }
};



int main() {


//    JucarieElectronica j1;
//    cin>>j1;
//    cout<<j1;

//    JucarieClasica j2;
//    cin>>j2;
//    cout<<j2;

//    JucarieModerna j3;
//    cin>>j3;
//    cout<<j3;

//    CopiiMenu menu;
//    menu.mainLoop();



    return 0;
}
