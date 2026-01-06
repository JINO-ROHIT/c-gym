// why is tiling slower?

#include <iostream>

using namespace std;

int main(){

    const int rows = 2048;
    const int cols = 2048;
    const int stride = cols;

    const int block_size = 16;

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

    for(int bx = 0; bx < rows; bx += block_size){
        for(int by = 0; by < cols; by += block_size){
            for(int bk = 0; bk < cols; bk += block_size){ 
                for(int i = 0; i < block_size; i++){
                    for(int k = 0; k < block_size; k++){ 
                        int temp_M = M[(bx + i) * stride + (bk + k)]; 
                        for(int j = 0; j < block_size; j++){ 
                            O[(bx + i) * stride + (by + j)] += temp_M * N[(bk + k) * stride + (by + j)];
                        }
                    }
                }
            }
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto naive_gemm_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "naive GEMM: " << naive_gemm_time << " millioseconds\n";
}