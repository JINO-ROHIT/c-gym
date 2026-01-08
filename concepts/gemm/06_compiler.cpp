#include <iostream>

using namespace std;

int main(){

    const int rows = 2048;
    const int cols = 2048;
    const int stride = cols;

    int* M = new int[rows * cols];
    int* N = new int[rows * cols];
    int* O = new int[rows * cols];
    
    for(int i = 0; i < rows * cols; i++){
        M[i] = i % 10;
        N[i] = (i + 1) % 10;
        O[i] = 0;
    }

    cout << "\n\n" << "Result" << "\n\n";

    auto start = chrono::high_resolution_clock::now();

    for(int i = 0; i < rows; i++){
        for(int k = 0; k < cols; k++){ 
            int temp_M = M[i * stride + k]; 
            for(int j = 0; j < cols; j++){ 
                O[i * stride + j] += temp_M * N[k * stride + j];
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto naive_gemm_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "naive GEMM: " << naive_gemm_time << " millioseconds\n";
}

// compile using g++ -O3 -march=native -ffast-math 06_compiler.cpp utils.cpp -o test && ./test
// with simply -O3 rapid af