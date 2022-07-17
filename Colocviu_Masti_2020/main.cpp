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




class Masca: public IoBase{
public:
    Masca(){};
};



class MascaChirurgicala: public virtual Masca{
private:
    string tip_protectie;
    string culoare;
    int numar_pliuri;
    string logo;

public:
    MascaChirurgicala(){
        logo="none";
        numar_pliuri=0;
    }

    MascaChirurgicala(const string &tipProtectie, const string &culoare, int numarPliuri, string logo="none")
            : tip_protectie(tipProtectie), culoare(culoare), numar_pliuri(numarPliuri), logo(logo) {}

    MascaChirurgicala(MascaChirurgicala &m){
        this->logo=m.logo;
        this->numar_pliuri=m.numar_pliuri;
        this->tip_protectie=m.tip_protectie;
        this->culoare=m.culoare;
    }

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Tip protectie: ";
        cin>>tip_protectie;
        cin.get();
        cout<<"Culoare: ";
        getline(cin, culoare);
        cout<<"Numar pliuri: ";
        cin>>numar_pliuri;
        cout<<"Introduceti tasta 1 daca vreti un anumit logo, altfel tasta 0.\n";
        int t;
        cin>>t;
        while(t!=1 and t!=0){
            cout<<"Introduceti tasta 1 daca vreti un anumit logo, altfel tasta 0.\n";
            cin>>t;
        }

        if(t==1){
            cin.get();
            cout<<"Logo: ";
            getline(cin, logo);
        }else{
            logo="none";
        }
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Tip protectie: "<<tip_protectie<<"\n";
        cout<<"Culoare: "<<culoare<<"\n";
        cout<<"Numar pliuri: "<<numar_pliuri<<"\n";
        cout<<"Logo: "<<logo<<"\n";
        return os;
    }

    const string &getTipProtectie() const {
        return tip_protectie;
    }

    const string &getCuloare() const {
        return culoare;
    }

    int getNumarPliuri() const {
        return numar_pliuri;
    }

    const string &getLogo() const {
        return logo;
    }
};

class MascaPolicarbonat: public virtual Masca{
private:
    string tip_protectie;
    string tip_prindere;

public:
    MascaPolicarbonat(){
        tip_protectie="ffp0";
    }

    MascaPolicarbonat(const string &tipPrindere, const string &tipProtectie="ffp0") : tip_protectie(tipProtectie),
                                                                               tip_prindere(tipPrindere) {}

    MascaPolicarbonat(MascaPolicarbonat &m){
        this->tip_protectie=m.tip_protectie;
        this->tip_prindere=m.tip_prindere;
    }

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Tip protectie: ";
        cin>>tip_protectie;
        cin.get();
        cout<<"Tip prindere: ";
        getline(cin, tip_prindere);
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Tip protectie: "<<tip_protectie<<"\n";
        cout<<"Tip prindere: "<<tip_prindere<<"\n";
        return os;
    }
};
const int TotalBacterii=1e9;
const int TotalFungi=1.5*1e6;
const int TotalVirusi=1e8;

class Dezinfectant:public IoBase{
protected:
    int numar_specii;
    vector<string> ingrediente;
    vector<string> suprafete;

public:
    Dezinfectant()=default;

    Dezinfectant(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete) : numar_specii(
            numarSpecii), ingrediente(ingrediente), suprafete(suprafete) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Numar specii: ";
        cin>>numar_specii;
        cout<<"Ingrediente: ";
        cin>>ingrediente;
        cout<<"Suprafete pe care poate fi aplicat: ";
        cin>>suprafete;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Numar specii: "<<numar_specii<<"\n";
        cout<<"Ingrediente:\n"<<ingrediente<<"\n";
        cout<<"Suprafete pe care poate fi aplicat:\n"<<suprafete<<"\n";
    }

    virtual double eficienta(){};

    int getNumarSpecii() const {
        return numar_specii;
    }

    const vector<string> &getIngrediente() const {
        return ingrediente;
    }

    const vector<string> &getSuprafete() const {
        return suprafete;
    }

    void setNumarSpecii(int numarSpecii) {
        numar_specii = numarSpecii;
    }

    void setIngrediente(const vector<string> &ingrediente) {
        Dezinfectant::ingrediente = ingrediente;
    }

    void setSuprafete(const vector<string> &suprafete) {
        Dezinfectant::suprafete = suprafete;
    }

};

