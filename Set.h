//
// Created by lokt0 on 23.05.2021.
//

#ifndef LAB5_SET_H
#define LAB5_SET_H

#include "BinaryTree.h"
#include "ArraySequence.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Set: public Tree<T>{
protected:
    using Node = typename Tree<T>::Node;
    void UnionPath(Node* node, Set<T> *set){
        if(node) {
            set->Add(node->key);
            UnionPath(node->left, set);
            UnionPath(node->right, set);
        }
    }

    Set<T> IntersectionPath(Node *root1, Node *root2)
    {
        // Create two stacks for two inorder traversals
        Set<T> result = Set<T>();
        ArraySequence<Node *> s1, s2;

        while (true)
        {
            // push the Nodes of first tree in stack s1
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }

                // push the Nodes of second tree in stack s2
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }

                // Both root1 and root2 are NULL here
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();

                // If current keys in two trees are same
                if (root1->key == root2->key)
                {
                    result.Append(root1->key);
                    s1.PopLast();
                    s2.PopLast();

                    // move to the inorder successor
                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    // If Node of first tree is smaller, than that of
                    // second tree, then its obvious that the inorder
                    // successors of current Node can have same value
                    // as that of the second tree Node. Thus, we pop
                    // from s2
                    s1.PopLast();
                    root1 = root1->right;

                    // root2 is set to NULL, because we need
                    // new Nodes of tree 1
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }

                // Both roots and both stacks are empty
            else  break;
        }
        return result;
    }

    Set<T> SubstractionPath(Node *root1, Node *root2, Set<T> set)
    {
        // Create two stacks for two inorder traversals
        Set<T> result = Set<T>(set);
        ArraySequence<Node *> s1, s2;

        while (true)
        {
            // push the Nodes of first tree in stack s1
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }

                // push the Nodes of second tree in stack s2
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }

                // Both root1 and root2 are NULL here
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();

                // If current keys in two trees are same
                if (root1->key == root2->key)
                {
                    result.Delete(root1->key);
                    s1.PopLast();
                    s2.PopLast();

                    // move to the inorder successor
                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    // If Node of first tree is smaller, than that of
                    // second tree, then its obvious that the inorder
                    // successors of current Node can have same value
                    // as that of the second tree Node. Thus, we pop
                    // from s2
                    s1.PopLast();
                    root1 = root1->right;

                    // root2 is set to NULL, because we need
                    // new Nodes of tree 1
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }

                // Both roots and both stacks are empty
            else  break;
        }
        return result;
    }

    bool SubSetPath(Node *root1, Node *root2, Set<T> set)
    {
        Set<T> result = Set<T>();
        ArraySequence<Node *> s1, s2;
        while (true)
        {
            if (root1)
            {
                s1.Append(root1);
                root1 = root1->left;
            }
            else if (root2)
            {
                s2.Append(root2);
                root2 = root2->left;
            }
            else if (s1.GetLength() > 0 && s2.GetLength() > 0)
            {
                root1 = s1.GetLast();
                root2 = s2.GetLast();

                if (root1->key == root2->key)
                {
                    result.Append(root1->key);
                    s1.PopLast();
                    s2.PopLast();

                    root1 = root1->right;
                    root2 = root2->right;
                }

                else if (root1->key < root2->key)
                {
                    s1.PopLast();
                    root1 = root1->right;
                    root2 = NULL;
                }
                else if (root1->key > root2->key)
                {
                    s2.PopLast();
                    root2 = root2->right;
                    root1 = NULL;
                }
            }
            else  break;
        }
        return set.IsEqual(result);
    }

    bool IsEqualNode(Node* node1, Node* node2){
        if(node1 && node2){
            if(node1->key == node2->key){
                bool result = IsEqualNode(node1->left, node2->left) && IsEqualNode(node1->right, node2->right);
                return result;
            }
            else{
                return false;
            }
        }
        if(!node1 && !node2){
            return true;
        }
        return false;
    }

    void DisplayNode(Node* node){
        if(node){
            DisplayNode(node->left);
            cout << node->key << ", ";
            DisplayNode(node->right);
        }
    }
    void DisplayNode(Node* node, bool isList){
        if(node){
            if(!isList) {
                DisplayNode(node->left);
                cout << node->key << ", ";
                DisplayNode(node->right);
            }
            else{
                DisplayNode(node->left, isList);
                cout << node->key << "\n";
                DisplayNode(node->right, isList);
            }
        }
    }

    void GetPath(Node* node, ArraySequence<T> *array){
        if(node){
            array->Append(node->key);
            if(node->left) GetPath(node->left, array);
            if(node->right) GetPath(node->right, array);
        }
    }
public:
    Set() = default;
    Set(initializer_list<T> items){
        for(T item : items){
            this->Append(item);
        }
    }
    Set(const Set& set): Tree<T>(set){

    }
    explicit Set(const Node& node): Tree<T>(node){

    }

    void Add(T value){
        this->Append(value);
    }

    void Delete(T value){
        this->Remove(value);
    }
    bool Contains(T value){
        return this->Search(value);
    }
    Set<T> MapSet(T(*mapper)(T)){
        if (mapper == nullptr)
            throw std::invalid_argument("mapper is NULL");
        Set<T> newSet = Set<T>();
        this->Mapping(mapper, this->root, &newSet);
        return newSet;
    }
    Set<T> WhereSet(bool(*predicate)(T)){
        if (predicate == nullptr)
            throw std::invalid_argument("predicate is NULL");
        Set<T> newSet = Set<T>();
        this->WherePath(predicate, this->root, &newSet);
        return newSet;
    }
    T ReduceSet(T(*reducer)(T, T), T const &c){
        if (reducer == nullptr)
            throw std::invalid_argument("reducer is NULL");
        T res = this->ReducePath(reducer, c, this->root);
        return res;
    }

    Set<T> Intersection(Set<T> set){
        return IntersectionPath(set.root, this->root);
    }

    Set<T> Union(Set<T> set){
        Set<T> result = Set<T>(*this);
        UnionPath(set.root, &result);
        return result;
    }

    Set<T> Substraction(Set<T> set){
        return SubstractionPath(set.root, this->root, *this);
    }

    ArraySequence<T> ToArray(){
        ArraySequence<T> res = ArraySequence<T>();
        GetPath(this->root, &res);
        return res;
    }

    bool IsEqual(Set<T> set){
        return IsEqualNode(set.root, this->root);
    }

    bool IsSubSet(Set<T> set){
        return SubSetPath(set.root, this->root, set);
    }

    bool operator==(Set<T> set){
        return IsEqual(set);
    }
    Set<T> operator&(Set<T> set){
        return Intersection(set);
    }
    Set<T> operator|(Set<T> set){
        return Union(set);
    }
    Set<T> operator-(Set<T> set){
        return Substraction(set);
    }

    void Display(){
        cout << "(";
        if(this->root) DisplayNode(this->root);
        cout << ")\n";
    }
    void Display(bool isList){
        cout << "(\n";
        if(this->root) DisplayNode(this->root, isList);
        cout << ")\n";
    }
};

#endif //LAB5_SET_H
