#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

enum SYRUP {
    AMARETTO,
    VANILLA,
    HAZELNUT,
    COCONUT
};

enum MILK {
    NONMILK,
    DOUBLEMILK,
    TRIPLEMILK
};

enum TOPPING {
    CHOCOLATE,
    STRAWBERRY,
    CARAMEL
};

class CoffeeFirst {
    TOPPING topping;

public:

    CoffeeFirst(TOPPING topping) : topping(topping) {

    }
    string toString()
    {
        switch (topping) {
            case TOPPING ::CHOCOLATE: return "CHOCOLATE";
            case TOPPING ::STRAWBERRY: return "STRAWBERRY";
            case TOPPING ::CARAMEL: return "CARAMEL";
        }

        throw std::logic_error("err");
    }
};

class Coffee {

    vector<CoffeeFirst *> data;
    SYRUP syrup;
    MILK milk;

    friend class CoffeeVanillaBuilder;
    friend class CoffeeWilkBuilder ;

public:
    string toString()
    {
        string s = "";

        switch (syrup) {
            case SYRUP::AMARETTO: s += "AMARETTO"; break;
            case SYRUP:: VANILLA: s += " VANILLA"; break;
            case SYRUP::HAZELNUT: s += "HAZELNUT"; break;
            case SYRUP::COCONUT: s += "COCONUT"; break;
        }

        for (auto & datac : data) {
            s += ", " + datac->toString();
        }

        switch (milk) {
            case MILK ::NONMILK: s += ", NON MILK"; break;
            case MILK::DOUBLEMILK: s += ", DOUBLEMILK"; break;
            case MILK::TRIPLEMILK: s += ", TRIPLEMILK"; break;

        }

        return s;
    }
};

class CoffeeBuilder {
protected:
    vector<TOPPING> toppings;
    SYRUP syrup;

public:
    void addFirst(TOPPING topping) {
        toppings.push_back(topping);
    }

    void setSyrup(SYRUP syrup) {
        this->syrup = syrup;
    }

    virtual Coffee* build() = 0;

};

class CoffeeVanillaBuilder: public CoffeeBuilder {
public:
    virtual Coffee* build() {
        Coffee* coffee = new Coffee();
        for (auto & t : toppings) {
            coffee->data.push_back(new CoffeeFirst(t));
        }
        coffee->syrup = SYRUP::VANILLA;
        coffee->milk = MILK::DOUBLEMILK;
        return coffee;
    }
};

class CoffeeWilkBuilder : public CoffeeBuilder {
public:
    virtual Coffee* build() {
        Coffee* coffee = new Coffee();
        coffee->milk = MILK::TRIPLEMILK;
        return coffee;
    }
};

void userGUI (CoffeeBuilder &builder) {
    builder.addFirst(TOPPING::CHOCOLATE);
    builder.setSyrup(SYRUP::COCONUT);

    Coffee *coffee= builder.build();

    cout << "It's your's coffee: " << coffee->toString() << endl;
}
int main() {
    CoffeeVanillaBuilder coffee1;
    CoffeeWilkBuilder coffee2;

    userGUI(coffee1);
    userGUI(coffee2);
}
