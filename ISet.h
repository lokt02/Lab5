//
// Created by lokt0 on 11.10.2021.
//

#ifndef LAB5_ISET_H
#define LAB5_ISET_H

template<typename T>
class ISet{
public:
    virtual ISet<T> Union(ISet<T>) = 0;
    virtual ISet<T> Intersection(ISet<T>) = 0;
    virtual ISet<T> Substraction(ISet<T>) = 0;
    virtual bool IsEqual(ISet<T>) = 0;
    virtual void Add(T) = 0;
    virtual void Delete(T) = 0;
    virtual bool Contains(T) = 0;
};

#endif //LAB5_ISET_H
