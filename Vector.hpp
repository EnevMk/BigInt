#pragma once

template <typename T>
class Vector {

private:
    T *arr;
    int current;
    int capacity;

public:
    Vector();
    //Vector(const T arr_[], int count);
    Vector(const T *arr_, int count);
    Vector(int len_);
    Vector<T>& operator=(const Vector<T> &obj);
    void push(T data);
    void push(T data, int index);
    void popBack();
    void removeAtIndex(const int index);
    void null();
    int size() const;
    int maxCapacity() const;
    T& operator[](int index) const;
    void reserve(unsigned n);
    ~Vector();
    
};

template class Vector<int>;
template class Vector<double>;
template class Vector<long long>;