//
// Created by lokt on 13.04.2021.
//

#ifndef LAB5_LINKEDLIST_H
#define LAB5_LINKEDLIST_H
#include <iostream>
#include <cstring>

template<class T>
class LinkedList {
    size_t Count = 0;
private:
    class Node {
    public:
        T data;
        Node *next;

        Node() : Node(T(), NULL) {

        };

        explicit Node(T data) : Node(data, NULL) {

        };

        Node(T data, Node *next) {
            this->data = data;
            this->next = next;
        };
    };

    Node *first;
    Node *last;

    Node *GetNode(int index) {
        if(index == 0) return first;
        if(index == Count - 1) return last;
        Node *temp = first;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

public:
    LinkedList() {
        first = NULL;
        last = NULL;
        Count = 0;
    };
    LinkedList(T* items, int count) {
        if(count < 0){
            throw std::out_of_range("You cannot create a list with count < 0");
        }
        if(!items){
            throw std::out_of_range("You cannot create a list with NULL array");
        }
        first = NULL;
        last = NULL;
        if(count > 0) {
            for(size_t i = 0; i < count; i++){
                Append(items[i]);
            }
        }
    };
    explicit LinkedList(size_t count) : LinkedList() {
        if (count >= 536870912)
            throw std::out_of_range("count < 0");
        if (count > 0) {
            first = new Node();
            last = first;
            Node *prev = last;
            for (size_t i = 1; i < count; ++i) {
                prev->next = new Node();
                prev = prev->next;
            }
            last = prev;
            this->Count = count;
        }
    }
    LinkedList(const LinkedList<T> &list) : LinkedList() {
        *this = list;
    }

    ~LinkedList(){
        while (Count > 0)
        {
            PopFirst();
        }
    }

    void Append(T value) {
        Node *temp = new Node(value);
        if(this->first == NULL && this->last == NULL){
            this->first = temp;
            this->last = temp;
        }
        else{
            this->last->next = temp;
            this->last = temp;
        }
        this->Count++;
    }

    size_t GetLength() const {
        return this->Count;
    }

    void Prepend(T value) {
        Node *temp = new Node(value);
        if(this->first == NULL && this->last == NULL){
            this->first = temp;
            this->last = temp;
        }
        else{
            temp->next = this->first;
            this->first = temp;
        }
        this->Count++;
    }
    T& GetFirst() {
        if(!first || this->Count <= 0)
            throw std::out_of_range("List is empty");
        return first->data;
    }
    T& GetLast() {
        if(!last || this->Count <= 0)
            throw std::out_of_range("List is empty");
        return last->data;
    }
    T& Get(int pos) {
        if (pos >= this->Count || pos < 0) {
            throw std::range_error("You got shedko'd");
        }
        if(pos == 0){
            return GetFirst();
        }
        else if(pos == this->Count - 1){
            return GetLast();
        }
        else{
            Node* temp;
            temp = first;
            for(size_t i = 0; i < pos; i++){
                temp = temp->next;
            }
            return temp->data;
        }
    }
    T& operator[](int const index){
        return this->Get(index);
    }
    void Display() {
        for(size_t i = 0; i < this->Count; i++){
            std::cout << this->Get(i) << " ";
        }
        std::cout << "\n";
    }

    void InsertAt(int pos, T value) {
        if (pos < 0 || pos >= this->Count)
            throw std::range_error("index < 0 or index >= length");
        if (pos == this->Count - 1) {
            this->Append(value);
            return;
        } else if (pos == 0) {
            this->Prepend(value);
            return;
        }
        else {
            Node *current;
            Node *previous;
            Node *temp = new Node(value);
            current = GetNode(pos);
            previous = GetNode(pos - 1);
            previous->next = temp;
            temp->next = current;
            Count++;
        }
    }

    void DeleteAt(int pos) {
        if (pos >= this->Count || pos < 0 || this->first == NULL && this->last == NULL) {
            throw std::range_error("You got shedko'd");
        }
        if(pos == 0){
            PopFirst();
        }
        else if(pos == this->Count - 1){
            PopLast();
        }
        else {
            Node *current;
            Node *previous;
            current = GetNode(pos);
            previous = GetNode(pos - 1);
            previous->next = current->next;
            delete current;
            Count--;
        }
    }

    T PopLast() {
        if(this->first == NULL && this->last == NULL || this->Count <= 0){
            throw std::range_error("You got cyberbullied");
        }
        else{
            Node* temp = GetNode(this->Count - 2);
            T value = this->last->data;
            delete this->last;
            this->last = temp;
            this->Count--;
            return value;
        }
    }

    T PopFirst() {
        if(this->first == NULL && this->last == NULL || this->Count <= 0){
            throw std::range_error("You got cyberbullied");
        }
        else{
            Node* temp = this->first->next;
            T value = this->first->data;
            delete this->first;
            this->first = temp;
            this->Count--;
            return value;
        }
    }

    LinkedList<T> SubList(int start, int end){
        if(start > end){
            throw std::range_error("Start cant be more than end");
        }
        LinkedList<T> buf;
        for (int i = start; i <= end; i++)
        {
            buf.Append(Get(i));
        }
        return buf;
    }

    LinkedList<T> Concat(LinkedList<T> &list) {
        LinkedList<T> res;
        for (size_t i = 0; i < this->Count; ++i) {
            res.Append(this->Get(i));
        }
        for (size_t i = 0; i < list.Count; ++i) {
            res.Append(list[i]);
        }
        return res;
    }

    LinkedList<T> &operator=(const LinkedList<T> &list) {
        if(&list != this) {
            while (Count > 0) {
                PopFirst();
            }
            if (list.Count > 0) {
                Node *tmp = list.first;
                first = new Node(tmp->data);
                Node *prev = first;
                tmp = tmp->next;
                while (tmp != NULL) {
                    prev->next = new Node(tmp->data);
                    prev = prev->next;
                    tmp = tmp->next;
                }
                last = prev;
                this->Count = list.Count;
            } else {
                first = nullptr;
                last = nullptr;
                this->Count = 0;
            }
        }
        return *this;
    }

};


#endif //LAB5_LINKEDLIST_H
