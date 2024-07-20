#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const int WIDTH = 100;
    const int HEIGHT = 100;
    const int SQUARE_SIZE = 50;

    ofstream fout;
    fout.open("problem1a.pgm");
    
    // Write PGM header
    fout << "P2"<<endl;
    fout << WIDTH << " " << HEIGHT <<endl;
    fout << 255 <<endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Transform to user coordinates
            int x = j - WIDTH / 2;
            int y = i- HEIGHT / 2;

            // Check if pixel is within square
            if ((x > (-SQUARE_SIZE / 2)) && (x < (SQUARE_SIZE/2)) && (y > (-SQUARE_SIZE/2)) && (y < (SQUARE_SIZE/2))) {
                fout << 0 << " " ;  // Black
            } else {
                fout << 255 <<" ";  // White
            }
        }
        fout << endl;
    }

    fout.close();
    return 0;
}