#ifndef LAB5_CACHE_H
#define LAB5_CACHE_H

#include "Dictionary.h"
#include "HashTable.h"

template<class T>
class Cache{
private:
    Dictionary<T, unsigned long> cache;
    int length{};

    void RemoveUnused(){
        unsigned long x = MostUnused();
        T unused_req = DataOfRequest(x);
        cache.Remove(unused_req);
    }

    T DataOfRequest(unsigned long req){
        return cache.FindByValue(req);
    }

    int NumberOfRequest(T data){
        return cache.FindByValue(data);
    }

    unsigned long MostUnused(){
        unsigned long min = -1;
        cache.Map([&](Pair<T, unsigned long> pair){
            if(pair.value < min){
                min = pair.value;
            }
            return pair;
        });

        return min;
    }

public:
    Cache() = default;;
    explicit Cache(int length) : Cache(){
        this->length = length;
    }
    Cache(std::initializer_list<T> list){
        for(int i = 0; i < list.size(); i++){
            Add(list[i]);
        }
    }
    Cache(std::initializer_list<T> list, int length) : Cache(length){
        for(int i = 0; i < list.size(); i++){
            Add(list[i]);
        }
    }

    void Add(T data){
        if(cache.ContainsKey(data)){
            int q = cache[data];
            cache.Remove(data);
            cache.Add(data, q + 1);
        }
        else{
            if(length > cache.GetCount()){
                cache.Add(data, 1);
            }
            else{
                RemoveUnused();
                cache.Add(data, 1);
            }
        }
    }

    Dictionary<T, unsigned long> GetCache(){
        return cache;
    }
};

#endif //LAB5_CACHE_H
