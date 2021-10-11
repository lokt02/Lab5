//
// Created by lokt0 on 23.05.2021.
//
#include "gtest/gtest.h"
#include "../BinaryTree.h"
#include <string>

using namespace std;

int MapCheck(int a){
    return a * 3;
}
string MapCheckString(string a){
    return a + "1";
}
bool IsEven(int a){
    return a % 2 == 0;
}
int ReduceCheck(int a, int b){
    return a + b;
}

TEST(Tree_test, Init){
    Tree<int> tree = Tree<int>();
    EXPECT_ANY_THROW(tree.Remove(0));
    // EXPECT_ANY_THROW(tree.Search((int)nullptr));
    EXPECT_ANY_THROW(tree.Search(1));
    tree.Append(0);
    tree.Append(1);
    tree.Append(2);
    tree.Append(3);
    tree.Append(4);

    Tree<int> tree1 = Tree<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(tree.SearchSubTree(tree1));
}

TEST(Tree_test, Search_Append){
    Tree<int> tree = Tree<int>();
    tree.Append(1);
    tree.Append(2);
    tree.Append(2);
    ASSERT_TRUE(tree.Search(1));
    ASSERT_TRUE(tree.Search(2));
    ASSERT_FALSE(tree.Search(3));
}

TEST(Tree_test, Remove){
    Tree<int> tree = Tree<int>();
    tree.Append(1);
    tree.Append(2);
    tree.Append(3);
    tree.Append(4);
    tree.Append(5);
    tree.Remove(3);
    ASSERT_TRUE(tree.Search(1));
    ASSERT_TRUE(tree.Search(2));
    ASSERT_FALSE(tree.Search(3));
}

TEST(Tree_test, SubTree){
    Tree<int> tree = Tree<int>({0, 1, 2, 3, 4});
    Tree<int> tree1 = Tree<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(tree.SearchSubTree(tree1));

    Tree<string> tree2 = Tree<string>({"apple", "", "banana", "aboba", "1"});
    Tree<string> tree3 = Tree<string>({"apple", "", "banana", "aboba", "1"});
    Tree<string> tree4 = Tree<string>({"apple", "", "banana", "vadim", "2"});
    ASSERT_TRUE(tree2.SearchSubTree(tree3));
    ASSERT_FALSE(tree2.SearchSubTree(tree4));


    Tree<string> tree5 = tree4.SubTree("");
    ASSERT_TRUE(tree5.SearchSubTree(Tree<string>({"", "2"})));
}

TEST(Tree_test, Map){
    Tree<int> tree = Tree<int>({0, 1, 2, 3, 4});
    Tree<int> treeMap = tree.Map(MapCheck);
    ASSERT_TRUE(treeMap.SearchSubTree(Tree<int>({0, 3, 6, 9, 12})));

//    Tree<string> treeString = Tree<string>({"", "lol", "kek", "r", "0"});
//    Tree<string> treeMapString = treeString.Map(MapCheckString);
//    treeMapString.Output();
//    auto tempTree = Tree<string>({"1", "lol1", "kek1", "r1", "01"});
//    tempTree.Output();
//    ASSERT_TRUE(treeMapString.SearchSubTree(Tree<string>({"1", "lol1", "kek1", "r1", "01"})));

    Tree<int(*)(int)> test = Tree<int(*)(int)>();
    EXPECT_NO_THROW(test.Append(MapCheck));
}

TEST(Tree_test, Where){
    Tree<int> tree = Tree<int>({0, 1, 2, 3, 4});
    Tree<int> treeMap = tree.Where(IsEven);
    ASSERT_TRUE(treeMap.SearchSubTree(Tree<int>({0, 2, 4})));
}

TEST(Tree_test, Reduce){
    Tree<int> tree = Tree<int>({0, 1, 2, 3, 4});
    ASSERT_EQ(tree.Reduce(ReduceCheck, 0), 10);
}
