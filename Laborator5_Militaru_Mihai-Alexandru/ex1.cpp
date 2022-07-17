//#include <iostream>
//#include <vector>
//#include <string>
//#include<set>
//
//using namespace std;
//
//struct Nota {
//    int value;
//    string subject;
//};
//
//
//class PersoanaEvaluata {
//protected:
//    vector<Nota> note;
//public:
//    PersoanaEvaluata();
//    PersoanaEvaluata(const vector<Nota> &note) : note(note) {}
//    double mean() {
//        double sum = 0;
//        for(auto nota : note) {
//            sum += nota.value;
//        }
//        return sum / note.size();
//    }
//    void showGradeSheet();
//
//    void gradesGroupedBySubject();
//};
//
//void PersoanaEvaluata::showGradeSheet() {
//    for(auto & i : note){
//        cout<<"subject: "<<i.subject<<", value: "<<i.value<<"\n";
//    }
//}
//
//void PersoanaEvaluata::gradesGroupedBySubject() {
//    set <string> sub;
//    for(auto i : note){
//        sub.emplace(i.subject);
//    }
//
//    for(auto & i : sub){
//        cout<<i<<": ";
//        for(auto & j : note){
//            if(j.subject==i){
//                cout<<j.value<<" ";
//            }
//        }
//        cout<<"\n";
//    }
//
//}
//
//
//class Pupil:public PersoanaEvaluata{
//private:
//    string cycle;
//public:
//    Pupil();
//    Pupil(const vector<Nota> &note, const string &cycle) : PersoanaEvaluata(note), cycle(cycle) {}
//};
//
//class Student:public PersoanaEvaluata{
//private:
//    string facultate;
//public:
//    Student();
//    Student(const vector<Nota> &note, const string &facultate) : PersoanaEvaluata(note), facultate(facultate) {}
//};
//
//
//class Coursetaker:public PersoanaEvaluata{
//private:
//    string curs;
//public:
//    Coursetaker();
//    Coursetaker(const vector<Nota> &note, const string &curs) : PersoanaEvaluata(note), curs(curs) {}
//};
//
//
//int main() {
//
//    Pupil p(
//
//            {
//                    {4, "Maths"}, {5,"English"}, {10,"Informatics"}, {9, "Informatics"}
//            },
//            "Gimnazial"
//            );
//
//    p.gradesGroupedBySubject();
//    p.showGradeSheet();
//    return 0;
//
//}
