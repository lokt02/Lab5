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
        Pair() = default;
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
            return key > pair.key;
        }
        bool operator<(Pair pair){
            return key < pair.key;
        }
        bool operator>=(Pair pair){
            return key >= pair.key;
        }
        bool operator<=(Pair pair){
            return key <= pair.key;
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
        // Set<Pair> set = Set<Pair>();
        // set.Add(Pair(key, value));
        items.Remove(Pair(key, value));
        // items.Substraction(set);
        count--;
        //items.Delete(Pair(key, value));
    }

    TValue &Get(TKey key){
        TValue value;
        items.Map([&](Pair pair){
            if(pair.key == key){
                value = pair.value;
            }
            return pair;
        });
        Pair * pair = items.GetValue(Pair(key, value));
        if(pair){
            return pair->value;
        }
        throw std::runtime_error("This KEY does not exists!");
    }

    TValue& operator[](const TKey &key){
        return Get(key);
    }

    TKey FindByValue(const TValue& value){
        TKey key;
        int count = 0;
        items.Map([&](Pair pair){
            if(pair.value == value){
                key = pair.key;
                count++;
            }
            return pair;
        });
        if(count == 0) std::runtime_error("Value with this KEY does not exists!");
        return key;
    }

    bool operator==(Dictionary<TKey, TValue> dictionary){
        if(GetCount() == 0 && dictionary.GetCount() == 0) return true;
        return items.IsEqual(dictionary.items);
    }

    Dictionary Map(std::function<Pair(TKey, TValue)> const & mapper){
        Dictionary<TKey, TValue> newDict = Dictionary<TKey, TValue>();
        newDict.items = items.Map(mapper);
        return newDict;
    }
};

#endif //LAB5_DICTIONARY_H
