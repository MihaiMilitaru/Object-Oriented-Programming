#include<iostream>#include<functional>#include<map>#include<vector>#include<algorithm>#include"util/IoBase.h"using namespace std;class Building : public IoBase {private:    string color, owner;    unsigned height;public:    const string &get_color() const {        return color;    }    const string &get_owner() const {        return owner;    }    unsigned get_height() const {        return height;    }    Building(string _color, string _owner, unsigned _height) : color(move(_color)),owner(move(_owner)), height(_height) {}    Building() : color(), owner(), height(0) {}    istream &read(istream &is) override {        IoBase::read(is);        is >> color >> owner >> height;        return is;    }    ostream &write(ostream &os) const override {        IoBase::write(os);        os << "Color : " << color << ", Owner: " << owner << " Height: " << height;        return os;    }    bool operator<(const Building &other) const {        return height < other.height;    }};template<class X>bool compare(const X &a, const X &b) {    return a < b;}class BaseMenu {public:    virtual void listOptions() = 0;    virtual int chooseOption(int first, int last) = 0;    virtual void mainLoop() = 0;};template<class TipDate>class CrudMenu : public BaseMenu {private:    map<string, function<void(const vector<TipDate> &)> > options;    vector<TipDate> buildings;public:    CrudMenu(vector<TipDate> _buildings, map<string, function<void(const vector<TipDate> &)>> _options): buildings(move(_buildings)), options(move(_options)) {}    void listOptions() override {        unsigned i = 1;        for (const auto &opt: options) {            cout << i << " " << opt.first << endl;            i++;        }        cout << i << " Iesire" << endl;    }    int chooseOption(int first, int last) override {        int option = -1;        while (option < first || option > last) {            cout << '\n';            cout << "Pentru a rula comanda, alegeți un număr între "<< first << " și " << last << '\n';            listOptions();            cout << "Alegere:";            cin >> option;        }        return option;    }    void mainLoop() override {        while (true) {            int option = chooseOption(1, (int) options.size() + 1);            if (option == options.size() + 1) {                break;            }            auto it = options.begin();            for (int i = 1; i < option; i++) {                it++;            }            auto functie = it->second;            functie(buildings);        }        cout << '\n'                  << "---------------------------------"                  << '\n'                  << "Programul s-a încheiat cu success";    }};void sorteaza(const vector<Building> &p) {    vector<Building> cpy = p;    sort(cpy.begin(), cpy.end(), compare<Building>);    for (const auto &x: cpy) {        cout << x << endl;    }}/*void afiseaza(const vector<Building> &v) {    for (const auto &building: v) {        cout << building << '\n';    }}*/int main() {    auto afisare = [](const vector<Building> &v) -> void {        for (auto &building: v) {            cout << building << '\n';        }    };    CrudMenu<Building> menu(            { // vectorul de cladiri (culoare, proprietar, inaltime)                    Building("red", "Gabriel", 7),                    Building("blue", "Penelope", 4),            },            /*{  // map-ul care contine etichetele optiunilor si functiile rulata                    {"Afiseaza", afiseaza<Building>},                    {"Sorteaza", sorteaza < Building > }            }*/            {  // map-ul care contine etichetele optiunilor si functiile rulata                    {"Afiseaza", afisare},                    {"Sorteaza", sorteaza}            }    );    menu.mainLoop();    return 0;}// varianat generalizata/*template<class TipDate>void sorteaza(const vector<TipDate> &p) {    vector<TipDate> cpy = p;    sort(cpy.begin(), cpy.end(), compare<TipDate>);    for (const auto &x: cpy) {        cout << x << endl;    }}template<class TipDate>void afiseaza(const vector<TipDate> &v) {    for (const auto &building: v) {        cout << building << '\n';    }}int main() {    CrudMenu<Building> menu(            { // vectorul de cladiri (culoare, proprietar, inaltime)                    Building("red", "Gabriel", 7),                    Building("blue", "Penelope", 4),            },            {  // map-ul care contine etichetele optiunilor si functiile rulata                    {"Afiseaza", afiseaza<Building>},                    {"Sorteaza", sorteaza<Building>}            }    );    menu.mainLoop();    return 0;}*/