#include <bits/stdc++.h>
using namespace std;

class Iobase{
public:
    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os){
        return os;
    }

    friend istream &operator>>(istream &is, Iobase &base){
        return base.read(is);
    }
    friend ostream &operator<<(ostream &os, Iobase &base){
        return base.write(os);
    }

};

template <typename T>
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



class Produs:public Iobase{
    private:
        string nume;
        int cantitate;

    public:
        Produs(){
            nume="";
            cantitate=0;
        }

    Produs(const string &nume, int cantitate) : nume(nume), cantitate(cantitate) {}

    istream &read(istream &is) override {
        Iobase::read(is);
        cin.get();
        cout<<"Nume produs: ";
        getline(cin, nume);
        cout<<"Cantitate: ";
        cin>>cantitate;
        return is;
    }

    ostream &write(ostream &os) override {
        Iobase::write(os);
        cout<<"Nume produs: "<<nume<<"\n";
        cout<<"Cantitate: "<<cantitate<<"\n";
        return os;
    }


};

class Comanda:public Iobase{
    protected:
        int id_c;
        int static id;
        string client;
        string adresa;
        double pret;
        int timp_livrare;


    public:
        Comanda(){
            id_c=id++;
            client="";
            adresa="";
            pret=0;
            timp_livrare=0;
        }

    Comanda(const string &client, const string &adresa, double pret, int timpLivrare);

    istream &read(istream &is) override;

    ostream &write(ostream &os) override;

    int getIdC() const;

    const string &getClient() const;

    double getPret() const;

};

int Comanda::id=1;


istream &Comanda::read(istream &is) {
    Iobase::read(is);
    cout<<"Client: ";
    cin.get();
    getline(cin, client);
    cout<<"Adresa: ";
    getline(cin, adresa);
    cout<<"Pret: ";
    cin>>pret;
    cout<<"Timp livrare: ";
    cin>>timp_livrare;
    return is;
}

ostream &Comanda::write(ostream &os) {
    Iobase::write(os);
    cout<<"ID comanda: "<<id_c<<"\n";
    cout<<"Client: "<<client<<"\n";
    cout<<"Adresa: "<<adresa<<"\n";
    cout<<"Pret: "<<pret<<"\n";
    cout<<"Timp livrare: "<<timp_livrare<<"\n";
    return os;
}

Comanda::Comanda(const string &client, const string &adresa, double pret, int timpLivrare) :client(client),adresa(adresa),pret(pret),timp_livrare(timpLivrare) {id_c=id++;}

int Comanda::getIdC() const {
    return id_c;
}

const string &Comanda::getClient() const {
    return client;
}

double Comanda::getPret() const {
    return pret;
}


class ComandaMancare:public virtual Comanda{
protected:
    string local;
    vector<Produs> produse;

public:
    ComandaMancare(){
        local="";
    }

    ComandaMancare(const string &client, const string &adresa, double pret, int timpLivrare, const string &local,
                   const vector<Produs> &produse) : Comanda(client, adresa, pret, timpLivrare), local(local),
                                                    produse(produse) {}


    istream &read(istream &is) override {
        Comanda::read(is);
        cin.get();
        cout<<"Local: ";
        getline(cin, local);
        cout<<"Produse:\n";
        cout<<"n= ";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            Produs p;
            cin>>p;
            produse.push_back(p);
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Comanda::write(os);
        cout<<"Local: "<<local<<"\n";
        cout<<"Produse:\n";
        for(int i=0;i<produse.size();i++){
            cout<<produse[i];
        }
        return os;
    }
};

class ComandaRestaurant: public virtual ComandaMancare{
private:
    bool tacamuri;

public:
    ComandaRestaurant(){
        tacamuri= false;
    }

    ComandaRestaurant(const string &client, const string &adresa, double pret, int timpLivrare, const string &local,
                      const vector<Produs> &produse, bool tacamuri) : ComandaMancare(client, adresa, pret, timpLivrare,
                                                                                     local, produse),
                                                                      tacamuri(tacamuri) {}

    istream &read(istream &is) override {
        ComandaMancare::read(is);
        cout<<"Introduceti 1 pentru tacamuri, 0 fara tacamuri.\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip!=0){
            cout<<"Introduceti 1 pentru tacamuri, 0 fara tacamuri.\n";
            cin>>tip;
        }
        if(tip==1){
            tacamuri= true;
        }else{
            tacamuri= false;
        }
        return is;
    }

    ostream &write(ostream &os) override {
        ComandaMancare::write(os);
        if(tacamuri){
            cout<<"Tacamuri: da\n";
        }else{
            cout<<"Tacamuri: nu\n";
        }
        return os;
    }

};

