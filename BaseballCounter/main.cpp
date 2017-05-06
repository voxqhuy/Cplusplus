// Vo Huy
// BaseBall Counter
// 4-11-2017 what a beautiful day!
// CPTR 215 by Prof. O
// from Lab 7.

#include <iostream>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std;

class BC {
    private:
        int _min, _max, _val;
        BC* _next;
    public:
        BC(int min = 0, int max = 9, BC* next = nullptr) :
            _min(min), _max(max), _val(min), _next(next) {}

        void increment() {

            _val++;
            if (_val > _max) {
                _val = _min;
                if (_next != nullptr)
                    _next->increment();
            }
        }

        int getValue() const {
            return _val;
        }

        void setVal(int i) {
            _val = i;
        }

        void setNext(BC* next) {
            _next = next;
        }

        void print(bool isLastOne = true) const {
            if (_next != nullptr)
                _next->print(false);
            cout << _val;
            if (isLastOne)
                cout << endl;
        }
};

void printStuff(BC inning, BC out, BC strike, BC ball) {
    cout << "Inning: " << inning.getValue() << endl;
    cout << "Out: " << out.getValue() << endl;
    cout << "Strike: " << strike.getValue() << endl;
    cout<< "Ball: " << ball.getValue() << endl;
}

int main() {

    doctest::Context().run();
    cout << "Hello World!" << endl;

    string userInput;
    BC inning(1, 10);
    BC changeInning(1, 2, &inning);
    BC out(0, 2, &changeInning);
    BC strike(0, 2, &out);
    BC ball(0, 3, &strike);

    printStuff(inning, out, strike, ball);
    cout << endl;

    cout << "type \"b\" for a ball, \"o\" for an out, \"s\" for a strike (or \"Quit\" if you want to quit)" << endl;

    while(getline(cin, userInput)) {
        if (userInput == "b") {
                ball.increment();
        } else if (userInput == "o") {
                if (out.getValue() == 2) {
                    ball.setVal(0);
                    strike.setVal(0);
                }
                out.increment();
        } else if(userInput == "s") {
            if (strike.getValue() == 2) {
                ball.setVal(0);
            }
            strike.increment();
        } else if (userInput == "Quit") {
            break;
        }
        printStuff(inning, out, strike, ball);
        cout << endl;
        cout << "type \"b\" for a ball, \"o\" for an out, \"s\" for a strike or \"Quit\" if you want to quit)" << endl;
    }
    return 0;
}

TEST_CASE("BC::BC")
{
    BC inning(1, 9);
    inning.increment();
    CHECK(inning.getValue() == 2);
}

TEST_CASE("increment")
{
    BC inning(1, 10);
    BC changeInning(1, 2, &inning);
    inning.increment();
    CHECK(inning.getValue() == 2);

    inning.increment();
    CHECK(inning.getValue() == 3);

    changeInning.increment();
    CHECK(changeInning.getValue() == 2);

    changeInning.increment();
    CHECK(changeInning.getValue() == 1);
}

TEST_CASE("getValue")
{
    BC inning(1, 10);
    BC changeInning(1, 2, &inning);
    inning.increment();
    CHECK(inning.getValue() == 2);

    inning.increment();
    CHECK(inning.getValue() == 3);

    changeInning.increment();
    CHECK(changeInning.getValue() == 2);
}
