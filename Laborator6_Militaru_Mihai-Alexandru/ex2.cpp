#include <bits/stdc++.h>
#include <memory>
#include "IoBase.h"

class Participant:public IoBase{
protected:
    string CNP;
    string nume;

public:
    Participant()=default;

    Participant(const string &cnp, const string &nume) : CNP(cnp), nume(nume) {}

    istream &read(istream &is) override {
        IoBase::read(is);
        cout<<"Nume: ";
        getline(cin, nume);
        cout<<"CNP: ";
        cin>>CNP;
        return is;
    }

    ostream &write(ostream &os) const override {
        IoBase::write(os);
        cout<<"Nume: "<<nume<<"\n";
        cout<<"CNP: "<<CNP<<"\n";
        return os;
    }
};


class Elev:public Participant{
private:
    string limbaj;

public:
    Elev()=default;
    Elev(string CNP, string nume, string limbaj){
        this->CNP=CNP;
        this->nume=nume;
        this->limbaj=limbaj;
    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout<<"Limbaj: ";
        cin>>limbaj;
        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        cout<<"Limbaj: ";
        cout<<limbaj<<"\n";
        return os;
    }

};

class Student:public Participant{
private:
    vector<string> limbaje;
    int an_studii;

public:
    Student()=default;
    Student(string CNP, string nume, vector<string> limbaje, int an_studii){
        this->CNP=CNP;
        this->nume=nume;
        this->limbaje=limbaje;
        this->an_studii=an_studii;
    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout<<"Numar limbaje: ";
        int nr_lb;
        cin>>nr_lb;
        limbaje.resize(nr_lb);
        cout<<"Introduceti limbajele: ";
        for(int i=0;i<nr_lb;i++){
            cin>>limbaje[i];
        }
        cout<<"\n"<<"An studii: ";
        cin>>an_studii;
        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        cout<<"Limbaje: ";
        for(int i=0;i<limbaje.size();i++){
            cout<<limbaje[i]<<" ";
        }
        cout<<"\n"<<"An studii: ";
        cout<<an_studii;
        return os;
    }

};


class ProfessionalProgrammer:public Participant{
private:
    vector<string> limbaje;
    string firma;

public:
    ProfessionalProgrammer()=default;
    ProfessionalProgrammer(string CNP, string nume, vector<string> limbaje, string firma){
        this->CNP=CNP;
        this->nume=nume;
        this->limbaje=limbaje;
        this->firma=firma;
    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout<<"Numar limbaje: ";
        int nr_lb;
        cin>>nr_lb;
        limbaje.resize(nr_lb);
        cout<<"Introduceti limbajele: ";
        for(int i=0;i<nr_lb;i++){
            cin>>limbaje[i];
        }
        cout<<"Firma: ";
        cin>>firma;
        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        cout<<"Limbaje: ";
        for(int i=0;i<limbaje.size();i++){
            cout<<limbaje[i]<<" ";
        }
        cout<<"\n";
        cout<<"Firma: "<<firma<<"\n";
        return os;
    }
};

class Echipa{
private:
    int max_members;
    string nume;
    string domeniu;
    ProfessionalProgrammer leader;
    vector<shared_ptr<Participant> >team_members;

public:
    Echipa(){
        max_members=0;
    }

    Echipa(int maxMembers, const string &nume, const string &domeniu, const ProfessionalProgrammer &leader,
           const vector<shared_ptr<Participant>> &teamMembers) : max_members(maxMembers), nume(nume), domeniu(domeniu),
                                                                 leader(leader), team_members(teamMembers) {}

    void eliminaMembru(int);
    void adaugaMembru(shared_ptr<Participant>&);
    void inregistreazaNouMembru();
    void modificaMentor(ProfessionalProgrammer&);
    int locuriLibere();
    void afisareEchipa();


};

void Echipa::eliminaMembru(int index) {
    int members=team_members.size();
    if(index<0 or index>=members){
        cout<<"Cannot find current index to remove participant.\n";
    }else{
        vector<shared_ptr<Participant> >vect;
        for(int i=0;i<members;i++){
            if(i==index){
                continue;
            }else{
                vect.push_back(team_members[i]);
            }
        }
        team_members=vect;
    }

}

void Echipa::adaugaMembru(shared_ptr<Participant> &p) {
    if(team_members.size()==max_members){
        cout<<"Team at max capacity. Cannot add member.\n";
    }else{
        team_members.push_back(p);
    }
}

void Echipa::inregistreazaNouMembru() {
    cout<<"Select member type(student, elev, pro_programator): ";
    string type;
    shared_ptr<Participant> p;
    cin>>type;
    if(type=="student"){
        Student s;
        cin>>s;
        team_members.push_back(make_shared<Student>(s));
    }else if(type=="elev"){
        Elev e;
        cin>>e;
        team_members.push_back(make_shared<Elev>(e));
    }else if(type=="pro_programator"){
        ProfessionalProgrammer p;
        cin>>p;
        team_members.push_back(make_shared<ProfessionalProgrammer>(p));
    }else{
        cout<<"Invalid category.\n";
    }

}

void Echipa::modificaMentor(ProfessionalProgrammer &p) {
    leader=p;
}

int Echipa::locuriLibere() {
    return max_members-team_members.size();
}

void Echipa::afisareEchipa() {
    cout<<"The team "<<nume<<" has the domain "<<domeniu<<" and the leader is:\n";
    cout<<leader;
    cout<<"List of members:\n";
    for(int i=0;i<team_members.size();i++){
        cout<<*team_members[i];
    }

}

int main(){
//    Student e;
//    cin>>e;
//    cout<<e;

ProfessionalProgrammer p;
cin>>p;
vector<shared_ptr<Participant> > allKindsOfParticipants ={
        make_shared<Elev>(Elev("cnp123", "Mihai", "c++")),
        make_shared<Student>(Student("cnp124", "Alex", {"c++", "assembly", "python"}, 2)),
        make_shared<ProfessionalProgrammer>(ProfessionalProgrammer("cnp125", "Bogdan", {"c++", "react", "js"}, "Bitdifender"))
};
        Echipa team(30, "Pyhtoneers", "Data Science",p, allKindsOfParticipants);
        team.afisareEchipa();
}