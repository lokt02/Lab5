//
// Created by lokt0 on 05.11.2021.
//

#ifndef LAB5_TICTACTOE_H
#define LAB5_TICTACTOE_H

#include "ArraySequence.h"
#include "Dictionary.h"

typedef Dictionary<int, int> FieldType;
// 0 - clear cell, 1 - X, 2 - O
class TicTacToe{
private:
    class Node{
    public:
        FieldType field;
        ArraySequence<Node*> children;

        Node(){
            field = FieldType();
            for(int i = 1; i <= 9; i++) field.Add(i, 0);
            children = ArraySequence<Node*>();
        };

        bool FieldFull(){
            bool res = true;
            for(int i = 1; i <= 9; i++){
                if(field[i] == 0) res = false;
            }
            return res;
        };
    };
    Node* firstState;
    int turn;
public:
    TicTacToe(){
        turn = 1;
        Node* begin = new Node();
        FieldType state = BuildField();
        begin->field = state;
        firstState = begin;
    }

    FieldType BuildField(){
        FieldType state = FieldType();
        for(int i = 1; i <= 9; i++) state.Add(i, 0);
        return state;
    }

    void BuildTree(Node* node){
        for(int i = 1; i <= 9; i++){
            FieldType currentField = node->field;
            if(node->FieldFull()) break;

            if(currentField[i] == 0){
                currentField[i] = turn;
                Node* newNode = new Node();
                newNode->field = currentField;
                node->children.Append(newNode);
                if(CheckWin(currentField)) break;
            }
        }
        NextTurn();
        for(int i = 0; i < node->children.GetLength(); i++){
            BuildTree(node->children[i]);
        }
    }

    bool CheckWin(FieldType field){
        for(int i = 1; i <= 3; i++){
            if (field[i] == turn && field[i + 3] == turn && field[i + 6] == turn)  return true;
            if(i == 1) {
                if (field[i] == turn && field[i + 4] == turn && field[i + 8] == turn) return true;
            }
            else if(i == 3) {
                if (field[i] == turn && field[i + 2] == turn && field[i + 4] == turn) return true;
            }
        }
        for(int i = 1; i <= 9; i+=3){
            if (field[i] == turn && field[i + 1] == turn && field[i + 2] == turn)  return true;
        }
        return false;
    }

    void Build(){
        BuildTree(firstState);
    }

    void NextTurn(){
        turn = turn % 2 + 1;
    }

    void Output(Node* node){
        for(int i = 1; i <= 9; i++){
            std::cout << node->field[i] << " ";
            if(i % 3 == 0) std::cout << "\n";
        }
        std::cout << "-------------------\n";
        for(int i = 0; i < node->children.GetLength(); i++){
            Output(node->children[i]);
        }
    }
    void Output(){
        Output(firstState);
    }
};

#endif //LAB5_TICTACTOE_H