class DezinfectantBacterii: public virtual Dezinfectant{
public:
    DezinfectantBacterii()=default;

    DezinfectantBacterii(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete)
            : Dezinfectant(numarSpecii, ingrediente, suprafete) {}

    istream &read(istream &is) override {
        return Dezinfectant::read(is);
    }

    ostream &write(ostream &os) const override {
        return Dezinfectant::write(os);
    }

    double eficienta() override {
        return double(numar_specii)/TotalBacterii;
    }

};

class DezinfectantFungi: public virtual Dezinfectant{
public:
    DezinfectantFungi()=default;

    DezinfectantFungi(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete)
            : Dezinfectant(numarSpecii, ingrediente, suprafete) {}

    istream &read(istream &is) override {
        return Dezinfectant::read(is);
    }

    ostream &write(ostream &os) const override {
        return Dezinfectant::write(os);
    }

    double eficienta() override {
        return double(numar_specii)/TotalFungi;
    }
};

class DezinfectantVirusi: public virtual Dezinfectant{
public:
    DezinfectantVirusi()=default;

    DezinfectantVirusi(int numarSpecii, const vector<string> &ingrediente, const vector<string> &suprafete)
            : Dezinfectant(numarSpecii, ingrediente, suprafete) {}

    istream &read(istream &is) override {
        return Dezinfectant::read(is);
    }

    ostream &write(ostream &os) const override {
        return Dezinfectant::write(os);
    }

    double eficienta() override {
        return double(numar_specii)/TotalVirusi;
    }

};

struct Data{
    int zi;
    int luna;
    int an;
    Data(int x, int y, int z){
        zi=x;
        luna=z;
        an=y;
    }
    Data(){
        zi=0;
        luna=0;
        an=0;
    }
};



class Achizitie:public IoBase{
private:
    Data data;
    string client;
    vector<shared_ptr<Masca>> masti;
    vector<shared_ptr<Dezinfectant>> dezinfectante;
    int total;

public:
    Achizitie()=default;

    Achizitie(const Data &data, const string &client, const vector<shared_ptr<Masca>> &masti={},
              const vector<shared_ptr<Dezinfectant>> &dezinfectante={}) : data(data), client(client), masti(masti),
                                                                       dezinfectante(dezinfectante) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Data achizitiei: ";
        cin>>data.zi>>data.luna>>data.an;
        cin.get();
        cout<<"Nume client: ";
        getline(cin, client);
        cout<<"Introduceti numarul de dezinfectante: ";
        int n;
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"Introduceti:\n1.Bacterii\n2.Fungi\n3.Virusi\n";
            int tip;
            cin>>tip;
            while(tip!=1 and tip !=2 and tip!=3){
                cout<<"Tip invalid. Reintroduceti tipul.\n";
                cin>>tip;
            }
            if(tip==1){
                DezinfectantBacterii d;
                cin>>d;
                double ef=d.eficienta();
                if(ef*100<90){
                    total+=10;
                }
                if(ef*100>=90 and ef*100<95){
                    total+=20;
                }
                if(ef*100>=95 and ef*100<97.5){
                    total+=30;
                }
                if(ef*100>=97.5 and ef*100<99){
                    total+=40;
                }
                if(ef*100>=99 and ef*100<99.99){
                    total+=50;
                }
                dezinfectante.push_back(make_shared<Dezinfectant>(d));
            }

            if(tip==2){
                DezinfectantFungi d;
                cin>>d;
                double ef=d.eficienta();
                if(ef*100<90){
                    total+=10;
                }
                if(ef*100>=90 and ef*100<95){
                    total+=20;
                }
                if(ef*100>=95 and ef*100<97.5){
                    total+=30;
                }
                if(ef*100>=97.5 and ef*100<99){
                    total+=40;
                }
                if(ef*100>=99 and ef*100<99.99){
                    total+=50;
                }
                dezinfectante.push_back(make_shared<Dezinfectant>(d));
            }

