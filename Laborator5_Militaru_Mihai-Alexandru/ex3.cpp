#include <iostream>
#include <vector>
#include <string>
#include<set>

using namespace std;

template<typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    is>>n;
    is.get();
    for(int i=0;i<n;i++){
        T object;
        is>>object;
        v.push_back(object);
    }
    return is;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> &v){
    for(int i=0;i<v.size();i++){
        os<<v[i]<<" ";
    }
    return os;
}


class IoBase {
private:
public:
    virtual istream& read(istream& is) {
        return is;
    }
    virtual ostream& write(ostream& os) const {
        return os;
    }

    friend ostream &operator<<(ostream &os, const IoBase &base) {
        return base.write(os);
    }
    friend istream &operator>>(istream &is, IoBase &base) {
        return base.read(is);
    }
};


struct Nota {
    int value;
    string subject;
};

class PersoanaEvaluata:public IoBase{
protected:
    vector<Nota> note;
public:
    PersoanaEvaluata()= default;
    PersoanaEvaluata(const vector<Nota> &note) : note(note) {}
    double mean() {
        double sum = 0;
        for(auto nota : note) {
            sum += nota.value;
        }
        return sum / note.size();
    }
    void showGradeSheet();

    void gradesGroupedBySubject();

    ostream &write(ostream &os) const override{
        for(auto & i : note){
            os<<"( "<<i.value<<" "<<i.subject<<") ";
        }
        return os;
    }

    istream &read(istream &is) override{
        int nr_note;
        is>>nr_note;
        for(int i=0;i<nr_note;i++){
            Nota grade;
            is>>grade.value>>grade.subject;
            note.push_back(grade);
        }
        return is;

    }


};

void PersoanaEvaluata::showGradeSheet() {
    for(auto & i : note){
        cout<<"subject: "<<i.subject<<", value: "<<i.value<<"\n";
    }
}

void PersoanaEvaluata::gradesGroupedBySubject() {
    set <string> sub;
    for(auto i : note){
        sub.emplace(i.subject);
    }

    for(auto & i : sub){
        cout<<i<<": ";
        for(auto & j : note){
            if(j.subject==i){
                cout<<j.value<<" ";
            }
        }
        cout<<"\n";
    }

}



class Pupil:public PersoanaEvaluata{
private:
    string cycle;
public:
    Pupil()= default;
    Pupil(const vector<Nota> &note, const string &cycle) : PersoanaEvaluata(note), cycle(cycle) {}

    istream &read(istream &is) override {
        int nr_note;
        cin >> nr_note;
        for (int i = 0; i < nr_note; i++) {
            Nota grade;
            cin >> grade.value >> grade.subject;
            cin.get();
            note.push_back(grade);
        }
        getline(cin, cycle);
    }


    ostream &write(ostream &os) const override{
        cout<<cycle<<"\n";
        for(auto & i : note){
            cout<<"( "<<i.value<<" "<<i.subject<<") ";
        }
    }
};


class Student:public PersoanaEvaluata{
private:
    string facultate;
public:
    Student()= default;
    Student(const vector<Nota> &note, const string &facultate) : PersoanaEvaluata(note), facultate(facultate) {}

    istream &read(istream &is) override {
        int nr_note;
        cin >> nr_note;
        for (int i = 0; i < nr_note; i++) {
            Nota grade;
            cin >> grade.value >> grade.subject;
            cin.get();
            note.push_back(grade);
        }
        getline(cin, facultate);
    }

    ostream &write(ostream &os) const override{
        cout<<facultate<<"\n";
        for(auto & i : note){
            cout<<"( "<<i.value<<" "<<i.subject<<") ";
        }
    }

};


class Coursetaker:public PersoanaEvaluata{
private:
    string curs;
public:
    Coursetaker()=default;
    Coursetaker(const vector<Nota> &note, const string &curs) : PersoanaEvaluata(note), curs(curs) {}


    istream &read(istream &is) override {
        int nr_note;
        cin >> nr_note;
        for (int i = 0; i < nr_note; i++) {
            Nota grade;
            cin >> grade.value >> grade.subject;
            cin.get();
            note.push_back(grade);
        }
        getline(cin, curs);
    }

    ostream &write(ostream &os) const override{
        cout<<curs<<"\n";
        for(auto & i : note){
            cout<<"( "<<i.value<<" "<<i.subject<<") ";
        }
    }
};

int main(){
    Coursetaker cursant;
    cin>>cursant;
    cout<<cursant;

//    vector <PersoanaEvaluata> persoane;
//    cin>>persoane;
//    cout<<persoane;

//    vector <string> personaje;
//    cin>>personaje;
//    cout<<personaje;
}


