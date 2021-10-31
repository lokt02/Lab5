//
// Created by lokt0 on 23.05.2021.
//

#ifndef LAB5_SET_H
#define LAB5_SET_H

#include "BinaryTree.h"
#include "ArraySequence.h"
#include "SequenceSorter.h"
#include "ISet.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Set: public ISet<T>{
private:
    Tree<T> tree;
protected:
    Tree<T> GetTree(){
        return tree;
    }

public:
    Set() {
        tree = Tree<T>();
    };
    Set(initializer_list<T> items){
        for(T item : items){
            this->Add(item);
        }
    }
    explicit Set(Tree<T> newTree){
        tree = newTree;
    }
    explicit Set(Set<T>* set){
        tree = Tree<T>(set->tree);
    }
    Set(const Set& set): Set(){
        tree = Tree<T>(set.tree);
    }

    void Add(T value){
        tree.Append(value);
    }

    void Delete(T value){
        tree.Remove(value);
    }
    bool Contains(T value){
        return tree.Search(value);
    }
    template<typename T1>
    Set<T1> MapSet(T1(*mapper)(T)){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Tree<T1> newTree = tree.Map(mapper);
        Set<T1> newSet = Set<T1>(newTree);
        return newSet;
    }

    Set<T> Map(std::function<T(T)> const & mapper){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Tree<T> newTree = tree.Map(mapper);
        Set<T> newSet = Set<T>(newTree);
        return newSet;
    }
    Set<T> WhereSet(bool(*predicate)(T)){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Tree<T> newTree = tree.Where(predicate);
        Set<T> newSet = Set<T>(newTree);
        return newSet;
    }
    Set<T> Where(std::function<bool(T)> const & predicate){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Tree<T> newTree = tree.Where(predicate);
        Set<T> newSet = Set<T>(newTree);
        return newSet;
    }
    T ReduceSet(T(*reducer)(T, T), T const &c){
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = tree.Reduce(reducer, c);
        return res;
    }

    ISet<T>* Intersection(ISet<T> &set){
        Set<T>* result = new Set<T>();
        this->tree.Map([&](T item){
            if(set.Contains(item)){
                result->Add(item);
            }
            return item;
        });
        // return IntersectionPath(((Set<T>&)set).root, this->root);
        return result;
    }

    ISet<T>* Union(ISet<T> &set) {
        Set<T>* result = new Set<T>((Set<T> &)set);
        //UnionPath(((Set<T>&)set).root, result);
        this->GetTree().Map([&](T item){
            result->Add(item);
            return item;
        });
        return result;
    }

    ISet<T>* Substraction(ISet<T>& set){
        Set<T>* result = new Set<T>(*this);
        this->tree.Map([&](T item){
            if(set.Contains(item)){
                result->Remove(item);
            }
            return item;
        });
        // return SubstractionPath(((Set<T>&)set).root, this->root, *this);
        return result;
    }

    void Remove(T item){
        tree.Remove(item);
    }

    ArraySequence<T> ToArray(){
        ArraySequence<T> res = ArraySequence<T>();
        // GetPath(this->root, &res);
        tree.Map([&res](T item){
            res.Append(item);
            return item;
        });
        SequenceSorter<T>::QuickSort(&res);
        return res;
    }

    bool IsEqual(const ISet<T> &set){
        auto array = ((Set<T> *)(&set))->ToArray();
        auto myArray = this->ToArray();
        return myArray == array;
        // return IsEqualNode(((Set<T>&)set).root, this->root);
    }

    bool IsSubSet(Set<T> set){
        auto array = set.ToArray();
        bool isSub = true;
        for(int i = 0; i < array.Count; i++){
            if(!Contains(array[i])){
                isSub = false;
            }
        }
        // auto myArray = this->ToArray();
        // return SubSetPath(set.root, this->root, set);
        // return myArray.SubSequenceSearch(&array);
        return isSub;
    }

    bool operator==(Set<T> set){
        return IsEqual(set);
    }
    Set<T>* operator&(Set<T> set){
        return (Set<T>*)Intersection(set);
    }
    Set<T>* operator|(Set<T> set){
        return (Set<T>*)Union(set);
    }
    Set<T>* operator-(Set<T> set){
        return (Set<T>*)Substraction(set);
    }

    T* GetValue(T value){
        return tree.GetValue(value);
    }

    void Display(){
        cout << "(";
        tree.Map([](T item){
            cout << item << ", ";
            return item;
        });
        // if(this->root) DisplayNode(this->root);
        cout << ")\n";
    }
    void Display(bool isList){
        cout << "(\n";
        tree.Map([](T item){
            cout << item << ",\n";
            return item;
        });
        // if(this->root) DisplayNode(this->root, isList);
        cout << ")\n";
    }
};

#endif //LAB5_SET_H