            if(tip==3){
                DezinfectantVirusi d;
                cin>>d;
                double ef=d.eficienta();
                if(ef*100<90){
                    total+=10;
                }
                if(ef*100>=90 and ef*100<95){
                    total+=20;
                }
                if(ef*100>=95 and ef*100<97.5){
                    total+=30;
                }
                if(ef*100>=97.5 and ef*100<99){
                    total+=40;
                }
                if(ef*100>=99 and ef*100<99.99){
                    total+=50;
                }
                dezinfectante.push_back(make_shared<Dezinfectant>(d));
            }
        }

        cout<<"Introduceti numarul de masti: ";
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"Introduceti:\n1.Masca Chirurgicala\n2.Masca Policarbonat\n";
            int tip;
            cin>>tip;
            while(tip!=1 and tip !=2){
                cout<<"Tip invalid. Reintroduceti tipul.\n";
                cin>>tip;
            }
            if(tip==1){
                MascaChirurgicala m;
                cin>>m;
                masti.push_back(make_shared<Masca>(m));
                string protectie=m.getTipProtectie();
                if(protectie=="ffp1"){
                    total+=5;
                }else if(protectie=="ffp2"){
                    total+=10;
                }else if(protectie=="ffp3"){
                    total+=15;
                }
            }

            if(tip==2){
                MascaPolicarbonat m;
                cin>>m;
                total+=20;
                masti.push_back(make_shared<Masca>(m));
            }

        }
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Data achizitiei: "<<data.zi<<" "<<data.luna<<" "<<data.an<<"\n";
        cout<<"Client: "<<client<<"\n";
        cout<<"Dezinfectante:\n";
        for(const auto & i : dezinfectante){
            auto *asFungi = dynamic_cast<DezinfectantFungi *>(i.get());
            auto *asBacterii = dynamic_cast<DezinfectantBacterii *>(i.get());
            auto *asVirusi = dynamic_cast<DezinfectantVirusi *>(i.get());
            auto *asDez = dynamic_cast<Dezinfectant *>(i.get());

            if(asFungi){
                cout<<*asFungi;
            }else if(asBacterii){
                cout<<*asBacterii;
            }else if(asVirusi){
                cout<<*asVirusi;
            }else if(asDez){
                cout<<*asDez;
            }
        }
        cout<<"Masti:\n";
        for(const auto & i : masti){
            auto *asChir = dynamic_cast<MascaChirurgicala *>(i.get());
            auto *asPoli = dynamic_cast<MascaPolicarbonat *>(i.get());

            if(asChir){
                cout<<*asChir;
            }else if(asPoli){
                cout<<*asPoli;
            }
        }
    }

    //redefinire de operatori += pentru achiztii

    friend Achizitie operator+=(Achizitie &aq, const MascaPolicarbonat &m);
    friend Achizitie operator+=(Achizitie &aq, const MascaChirurgicala &m);
    friend Achizitie operator+=(Achizitie &aq, DezinfectantVirusi &d);
    friend Achizitie operator+=(Achizitie &aq, DezinfectantFungi &d);
    friend Achizitie operator+=(Achizitie &aq, DezinfectantBacterii &d);
    friend Achizitie operator+=(Achizitie &aq, Dezinfectant &d);
    friend bool operator <(Achizitie &aq1, Achizitie &aq2);
    friend bool operator ==(Achizitie &aq1, Achizitie &aq2);

    const Data &getData() const;

    const string &getClient() const;

    const vector<shared_ptr<Masca>> &getMasti() const;

    const vector<shared_ptr<Dezinfectant>> &getDezinfectante() const;

    int getTotal() const;
};

Achizitie operator+=(Achizitie &aq, const MascaPolicarbonat &m) {
    aq.total+=20;
    aq.masti.push_back(make_shared<Masca>(m));
    return aq;
}

