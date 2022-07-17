#include <bits/stdc++.h>

#include <utility>
#include "util/IoBase.h"
#include "util/functions.h"

using namespace std;

class BaseMenu {
public:
    virtual void listOptions() {}

    virtual int chooseOption(int first, unsigned long long last) {}

    virtual void mainLoop() {}
};

class CreateSubmenu : public BaseMenu {
private:
    string nume;
    vector<string> instructiuni;
public:
    CreateSubmenu(string nume, vector<string> instructiuni) : nume(std::move(nume)), instructiuni(std::move(instructiuni)) {}

    void listOptions() override {
        int i;
        for(i = 0;i < instructiuni.size(); ++i)
            cout << i+1 << " " << instructiuni[i] <<"\n";
        i++;
        cout << i << " Exit" << '\n';
    }

    int chooseOption(int first, unsigned long long last) override {
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


    static void create_class(){
        cout<<"Am creat cu succes o clasa C++.\n";
    }

    static void create_text_file(){
        cout<<"Am creat cu succes un nou fisier text.\n";
    }
    static void browse(){
        cout<<"Am deschis folder.\n";
    }


    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, instructiuni.size()+1);
            if(nume == "Create") {
                if (option == 1) {
                    create_class();
                } else if (option == 2) {
                    create_text_file();
                } else if (option == 3) {
                    break;
                }
            }
            else if(nume == "Open") {
                if (option == 1) {
                    browse();
                } else if (option == 2)
                    break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Am inchis submeniul."<< nume <<"\n";
    }
};


class ComposedMenu : public BaseMenu {
protected:
    string nume;
    map <string, shared_ptr <BaseMenu> > subMenues;
    vector <string> optiuni;

public:
    ComposedMenu(string nume,const map<string, shared_ptr<BaseMenu>> &subMenues, const vector<string> &optiuni) :nume(move(nume)), subMenues(subMenues), optiuni(optiuni) {};

    void listOptions() override {
        auto it = subMenues.begin();
        int i;
        for(i = 0;i < subMenues.size();++i){
            std::advance(it, i);
            cout << i+1 << " " << it->first << "\n";
        }
        i++;
        for(auto  &x: optiuni)
            cout << i++ << " " << x << "\n";
        cout << i << " Exit" << '\n';
    }

    int chooseOption(int first, unsigned long long  last) override {
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
        auto it = subMenues.begin();
        cout << "Am deschis meniul " << it->first <<"\n";
        it->second->mainLoop();
    }
    void option2(){
        auto it = subMenues.begin();
        advance(it, 1);
        cout << "Am deschis meniul " << it->first <<"\n";
        it->second->mainLoop();
    }
    static void option3() {
        cout<<"Am sters fisierul.\n";
    }

    void mainLoop() override {
        while (true) {
            int option = chooseOption(1, subMenues.size()+optiuni.size()+1);
            if (option == 1) {
                option1();
            } else if (option == 2) {
                option2();
            } else if (option == 3) {
                option3();
            } else if (option == 4) {
                break;
            }
        }
        cout << '\n'<< "---------------------------------"<< '\n'<< "Programul s-a incheiat cu success";
    }

};

int main() {
    CreateSubmenu meniu1 = CreateSubmenu("Create",{"C++ Class","Text File"});
    CreateSubmenu meniu2 = CreateSubmenu("Open",{"Browse"});
    map<string, shared_ptr<BaseMenu>> menulist = {{"Create", make_shared<CreateSubmenu>(meniu1)},{"Open", make_shared<CreateSubmenu>(meniu2)}};
    ComposedMenu m = ComposedMenu("File", menulist, {"Delete File"});
    m.mainLoop();

}