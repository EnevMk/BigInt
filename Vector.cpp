#include "Vector.hpp"
#include "BigInt.hpp"

template class Vector<BigInt>;

template <typename T>
Vector<T>::Vector() {
    arr = new T[1];
    current = 0;
    capacity = 1;
    lastFreeIndex = 0;
}

/* template <typename T>
Vector<T>::Vector(const T arr_[], int count) {
    arr = new T[count];

    for (int i = 0; i < count; ++i) {
        arr[i] = arr_[i];
    }

    current = count;
    capacity = count;
}

 */template <typename T>
Vector<T>::Vector(const T *arr_, int count) {
    arr = new T[count];

    capacity = count;
    current = count;
    lastFreeIndex = -1;

    for (int i = 0; i < current; ++i) {
        arr[i] = arr_[i];
    }
}

template <typename T>
Vector<T>::Vector(int len_) {
    arr = new T[len_];
    capacity = len_;
    current = 0;
    lastFreeIndex = capacity - 1;
}

template <typename T>
Vector<T>::Vector(const Vector<T> &obj) {
    current = obj.current;
    capacity = obj.capacity;
    lastFreeIndex = obj.lastFreeIndex;

    arr = new T[capacity];

    for (int i = 0; i < current; ++i) {
        arr[i] = obj.arr[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &obj) {
    if(this != &obj) {
        capacity = obj.capacity;
        current = obj.current;
        lastFreeIndex = obj.lastFreeIndex;
        delete[] arr;
        arr = new T[capacity];

        for (int i = 0; i < current; ++i) {
            arr[i] = obj.arr[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {

    delete[] arr;
    current = 0;
    capacity = 0;
    lastFreeIndex = -1;
}


template <typename T>
void Vector<T>::push(T data) {
    if (current == capacity) {
        T *temp = new T[2 * capacity];

        for (int i = 0; i < current; ++i) {
            temp[i] = arr[i];
        }

        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    arr[current] = data;
    current++;

}

template <typename T>
void Vector<T>::push(T data, int index) {
    /* if (current == capacity) {
        T *temp = new T[2 * capacity];

        for (int i = 0; i < capacity; ++i) {
            temp[i] = arr[i];
        }

        delete[] arr;
        capacity *= 2;
        arr = temp;
    }
    arr[current++] = data; */

    if (index >= 0 && index < capacity) {
        arr[index] = data;
        current++;
    }
}

template <typename T>
void Vector<T>::popBack() {
    current--;
}

template <typename T>
void Vector<T>::removeAtIndex(const int index) {
    if (index < size()) {
        for (int i = index; i < size() - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        current--;
    }
}

/* template <>
long long Vector<int>::sum() const {
    int len = size();
    long long prod = 1;

    for (int i = 0; i < len; ++i) {
        prod *= arr[i];
    }

    return prod;
} */

template<>
void Vector<long long>::cutFirstNull() {
    if (arr[0] == 0) {
        
        long long *newArr = new long long[capacity - 1];
        for (int i = 0; i < capacity - 1; ++i) {
            newArr[i] = arr[i + 1];
        }
        capacity--;
        current = capacity;
        delete[] arr;
        arr = newArr;
    }
    
}

template <typename T>
int Vector<T>::size() const{
    return current;
}

template <typename T>
int Vector<T>::maxCapacity() const {
    return capacity;
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
    return *(arr + index);
}

template <typename T>
T& Vector<T>::operator[](int index) {
    return *(arr + index);
}

template <typename T>
void Vector<T>::reserve(unsigned n) {
    if (n > capacity) {
        T *temp = new T[n];

        for (int i = 0; i < current; ++i) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        capacity = n;
        lastFreeIndex = capacity - 1;
    }
}

template <>
void Vector<long long>::null() {
    for (int i = 0; i < this->maxCapacity(); ++i) {
        arr[i] = 0;
    }
}

template <typename T>
int Vector<T>::getLastFreeIndex() const {
    return lastFreeIndex;
}

template <typename T>
void Vector<T>::setLastFreeIndex(int ind) {
    
    lastFreeIndex = ind;

}

template <>
bool Vector<long long>::operator==(const Vector<long long> &obj) const {
    
    for (int i = 0; i < this->size(); ++i) {

        if (arr[i] != obj.arr[i]) {
            return false;
        }
    }
    return this->size() == obj.size();
}