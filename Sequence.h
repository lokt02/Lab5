//
// Created by lokt on 15.04.2021.
//

#ifndef LAB5_SEQUENCE_H
#define LAB5_SEQUENCE_H

#include <iostream>
#include <memory>
#include "ICollection.h"

template<class T>
class Sequence: public ICollection<T> {
public:
    Sequence() = default;
    ~Sequence() = default;

    virtual T &Get(int) = 0;

    //Decomposition
    T &GetFirst() { return this->Get(0); }

    T &GetLast() { return this->Get(this->GetLength() - 1); }

    void Set(size_t index, T value) {
        this->Get(index) = value;
    }

//    virtual T &Get(size_t index) = 0;

    virtual size_t GetLength() = 0;

    T &operator[](size_t index) { return this->Get(index); }

    //Operations
    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, size_t index) = 0;

    virtual void PopFirst() = 0;

    virtual void PopLast() = 0;

    virtual void RemoveAt(size_t index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> &list) = 0;

    virtual Sequence<T> *Concat(const std::unique_ptr<Sequence<T>> &list) {
        return Concat(*list);
    }

    bool SubSequenceSearch(Sequence<T>* seq)
    {
        bool result = false;
        for (int i = 0; i < this->Count-seq->GetLength(); i++)
        {
            result = true;
            for (int j = 0; j < seq->GetLength(); j++)
            {
                result &= (this->Get(i + j) == seq->Get(j));
            };
            if (result)break;
        }
        return result;
    }
};


#endif //LAB5_SEQUENCE_H
