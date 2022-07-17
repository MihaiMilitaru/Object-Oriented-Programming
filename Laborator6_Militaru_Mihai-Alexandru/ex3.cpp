#include "IoBase.h"
#include <bits/stdc++.h>
#include <utility>

using namespace std;

class Angajat:public IoBase{
protected:
    double salariu;
    string functie, nume;
    int ani_exp;
public:
    Angajat();
    Angajat(double sal,string funct,string name, int ani);
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
    virtual double salariu_net();

    //double getSalariu() const;

    //const string &getFunctie() const;

    const string &getNume() const;

    int getAniExp() const;
};

Angajat::Angajat(){
    salariu = 0;
    ani_exp = 0;
}

Angajat::Angajat(double sal, string funct,string name,int ani) {
    salariu = sal;
    functie = move(funct);
    nume = move(name);
    ani_exp = ani;
}

istream &Angajat::read(istream &is) {
    cout<<"Nume:";
    getline(cin,nume);
    cout<<"Functie:";
    getline(cin,functie);
    cout<<"Salariu de baza:";
    cin >> salariu;
    cout<<"Ani de experienta:";
    cin>>ani_exp;
    return IoBase::read(is);
}

ostream &Angajat::write(ostream &os) const {
    cout<<"Nume:"<< nume << "\n";
    cout<<"Functie:" << functie <<"\n";
    cout<<"Salariu de baza:" << salariu << "\n";
    cout<<"Ani de experienta:" << ani_exp <<"\n";
    return IoBase::write(os);
}

double Angajat::salariu_net() {
    return salariu/2;
}

//double Angajat::getSalariu() const {
//    return salariu;
//}

//const string &Angajat::getFunctie() const {
//    return functie;
//}

const string &Angajat::getNume() const {
    return nume;
}

int Angajat::getAniExp() const {
    return ani_exp;
}

class Programator: public Angajat{
protected:
    int cntBonusHours;
public:
    Programator();
    Programator(double sal,string funct,string name, int ani, int ore);
    istream &read(istream &is) override;

    ostream &write(ostream &os) const override;
    double salariu_net() override;
};
double Programator :: salariu_net(){
    double BONUS_HOUR_INCOME = 2.5 * salariu / 160;
    return Angajat::salariu_net() + cntBonusHours * BONUS_HOUR_INCOME;
}
Programator::Programator():Angajat(){
    cntBonusHours = 0;
}

Programator::Programator(double sal, string funct,string name,int ani, int ore):Angajat(sal,std::move(funct),std::move(name),ani){
    cntBonusHours = ore;
}

istream &Programator::read(istream &is) {
    Angajat::read(is);
    cout<<"Ore Bonus:";
    cin >> cntBonusHours;
    return is;
}

ostream &Programator::write(ostream &os) const {
    Angajat::write(os);
    cout<<"Ore Bonus:" << cntBonusHours << "\n";
    return os;
}

class Fullstack : public Programator{

public:
    Fullstack();
    Fullstack(double sal, string funct,string name,int ani, int ore);
    ostream &write(ostream &os) const override {
        return Programator::write(os);
    }

    istream &read(istream &is) override {
        return Programator::read(is);
    }

    double salariu_net() override;
};
Fullstack::Fullstack()=default;

Fullstack::Fullstack(double sal, string funct,string name,int ani,int ore): Programator(sal,std::move(funct),std::move(name),ani, ore){}

double Fullstack::salariu_net() {
    return Programator::salariu_net();
}

class DevOps : public Programator{
public:
    DevOps();
    DevOps(double sal, string funct,string name,int ani, int ore);
    ostream &write(ostream &os) const override {
        return Programator::write(os);
    }

    istream &read(istream &is) override {
        return Programator::read(is);
    }

    double salariu_net() override;
};

DevOps::DevOps() = default;

DevOps::DevOps(double sal, string funct,string name,int ani, int ore): Programator(sal,std::move(funct),std::move(name),ani, ore){}

double DevOps::salariu_net() {
    return Programator::salariu_net();
}

class Manager:public Angajat{

public:
    Manager();
    Manager(double sal, string funct,string name,int ani);
    ostream &write(ostream &os) const override {
        return Angajat::write(os);
    }

