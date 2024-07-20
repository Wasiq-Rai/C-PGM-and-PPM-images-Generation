#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
    const int WIDTH = 150;
    const int HEIGHT = 100;
    const int CIRCLE_RADIUS = 30;  // 3/5 of height

    ofstream fout;
    fout.open("problem1d.ppm");
    
    // Write PPM header
    fout << "P3" << endl;
    fout << WIDTH << " " << HEIGHT << endl;
    fout << 255 << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Transform to user coordinates
            int x = j - WIDTH / 2;
            int y = i - HEIGHT / 2;

            // Check if pixel is within circle
            if (sqrt(x*x + y*y) <= CIRCLE_RADIUS) {
                fout << 188 << " " << 0 << " " << 45 << " ";  // Japan Red
            } else {
                fout << 255 << " " << 255 << " " << 255 << " ";  // White
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}