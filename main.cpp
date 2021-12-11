#include <iostream>
#include "ArraySequence.h"
#include "SequenceSorter.h"
#include "TicTacToe.h"
#include <random>
#include <chrono>

int main() {
    TicTacToe t = TicTacToe();
    t.Build();
    t.Output();
    return 0;
}
