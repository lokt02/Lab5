//
// Created by lokt on 15.04.2021.
//

#ifndef LAB5_ARRAYSEQUENCE_H
#define LAB5_ARRAYSEQUENCE_H
#include "Sequence.h"
#include "DynamicArray.h"
#include <iostream>
#include <cstring>

template<class T>
class ArraySequence: public Sequence<T> {
private:
    DynamicArray<T> items;
public:
    ArraySequence(){
        items = DynamicArray<T>();
    };
    ArraySequence(T* items, int count){
        this->items = DynamicArray<T>(items, count);
    };
    explicit ArraySequence(DynamicArray<T> &list){
        items = list;
    };
    explicit ArraySequence(int count) : ArraySequence() {
        if (count < 0)
            throw std::out_of_range("count < 0");
        if (count > 0) {
            for (size_t i = 0; i < count; ++i) {
                items.Append(T());
            }
            this->Count = count;
        }
    }
    template<size_t N>
    explicit ArraySequence(T (&items)[N]) : ArraySequence(items, N) {}

    ArraySequence(std::initializer_list<T> items) : ArraySequence() {
        for (T item : items)
            this->Append(item);
    }

    ArraySequence(ArraySequence<T> const &list) {
        items = DynamicArray<T>(list.items);
        this->Count = items.Count;
    }

    explicit ArraySequence(Sequence<T> &list) : ArraySequence(dynamic_cast<ArraySequence<T> &>(list)) {
    }

    explicit ArraySequence(Sequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const ArraySequence<T> *list) : ArraySequence(*list) {
    }

    explicit ArraySequence(const std::unique_ptr<Sequence<T>> &list) : ArraySequence(list.get()) {
    }

    explicit ArraySequence(const std::unique_ptr<ArraySequence<T>> &list) : ArraySequence(*list) {
    }

    ~ArraySequence(){

    }

    T &Get(int index)
    {
        return items.Get(index);
    }

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex)
    {
        items->GetSubsequence(startIndex, endIndex);
        this->Count = items.Count;
        return this;
    }
    size_t GetLength()
    {
        return items.GetSize();
    }
    void Set(int index, T value)
    {
        items.Set(index, value);
        this->Count = items.Count;
    }

    void Append(T item)
    {
        items.Resize(items.GetSize() + 1);
        items.Set(items.GetSize() - 1, item);
        this->Count = items.Count;
    }

    void Prepend(T item)
    {
        items.ResizeRight(items.GetSize() + 1);
        items.Set(0, item);
        this->Count = items.Count;
    }

    bool operator==(ArraySequence<T> &list) {
        size_t len = list.GetLength();
        if (len != this->items.GetLength())
            return false;
        for (size_t i = 0; i < len; ++i)
            if (this->Get(i) != list.Get(i))
                return false;

        return true;
    }

    template<typename T1>
    ArraySequence<T1> *Init() const {
        return new ArraySequence<T1>();
    }

    template<typename T1>
    ArraySequence<T1> *Init(size_t count) const {
        return new ArraySequence<T1>(count);
    }

    void InsertAt(T item, size_t index) {
        items.Resize(items.GetLength() + 1);

        for (size_t i = items.GetLength() - 1; i > index; --i) {
            items.Set(i, items[i - 1]);
        }
        if (items.GetLength() - 2 != index)
            items.Set(index, item);
        else
            items.Set(items.GetLength() - 1, item);
        this->Count = items.Count;
    }

    ArraySequence<T> *Concat(Sequence<T> &list) {
        ArraySequence<T> *res = new ArraySequence<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items[i]);
        }
        for (size_t i = 0; i < list.GetLength(); ++i) {
            res->Append(list[i]);
        }
        return res;
    }

    ArraySequence<T> *Subsequence(size_t startIndex, size_t endIndex) {
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ArraySequence<T> *res = new ArraySequence<T>();
        res->items = items.GetSubArray(startIndex, endIndex);
        this->Count = items.Count;
        return res;
    }

    void PopFirst() {
        for (size_t i = 0; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
        this->Count = items.Count;
    }

    void PopLast() {
        items.Resize(items.GetLength() - 1);
        this->Count = items.Count;
    }

    void RemoveAt(size_t index) {
        if (index < 0 || index >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        for (size_t i = index; i < items.GetLength() - 1; ++i) {
            items.Set(i, items[i + 1]);
        }
        items.Resize(items.GetLength() - 1);
        this->Count = items.Count;
    }

    void Clear() {
        items.Resize(0);
        this->Count = items.Count;
    }
    ArraySequence<T> *Clone() const {
        return new ArraySequence<T>(this);
    }

    ArraySequence<T> *Concat(const Sequence<T> &list) {
        return Concat(dynamic_cast<ArraySequence<T>>(list));
    }

    ArraySequence<T> *Concat(const ArraySequence<T> *list) {
        return Concat(*list);
    }

    ArraySequence<T> &operator=(const ArraySequence<T> &list) {
        items = DynamicArray<T>(list.items);
        this->Count = items.Count;
        return *this;
    }
};


#endif //LAB5_ARRAYSEQUENCE_H
