#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAX_SIZE 64

typedef int Table[MAX_SIZE][MAX_SIZE];

void addTables(Table src1, Table src2, Table result, int sz)
{
    for (int r = 0; r < sz; r++)
        for (int c = 0; c < sz; c++)
            result[r][c] = src1[r][c] + src2[r][c];
}

void splitTable(Table src, Table dest, int rowOffset, int colOffset, int sz)
{
    for (int r = 0; r < sz; r++)
        for (int c = 0; c < sz; c++)
            dest[r][c] = src[r + rowOffset][c + colOffset];
}

void mergeTable(Table src, Table dest, int rowOffset, int colOffset, int sz)
{
    for (int r = 0; r < sz; r++)
        for (int c = 0; c < sz; c++)
            dest[r + rowOffset][c + colOffset] = src[r][c];
}

void multiplyTables(Table mat1, Table mat2, Table res, int sz)
{
    if (sz == 1)
    {
        res[0][0] = mat1[0][0] * mat2[0][0];
        return;
    }

    int half = sz / 2;

    Table p11, p12, p21, p22;
    Table q11, q12, q21, q22;

    splitTable(mat1, p11, 0, 0, half);
    splitTable(mat1, p12, 0, half, half);
    splitTable(mat1, p21, half, 0, half);
    splitTable(mat1, p22, half, half, half);

    splitTable(mat2, q11, 0, 0, half);
    splitTable(mat2, q12, 0, half, half);
    splitTable(mat2, q21, half, 0, half);
    splitTable(mat2, q22, half, half, half);

    Table t1, t2;
    Table r11, r12, r21, r22;

    multiplyTables(p11, q11, t1, half);
    multiplyTables(p12, q21, t2, half);
    addTables(t1, t2, r11, half);

    multiplyTables(p11, q12, t1, half);
    multiplyTables(p12, q22, t2, half);
    addTables(t1, t2, r12, half);

    multiplyTables(p21, q11, t1, half);
    multiplyTables(p22, q21, t2, half);
    addTables(t1, t2, r21, half);

    multiplyTables(p21, q12, t1, half);
    multiplyTables(p22, q22, t2, half);
    addTables(t1, t2, r22, half);

    mergeTable(r11, res, 0, 0, half);
    mergeTable(r12, res, 0, half, half);
    mergeTable(r21, res, half, 0, half);
    mergeTable(r22, res, half, half, half);
}

int main()
{
    int sizes[] = {2, 4, 8, 16, 32, 64};
    int numSizes = 6;
    int numTrials = 10;
    cout << "UEM243135 Code for Matrix Multiplication\n";
    cout << "Matrix Multiplication (Divide and Conquer) - Time Analysis\n";
    cout << fixed << setprecision(4);

    for (int idx = 0; idx < numSizes; idx++)
    {
        int sz = sizes[idx];

        Table gridA, gridB, gridC;

        srand((unsigned int)(time(0) + idx));

        for (int r = 0; r < sz; r++)
            for (int c = 0; c < sz; c++)
            {
                gridA[r][c] = rand() % 10;
                gridB[r][c] = rand() % 10;
            }

        double totalTime = 0.0;

        for (int trial = 0; trial < numTrials; trial++)
        {
            auto tStart = chrono::high_resolution_clock::now();
            multiplyTables(gridA, gridB, gridC, sz);
            auto tEnd = chrono::high_resolution_clock::now();

            chrono::duration<double, micro> elapsed = tEnd - tStart;
            totalTime += elapsed.count();
        }

        double avgTime = totalTime / (double)numTrials;
        cout << "Size " << setw(3) << sz << " : " << avgTime << " microseconds (avg)\n";
    }

    return 0;
}
