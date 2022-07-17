//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//class Gift {
//protected:
//    string name, giverName;
//public:
//    Gift(const string &name, const string &giverName) : name(name), giverName(giverName) {}
//
//    virtual void offerGift(string receivedBy) {
//        cout << "The gift named " << name
//             << " was received by " << receivedBy
//             << " thanks to the courtesy of " << giverName << '\n';
//    }
//};
//
//
//class GiftCard : public Gift {
//private:
//    int sum;
//public:
//    void offerGift(string receivedBy) override {
////        Gift::offerGift(receivedBy);
//        cout << "Congratulations " << '"' << receivedBy << '"'
//             << "! You received a gift card of " << sum << "USD from "
//             << '"' << giverName << '"'
//             << '\n';
//
//
//    }
//
//    GiftCard(const string &name, const string &giverName, int sum) : Gift(name, giverName), sum(sum) {}
//};
//
//class GiftHoliday : public Gift {
//private:
//    string location;
//public:
//    void offerGift(string receivedBy) override {
////        Gift::offerGift(receivedBy);
//        cout << "Heyy " << '"' << receivedBy << '"'
//             << "! Guess what! You're travelling to " << location << ". It's a gift from"
//             << '"' << giverName << '"'
//             << '\n';
//
//
//
//
//
//    }
//
//    GiftHoliday(const string &name, const string &giverName, const string &location) : Gift(name, giverName),
//                                                                                       location(location) {}
//};
//
//class GiftFavouriteProduct : public Gift {
//private:
//    string category;
//public:
//    void offerGift(string receivedBy) override {
////        Gift::offerGift(receivedBy);
//        cout << "Hello there " << '"' << receivedBy << '"'
//             << "! Yours wishes come true! You can pick whatever item from " << category << ". It's a gift from "
//             << '"' << giverName << '"'
//             << '\n';
//    }
//
//    GiftFavouriteProduct(const string &name, const string &giverName, const string &category) : Gift(name, giverName),
//                                                                                                category(category) {}
//};
//
//
//int main() {
//    Gift simpleGift("No Name", "Eleanor Roosevelt");
//    GiftCard card("Andrei Popescu", "Popescu Miruna", 300);
//    GiftHoliday holiday("Ibiza platita!", "Leonard Coste", "Ibiza, Spain");
//    GiftFavouriteProduct phone("Pentru tine", "Costache Leurdean", "Apple Products");
//
//    simpleGift.offerGift("Ioan");
//    card.offerGift("Persida");
//    holiday.offerGift("Romeo");
//    phone.offerGift("Caligula");
//}


