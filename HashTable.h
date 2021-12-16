#ifndef LAB5_HASHTABLE_H
#define LAB5_HASHTABLE_H

#include "IDictionary.h"
#include "Dictionary.h"

template<class T, size_t size>
struct Hash : IDictionary<unsigned long int, T>{
    unsigned long int operator()(const T& value) const {
        return reinterpret_cast<unsigned long>(value) % size;
    }
};

template<class T, size_t size = 10, typename F = Hash<T, size>>
class HashTable{
private:
    Dictionary<unsigned long int, T> table;
    F HashFunction;
public:
    HashTable(){
        table = Dictionary<unsigned long int, T>();
    }

    void Add(T value){
        auto key = HashFunction(value);
        if(table.ContainsKey(key)){
            // Collision
        }
        else {
            table.Add(key, value);
        }
    }

    T &Get(unsigned long key){
        return table[key];
    }

    size_t GetCount(){
        return table.GetCount();
    }

    void Remove(unsigned long key){
        table.Remove(key);
    }

    bool ContainsKey(unsigned long key){
        return table.ContainsKey(key);
    }
};

#endif //LAB5_HASHTABLE_H
