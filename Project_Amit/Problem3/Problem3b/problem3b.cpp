#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>

using namespace std;

int main() {
    const int WIDTH = 500;
    const int HEIGHT = 500;
    const int MAX_ITERATIONS = 1000;
    const double ZOOM = 2.0;
    complex<double> CENTER(0.0, 0.0);

    ofstream fout;
    fout.open("problem3b.pgm");
    
    // Write PGM header
    fout << "P2" << endl;
    fout << WIDTH << " " << HEIGHT << endl;
    fout << 255 << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            double x = (j - WIDTH / 2.0) / (0.125 * ZOOM * WIDTH) + real(CENTER);
            double y = (i - HEIGHT / 2.0) / (0.125 * ZOOM * HEIGHT) + imag(CENTER);
            
            complex<double> c(x, y);
            complex<double> z(0.0, 0.0);
            
            int iterations = 0;
            while (abs(z) <= 2.0 && iterations < MAX_ITERATIONS) {
                z = z * z + c;
                iterations++;
            }
            
            if (iterations == MAX_ITERATIONS) {
                fout << 0 <<" ";  // Black for points in the set
            } else {
                // Continuous coloring
                int color = static_cast<int>(255.0 * iterations / MAX_ITERATIONS);
                fout << color << " ";
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}