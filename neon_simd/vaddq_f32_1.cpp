#include <iostream>
#include <arm_neon.h>
#include <chrono>

void normal_vadd(const float* a, const float* b, float* c){
    for(int i = 0; i < 10; i++){
        c[i] = a[i] + b[i];
    }
}

void simd_vadd(const float* a, const float* b, float* c){
    // process 4 elements at a time (128 bits / 32 bits = 4 floats)
    int simd_size = 4; // its 4 here bc we know we have 32 bits and the register can hold max 128 bit
    int total_elements = 10;
    int simd_iterations = total_elements / simd_size;


    for(int i = 0; i < simd_iterations; i++){

        float32x4_t va = vld1q_f32(a + i * simd_size);
        float32x4_t vb = vld1q_f32(b + i * simd_size);

        float32x4_t vc = vaddq_f32(va, vb);

        vst1q_f32(c + i * simd_size, vc); 

        // for(int j = 0; j < simd_size; j++){
        //     std::cout << c[i * simd_size + j] << std::endl;
        // }
    }

    // handle remaining elements 
    for(int i = simd_iterations * simd_size; i < total_elements; i++){
        c[i] = a[i] + b[i];
    }
}

int main(){
    float32_t a[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float32_t b[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float32_t c_normal[10];
    float32_t c_simd[10];

    std::cout << "Normal vector addition:" << std::endl;
    auto start_normal = std::chrono::high_resolution_clock::now();
    normal_vadd(a, b, c_normal);
    auto end_normal = std::chrono::high_resolution_clock::now();
    auto duration_normal = std::chrono::duration_cast<std::chrono::nanoseconds>(end_normal - start_normal);
    std::cout << "Normal addition time: " << duration_normal.count() << " nanoseconds" << std::endl;

    std::cout << "\n";

    auto start_simd = std::chrono::high_resolution_clock::now();
    simd_vadd(a, b, c_simd);
    auto end_simd = std::chrono::high_resolution_clock::now();
    auto duration_simd = std::chrono::duration_cast<std::chrono::nanoseconds>(end_simd - start_simd);
    std::cout << "SIMD addition time: " << duration_simd.count() << " nanoseconds" << std::endl;

    std::cout << "\n";

    bool results_match = true;
    for(int i = 0; i < 10; i++){
        if(c_normal[i] != c_simd[i]){
            results_match = false;
            break;
        }
    }

    if(results_match){
        std::cout << "Results match: Both normal and SIMD addition produce identical results" << std::endl;
    } else {
        std::cout << "Results differ: Normal and SIMD addition produce different results" << std::endl;
    }

    return 0;
}