    istream &read(istream &is) override {
        return Angajat::read(is);
    }

    double salariu_net() override;
};
Manager::Manager()=default;

Manager::Manager(double sal, string funct,string name,int ani): Angajat(sal,std::move(funct),std::move(name),ani){}

double Manager::salariu_net() {
    return Angajat::salariu_net();
}


// Cerinta c. cu cele 3 functii.

//bool can_find_team(const vector<shared_ptr<Angajat>>& a){
//    int minimal_2_year_experience=0;
//    int nr_fullstack=0;
//    int nr_devop=0;
//    int nr_man=0;
//
//    int nr_fullstack_exp=0;
//    int nr_devop_exp=0;
//
//    for(auto &angajat:a) {
//        Fullstack *asFullstack = dynamic_cast<Fullstack *>(angajat.get());
//        Manager *asManager = dynamic_cast<Manager *>(angajat.get());
//        DevOps *asDevOp = dynamic_cast<DevOps *>(angajat.get());
//
//        if (asFullstack) {
//
//            if(asFullstack->getAniExp() >= 2){
//                nr_fullstack_exp++;
//                minimal_2_year_experience++;
//            }
//            nr_fullstack++;
//        }else if(asDevOp){
//
//            nr_devop++;
//            if(asDevOp->getAniExp() >=2){
//                nr_devop_exp++;
//                minimal_2_year_experience++;
//            }
//        }else if(asManager){
//            nr_man++;
//        }
//
//    }
//
//    if(nr_man>=1 and nr_devop>=1 and nr_fullstack>=1 and (nr_fullstack_exp>=1 or nr_devop_exp>=1)){
//        return true;
//    }else return false;
//}
//
//
/*
bool ok_team(const vector<shared_ptr<Angajat>>& a){
//    vector<shared_ptr<Angajat>> peste_2_ani;
    int minimal_2_year_experience=0;
    int nr_fullstack=0;
    int nr_devop=0;
    int nr_man=0;

    int nr_fullstack_exp=0;
    int nr_devop_exp=0;

    for(auto &angajat:a) {
        auto *asFullstack = dynamic_cast<Fullstack *>(angajat.get());
        auto *asManager = dynamic_cast<Manager *>(angajat.get());
        auto *asDevOp = dynamic_cast<DevOps *>(angajat.get());

        if (asFullstack) {
//            peste_2_ani.push_back(make_shared<Fullstack>(*asFullstack));

            if(asFullstack->getAniExp() >= 2){
                nr_fullstack_exp++;
                minimal_2_year_experience++;
            }
            nr_fullstack++;
        }else if(asDevOp){

            nr_devop++;
            if(asDevOp->getAniExp() >=2){
                nr_devop_exp++;
                minimal_2_year_experience++;
            }
        }else if(asManager){
            nr_man++;
        }

    }

    if(a.size()==3){
        if(nr_man==nr_devop==nr_fullstack and (nr_fullstack_exp==1 or nr_devop_exp==1)){
            return true;
        }else return false;
    }else if(a.size()>=4){
        int nr_exp=nr_fullstack_exp+nr_devop_exp;
        if(nr_man==1 and nr_devop>=1 and nr_fullstack>=1 and nr_exp>=a.size()/2){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}
*/
/*
void back_nr(int k, vector<int>& st, const vector<shared_ptr<Angajat>>& a, int &sum){
    for(int i=0;i<=1;i++){
        st[k]=i;
        if(k==a.size()-1){
            vector<shared_ptr<Angajat>> angajati;
            for(int j=0;j<a.size();j++){
                if(st[j]==1){
                    angajati.push_back(a[j]);
                }
            }
            bool ok= ok_team(angajati);
            if(ok){
                for(auto & j : angajati){
                    cout<<*j<<"\n";
                }
                cout<<"Asta a fost o solutie\n";
                sum++;
            }
        }else{
            back_nr(k+1, st, a, sum);
        }
    }
}
*/
//
//int numar_echipe(const vector<shared_ptr<Angajat>>& a){
//    vector<int> st;
//    st.resize(a.size());
//    int sum=0;
//    back_nr(0,st,a,sum);
//    return sum;
//}
//
/*
void back_teams(int k, vector<int>& st, const vector<shared_ptr<Angajat>>& a, vector<vector<shared_ptr<Angajat>>> &teams){
    for(int i=0;i<=1;i++){
        st[k]=i;
        if(k==a.size()-1){
            vector<shared_ptr<Angajat>> angajati;
            for(int j = 0;j < a.size(); ++j){
                if(st[j]==1){
                    angajati.push_back(a[j]);
                }
            }
            bool ok= ok_team(angajati);
            if(ok){
                teams.push_back(angajati);
            }
        }else{
            back_teams(k+1, st, a, teams);
        }
    }
}
*/