class ComandaFastFood:public ComandaMancare{
private:
    double discount;

public:
    ComandaFastFood(){
        discount=0;
    }

    ComandaFastFood(const string &client, const string &adresa, double pret, int timpLivrare, const string &local,
                    const vector<Produs> &produse, double discount) : ComandaMancare(client, adresa, pret, timpLivrare,
                                                                                     local, produse),
                                                                      discount(discount) {}

    istream &read(istream &is) override {
        ComandaMancare::read(is);
        cout<<"Discount: ";
        cin>>discount;
        return is;
    }

    ostream &write(ostream &os) override {
        ComandaMancare::write(os);
        cout<<"Discount: "<<discount<<"\n";
        return os;
    }
};

class Medicament: public virtual Produs{
private:
    bool antibiotic;

public:
    Medicament(){
        antibiotic= false;
    }

    Medicament(const string &nume, int cantitate, bool antibiotic) : Produs(nume, cantitate), antibiotic(antibiotic) {}

    istream &read(istream &is) override {
        Produs::read(is);
        cout<<"Introduceti 1 daca e medicament 0 in caz contrar.\n";
        int tip;
        cin>>tip;
        if(tip!=1 and tip!=0){
            cout<<"Introduceti 1 daca e medicament 0 in caz contrar.\n";
            cin>>tip;
        }
        if(tip){
            antibiotic=true;
        }else{
            antibiotic= false;
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Produs::write(os);
        if(antibiotic){
            cout<<"Antibiotic: da\n";
        }else{
            cout<<"Antibiotic: nu\n";
        }
        return os;
    }

};

class ComandaMedicamente: public virtual Comanda{
private:
    vector<Medicament> medicamente;

public:
    ComandaMedicamente()=default;

    ComandaMedicamente(const string &client, const string &adresa, double pret, int timpLivrare,
                       const vector<Medicament> &medicamente) : Comanda(client, adresa, pret, timpLivrare),
                                                                medicamente(medicamente) {}

    istream &read(istream &is) override {
        Comanda::read(is);
        cout<<"Medicamente:\n";
        cout<<"n= ";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            Medicament m;
            cin>>m;
            medicamente.push_back(m);
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Comanda::write(os);
        cout<<"Medicamente:\n";
        for(auto & i : medicamente){
            cout<<i;
        }
        return os;
    }

};

class Tigara:public virtual Produs{
private:
    bool clasic;

public:
    Tigara(){
        clasic= true;
    }

    Tigara(const string &nume, int cantitate, bool clasic) : Produs(nume, cantitate), clasic(clasic) {}

    istream &read(istream &is) override {
        Produs::read(is);
        cout<<"Introduceti 1 pentru tiagar clasica si 0 pentru trabuc.\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip!=0){
            cout<<"Introduceti 1 pentru tigara clasica si 0 pentru trabuc.\n";
            cin>>tip;
        }
        if(tip){
            clasic=true;
        }else{
            clasic=false;
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Produs::write(os);
        if(clasic){
            cout<<"Tip tigara: normala\n";
        }else{
            cout<<"Tip tigara: trabuc\n";
        }
    }

};

class ComandaTigari: public virtual Comanda{
private:
    vector<Tigara> tigari;

public:
    ComandaTigari()=default;

    ComandaTigari(const string &client, const string &adresa, double pret, int timpLivrare,
                  const vector<Tigara> &tigari) : Comanda(client, adresa, pret, timpLivrare), tigari(tigari) {}

    istream &read(istream &is) override {
        Comanda::read(is);
        cout<<"Tigari:\n";
        int n;
        cout<<"n= ";
        cin>>n;
        for(int i=0;i<n;i++){
            Tigara t;
            cin>>t;
            tigari.push_back(t);
        }
        return is;
    }

