#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Point {
    int x, y;
};

long long cross(Point A, Point B, Point C) {
    return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
}

bool pointInsideTriangle(Point A, Point B, Point C, Point P) {
    long long c1=cross(A, B, P);
    long long c2=cross(B, C, P);
    long long c3=cross(C, A, P);
    bool has_neg=(c1<0) || (c2<0) || (c3<0);
    bool has_pos=(c1>0) || (c2>0) || (c3>0);
    return !(has_neg && has_pos); 
}

int convexHull(vector<Point>& points) {
    int n = points.size();
    vector<bool> isInterior(n, false);
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            for (int k=j+1; k<n; k++) {
                for (int p=0; p<n; p++) {
                    if (p==i || p==j || p==k)
                        continue;
                    if (pointInsideTriangle(points[i], points[j], points[k], points[p])) {
                        isInterior[p]=true;
                    }
                }
            }
        }
    }
    int boundaryCount = 0;
    for (int i=0; i<n; i++) {
        if (!isInterior[i]) boundaryCount++;
    }
    return boundaryCount;
}

int main() {
    vector<vector<double>> timings(10, vector<double>(10));
    vector<long long> testValues={10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    cout << "Convex Hull - Time Analysis\n";
    for (long long i=0; i<10; i++) {
        long long n=testValues[i];
        vector<Point> points(n);
        srand(time(0)+i);
        for (long long k=0; k<n; k++) {
            points[k].x = rand()%1000;
            points[k].y = rand()%1000;
        }
        double timeTaken=0;
        for (long long iter=0; iter<10; iter++) {
            auto start=chrono::high_resolution_clock::now();
            int result = convexHull(points);
            auto end=chrono::high_resolution_clock::now();
            chrono::duration<double, micro> duration=end-start;
            timings[i][iter]=duration.count();
            timeTaken+=duration.count();
        }
        double avgTime=timeTaken/10.0;
        cout << avgTime << ",";
    }
    cout << endl;
}
