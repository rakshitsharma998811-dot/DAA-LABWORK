#include <iostream>
#include <chrono>
#include <cstring>
using namespace std;

void permutation(char arr[], int start, int n)
{
    if (start == n)
    {
        return;
    }
    for (int i = start; i < n; i++)
    {
        char temp = arr[start];
        arr[start] = arr[i];
        arr[i] = arr[start];

        permutation(arr, start + 1, n);

        char temp2 = arr[start];
        arr[start] = arr[i];
        arr[i] = arr[start];
    }
}

int main()
{
    int testValues[8] = {3, 4, 5, 6, 7, 8, 9, 10};
    cout << "UEM24135 CODE FOR PERMUTATION GENERATOR OF A STRING\n";
    cout << "String Length | Average Time (microseconds)\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < 8; i++)
    {
        int n = testValues[i];

        double totalTime = 0.0;

        for (int iter = 0; iter < 10; iter++)
        {
            char arr[11];
            for (int k = 0; k < n; k++)
            {
                arr[k] = 'a' + k; 
            }
            arr[n] = '\0';

            auto start = chrono::high_resolution_clock::now();
            permutation(arr, 0, n);
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> duration = end - start;
            totalTime += duration.count();
        }

        double avgTime = totalTime / 10.0;
        cout << n << "            | " << avgTime << " microseconds\n";
    }

    return 0;
}
