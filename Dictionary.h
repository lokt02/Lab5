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
            return value <= pair.value;
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
    size_t count;
public:
    Dictionary(){
        items = Set<Pair>();
        count = 0;
    }

    size_t GetCount() override{
        return count;
    }

    bool ContainsKey(TKey key) override{
        auto array = items.ToArray();
        for(int i = 0; i < array.GetLength(); i++){
            if(array.Get(i).key == key) return true;
        }
        return false;
    }

    void Add(TKey key, TValue value){
        auto array = items.ToArray();
        for(int i = 0; i < array.GetLength(); i++){
            if(array.Get(i).key == key) throw std::range_error("This KEY already exists!");
        }
        items.Add(Pair(key, value));
        count++;
    }

    void Remove(TKey key){
        TValue value = Get(key);
        Set<Pair> set = Set<Pair>();
        set.Add(Pair(key, value));
        items.Substraction(set);
        count--;
        //items.Delete(Pair(key, value));
    }

    TValue &Get(TKey key){
        auto array = items.ToArray();
        TValue value;
        for(int i = 0; i < array.GetLength(); i++){
            if(array.Get(i).key == key) value = array.Get(i).value;
        }
        if(items.GetValue(Pair(key, value)))
            return items.GetValue(Pair(key, value))->value;
        else
            throw std::runtime_error("This KEY does not exists!");
            // return *value;
            // throw std::range_error("This KEY does not exists!");
        // throw std::range_error("This KEY does not exists!");
    }

    TValue& operator[](TKey key){
        // TValue value = Get(key);
        // auto pair = Pair(key, value);
        // return items.GetValue(Pair(key, value)).value;
        return Get(key);
    }

    bool operator==(Dictionary<TKey, TValue> dictionary){
        return items.IsEqual(dictionary.items);
    }

    void Display(){
        items.Display();
    }
};

#endif //LAB5_DICTIONARY_H
