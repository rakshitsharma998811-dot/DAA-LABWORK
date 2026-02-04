#include <iostream>
using namespace std;

void TOH(int n, char source, char helper, char destination) {
    // Base case
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << destination << endl;
        return;
    }

    // Step 1: Move n-1 disks from source to helper
    TOH(n - 1, source, destination, helper);

    // Step 2: Move nth disk from source to destination
    cout << "Move disk " << n << " from " << source << " to " << destination << endl;

    // Step 3: Move n-1 disks from helper to destination
    TOH(n - 1, helper, source, destination);
}

int main() {
    int n;
    cout << "Enter number of disks: ";
    cin >> n;

    TOH(n, 'A', 'B', 'C');  // A = source, B = helper, C = destination

    return 0;
}