//vector<vector<shared_ptr<Angajat>>> partitie_echipe(const vector<shared_ptr<Angajat>>& a){
//    vector<int> st;
//    vector<vector<shared_ptr<Angajat>>> teams;
//    st.resize(a.size());
//    back_teams(0,st,a, teams);
//    return teams;
//}


// Cerinta d.

class Team{
private:
    double buget_maxim;
    vector<shared_ptr<Angajat>> angajati;
public:
    Team():buget_maxim(0) {};

    const vector<shared_ptr<Angajat>> &getAngajati() const;

    Team(double bugetMaxim, const vector<shared_ptr<Angajat>> &angajati) : buget_maxim(bugetMaxim), angajati(angajati) {}

    bool can_find_team_method();
    int numar_echipe_method();

    static bool ok_team(vector<shared_ptr<Angajat>>& a);

    void back_nr(int k, vector<int>& st, const vector<shared_ptr<Angajat>>& a, int &sum);
    void bkt(int k, vector<int>& st, const vector<shared_ptr<Angajat>>& a, vector<vector<shared_ptr<Angajat>>> &teams);
    vector<vector<shared_ptr<Angajat>>> partitie_echipe_method();
    vector<Team> sortedTeams();
    int maximumTeamCount();
};
void Team::bkt(int k, vector<int>& st, const vector<shared_ptr<Angajat>>& a, vector<vector<shared_ptr<Angajat>>> &teams) {
    for(int i = 0;i <= 1;i++){
        st[k] = i;
        if(k == a.size() - 1){
            vector<shared_ptr<Angajat>> angajat;
            for(int j = 0;j < a.size(); ++j){
                if(st[j] == 1){
                    angajat.push_back(a[j]);
                }
            }
            bool ok = ok_team(angajat);
            if(ok){
                teams.push_back(angajat);
            }
        }else{
            bkt(k+1, st, a, teams);
        }
    }
}
bool Team::can_find_team_method() {
    int nr_fullstack=0;
    int nr_devop=0;
    int nr_man=0;

    int nr_fullstack_exp=0;
    int nr_devop_exp=0;

    for(auto &angajat:angajati) {
        auto *asFullstack = dynamic_cast<Fullstack *>(angajat.get());
        auto *asManager = dynamic_cast<Manager *>(angajat.get());
        auto *asDevOp = dynamic_cast<DevOps *>(angajat.get());

        if (asFullstack) {
            if(asFullstack->getAniExp() >= 2){
                nr_fullstack_exp++;
            }
            nr_fullstack++;
        }
        else if(asDevOp){
            nr_devop++;
            if(asDevOp->getAniExp() >=2){
                nr_devop_exp++;
            }
        }else if(asManager){
            nr_man++;
        }
    }
    if(nr_man>=1 and nr_devop>=1 and nr_fullstack>=1 and (nr_fullstack_exp>=1 or nr_devop_exp>=1))
        return true;
    else return false;
}

int Team::numar_echipe_method() {
    vector<int> st;
    st.resize(angajati.size());
    int sum=0;
    back_nr(0,st,angajati,sum);
    return sum;
}

vector<vector<shared_ptr<Angajat>>> Team::partitie_echipe_method() {
    vector<int> st;
    vector<vector<shared_ptr<Angajat>>> teams;
    st.resize(angajati.size());
    bkt(0,st,angajati, teams);
    return teams;
}

