//
// Created by lokt0 on 23.05.2021.
//
#include "gtest/gtest.h"
#include "../Set.h"
#include "../Person.h"
#include "../SequenceSorter.h"
#include <string>

using namespace std;

int MapCheck1(int a){
    return a * 3;
}
string MapCheckString1(string a){
    return a + " aboba";
}
bool IsEven1(int a){
    return a % 2 == 0;
}
int ReduceCheck1(int a, int b){
    return a + b;
}

TEST(SetTest, Init){
    Set<int> set = Set<int>();
    EXPECT_ANY_THROW(set.Delete(0));
    // EXPECT_ANY_THROW(set.Contains((int)nullptr));
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Add(4);

    Set<int> set1 = Set<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(set.IsEqual(set1));
}

TEST(SetTest, Add_Delete){
    Set<int> set = Set<int>();
    set.Add(0);
    set.Add(1);
    set.Add(2);
    set.Add(3);
    set.Delete(0);
    set.Delete(3);
    ASSERT_TRUE(set.Contains(2));
    ASSERT_FALSE(set.Contains(3));

    Set<int> set1 = Set<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(set1.IsSubSet(set));
}

TEST(SetTest, SubSet){
    Set<int> set = Set<int>({2, 4});
    Set<int> set1 = Set<int>({0, 1, 2, 3, 4});
    ASSERT_TRUE(set1.IsSubSet(set));


    Set<Person> people = Set<Person>({Person({1, 01}, "Oleg", "Mid", "Punk", time(nullptr)),
                                      Person({1, 02}, "Lul", "Papa", "Go", time(nullptr)),
                                      Person({1, 03}, "Lol", "Lul", "Kek", time(nullptr)),
                                      Person({1, 04}, "UwU", "Ok", "No", time(nullptr))});
    Set<Person> people1 = Set<Person>({Person({1, 01}, "Oleg", "Mid", "Punk", time(nullptr)),
                                      Person({1, 04}, "UwU", "Ok", "No", time(nullptr))});
    ASSERT_TRUE(people.IsSubSet(people1));
}

int MapTestLab(int x){
    return x % 2;
}

TEST(SetTest, Map){
    Set<int> set = Set<int>({-4, -3, -2, 0});
    Set<int> mapSet = set.MapSet(MapCheck1);
    ASSERT_TRUE(mapSet.IsEqual(Set<int>({-12, -9, -6, 0})));

    Set<string> setString = Set<string>({"", "0", "0"});
    Set<string> mapSetString = setString.MapSet(MapCheckString1);
    ASSERT_TRUE(mapSetString.IsEqual(Set<string>({" aboba", "0 aboba"})));

    Set<int(*)(int)> test = Set<int(*)(int)>();
    test.Add(MapCheck1);


    Set<int> set1 = Set<int>({1, 2, 3, 4, 5, 6});
    Set<int> set2 = set1.MapSet(MapTestLab);
}

TEST(SetTest, Where){
    Set<int> set = Set<int>({-4, -3, -2, 0});
    Set<int> mapSet = set.WhereSet(IsEven1);
    ASSERT_TRUE(mapSet.IsEqual(Set<int>({-4, -2, 0})));
}

TEST(SetTest, Reduce){
    Set<int> set = Set<int>({-4, -3, -2, 0});
    int reduce = set.ReduceSet(ReduceCheck1, 0);
    ASSERT_EQ(reduce, -9);
}

TEST(SetTest, Inersection){
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    auto intersection = set & set1;
    //Set<int> intersection = Set<int>(sets);
    ASSERT_TRUE(intersection->IsEqual(Set<int>({4, 5})));
}

TEST(SetTest, Union){
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    Set<int> uni = Set<int>(set | set1);
    auto sets = Set<int>({1, 2, 3, 4, 5, 6, 7, 8});
    ASSERT_TRUE(uni.IsEqual(Set<int>({1, 2, 3, 4, 5, 6, 7, 8})));
}

TEST(SetTest, Substraction){
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>({4, 5, 6, 7, 8});
    Set<int> sub = Set<int>(set - set1);
    ASSERT_TRUE(sub.IsEqual(Set<int>({1, 2, 3})));
}

TEST(SetTest, EqualTest){
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    Set<int> set1 = Set<int>(set);
    ASSERT_TRUE(set1 == set);
}

TEST(SetTest, ToArray){
    Set<int> set = Set<int>({1, 2, 3, 4, 5});
    auto arr = ArraySequence<int>({1, 2, 3, 4, 5});
    auto arr1 = set.ToArray();
    SequenceSorter<int>::QuickSort(&arr1);
    ASSERT_TRUE(arr1 == arr);
}
