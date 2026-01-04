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
        for(int j = 0; j < cols; j++){
            int sum = 0;
            for(int k = 0; k < cols; k++){
                sum += M[i * stride + k] * N[k * stride + j];
                //cout << M[i * stride + k] << " " << N[k * stride + j] << " " << sum << endl; 
            }
            O[i * stride + j] = sum;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto naive_gemm_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "naive GEMM: " << naive_gemm_time << " millioseconds\n";
}