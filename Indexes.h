#ifndef LAB5_INDEXES_H
#define LAB5_INDEXES_H

#include "Dictionary.h"
#include "ArraySequence.h"

template <class T, class R>
class Indexes{
private:
    Dictionary<T, R> dictionary;
    ArraySequence<R> array;
    std::function<T(R)> indexer;
public:
    Indexes()=default;
    Indexes(Sequence<R>* a, std::function<T(R)> const & indexer){
        for(int i = 0; i < a->GetLength(); i++){
            T index = indexer(a->Get(i));
            dictionary.Add(index, a->Get(i));
        }
    }
    Indexes(std::initializer_list<R> a, std::function<T(R)> const & indexer){
        for(int i = 0; i < a->GetLength(); i++){
            T index = indexer(a->Get(i));
            dictionary.Add(index, a->Get(i));
        }
    }
    Indexes(std::function<T(R)> const & indexer){
        this->indexer = indexer;
    }

    void AddData(R data){
        array.Append(data);
    }

    void BuildIndexed(){
        dictionary = Dictionary<T, R>();
        for(int i = 0; i < array.GetLength(); i++){
            T index = indexer(array.Get(i));
            dictionary.Add(index, array.Get(i));
        }
    }

    Dictionary<T, R> ReturnIndexed(){
        return dictionary;
    }
};

#endif //LAB5_INDEXES_H
