#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// Function to determine the color of a point in the Sierpinski carpet
vector<int> getColor(int x, int y, int size) {
    vector<vector<int>> colors = {
        {255, 0, 255},    // Magenta
        {0, 255, 255},    // Cyan
        {255, 165, 0},    // Orange
        {0, 0, 255},      // Blue
        {0, 0, 0},        // Black (center)
        {0, 255, 0},      // Green
        {255, 255, 0},    // Yellow
        {0, 128, 0},      // Dark Green
        {255, 0, 0}       // Red
    };

    int block_size = size / 3;
    int block_x = x / block_size;
    int block_y = y / block_size;
    int color_index = block_y * 3 + block_x;

    return colors[color_index];
}

// Recursive function to draw the Sierpinski carpet
void drawCarpet(vector<vector<vector<int>>>& image, int x, int y, int size, int order) {
    if (order == 0) {
        return;
    }

    int new_size = size / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                // Color the center black
                for (int py = y + new_size; py < y + 2 * new_size; py++) {
                    for (int px = x + new_size; px < x + 2 * new_size; px++) {
                        image[py][px] = {0, 0, 0};
                    }
                }
            } else {
                // Recursively draw smaller carpets
                drawCarpet(image, x + i * new_size, y + j * new_size, new_size, order - 1);
            }
        }
    }
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

    // Create a 3D vector to store the image
    vector<vector<vector<int>>> image(SIZE, vector<vector<int>>(SIZE, vector<int>(3)));

    // Color the base image
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            image[y][x] = getColor(x, y, SIZE);
        }
    }

    // Draw the Sierpinski carpet
    drawCarpet(image, 0, 0, SIZE, order);

    // Open the output file
    ofstream fout;
    fout.open("problem2b.ppm");

    // Write PPM header
    fout << "P3" << endl;
    fout << SIZE << " " << SIZE << endl;
    fout << 255 << endl;

    // Write the image data
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            fout << image[y][x][0] << " " << image[y][x][1] << " " << image[y][x][2] << " ";
        }
        fout << endl;
    }

    fout.close();
    cout << "Image generated successfully as 'problem2b.ppm'" << endl;
    return 0;
}