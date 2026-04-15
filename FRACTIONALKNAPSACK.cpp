#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Item {
    int profit;
    int weight;
};

int sortByWeight(Item items[], int n, int M) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (items[j].weight > items[j+1].weight)
                swap(items[j], items[j+1]);

    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (M >= items[i].weight) {
            totalProfit += items[i].profit;
            M -= items[i].weight;
        }
    }
    return totalProfit;
}

int sortByProfit(Item items[], int n, int M) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (items[j].profit < items[j+1].profit)
                swap(items[j], items[j+1]);

    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        if (M >= items[i].weight) {
            totalProfit += items[i].profit;
            M -= items[i].weight;
        }
    }
    return totalProfit;
}

void sortByRatio(Item items[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ((double)items[j].profit / items[j].weight 
                (double)items[j+1].profit / items[j+1].weight)
                swap(items[j], items[j+1]);
}

double fractionalKnapsack(Item items[], int n, int M) {
    sortByRatio(items, n);

    double totalProfit = 0.0; 

    for (int i = 0; i < n; i++) {
        if (M >= items[i].weight) {
            totalProfit += items[i].profit;
            M -= items[i].weight;
        } else {
            double fraction = (double)M / items[i].weight;
            totalProfit += fraction * items[i].profit;
            break;  
        }
    }
    return totalProfit;
}


int main() {
    int sizes[10] = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000};
    int runs = 10;

    srand(time(0));
    cout << "UEM243135 Code for Fractional Knapsack\n"
    cout << "Knapsack - Time Analysis\n";
    cout << "Size | ByWeight | ByProfit | ByRatio\n";
    cout << "----------------------------------------------\n";

    for (int i = 0; i < 10; i++) {
        int n = sizes[i];
        int M = rand() % 5000 + 1000;

        Item* orig = new Item[n];
        for (int k = 0; k < n; k++) {
            orig[k].profit = rand() % 1000 + 1;
            orig[k].weight = rand() % 100  + 1;
        }

        double t1 = 0, t2 = 0, t3 = 0;

        for (int r = 0; r < runs; r++) {
            Item* temp = new Item[n];

            for (int k = 0; k < n; k++) temp[k] = orig[k];
            auto start = chrono::high_resolution_clock::now();
            sortByWeight(temp, n, M);
            auto end = chrono::high_resolution_clock::now();
            t1 += chrono::duration<double, micro>(end - start).count();

            for (int k = 0; k < n; k++) temp[k] = orig[k];
            start = chrono::high_resolution_clock::now();
            sortByProfit(temp, n, M);
            end = chrono::high_resolution_clock::now();
            t2 += chrono::duration<double, micro>(end - start).count();

            for (int k = 0; k < n; k++) temp[k] = orig[k];
            start = chrono::high_resolution_clock::now();
            sortByRatio(temp, n, M);
            end = chrono::high_resolution_clock::now();
            t3 += chrono::duration<double, micro>(end - start).count();

            delete[] temp;
        }

        cout << n
             << " | " << t1/runs
             << " | " << t2/runs
             << " | " << t3/runs
             << " microseconds\n";

        delete[] orig;
    }

    return 0;
}
