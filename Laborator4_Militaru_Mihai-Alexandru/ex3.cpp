//#include <iostream>
//#include <string>
//#include <utility>
//#include <vector>
//#include <cmath>
//
//using namespace std;
//
//class InterestPoint{
//private:
//    int nr_vizitatori;
//    int x;
//    int y;
//
//public:
//    InterestPoint(){
//        nr_vizitatori=0;
//    }
//    InterestPoint(int nr_vizitatori, int x, int y){
//        this->nr_vizitatori=nr_vizitatori;
//        this->x=x;
//        this->y=y;
//    }
//
//
//    friend ostream &operator<<(ostream &os, const InterestPoint &punct);
//
//    friend istream &operator>>(istream &is, InterestPoint &punct);
//
//    int getNrVizitatori() const;
//
//    int getX() const;
//
//    int getY() const;
//
//    friend float distance_2points(InterestPoint, InterestPoint);
//};
//
//ostream &operator<<(ostream &os, const InterestPoint &punct){
//    os<<punct.nr_vizitatori<<" "<<punct.x<<" "<<punct.y;
//    return os;
//}
//
//istream &operator>>(istream &is, InterestPoint &punct){
//   is>>punct.nr_vizitatori>>punct.x>>punct.y;
//}
//
//int InterestPoint::getNrVizitatori() const {
//    return nr_vizitatori;
//}
//
//int InterestPoint::getX() const {
//    return x;
//}
//
//int InterestPoint::getY() const {
//    return y;
//}
//
//
//class BikeTrail{
//private:
//    string nume_pista;
//    string oras;
//    vector<InterestPoint> puncte;
//
//public:
//    BikeTrail()= default;
//
//    BikeTrail(string numePista, string oras, const vector<InterestPoint> &puncte) : nume_pista(std::move(numePista)),
//                                                                                                  oras(std::move(oras)),
//                                                                                                  puncte(puncte) {}
//
//    friend ostream &operator<<(ostream &os, const BikeTrail &traseu);
//
//    friend istream &operator>>(istream &is, BikeTrail &traseu);
//
//    const string &getNumePista() const;
//
//    const string &getOras() const;
//
//    const vector<InterestPoint> &getPuncte() const;
//};
//
//
//ostream &operator<<(ostream &os, const BikeTrail &traseu){
//    os<<traseu.nume_pista<<"\n";
//    os<<traseu.oras<<"\n";
//    for(auto i : traseu.puncte){
//        os<<i<<"\n";
//    }
//    return os;
//}
//
//istream &operator>>(istream &is, BikeTrail &traseu){
//    int nr_puncte;
//    InterestPoint punct;
//    getline(is, traseu.nume_pista);
//    getline(is, traseu.oras);
//    is>>nr_puncte;
//    is.get();
//    for(int i=0;i<nr_puncte;i++){
//        is>>punct;
//        traseu.puncte.push_back(punct);
//        is.get();
//    }
//}
//
//const string &BikeTrail::getNumePista() const {
//    return nume_pista;
//}
//
//const string &BikeTrail::getOras() const {
//    return oras;
//}
//
//const vector<InterestPoint> &BikeTrail::getPuncte() const {
//    return puncte;
//}
//
//
//
//
//// Functiile necesare rezolvarii cerintei d)
//
//
//// Functia care calculeaza distanta dintre 2 puncte.
//
//float distance_2points(InterestPoint p1, InterestPoint p2){
//    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
//}
//
//
//// Functia care calculeaza distanta maxima intr-un triunghi.
//
//float distanta_maxima_3puncte(InterestPoint punct1, InterestPoint punct2, InterestPoint punct3){
//    float distance12= distance_2points(punct1, punct2);
//    float distance13= distance_2points(punct1, punct3);
//    float distance23= distance_2points(punct2, punct3);
//
//    return max(distance12+distance13, max(distance13+distance23, distance12+distance23));
//}
//
//float distanta_minima_3puncte(InterestPoint punct1, InterestPoint punct2, InterestPoint punct3){
//    float distance12= distance_2points(punct1, punct2);
//    float distance13= distance_2points(punct1, punct3);
//    float distance23= distance_2points(punct2, punct3);
//
//    return min(distance12+distance13, min(distance13+distance23, distance12+distance23));
//
//}
//
//void traseu_maxim(BikeTrail &traseu){
//    float lmax=0;
//    int index1, index2, index3=0;
//    int n=traseu.getPuncte().size();
//
//    for(int i=0;i<n-2;i++){
//        for(int j=i+1;j<n-1;j++){
//            for(int l=j+1;l<n;l++){
//                InterestPoint point1=traseu.getPuncte()[i];
//                InterestPoint point2=traseu.getPuncte()[j];
//                InterestPoint point3=traseu.getPuncte()[l];
//
//
//                float current_distance= distanta_maxima_3puncte(point1, point2, point3);
//                if(current_distance > lmax){
//                    lmax=current_distance;
//                    index1=i;
//                    index2=j;
//                    index3=l;
//                }
//            }
//        }
//    }
//    cout<<"Cele 3 puncte sunt:\n";
//    cout<<traseu.getPuncte()[index1]<<"\n"<<traseu.getPuncte()[index2]<<"\n"<<traseu.getPuncte()[index3]<<"\n";
//    cout<<"Lungimea maxima a traseului este: "<<lmax<<"\n";
//
//}
//
//
//void traseu_vizitatori_maxim(BikeTrail &traseu){
//    int index1, index2, index3=0;
//    int sum_visitors=0;
//    int smax=0;
//    int dmin;
//    int n=traseu.getPuncte().size();
//    for(int i=0;i<n-2;i++){
//        for(int j=i+1;j<n-1;j++){
//            for(int l=j+1;l<n;l++){
//                InterestPoint point1=traseu.getPuncte()[i];
//                InterestPoint point2=traseu.getPuncte()[j];
//                InterestPoint point3=traseu.getPuncte()[l];
//
//                sum_visitors=point1.getNrVizitatori()+point2.getNrVizitatori()+point3.getNrVizitatori();
//                if(sum_visitors>smax){
//                    smax=sum_visitors;
//                    index1=i;
//                    index2=j;
//                    index3=l;
//                    dmin= distanta_minima_3puncte(point1,point2,point3);
//
//                }
//            }
//        }
//    }
//
//    cout<<"Cele mai populare 3 puncte sunt "<<traseu.getPuncte()[index1]<<" "<<traseu.getPuncte()[index2]<<" "<<traseu.getPuncte()[index3]<<"\n";
//    cout<<"Distanta minima intre cele 3 puncte de mai sus este "<<dmin<<"\n";
//
//}
//
//
//int main(){
//    BikeTrail traseu;
//    cin>>traseu;
//    traseu_maxim(traseu);
//    traseu_vizitatori_maxim(traseu);
//
//    return 0;
//
//}
