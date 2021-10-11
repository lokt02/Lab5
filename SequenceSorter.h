//
// Created by lokt0 on 13.09.2021.
//

#ifndef LAB5_SEQUENCESORTER_H
#define LAB5_SEQUENCESORTER_H

#include <functional>
#include "Sequence.h"

template<class T>
class SequenceSorter{
public:
    static Sequence<T>* BubbleSort(Sequence<T>* sequence, std::function<bool(T, T)> const & comparer){
        int i, j;
        bool swapped;
        for(i = 0; i < sequence->GetLength() - 1; i++){
            swapped = false;
            for(j = 0; j < sequence->GetLength() - 1 - i; j++){
                if(comparer(sequence->Get(j), sequence->Get(j+1))){
                    swap(sequence->Get(j), sequence->Get(j+1));
                    swapped = true;
                }
            }

            if (!swapped)
                break;
        }
        return sequence;
    }

    static Sequence<T>* InsertionSort(Sequence<T>* sequence, std::function<bool(T, T)> const & comparer){
        T key;
        int j;
        for(int i = 1; i < sequence->GetLength(); i++){
            key = sequence->Get(i);
            j = i;
            while(j > 0 && comparer(sequence->Get(j-1), key)){
                sequence->Set(j, sequence->Get(j-1));
                j--;
            }
            sequence->Get(j) = key;
        }
        return sequence;
    }

    static Sequence<T>* HeapSort(Sequence<T>* sequence, std::function<bool(T, T)> const & comparer){
        int count = sequence->GetLength();

        for(int i = count / 2 - 1; i >= 0; i--){
            heapify(sequence, i, count, comparer);
        }

        for (int i = count - 1; i >= 0; i--) {
            swap(sequence->Get(0), sequence->Get(i));
            heapify(sequence, 0, i, comparer);
        }

        return sequence;
    }

    static Sequence<T>* QuickSort(Sequence<T>* sequence, std::function<bool(T, T)> const & comparer = [](T a, T b){ return a > b; }){
        quickSort(sequence, 0, sequence->GetLength() - 1, comparer);
        return sequence;
    }

private:
    static void quickSort(Sequence<T>* seq, int low, int high, std::function<bool(T, T)> const & comp) {
        if(low < high){
            int pi = partition(seq, low, high, comp);

            quickSort(seq, low, pi - 1, comp);
            quickSort(seq, pi + 1, high, comp);
        }
    }
    static int partition(Sequence<T>* seq, int low, int high, std::function<bool(T, T)> const & comp) {
        T pivot = seq->Get(high);
        int i = low - 1;
        for(int j = low; j <= high - 1; j++){
            if(!comp(seq->Get(j), pivot)){
                i++;
                swap(seq->Get(i), seq->Get(j));
            }
        }
        swap(seq->Get(i+1), seq->Get(high));
        return i + 1;
    }
    static void heapify(Sequence<T>* seq, int i, int count, std::function<bool(T, T)> const & comp){
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if(l < count && comp(seq->Get(l), seq->Get(largest))){
            largest = l;
        }

        if(r < count && comp(seq->Get(r), seq->Get(largest))){
            largest = r;
        }

        if(largest != i){
            swap(seq->Get(i), seq->Get(largest));
            heapify(seq, count, largest, comp);
        }
    };
};
#endif //LAB5_SEQUENCESORTER_H
