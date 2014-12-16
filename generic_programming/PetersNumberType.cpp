/**
* This is a short example of how a class template works in c+
**/

#include <iostream>
using namespace std;

template <class T>
class PetersNumberType {
    T n;
  public:
    PetersNumberType (T num)
        {n = num;}
    T getNum ();
};

template <class T>
T PetersNumberType<T>::getNum ()
{
    T returnMe;
    returnMe = n;
    return returnMe;
}

int main () {
    PetersNumberType <int> intNumber (42);

    PetersNumberType <double> doubleNumber (3.1415);

    cout << intNumber.getNum() << " is an int." << endl;
    cout << "     ...but also a PetersNumberType." << endl;

    cout << doubleNumber.getNum() << " is a double." << endl;
    cout << "     ...but it is also a PetersNumberType." << endl;

    return 0;
}