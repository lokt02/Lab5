#ifndef LAB5_DICTIONARY_H
#define LAB5_DICTIONARY_H

#include "IDictionary.h"
#include "Set.h"

template<typename TKey, typename TValue>
class Dictionary: public IDictionary<TKey, TValue>{
protected:
    class Pair{
    public:
        TKey key;
        TValue value;
        Pair(){
            key = TKey();
            value = TValue();
        }
        Pair(TKey key, TValue value){
            this->key = key;
            this->value = value;
        }
        bool operator==(Pair pair){
            return key == pair.key && value == pair.value;
        }
        bool operator!=(Pair pair){
            return key != pair.key || value != pair.value;
        }
        bool operator>(Pair pair){
            return value > pair.value;
        }
        bool operator<(Pair pair){
            return value < pair.value;
        }
        bool operator>=(Pair pair){
            return value >= pair.value;
        }
        bool operator<=(Pair pair){
            return value <= pair.value;
        }
        friend ostream& operator<<(ostream &out, const Pair& pair){
            out << "key: ";
            out << pair.key;
            out << "; ";
            out << "value: ";
            out << pair.value;
            return out;
        }
    };
private:
    Set<Pair> items;

public:
    Dictionary(){
        items = Set<Pair>();
    }

    void Add(TKey key, TValue value){
        items.Add(Pair(key, value));
    }

    void Remove(TKey key){
        TValue value = Get(key);
        items.Delete(Pair(key, value));
    }

    TValue &Get(TKey key){
        auto array = items.ToArray();
        for(int i = 0; i < array.GetLength(); i++){
            if(array.Get(i).key == key) return array.Get(i).value;
        }
        throw std::range_error("This KEY does not exists!");
    }

    TValue& operator[](TKey key){
        TValue value = Get(key);
        // auto pair = Pair(key, value);
        return items.GetValue(Pair(key, value)).value;
    }

    bool operator==(Dictionary<TKey, TValue> dictionary){
        return items.IsEqual(dictionary.items);
    }

    void Display(){
        items.Display();
    }
};

#endif //LAB5_DICTIONARY_H
