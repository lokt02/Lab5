#ifndef LAB5_ICOLLECTION_H
#define LAB5_ICOLLECTION_H

#include <iostream>

template<class T>
class ICollection {
public:
    size_t Count;
    ICollection(){
        Count = 0;
    }
//    virtual void Append(T) = 0;
    virtual void Clear() = 0;
    virtual size_t GetLength() const {
        return Count;
    }
};

#endif //LAB5_ICOLLECTION_H