vector<Team> Team::sortedTeams() {
    vector<vector<shared_ptr<Angajat>>> echipe;
    echipe = partitie_echipe_method();
    vector<Team> teams;
    double sum1, sum2;
    for(int i = 0;i < echipe.size() - 1; ++i){
        sum1 = 0;
        for(auto & j : echipe[i]){
            sum1 += j->salariu_net();
        }
        for(int j = i + 1;j < echipe.size(); ++j){
            sum2=0;
            for(auto & l : echipe[j]){
                sum2 += l->salariu_net();
            }
            if(sum1 > sum2){
                swap(echipe[i], echipe[j]);
            }
        }
    }
    for(auto & i : echipe){
        Team t;
        t.angajati = i;
        double buget = 0;
        for(auto & j : i){
            buget += j->salariu_net();
        }
        t.buget_maxim = buget;
        teams.push_back(t);
    }
    return teams;
}

int Team::maximumTeamCount() {
    vector<vector<shared_ptr<Angajat>>> echipe;
    echipe=partitie_echipe_method();
    int nr_teams_budget=0;
    for(auto & i : echipe){
        double local_budget=0;
        for(auto & j : i){
            local_budget += j->salariu_net();
        }
        if(local_budget <= buget_maxim){
            nr_teams_budget++;
        }
    }
    return nr_teams_budget;
}

bool Team::ok_team(vector<shared_ptr<Angajat>>& a) {
    int minimal_2_year_experience=0;
    int nr_fullstack=0;
    int nr_devop=0;
    int nr_man=0;

    int nr_fullstack_exp=0;
    int nr_devop_exp=0;

    for(auto &angajat:a) {
        auto *asFullstack = dynamic_cast<Fullstack *>(angajat.get());
        auto *asManager = dynamic_cast<Manager *>(angajat.get());
        auto *asDevOp = dynamic_cast<DevOps *>(angajat.get());

        if (asFullstack) {


            if(asFullstack->getAniExp() >= 2){
                nr_fullstack_exp++;
                minimal_2_year_experience++;
            }
            nr_fullstack++;
        }else if(asDevOp){

            nr_devop++;
            if(asDevOp->getAniExp() >=2){
                nr_devop_exp++;
                minimal_2_year_experience++;
            }
        }else if(asManager){
            nr_man++;
        }
    }

    if(a.size()==3){
        if(nr_man==nr_devop==nr_fullstack and (nr_fullstack_exp==1 or nr_devop_exp==1)){
            return true;
        }else return false;
    }else if(a.size()>=4){
        int nr_exp=nr_fullstack_exp+nr_devop_exp;
        if(nr_man==1 and nr_devop>=1 and nr_fullstack>=1 and nr_exp>=a.size()/2){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void Team::back_nr(int k, vector<int> &st, const vector<shared_ptr<Angajat>> &a, int &sum) {
    for(int i=0;i<=1;i++) {
        st[k] = i;
        if (k == a.size() - 1) {
            vector<shared_ptr<Angajat>> angajat;
            for (int j = 0; j < a.size(); j++) {
                if (st[j] == 1) {
                    angajat.push_back(a[j]);
                }
            }
            bool ok = ok_team(angajat);
            if (ok)
                sum++;
        } else {
            back_nr(k + 1, st, a, sum);
        }
    }
}

const vector<shared_ptr<Angajat>> &Team::getAngajati() const {
    return angajati;
}


int main(){
    vector<shared_ptr<Angajat>> ang= {
            make_shared<Manager>(
                    2000, "Manager", "Matei Pop",3
            ),
            make_shared<Fullstack>(
                    Fullstack(
                            2000, "Fst", "Alex Popa",4,2
                    )
            ),
            make_shared<DevOps>(
                    DevOps(
                            2000, "Dev", "Andrei Simplu",3,2
                    )
            ),
            make_shared<DevOps>(
                    DevOps(
                            2000, "Dev", "Andrei Complex",5,7
                    )
            )
    };
    Team a = Team(20000,ang);
    if(a.can_find_team_method()) {
        cout << "Se pot forma "<< a.numar_echipe_method() <<" echipe\n";
        cout << "Doar " << a.maximumTeamCount() << " vor fi alese\n";
        cout << "Echipele sunt:\n";
        auto it = a.sortedTeams();
        for(auto &x : it) {
            for (auto &c: x.getAngajati())
                cout << c->getNume() << "\n";
            cout<<"------\n";
        }
    }
    else cout<<"Nu se pot forma echipe\n";
    return 0;
}
