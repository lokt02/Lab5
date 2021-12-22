//
// Created by lokt on 15.04.2021.
//

#ifndef LAB5_DYNAMICARRAY_H
#define LAB5_DYNAMICARRAY_H

#include "ICollection.h"
#include <cassert>
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class DynamicArray : public ICollection<T> {
private:
    T *data;
public:
    DynamicArray() {
        data = new T[1];
        this->Count = 0;
    }

    DynamicArray(T *items, int count) {
        if (count < 0) {
            throw std::range_error("Incorrect count of elements");
        }
        data = new T[count];
        this->Count = count;
        if (items != NULL) {
            for (int i = 0; i < this->Count; i++) {
                data[i] = items[i];
            }
        } else {
            for (int i = 0; i < this->Count; i++) {
                data[i] = T();
            }
        }
    }

    explicit DynamicArray(int count) : DynamicArray(NULL, count) {};

    DynamicArray(DynamicArray<T> *dynamicArray) {
        this->Count = dynamicArray->Count;
        data = new T[this->Count];
        for (int i = 0; i < this->Count; i++) {
            data[i] = dynamicArray->Get(i);
        }
    }

    DynamicArray(DynamicArray<T> const &dynamicArray) : DynamicArray() {
        *this = dynamicArray;
    }

    DynamicArray(std::initializer_list<T> items) : DynamicArray() {
        for (T item: items)
            this->Append(item);
    }

    DynamicArray<T> &operator=(const DynamicArray<T> &list) {
        if (&list != this) {
            if (data != nullptr) {
                delete[] data;
                data = nullptr;
            }
            this->Count = list.GetLength();
            if (this->Count > 0) {
                data = new T[this->Count]();
                memcpy(data, list.data, this->Count * sizeof(T));
            } else
                data = new T[1]();
        }
        return *this;
    }

    //Termination
    ~DynamicArray() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    T &operator[](int const index) {
        if (index < 0 || index >= this->Count) {
            throw std::range_error("index out of range");
        }
        return data[index];
    }

    void Set(int index, T value) {
        if (index < 0 || index >= this->Count) {
            throw std::range_error("index out of range");
        }
        data[index] = value;
    }

    T &Get(int index) {
        if (index < 0 || index >= this->Count) {
            throw std::range_error("index out of range");
        }
        return data[index];
    }

    T GetLast() {
        return data[this->Count - 1];
    }

    T GetFirst() {
        return data[0];
    }

    size_t GetSize() {
        return this->Count;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::range_error("new size cannot be lower 0");
        }
        T *newData = new T[newSize];
        size_t tempSize = 0;
        tempSize = (newSize > this->Count) ? this->Count : newSize;
        for (int i = 0; i < tempSize; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        this->Count = newSize;
    }

    void ResizeRight(int newSize) {
        assert(newSize > 0);
        T *newData = new T[newSize];
        size_t tempSize = 0;
        tempSize = (newSize > this->Count) ? this->Count : newSize;
        for (int i = 0; i < tempSize; i++)
            newData[i + newSize - this->Count] = data[i];
        delete[] data;
        data = newData;
        this->Count = newSize;
    }

    void Append(T item) {
        this->Resize(this->GetSize() + 1);
        this->Set(this->GetSize() - 1, item);
    }

    DynamicArray<T> *Clone() const {
        return new DynamicArray<T>(this->items);
    }

    template<typename T1>
    DynamicArray<T1> *Init() const {
        return new DynamicArray<T1>();
    }

    template<typename T1>
    DynamicArray<T1> *Init(int count) const {
        return new DynamicArray<T1>(count);
    }

    DynamicArray<T> GetSubArray(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= this->Count)
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= this->Count)
            throw range_error("endIndex >= length");
        const size_t len = endIndex - startIndex + 1;

        T *arr = new T[len];
        memcpy(arr, this->data + startIndex, len * sizeof(T));
        auto res = DynamicArray(arr, len);
        delete[] arr;
        return res;
    }

    void Clear() {
        delete[] data;
        data = new T[1];
        this->Count = 0;
    };
};


#endif //LAB5_DYNAMICARRAY_H
