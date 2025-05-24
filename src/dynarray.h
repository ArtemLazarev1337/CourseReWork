#pragma once

#include <cstddef>
#include <ostream>

template <typename T>
class DynamicArray {
    private:
        size_t capacity;
        size_t size;
        T* array;
    public:
        DynamicArray(): capacity(10), size(0), array(new T[capacity]) {}

        DynamicArray(const DynamicArray& a): capacity(a.capacity), size(a.size), array(new T[capacity]) {
            for (size_t i = 0; i < size; ++i)
                array[i] = a.array[i];
        }

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
            if (size > 0)
                size--;
        }

        void clear() {
            delete[] array;
            capacity = 10;
            size = 0;
            array = new T[capacity];
        }

        size_t getSize() const {
            return size;
        }

        bool empty() const {
            return size == 0;
        }

        void removeAt(size_t index) {
            if (index < size) {
                for (size_t i = index + 1; i < size; ++i)
                    array[i - 1] = array[i];
                --size;
            }
        }

        T* getAddress() const {
            return array;
        }

        T& operator[](size_t i) const {
            return array[i];
        }

        DynamicArray& operator=(const DynamicArray& a) {
            capacity = a.capacity;
            size = a.size;
            delete[] array;
            array = new T[capacity];
            for (size_t i = 0; i < size; ++i)
                array[i] = a.array[i];
            return *this;
        }

        bool operator==(const DynamicArray& a) const {
            if (size != a.size) return false;
            for (size_t i = 0; i < size; ++i)
                if (array[i] != a.array[i]) return false;
            return true;
        }

        friend std::ostream& operator<<(std::ostream& out, const DynamicArray& a) {
            out << "[";
            if (a.size > 0) {
                for (size_t i = 0; i < a.size - 1; ++i)
                    out << a.array[i] << ", ";
                out << a.array[a.size - 1];
            }
            out << "]";
            return out;
        }
};
