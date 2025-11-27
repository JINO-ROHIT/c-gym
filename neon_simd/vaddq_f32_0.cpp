#include <iostream>
#include <arm_neon.h>

// vaddq_f32(v128, v128) takes 128 bit vector

int main(){
    float32x4_t v1 = { 1.0, 2.0, 3.0, 4.0 }, v2 = { 1.0, 1.0, 1.0, 1.0 };
    float32x4_t sum = vaddq_f32(v1, v2);
    // => sum = { 2.0, 3.0, 4.0, 5.0 }

    std::cout << "Sum: ";
    for(int i = 0; i < 4; ++i){
        std::cout << sum[i] << " "; 
    }
}