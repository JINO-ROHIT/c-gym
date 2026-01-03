#include <iostream>

using namespace std;

int main(){

    const int stride = 2;
    const int rows = 2;
    const int cols = 2;

    int M[4] = {1, 2, 3, 4}; // 2 x 2
    int N[4] = {5, 6, 7, 8}; // 2 x 2
    int O[4];

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << M[i * stride + j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n\n";

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << N[i * stride + j] << "\t";
        }
        cout << "\n";
    }

    cout << "\n\n" << "Result" << "\n\n";

    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int sum = 0;
            for(int k = 0; k < cols; k++){
                sum += M[i * stride + k] * N[k * stride + j];
                //cout << M[i * stride + k] << " " << N[k * stride + j] << " " << sum << endl; 
                O[i * stride + j] = sum;
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto naive_gemm_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "naive GEMM: " << naive_gemm_time << " microseconds\n";

    // uncomment to debug the values
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << O[i * stride + j] << "\t";
        }
        cout << "\n";
    }

}