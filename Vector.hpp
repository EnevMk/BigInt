#pragma once

template <typename T>
class Vector {

private:
    T *arr;
    int current;
    int capacity;

    int lastFreeIndex;

public:
    Vector();
    //Vector(const T arr_[], int count);
    Vector(const T *arr_, int count);
    Vector(int len_);
    Vector(const Vector<T> &obj);
    Vector<T>& operator=(const Vector<T> &obj);
    void push(T data);
    void push(T data, int index);
    void popBack();
    void removeAtIndex(const int index);
    //long long sum() const;
    void cutFirstNull();
    void null();
    int size() const;
    int maxCapacity() const;
    int getLastFreeIndex() const;
    void setLastFreeIndex(int ind);
    bool operator==(const Vector<T> &obj) const;
    T& operator[](int index) const;
    T& operator[](int index);
    void reserve(unsigned n);
    ~Vector();
    
};

template class Vector<int>;
template class Vector<double>;
template class Vector<long long>;
