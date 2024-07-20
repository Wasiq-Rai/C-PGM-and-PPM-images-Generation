#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
    const int WIDTH = 450;
    const int HEIGHT = 300;
    const int STRIPE_HEIGHT = HEIGHT / 3;
    const int CIRCLE_RADIUS = 45;

    ofstream fout;
    fout.open("problem1e.ppm");
    
    // Write PPM header
    fout << "P3" << endl;
    fout << WIDTH << " " << HEIGHT << endl;
    fout << 255 << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Transform to user coordinates
            int x = j - WIDTH / 2;
            int y = i - HEIGHT / 2;

            // Determine stripe color
            if (i < STRIPE_HEIGHT) {
                fout << 255 << " " << 153 << " " << 51 << " ";  // Saffron
            } else if (i < 2 * STRIPE_HEIGHT) {
                if (sqrt(x*x + y*y) <= CIRCLE_RADIUS) {
                    fout << 0 << " " << 0 << " " << 128 << " ";  // Navy Blue (Circle)
                } else {
                    fout << 255 << " " << 255 << " " << 255 << " ";  // White
                }
            } else {
                fout << 19 << " " << 136 << " " << 8 << " ";  // India Green
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}