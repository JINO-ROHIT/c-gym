#include <string>

using namespace std;

// assume square matrix
double flops_counter(int size, const string& unit = "gflops") {
    double flops = 2.0 * size * size * size;

    if (unit == "flops") {
        return flops;
    }
    else if (unit == "kflops") {
        return flops * 1e-3;
    }
    else if (unit == "mflops") {
        return flops * 1e-6;
    }
    else if (unit == "gflops") {
        return flops * 1e-9;
    }
    else if (unit == "tflops") {
        return flops * 1e-12;
    }
}