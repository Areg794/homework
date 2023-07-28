#include <iostream>

template<typename T>
class Array {
private:
    T* ptr;
    int size;
    int capacity;

public:
    Array(int size) : size(size), capacity(size) {
        ptr = new T[capacity];
    }

    virtual ~Array() {
        delete[] ptr;
    }

    
    Array(const Array& other) : size(other.size), capacity(other.capacity) {
        ptr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
    }

   
    Array& operator=(const Array& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr;
        size = other.size;
        capacity = other.capacity;
        ptr = new T[capacity];
        for (int i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
        return *this;
    }

    Array(Array&& other) : ptr(other.ptr), size(other.size), capacity(other.capacity) {
        other.ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(Array&& other) {
        if (this == &other) {
            return *this;
        }
        delete[] ptr;
        ptr = other.ptr;
        size = other.size;
        capacity = other.capacity;
        other.ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
        return *this;
    }
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return ptr[index];
    }
    int getSize() const {
        return size;
    }
public:
    void push_back(const T& value) {
        if (size == capacity) {
            capacity++;
            T* newPtr = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newPtr[i] = ptr[i];
            }
            delete[] ptr;
            ptr = newPtr;
        }
        ptr[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }
};

int main() {
    Array<int> intArray(3);
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);
    intArray.pop_back();

    for (int i = 0; i < intArray.getSize(); ++i) {
        std::cout << intArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}