#include <iostream>
#include <assert.h>

template<int N>
class Tensor{
    
    public:
        int shape[N];
        float* data;
        float* alloc;

        Tensor() : data(nullptr), alloc(nullptr){};

        Tensor(float* _data, int i){
            assert(N == 1);
            shape[0] = i;
            data = _data;
            alloc = nullptr;
        }

        Tensor(float* _data, int i, int j){
            assert(N == 2);
            shape[0] = i;
            shape[1] = j;
            data = _data;
            alloc = nullptr;
        }

        void _alloc(size_t nfloats){
            //aligned float array
            alloc = new float[nfloats + 7];
            data = (float *)(((uintptr_t)alloc + 31) & ~31);
        }

        Tensor(int i){
            assert(N == 1);
            shape[0] = i;
            _alloc(i);
        }

        Tensor(int i, int j) {
            assert(N == 2);
            shape[0] = i;
            shape[1] = j;
            _alloc(i*j);
        }

        Tensor(int i, int j, int k) {
            assert(N == 3);
            shape[0] = i;
            shape[1] = j;
            shape[2] = k;
            _alloc(i*j*k);
        }

        //to index
        float& operator[](int i) const {
            if (N != 1) {
            fprintf(stderr, "Tensor: operator[]: expected 1 dimension, got %d\n", N);
            abort();
            }
            if (i >= shape[0]) {
            fprintf(stderr, "Tensor: out of bounds: %d >= %d\n", i, shape[N-1]);
            abort();
            }
            return data[i];
        }

        float& operator()(int i, int j) const {
            if (N != 2) {
            fprintf(stderr, "Tensor: operator[]: expected 2 dimensions, got %d\n", N);
            abort();
            }
            if (i >= shape[0]) {
            fprintf(stderr, "Tensor: out of bounds: %d >= %d\n", i, shape[N-2]);
            abort();
            }
            if (j >= shape[1]) {
            fprintf(stderr, "Tensor: out of bounds: %d >= %d\n", j, shape[N-1]);
            abort();
            }
            return data[i * shape[1] + j];
        }

        Tensor<N-1> slice(int i) const {
            if (N <= 1) {
                fprintf(stderr, "Tensor: row: expected >1 dimensions, got %d\n", N);
                abort();
            }
            if (i >= shape[0]) {
                fprintf(stderr, "Tensor: out of bounds: %d >= %d\n", i, shape[0]);
                abort();
            }
            // return new tensor with no alloc, so it won't destroy the underlying array
            // when it goes out of scope
            Tensor<N-1> out;
            int stride = 1;
            for (int j = 0; j < N-1; j++) {
            out.shape[j] = shape[j+1];
            stride *= shape[j+1];
            }
            if (data != NULL) {
            out.data = data + i * stride;
            }
            out.alloc = NULL;
            return out;
        }
};

int main(){
    Tensor<1> t1(10);
    Tensor<2> t2(10, 20);

    std::cout << t1.shape[0] << std::endl;
    std::cout << t2.shape[0] << "    " << t2.shape[1] << std::endl;

    std::cout << *t1.data << std::endl;
    std::cout << *t1.alloc << std::endl;

    float nu[5] {1, 2, 3, 4, 5};
    float* ptr = nu;
    Tensor<1> t3(ptr, 5);
    std::cout << t3.shape[0] << std::endl;
    std::cout << "data" << std::endl;
    for(int i = 0; i < t3.shape[0]; i++){
        std::cout << t3[i] << std::endl;
    }

    //check indexing
    std::cout << "indexing" << std::endl;
    std::cout << t3[4] << std::endl;

    //check slicing
    Tensor<2> mat(3, 4);   // shape = [3 rows, 4 cols]
    int x = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            mat(i, j) = x++;
    
    /*
        Matrix mat:
        1   2   3   4
        5   6   7   8
        9  10  11  12
    */
    Tensor<1> row = mat.slice(0);

    std::cout << "Row 1 slice:" << std::endl;
    for (int i = 0; i < row.shape[0]; i++) {
        std::cout << row[i] << " ";
    }
    std::cout << std::endl;
    
}