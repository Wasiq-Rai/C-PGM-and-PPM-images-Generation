#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
    const int WIDTH = 100;
    const int HEIGHT = 100;
    const int CIRCLE_RADIUS = 30;

    ofstream fout;
    fout.open("problem1b.pgm");
    
    // Write PGM header
    fout << "P2" << endl;
    fout << WIDTH << " " << HEIGHT << endl;
    fout << 255 << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Transform to user coordinates
            int x = j - WIDTH / 2;
            int y = i - HEIGHT / 2;

            // Check if pixel is within circle
            if (sqrt(x*x + y*y) <= CIRCLE_RADIUS) {
                fout << 255 << " ";  // White
            } else {
                fout << 0 << " ";  // Black
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}