#ifndef LAB5_IDICTIONARY_H
#define LAB5_IDICTIONARY_H

template<typename TKey, typename TValue>
class IDictionary{
public:
    virtual size_t GetCount() = 0;
    virtual void Add(TKey, TValue) = 0;
    virtual void Remove(TKey) = 0;
    virtual TValue &Get(TKey) = 0;
    virtual bool ContainsKey(TKey) = 0;
};

#endif //LAB5_IDICTIONARY_H
