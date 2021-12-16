#ifndef LAB5_HASHTABLE_H
#define LAB5_HASHTABLE_H

#include "IDictionary.h"
#include "Dictionary.h"

template<class T, size_t size>
struct Hash{
    unsigned long int operator()(const T& value) const {
        return reinterpret_cast<unsigned long>(value) % size;
    }
};

template<class T, typename F = Hash<T, 100>>
class HashTable : IDictionary<unsigned long int, T>{
private:
    Dictionary<unsigned long int, T> table;
    F HashFunction;
public:
    HashTable(){
        table = Dictionary<unsigned long int, T>();
    }

    size_t GetCount(){
        return table.GetCount();
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

    void Remove(unsigned long key){
        table.Remove(key);
    }

    T &Get(unsigned long key){
        return table[key];
    }

    bool ContainsKey(unsigned long key){
        return table.ContainsKey(key);
    }

    Dictionary<unsigned long, T> ToDictionary(){
        return table;
    }
};

#endif //LAB5_HASHTABLE_H