Achizitie operator+=(Achizitie &aq, const MascaChirurgicala &m) {
    string tip=m.getTipProtectie();
    if(tip=="ffp1"){
        aq.total+=5;
    }
    if(tip=="ffp2"){
        aq.total+=10;
    }
    if(tip=="ffp3"){
        aq.total+=15;
    }
    aq.masti.push_back(make_shared<Masca>(m));
    return aq;
}

Achizitie operator+=(Achizitie &aq, DezinfectantVirusi &d) {
    double ef=d.eficienta();
    if(ef*100<90){
        aq.total+=10;
    }
    if(ef*100>=90 and ef*100<95){
        aq.total+=20;
    }
    if(ef*100>=95 and ef*100<97.5){
        aq.total+=30;
    }
    if(ef*100>=97.5 and ef*100<99){
        aq.total+=40;
    }
    if(ef*100>=99 and ef*100<99.99){
        aq.total+=50;
    }
    aq.dezinfectante.push_back(make_shared<Dezinfectant>(d));
    return aq;

}

Achizitie operator+=(Achizitie &aq, DezinfectantFungi &d) {
    double ef=d.eficienta();
    if(ef*100<90){
        aq.total+=10;
    }
    if(ef*100>=90 and ef*100<95){
        aq.total+=20;
    }
    if(ef*100>=95 and ef*100<97.5){
        aq.total+=30;
    }
    if(ef*100>=97.5 and ef*100<99){
        aq.total+=40;
    }
    if(ef*100>=99 and ef*100<99.99){
        aq.total+=50;
    }
    aq.dezinfectante.push_back(make_shared<Dezinfectant>(d));
    return aq;

}

Achizitie operator+=(Achizitie &aq, DezinfectantBacterii &d) {
    double ef=d.eficienta();
    if(ef*100<90){
        aq.total+=10;
    }
    if(ef*100>=90 and ef*100<95){
        aq.total+=20;
    }
    if(ef*100>=95 and ef*100<97.5){
        aq.total+=30;
    }
    if(ef*100>=97.5 and ef*100<99){
        aq.total+=40;
    }
    if(ef*100>=99 and ef*100<99.99){
        aq.total+=50;
    }
    aq.dezinfectante.push_back(make_shared<Dezinfectant>(d));
    return aq;

}

Achizitie operator+=(Achizitie &aq, Dezinfectant &d) {
    double ef=d.eficienta();
    if(ef*100<90){
        aq.total+=10;
    }
    if(ef*100>=90 and ef*100<95){
        aq.total+=20;
    }
    if(ef*100>=95 and ef*100<97.5){
        aq.total+=30;
    }
    if(ef*100>=97.5 and ef*100<99){
        aq.total+=40;
    }
    if(ef*100>=99 and ef*100<99.99){
        aq.total+=50;
    }
    aq.dezinfectante.push_back(make_shared<Dezinfectant>(d));
    return aq;
}

bool operator<(Achizitie &aq1, Achizitie &aq2) {
    return aq1.total<aq2.total;
}

bool operator==(Achizitie &aq1, Achizitie &aq2) {
    return aq1.total==aq2.total;
}

const Data &Achizitie::getData() const {
    return data;
}

const string &Achizitie::getClient() const {
    return client;
}

const vector<shared_ptr<Masca>> &Achizitie::getMasti() const {
    return masti;
}

const vector<shared_ptr<Dezinfectant>> &Achizitie::getDezinfectante() const {
    return dezinfectante;
}

int Achizitie::getTotal() const {
    return total;
}

class BaseMenu {
public:
    virtual void listOptions() = 0;

    virtual int chooseOption(int first, int last) = 0;

    virtual void mainLoop() = 0;


};

class Menu : public BaseMenu {
private:
    Menu() = default;
    vector<shared_ptr<Dezinfectant>> dezinfectante;
    vector<shared_ptr<Masca>> masti;
    vector<Achizitie> achizitii;

    static Menu *menu;

public:

    static Menu *getMenu() {
        if (menu != nullptr) {
            return menu;
        }
        menu = new Menu();
        return menu;
    }


