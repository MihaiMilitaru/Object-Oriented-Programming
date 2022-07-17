#include<iostream>
using namespace std;

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