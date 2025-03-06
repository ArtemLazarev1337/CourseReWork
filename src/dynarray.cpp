#include <cstddef>

template <typename T>
class DynamicArray {
    private:
        size_t capacity;
        size_t size;
        T* array;
    public:
        DynamicArray(): capacity(10), size(0), array(new T[capacity]) {}

        ~DynamicArray() {
            delete[] array;
        }

        void push_back(const T& value) {
            if (size == capacity) {
                capacity *= 2;
                T* t = new T[capacity];
                for (size_t i = 0; i < size; ++i)
                    t[i] = array[i];
                delete[] array;
                array = t;
            }
            array[size] = value;
            ++size;
        }

        void pop_back() {
            if (size > 0) {
                size--; // ?
            }
        }

        void clear() {
            delete[] array;
            capacity = 10;
            size = 0;
            array = new T[capacity];
        }

        size_t getSize() {
            return size;
        }

        bool empty() {
            return size == 0;
        }

        void removeAt(size_t index) {
            if (index < size) {
                for (size_t i = index + 1; i < size; ++i) {
                    array[i - 1] = array[i];
                }
                --size;
            }
        }

        T& operator[](size_t i) {
            return array[i];
        }
};
