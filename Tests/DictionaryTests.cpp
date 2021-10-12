//
// Created by lokt0 on 12.10.2021.
//
#include "gtest/gtest.h"
#include "../Dictionary.h"

TEST(Dictionary_Test, Init){
    Dictionary<string, int> dict = Dictionary<string, int>();
    EXPECT_ANY_THROW(dict.Remove(""));
    EXPECT_ANY_THROW(dict[""]);
    dict.Add("a", 1);
    dict.Add("b", 2);
    dict.Add("c", 3);
    dict.Add("d", 4);
    ASSERT_NO_THROW((Dictionary<string, string>()));
}

TEST(Dictionary_Test, Add){
    Dictionary<string, int> dict = Dictionary<string, int>();
    EXPECT_NO_THROW(dict.Add("a", 1));
    Dictionary<string, int> dict1 = Dictionary<string, int>();
    dict1.Add("b", 2);
    dict1.Add("a", 1);
    dict.Add("b", 2);
    EXPECT_TRUE(dict == dict1);

    EXPECT_ANY_THROW(dict.Add("b", 3));
}

TEST(Dictionary_Test, Remove){
    Dictionary<string, int> dict = Dictionary<string, int>();
    dict.Add("a", 1);
    EXPECT_NO_THROW(dict.Remove("a"));
    EXPECT_FALSE(dict == (Dictionary<string, int>()));
}

TEST(Dictionary_Test, Get_or_Set){
    Dictionary<string, int> dict = Dictionary<string, int>();
    dict.Add("a", 1);
    dict.Add("b", 2);
    dict.Add("c", 3);
    dict.Add("d", 4);
    EXPECT_TRUE(dict["a"] == 1);
    EXPECT_TRUE(dict["b"] == 2);
    EXPECT_TRUE(dict["c"] == 3);
    EXPECT_TRUE(dict["d"] == 4);
    dict["a"] = 10;
    dict.Display();
    EXPECT_TRUE(dict["a"] == 10);
}

TEST(Dictionary_Test, Equality){
    Dictionary<string, int> dict1 = Dictionary<string, int>();
    EXPECT_TRUE(dict1 == (Dictionary<string, int>()));
    dict1.Add("a", 1);
    dict1.Add("b", 2);
    dict1.Add("c", 3);
    dict1.Add("d", 4);

    Dictionary<string, int> dict = Dictionary<string, int>();
    dict.Add("a", 1);
    dict.Add("b", 2);
    dict.Add("c", 3);
    dict.Add("d", 4);

    EXPECT_TRUE(dict1 == dict);

    dict.Add("cook", 10);
    EXPECT_FALSE(dict1 == dict);
}
