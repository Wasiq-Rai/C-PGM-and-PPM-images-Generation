#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

// Function to check if a point should be colored or not in the Sierpinski carpet
bool isColored(int x, int y, int order) {
    while (order > 0) {
        if (x % 3 == 1 && y % 3 == 1)
            return false;
        x /= 3;
        y /= 3;
        order--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int order;

    // Check if order is provided as command line argument
    if (argc > 1) {
        order = stoi(argv[1]);
    } else {
        // If not provided, ask for input
        cout << "Enter the order of the Sierpinski carpet: ";
        cin >> order;
    }

    // Ensure the order is valid (1 to 7)
    if (order < 1 || order > 7) {
        cout << "Invalid order. Please enter a number between 1 and 7." << endl;
        return 1;
    }

    // Calculate the size of the image (3^order x 3^order)
    const int SIZE = pow(3, order);

    // Open the output file
    ofstream fout;
    fout.open("problem2a.pgm");

    // Write PGM header
    fout << "P2" << endl;
    fout << SIZE << " " << SIZE << endl;
    fout << 255 << endl;

    // Generate the Sierpinski carpet
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            // Check if the current pixel should be colored
            if (isColored(x, y, order)) {
                fout << 255 <<" ";  // White
            } else {
                fout << 0 <<" ";    // Black
            }
        }
        fout << endl;
    }

    fout.close();
    cout << "Sierpinski carpet of order " << order << " has been generated." << endl;
    return 0;
}