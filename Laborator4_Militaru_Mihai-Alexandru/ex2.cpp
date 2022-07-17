//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//int nr_produse;
//
//
//class ConstructionProduct{
//private:
//    string nume;
//    int cantitate;
//    string unitate_masura;
//    float pret;
//
//public:
//    ConstructionProduct():cantitate(0), pret(0){};
//
//    ConstructionProduct(const string &nume, int cantitate, const string &unitateMasura, float pret) : nume(nume),
//                                                                                                    cantitate(
//                                                                                                            cantitate),
//                                                                                                    unitate_masura(
//                                                                                                            unitateMasura),
//                                                                                                    pret(pret) {}
//
//
//    const string &getNume() const;
//
//    int getCantitate() const;
//
//    const string &getUnitateMasura() const;
//
//    float getPret() const;
//
//
//    friend ostream &operator<<(ostream &os, const ConstructionProduct &product);
//
//    friend istream &operator>>(istream &is, ConstructionProduct &product);
//
//    friend void  operator++(ConstructionProduct &produs);
//
//    ConstructionProduct operator++(int);
//
//    ConstructionProduct operator+=(int);
//};
//
//
//ostream &operator<<(ostream &os, const ConstructionProduct &product) {
//    os << "Nume: " << product.nume <<'\n'<< " Cantitate: " << product.cantitate <<'\n'<< " Unitate_masura: "
//       << product.unitate_masura <<'\n'<< " Pret/unitate: " << product.pret<<'\n';
//    return os;
//}
//
//istream &operator>>(istream &is, ConstructionProduct &product){
//    cout<<"Nume: ";
//    getline(is, product.nume);
//    cout<<"Cantitate: ";
//    is>>product.cantitate;
//    is.get();
//    cout<<"Unitate de masura: ";
//    getline(is, product.unitate_masura);
//    cout<<"Pret: ";
//    is>>product.pret;
//    is.get();
//}
//
//const string &ConstructionProduct::getNume() const {
//    return nume;
//}
//
//int ConstructionProduct::getCantitate() const {
//    return cantitate;
//}
//
//const string &ConstructionProduct::getUnitateMasura() const {
//    return unitate_masura;
//}
//
//float ConstructionProduct::getPret() const {
//    return pret;
//}
//
//void operator++(ConstructionProduct &produs) {
//    produs.cantitate++;
//}
//
//ConstructionProduct ConstructionProduct:: operator++(int x) {
//    ConstructionProduct cpy= *this;
//    cantitate++;
//    return *this;
//}
//
//ConstructionProduct ConstructionProduct:: operator+=(int x) {
//    ConstructionProduct cpy= *this;
//    cantitate+=x;
//    return *this;
//}
//
//void afisare_chitanta(const vector < ConstructionProduct >& produse){
//    float suma_totala=0;
//    cout<<"Chitanta renovare:\n";
//    for(int i=0;i<nr_produse;i++){
//        cout<<i+1<<' '<<produse[i].getNume()<<" ("<<produse[i].getUnitateMasura()<<") "<<"x "<<produse[i].getCantitate()<<'\n';
//        cout<<produse[i].getCantitate()<<" x "<<produse[i].getPret()<<" = "<<produse[i].getCantitate() * produse[i].getPret()<<"\n";
//        suma_totala+=produse[i].getCantitate() * produse[i].getPret();
//    }
//    cout<<"Total: "<<suma_totala<<"\n";
//}
//
//
//int main() {
//
//    ConstructionProduct produs;
//    cin>>produs;
//    produs+=5;
//    cout<<produs;
//
//    return 0;
//}
