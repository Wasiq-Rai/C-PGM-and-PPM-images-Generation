#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

// Define color schemes for the Mandelbrot set
enum ColorScheme { FIRE, OCEAN, FOREST, PSYCHEDELIC };

// Structure to represent RGB colors
struct Color {
    int r, g, b;
};

// Function to interpolate between two colors
Color interpolateColor(double t, const Color& start, const Color& end) {
    int r = static_cast<int>(start.r + t * (end.r - start.r));
    int g = static_cast<int>(start.g + t * (end.g - start.g));
    int b = static_cast<int>(start.b + t * (end.b - start.b));
    return {r, g, b};
}

// Function to get a color based on iteration count and color scheme
Color getColor(int iterations, int maxIterations, ColorScheme scheme) {
    double t = static_cast<double>(iterations) / maxIterations;
    Color startColor, midColor, endColor;
    
    // Define color gradients for each scheme
    switch(scheme) {
        case FIRE:
            startColor = {0, 0, 0};    // Black
            midColor = {255, 128, 0};  // Orange
            endColor = {255, 255, 0};  // Yellow
            break;
        case OCEAN:
            startColor = {0, 0, 128};  // Dark Blue
            midColor = {0, 128, 255};  // Light Blue
            endColor = {255, 255, 255};// White
            break;
        case FOREST:
            startColor = {0, 64, 0};   // Dark Green
            midColor = {0, 255, 0};    // Bright Green
            endColor = {255, 255, 0};  // Yellow
            break;
        case PSYCHEDELIC:
            startColor = {255, 0, 255};// Magenta
            midColor = {0, 255, 255};  // Cyan
            endColor = {255, 255, 0};  // Yellow
            break;
    }
    
    // Interpolate between colors based on iteration count
    if (t < 0.5) {
        return interpolateColor(t * 2, startColor, midColor);
    } else {
        return interpolateColor((t - 0.5) * 2, midColor, endColor);
    }
}

// Function to generate a Mandelbrot set image
void generateMandelbrot(const string& filename, int width, int height, complex<double> center, double zoom, ColorScheme colorScheme) {
    const int MAX_ITERATIONS = 1000;

    ofstream fout(filename);
    
    // Write PPM header
    fout << "P3" << endl;
    fout << width << " " << height << endl;
    fout << 255 << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Map pixel coordinates to complex plane
            double x = (j - width / 2.0) / (0.25 * zoom * width) + real(center);
            double y = (i - height / 2.0) / (0.25 * zoom * height) + imag(center);
            
            complex<double> c(x, y);
            complex<double> z(0.0, 0.0);
            
            // Iterate to determine if point is in Mandelbrot set
            int iterations = 0;
            while (abs(z) <= 2.0 && iterations < MAX_ITERATIONS) {
                z = z * z + c;
                iterations++;
            }
            
            // Color the pixel based on iteration count
            Color color = getColor(iterations, MAX_ITERATIONS, colorScheme);
            fout << color.r << " " << color.g << " " << color.b << " ";
        }
        fout << endl;
    }

    fout.close();
}

int main() {
    int width = 800;
    int height = 800;
    
    // Define a wider range of interesting center points for the Mandelbrot set
    vector<complex<double>> centers = {
        {-0.75, 0.0}, {-0.55, 0.64}, {0.37, 0.12}, {-1.4, 0.0}, {0.0, 0.0},
        {-0.235125, 0.827215}, {-0.70176, -0.3842}, {-0.4, 0.6}, {0.45, 0.1428},
        {-0.748, 0.1}, {0.28, 0.008}, {-0.12, 0.77}, {-1.25, 0.02}
    };
    
    // Define a wider range of zoom levels
    vector<double> zooms = {0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 8.0, 13.0, 20.0, 50.0, 100.0, 500.0, 1000.0};
    
    vector<ColorScheme> schemes = {FIRE, OCEAN, FOREST, PSYCHEDELIC};

    // Generate multiple Mandelbrot set images with different parameters
    for (int i = 0; i < centers.size(); i++) {
        // Select center, zoom, and color scheme
        complex<double> center = centers[i];
        double zoom = zooms[i % zooms.size()];
        ColorScheme scheme = schemes[i % schemes.size()];
        
        // Generate and save the image
        string filename = "mandelbrot_" + to_string(i+1) + ".ppm";
        generateMandelbrot(filename, width, height, center, zoom, scheme);
        cout << "Generated " << filename << endl;
    }

    return 0;
}