    ostream &write(ostream &os) override {
        Comanda::write(os);
        cout<<"Tigari:\n";
        for(int i=0;i<tigari.size();i++){
            cout<<tigari[i];
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

    vector<shared_ptr<Comanda>> comenzi;


public:

    static Menu *getMenu() {
        if (menu != nullptr) {
            return menu;
        }
        menu = new Menu();
        return menu;
    }


    void listOptions() override {
        cout<<"1. Citire comenzi.\n";
        cout<<"2. Adauga comanda.\n";
        cout<<"3. Afiseaza comenzi.\n";
        cout<<"4. Stergere comanda dupa ID.\n";
        cout<<"5. Cautare comanda dupa ID.\n";
        cout<<"6. Cautare comanda dupa numele clientului.\n";
        cout<<"7. Ordonare comenzi dupa pret descrescator.\n";
        cout<<"8. Exit.\n";
    }

    void option1(){
        cout<<"Introduceti un numar n.\n";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"Introduceti:\n1. Comanda fast-food\n2. Comanda restaurant\n3. Comanda farmacie\n4. Comanda Tigari\n";
            int tip;
            cin>>tip;
            while(tip!=1 and tip!=2 and tip!=3 and tip!=4){
                cout<<"Tip gresit introdus. Reintroduceti tipul.\n";
                cin>>tip;
            }
            if(tip==1){
                ComandaFastFood c;
                cin>>c;
                comenzi.push_back(make_shared<Comanda>(c));
            }

            if(tip==2){
                ComandaRestaurant c;
                cin>>c;
                comenzi.push_back(make_shared<Comanda>(c));
            }

            if(tip==3){
                ComandaMedicamente c;
                cin>>c;
                comenzi.push_back(make_shared<Comanda>(c));
            }

            if(tip==4){
                ComandaTigari c;
                cin>>c;
                comenzi.push_back(make_shared<Comanda>(c));
            }
        }

    }

    void option2(){
        cout<<"Introduceti:\n1. Comanda fast-food\n2. Comanda restaurant\n3. Comanda farmacie\n4. Comanda Tigari\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip!=2 and tip!=3 and tip!=4){
            cout<<"Tip gresit introdus. Reintroduceti tipul.\n";
            cin>>tip;
        }
        if(tip==1){
            ComandaFastFood c;
            cin>>c;
            comenzi.push_back(make_shared<ComandaFastFood>(c));
        }

        if(tip==2){
            ComandaRestaurant c;
            cin>>c;
            comenzi.push_back(make_shared<ComandaRestaurant>(c));
        }

        if(tip==3){
            ComandaMedicamente c;
            cin>>c;
            comenzi.push_back(make_shared<ComandaMedicamente>(c));
        }

        if(tip==4){
            ComandaTigari c;
            cin>>c;
            comenzi.push_back(make_shared<ComandaTigari>(c));
        }

    }

    void option3(){
        for(const auto & i : comenzi){
            auto *r=dynamic_cast< ComandaRestaurant *>(i.get());
            auto *f=dynamic_cast< ComandaFastFood *>(i.get());
            auto *t=dynamic_cast< ComandaTigari *>(i.get());
            auto *m=dynamic_cast< ComandaMedicamente *>(i.get());
            if(m){
                cout<<*m;
            }
            if(t){
                cout<<*t;
            }
            if(f){
                cout<<*f;
            }
            if(r){
                cout<<*r;
            }
        }

    }

    void option4(){
        cout<<"Introduceti ID-ul.\n";
        int id;
        cin>>id;
        vector<shared_ptr<Comanda>> comenzi_act;
        for(int i=0;i<comenzi.size();i++){
            if(comenzi[i]->getIdC()!=id){
                comenzi_act.push_back(comenzi[i]);
            }
        }
        if(comenzi_act.size()!=comenzi.size()){
            cout<<"Stergerea a fost facuta cu succes.\n";
        }else{
            cout<<"Nu s-a gasit comanda cu id.ul introdus.\n";
        }
        comenzi=comenzi_act;
    }

    void option5(){
        cout<<"Introduceti ID-ul.\n";
        int id;
        cin>>id;
        int ok=0;
        for(int i=0;i<comenzi.size();i++){
            if(comenzi[i]->getIdC()==id){
                cout<<comenzi[i];
                ok=1;
            }
        }
        if(ok==0){
            cout<<"Nu s-a gasit comanda cu id.ul introdus.\n";
        }

    }

    void option6(){
        cout<<"Introduceti numele clientului.\n";
        string nume;
        getline(cin, nume);
        int ok=0;
        for(int i=0;i<comenzi.size();i++){
            if(comenzi[i]->getClient()==nume){
                cout<<comenzi[i];
                ok=1;
            }
        }
        if(ok==0){
            cout<<"Nu s-a gasit comanda cu id.ulnumele clientului introdus.\n";
        }

    }

    void option7(){
        for(int i=0;i<comenzi.size()-1;i++){
            for(int j=i+1;j<comenzi.size();j++){
                if(comenzi[i]->getPret()<comenzi[j]->getPret()){
                    swap(comenzi[i], comenzi[j]);
                }
            }
        }
        cout<<"Sortarea a fost realizata.\n";

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
            int option = chooseOption(1, 8);
            if(option==1){
                option1();
            }
            if(option==2){
                option2();
            }
            if(option==3){
                option3();
            }
            if(option==4){
                option4();
            }
            if(option==5){
                option5();
            }
            if(option==6){
                option6();
            }
            if(option==7){
                option7();
            }
            if(option==8){
                break;
            }

        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }



};

Menu *Menu::menu = nullptr;



int main() {

    Menu *meniu = Menu::getMenu();
    meniu->mainLoop();
    return 0;
}


