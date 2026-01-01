#include <iostream>
#include <arm_neon.h>

#include <chrono>

void vdot(float16_t* a, float16_t* b, float16_t* c){
    for(int i = 0; i < 10; i++){
        c[i] = a[i] * b[i];
        // std::cout << sizeof(c[i]) << std::endl;
    }
}

void vdot_simd(float16_t* a, float16_t* b, float16_t* c){
    int n_elements = 10;
    int simd_size = 128 / 16; // you can read 8 elements in one go
    int iteration_factor = n_elements / simd_size;

    for(int i = 0; i < iteration_factor; i++){
        float16x8_t va = vld1q_f16(a + i * simd_size);
        float16x8_t vb = vld1q_f16(b + i * simd_size);

        float16x8_t vc = vmulq_f16(va, vb);

        vst1q_f16(c + i * simd_size, vc);
    }

    // remaining 2 elements
    for(int i = iteration_factor * simd_size; i < n_elements; i++){
        c[i] = a[i] * b[i];
    }


}

int main(){
    float16_t a[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float16_t b[10] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float16_t c_normal[10];
    float16_t c_simd[10];

    auto start = std::chrono::high_resolution_clock::now();
    vdot(a, b, c_normal);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "normal dot product took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;


    auto start_2 = std::chrono::high_resolution_clock::now();
    vdot_simd(a, b, c_simd);
    auto end_2 = std::chrono::high_resolution_clock::now();

    std::cout << "simd dot product took " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_2 - start_2).count() << std::endl;


}