    void listOptions() override {
        cout << "1. Adauga un nou dezinfectant in stoc"<<"\n";
        cout << "2. Adauga o noua masca in stoc"<<"\n";
        cout << "3. Adauga o noua achizitie"<<"\n";
        cout << "4. Afiseaza dezinfectantul cel mai eficient"<<"\n";
        cout << "5. Calculeaza venitul dintr-o anumita luna"<<"\n";
        cout << "6. Calculeaza venitul obtinut din mastile chirurgicale cu model."<<"\n";
        cout << "7. Modifica reteta unui dezinfectant, modificand unul sau mai multe ingrediente, lucru ce conduce si la o modificarea a numarului de specii de organisme ce vor fi ucise si a suprafețelor pe care poate fi aplicat."<<"\n";
        cout << "8. Afiseaza cel mai fidel client (clientii NU au nume unic)"<<"\n";
        cout << "9. Afiseaza ziua cu cele mai slabe venituri, de la deschidere pana in prezent."<<"\n";
        cout << "10. Calculeaza TVA-ul (19% din venituri) care trebuie returnat la ANAF pentru un anumit an."<<"\n";
        cout << "11. Exit."<<"\n";
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

    void option1() {
        cout<<"Introduceti:\n1.Bacterii\n2.Fungi\n3.Virusi\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip !=2 and tip!=3){
            cout<<"Tip invalid. Reintroduceti tipul.\n";
            cin>>tip;
        }
        if(tip==1){
            DezinfectantBacterii d;
            cin>>d;
            dezinfectante.push_back(make_shared<DezinfectantBacterii>(d));
        }

        if(tip==2){
            DezinfectantFungi d;
            cin>>d;
            dezinfectante.push_back(make_shared<DezinfectantFungi>(d));
        }

        if(tip==3){
            DezinfectantVirusi d;
            cin>>d;
            dezinfectante.push_back(make_shared<DezinfectantVirusi>(d));
        }
    }

    void option2() {
        cout<<"Introduceti:\n1.Masca Chirurgicala\n2.Masca Policarbonat\n";
        int tip;
        cin>>tip;
        while(tip!=1 and tip !=2){
            cout<<"Tip invalid. Reintroduceti tipul.\n";
            cin>>tip;
        }
        if(tip==1){
            MascaChirurgicala m;
            cin>>m;
            masti.push_back(make_shared<Masca>(m));

        }

        if(tip==2){
            MascaPolicarbonat m;
            cin>>m;
            masti.push_back(make_shared<Masca>(m));
        }

    }

    void option3() {
        Achizitie a;
        cin>>a;
        achizitii.push_back(a);
    }

    void option4() {
        double ef_max=-1;
        Dezinfectant dmax;
        for(auto & i : dezinfectante){
            auto *asF= dynamic_cast<DezinfectantFungi *>(i.get());
            auto *asB= dynamic_cast<DezinfectantBacterii *>(i.get());
            auto *asV= dynamic_cast<DezinfectantVirusi *>(i.get());

            if(asF){
                if(asF->eficienta()>ef_max){
                    ef_max=asF->eficienta();
                    dmax= *i;
                }
            }
            if(asB){
                if(asB->eficienta()>ef_max){
                    ef_max=asB->eficienta();
                    dmax= *i;
                }
            }
            if(asV){
                if(asV->eficienta()>ef_max){
                    ef_max=asV->eficienta();
                    dmax= *i;
                }
            }

        }
        cout<<dmax;

    }

    void option5(){
        int venit_lunar=0;
        cout<<"Introduceti luna si anul:\n";
        int luna,an;
        cin>>luna>>an;
        for(int i=0;i<achizitii.size();i++){
            if(achizitii[i].getData().luna==luna && achizitii[i].getData().an==an){
                venit_lunar+=achizitii[i].getTotal();
            }
        }
        cout<<"Venitul lunii: "<<venit_lunar<<"\n";

    }

    void option6(){
        int venit_logo=0;
        for(int i=0;i<masti.size();i++){
            auto *asChir = dynamic_cast<MascaChirurgicala *>(masti[i].get());
            auto *asPoli = dynamic_cast<MascaPolicarbonat *>(masti[i].get());

            if(asChir){
                if(asChir->getTipProtectie()=="ffp1" and asChir->getLogo()!="none")venit_logo+=5;
                if(asChir->getTipProtectie()=="ffp2" and asChir->getLogo()!="none")venit_logo+=10;
                if(asChir->getTipProtectie()=="ffp3" and asChir->getLogo()!="none")venit_logo+=15;
            }
        }
        cout<<"Venitul total pe mastile chirurgicale cu logo este "<<venit_logo<<"\n";
    }

