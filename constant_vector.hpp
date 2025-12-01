//
// Created by stepan on 30/11/2025.
//

#ifndef CONSTANT_VECTOR_CONSTANT_VECTOR_HPP
#define CONSTANT_VECTOR_CONSTANT_VECTOR_HPP

template <typename T>
class constant_vector {
    T *data, *resized_data;
    size_t capacity, size = 0, resized_size = 0;

    void transfer() {
        free(data);
        data = resized_data;

        capacity *= 2;
        resized_data = (T*) malloc(2 * capacity * sizeof(T));
    }

public:
    constant_vector() {
        capacity = 1;
        data = (T*) malloc(capacity * sizeof(T));
        resized_data = (T*) malloc(2 * capacity * sizeof(T));
    }

    ~constant_vector() {
        free(data);
        free(resized_data);
    }

    void push_back(const T v) {
        if (size == capacity)
            transfer();

        data[size] = v;
        resized_data[size] = v;
        size++;

        resized_data[resized_size] = data[resized_size];
        resized_size++;
    }

    T& operator[](const size_t i) const {
        return data[i];
    }

    size_t get_capacity() const {
        return capacity;
    }

    void clear() {
        free(data);
        free(resized_data);

        capacity = 1;
        size = 0;
        resized_size = 0;
        data = (T*) malloc(capacity * sizeof(T));
        resized_data = (T*) malloc(2 * capacity * sizeof(T));
    }
};


#endif //CONSTANT_VECTOR_CONSTANT_VECTOR_HPP
