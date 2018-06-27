#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>

enum
{
    ERRONEOUS_INDEX,
    CREATION_ERROR,
    PUSH_ERROR,
    POP_ERROR
};

const char* const error_list[] = {
        "Incorrect element's number",
        "Couldn't initialize the array",
        "Warning, vector is underflow",
        "Warning, vector is empty"
};

template <typename Data_T>
class Vector {
private:

    size_t current;
    size_t size;
    Data_T* data;

public:
    explicit Vector(size_t _size = 10);

    Vector(const Vector<Data_T> &that);

    Vector(size_t _size, const Data_T &extender);

    Vector(Vector &&that) noexcept;

    void dump();

    void dump(int error);

    void push_back(const Data_T &value);

    void pop_back(Data_T *value = NULL);

    bool print_Elem(int elemNum, std::ostream &out);

    Data_T &operator[](int position);

    void swap(Vector<Data_T> &that);

    Vector<Data_T> &operator=(const Vector &that);

    Vector<Data_T> &operator=(Vector &&that) noexcept;

    ~Vector();
};

template <typename Data_T>
Vector<Data_T>::Vector(size_t _size):
    current(0),
    size(_size),
    data( new Data_T[_size])
{
    if (!data)
        dump(CREATION_ERROR);
}

template <typename Data_T>
Vector<Data_T>::Vector(const Vector<Data_T> &that):
    current(that.current),
    size(that.size),
    data(new Data_T[that.size])
{
    if (!data)
        dump(CREATION_ERROR);

    for(int i = 0; i < size; i++)
        this->data[i] = that.data[i];
}

template <typename Data_T>
Vector<Data_T>::Vector(size_t _size, const Data_T &extender):
    current(0),
    size(_size),
    data(new Data_T[_size])
{
    if (!data)
        dump(CREATION_ERROR);

    for(int i = 0; i < size; i++)
        data[i] = extender;
    current = size;
}

template <typename Data_T>
Data_T &Vector<Data_T>::operator[](int position) {
    try {
        if (position >= size)
            throw 777;

        if (position > current)
            current = (size_t) position;

        return data[position];
    }
    catch (int error) {
        std::cerr << "Error " << error << "[" << position << "]" << std::endl;
        dump(ERRONEOUS_INDEX);
    }

}

template <typename Data_T>
Vector<Data_T>::~Vector() {
    std::cout << "Bye" << std::endl;
    if (data) {
        delete[] data;
    }
}

template <typename Data_T>
Vector<Data_T>::Vector(Vector &&that) noexcept :

        size(that.size),
        current(that.current),
        data(that.data)
{
    that.data = nullptr;
}

template <typename Data_T>

bool Vector<Data_T>::print_Elem(int elemNum, std::ostream &out) {

    return false;
}
#define print_Def(elem_t)                                         \
template <>                                                       \
bool Vector<elem_t>::print_Elem(int elemNum, std::ostream &out) { \
    if (elemNum < size) {                                         \
        out << data[elemNum];                                     \
        return true;                                              \
    }                                                             \
    return false;                                                 \
}                                                                 \

print_Def(int)

print_Def(bool)

print_Def(double)

print_Def(short)

print_Def(char)

print_Def(long long)

print_Def(size_t)

print_Def(float)

print_Def(unsigned)

print_Def(long double)

#undef print_Def

template <typename Data_T>
void Vector<Data_T>::dump() {
    int counter = 0;
    while (print_Elem(counter++, std::cout))
        std::cout << std::endl;
}

template <typename Data_T>
void Vector<Data_T>::dump(int error) {
    std::cerr << error_list[error] << std::endl;
    std::cerr << "Max size of vector is " << size << std::endl;
    std::cerr << "Size of full part is  " << current << std::endl;

    int counter = 0;
    while (print_Elem(counter++, std::cerr))
        std::cerr << std::endl;

}

template <typename Data_T>
void Vector<Data_T>::swap(Vector<Data_T> &that) {
    std::swap(current, that.current);
    std::swap(size, that.size);
    std::swap(data, that.data);
}

template <typename Data_T>
Vector<Data_T> &Vector<Data_T>::operator=(const Vector &that) {
    Vector<Data_T>buffer(that);
    buffer.swap(*this);
}

template <typename Data_T>
Vector<Data_T> &Vector<Data_T>::operator=(Vector &&that) noexcept {
    size = that.size;
    current = that.current;
    data = that.data;
    that.data = nullptr;
}

template<typename Data_T>
void Vector<Data_T>::push_back(const Data_T &value) {
    if (size == current)
        dump(PUSH_ERROR);
    else
        data[size++] = value;
}

template<typename Data_T>
void Vector<Data_T>::pop_back(Data_T *value)
{
    if (current > 0)
        *value = data[--size];
    else
        dump(POP_ERROR);
}


#endif
ok