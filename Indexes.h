#ifndef LAB5_INDEXES_H
#define LAB5_INDEXES_H

#include "Dictionary.h"

template <class T, class R>
class Indexes{
private:
    Dictionary<T, R> dictionary;
public:
    Indexes()=0;
    Indexes(Sequence<R>* a, std::function<T(R)> const & indexer){
        for(int i = 0; i < a->GetLength(); i++){
            T index = indexer(a->Get(i));
            dictionary.Add(index, a->Get(i));
        }
    }
    Dictionary<T, R> ReturnIndexed(){
        return dictionary;
    }
};

#endif //LAB5_INDEXES_H
