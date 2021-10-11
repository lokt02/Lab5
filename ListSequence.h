//
// Created by lokt on 15.04.2021.
//
#ifndef LAB5_LISTSEQUENCE_H
#define LAB5_LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> items;


public:
    //Creation of the object
    ListSequence() {
        items = LinkedList<T>();
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(int count) : ListSequence((size_t) count) {}

    explicit ListSequence(size_t count) {
        items = LinkedList<T>(count);
        this->Count = count;
    }

    ListSequence(T *items, size_t count) {
        this->items = LinkedList<T>(items, count);
        this->Count = this->items.GetLength();
    }

    ListSequence(const ListSequence<T> &list) {
        items = LinkedList<T>(list.items);
        this->Count = this->items.GetLength();
    }

    template<size_t N>
    explicit ListSequence(T (&items)[N]) : ListSequence(items, N) {}

    ListSequence(initializer_list<T> items) : ListSequence() {
        for (T item : items)
            this->Append(item);
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(const LinkedList<T> &list) {
        items = LinkedList<T>(list);
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(Sequence<T> &list) : ListSequence((*dynamic_cast<ListSequence<T> *>(&list))) {
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(Sequence<T> *list) : ListSequence(*list) {
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(const ListSequence<T> *list) : ListSequence(*list) {
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(const unique_ptr<Sequence<T>> &list) : ListSequence(list.get()) {
        this->Count = this->items.GetLength();
    }

    explicit ListSequence(const unique_ptr<ListSequence<T>> &list) : ListSequence(*list) {
        this->Count = this->items.GetLength();
    }

    //Decomposition

    T &Get(int index) {
        this->Count = this->items.GetLength();
        return items.Get(index);
    }

    ListSequence<T> *Subsequence(size_t startIndex, size_t endIndex) {
        this->Count = this->items.GetLength();
        if (startIndex < 0 || startIndex >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        if (startIndex > endIndex)
            throw range_error("startIndex > endIndex");
        if (endIndex >= items.GetLength())
            throw range_error("endIndex >= length");
        ListSequence<T> *res = new ListSequence<T>();
        res->items = items.SubList(startIndex, endIndex);
        return res;
    }

    size_t GetLength() {
        this->Count = this->items.GetLength();
        return items.GetLength();
    }

    bool operator==(ListSequence<T> list) {
        this->Count = this->items.GetLength();
        size_t len = list.GetLength();
        if (len != this->items.GetLength())
            return false;
        for (size_t i = 0; i < len; ++i)
            if (this->Get(i) != list.Get(i))
                return false;

        return true;
    }

    //Operations
    void Clear() {
        this->Count = this->items.GetLength();
        while (items.GetLength()) items.PopFirst();
    }

    ListSequence<T> *Clone() const {
        this->Count = this->items.GetLength();
        return new ListSequence<T>(this->items);
    }

    void Append(T item) {
        items.Append(item);
        this->Count = this->items.GetLength();
    }

    void Prepend(T item) {
        items.Prepend(item);
        this->Count = this->items.GetLength();
    }

    void InsertAt(T item, size_t index) {
        items.InsertAt(index, item);
        this->Count = this->items.GetLength();
    }

    void PopFirst() {
        items.PopFirst();
        this->Count = this->items.GetLength();
    }

    void PopLast() {
        items.PopLast();
        this->Count = this->items.GetLength();
    }

    void RemoveAt(size_t index) {
        if (index < 0 || index >= items.GetLength())
            throw range_error("index < 0 or index >= length");
        items.DeleteAt(index);
        this->Count = this->items.GetLength();
    }

    ListSequence<T> *Concat(Sequence<T> &list) {
        ListSequence<T> *res = new ListSequence<T>();
        for (size_t i = 0; i < items.GetLength(); ++i) {
            res->Append(items.Get(i));
        }
        for (size_t i = 0; i < list.GetLength(); ++i) {
            res->Append(list[i]);
        }
        this->Count = this->items.GetLength();
        return res;
    }

    ListSequence<T> *Concat(const Sequence<T> &list) {
        return Concat(dynamic_cast<ListSequence<T>>(list));
    }

    ListSequence<T> *Concat(const ListSequence<T> *list) {
        return Concat(*list);
    }

    ListSequence<T> &operator=(const ListSequence<T> &list) {
        items = LinkedList<T>(list.items);
        this->Count = this->items.GetLength();
        return *this;
    }
};

#endif //LAB5_LISTSEQUENCE_H
