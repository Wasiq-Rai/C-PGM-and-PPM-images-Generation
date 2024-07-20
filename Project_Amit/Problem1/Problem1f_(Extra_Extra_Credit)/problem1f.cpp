#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

bool isInTriangle(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
    float A = abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
    float A1 = abs((x*(y2-y3) + x2*(y3-y) + x3*(y-y2))/2.0);
    float A2 = abs((x1*(y-y3) + x*(y3-y1) + x3*(y1-y))/2.0);
    float A3 = abs((x1*(y2-y) + x2*(y-y1) + x*(y1-y2))/2.0);
    return (abs(A - (A1 + A2 + A3)) < 0.1);  // Allow for floating point imprecision
}

int main() {
    const int WIDTH = 450;
    const int HEIGHT = 300;
    const int CIRCLE_RADIUS = 60;

    ofstream fout;
    fout.open("problem1f.ppm");
    
    // Write PPM header
    fout << "P3" << endl;
    fout << WIDTH << " " << HEIGHT << endl;
    fout << 255 << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Transform to user coordinates
            int x = j - WIDTH / 2;
            int y = i - HEIGHT / 2;

            if (isInTriangle(x, y, -WIDTH/4, -HEIGHT/2, WIDTH/4, -HEIGHT/2, 0, HEIGHT/2)) {
                fout << 0 << " " << 255 << " " << 0 << " ";  // Green triangle
            } else if (sqrt((x-WIDTH/4)*(x-WIDTH/4) + y*y) <= CIRCLE_RADIUS) {
                fout << 255 << " " << 255 << " " << 0 << " ";  // Yellow circle
            } else {
                fout << 0 << " " << 0 << " " << 255 << " ";  // Blue background
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}