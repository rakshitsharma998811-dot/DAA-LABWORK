#include <iostream>
using namespace std;

int main() {
    int red, blue;
    cout << "Enter number of red balls: ";
    cin >> red;
    cout << "Enter number of blue balls: ";
    cin >> blue;

    float probability = (float)red / (red + blue);
    cout << "Probability of red ball = " << probability;

    return 0;
}