    void option7(){
        cout<<"Introdu id.ul dezinfectantului pe care doriti sa-l modificati: ";
        int id;
        cin>>id;
        while(id>=dezinfectante.size()){
            cout<<"Id intrdus gresit. Reintroduceti id.ul.\n";
            cin>>id;
        }
        Dezinfectant *d;
        d=dynamic_cast<Dezinfectant *>(dezinfectante[id].get());
        cout<<"Numar specii actualizate: ";
        int nr_specii;
        cin>>nr_specii;
        d->setNumarSpecii(nr_specii);

        cout<<"Ingrediente actualizate:\n";
        vector<string> ingr_act;
        cin>>ingr_act;
        d->setIngrediente(ingr_act);

        cout<<"Suprafete actualizate:\n";
        vector<string> supr_act;
        cin>>supr_act;
        d->setSuprafete(supr_act);
    }

    void option8(){

    }
    void option9(){

    }
    void option10(){

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
            } else if (option == 5) {
                option5();
            } else if (option == 6) {
                option6();
            }else if (option == 7) {
                option7();
            }else if (option == 8) {
                option8();
            }else if (option == 9) {
                option9();
            }else if (option == 10) {
                option10();
            }else if(option == 11){
                break;
            }
        }
        cout << '\n' << "---------------------------------" << '\n' << "Programul s-a incheiat cu success";
    }



};

Menu *Menu::menu = nullptr;


int main(){

    // Demo-ul din cerinta

//    MascaChirurgicala mc1, mc2("ffp2", "verde brotacel", 55), mc3(mc1), mc4, mc5;
//    mc4 = mc2;
//
//
//
//    std::cin >> mc5;
//    std::cout << mc1 << mc2;
//    MascaPolicarbonat *mp1 = new MascaPolicarbonat(), *mp2 = new MascaPolicarbonat();
//
//    MascaPolicarbonat *mp3 = new MascaPolicarbonat("elastic");
//    cin>> *mp1 >> *mp2;
//    cout << *mp3;
//
//    Dezinfectant *d1 = new DezinfectantBacterii(100000000,
//                                                        {"sulfati non-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"},
//                                                {"lemn", "sticla", "ceramica", "marmura"});
//    Dezinfectant *d2 = new DezinfectantVirusi(50000000,
//                                                        {"Alkil Dimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"},
//                                                {"lemn", "sticla", "ceramica", "marmura"});
//    Dezinfectant *d3 = new DezinfectantFungi(1400000,
//                                                     {"Alkil EtilBenzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"},
//                                             {"sticla", "plastic"});
//    std::cout << d1->eficienta() << " " << d2->eficienta() << " " << d3->eficienta() << "\n";
//
//    Achizitie *a1 = new Achizitie(Data(26, 5, 2020), "PlushBio SRL");
//    *a1 += *mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
//    *a1 += mc1; //se adauga masca chirugicala mc1 in lista
//    *a1 += *d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
//    Achizitie *a2 = new Achizitie(Data(25, 5, 2020), "Gucci");
//    *a2 += *d1;
//    *a2 += *d2;
//    *a2 += *d2;
//    DezinfectantBacterii d7;
//    Achizitie a7;
//    a7+=d7;
//    Achizitie a3, a4(*a1);
//    a3 = *a2;
//    if (*a1 < *a2) {
//        std::cout << a1->getClient() << " are valoarea facturii mai mica.\n";
//    } else if (*a1 == *a2) {
//        std::cout << a1->getClient() << " si " << a2->getClient()<< " au aceasi valoare afacturii.\n";
//    }
//    else {
//        std::cout << a2->getClient() << " are valoarea facturii mai mica.\n";
//    }


    Menu *meniu = Menu::getMenu();
    meniu->mainLoop();
    return 0;


}


