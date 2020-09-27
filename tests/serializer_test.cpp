// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <any>
#include <string>
#include "json_any_support.hpp"
using nlohmann::json;

TEST(Serializer_Parse, ToJson) {
  json j;

  std::any x = 5;
  j[0] = x;

  x = std::string("Hello");
  j[1] = x;

  x = 5.3f;
  j[2] = x;

  std::vector<std::string> test_vec_str = {"this", "is", "a", "test"};
  x = test_vec_str;
  j[3] = x;

  EXPECT_EQ(j.at(0).get<int>(), 5);
  EXPECT_EQ(j.at(1).get<std::string>(), std::string("Hello"));
  EXPECT_FLOAT_EQ(j.at(2).get<float>(), 5.3f);
  EXPECT_EQ(j.at(3).dump(), std::string(R"(["this","is","a","test"])"));
}

TEST(Serializer_Parse, FromJson) {
  json j = json::parse(R"([5,"Hello",5.3,["this","is","a","test"]])");
  std::any x = j.at(0).get<std::any>();
  EXPECT_EQ(std::any_cast<int>(x), 5);
  x = j.at(1).get<std::any>();
  EXPECT_EQ(std::any_cast<std::string>(x), std::string("Hello"));
  x = j.at(2).get<std::any>();
  EXPECT_FLOAT_EQ(std::any_cast<float>(x), 5.3);
  x = j.at(3).get<std::any>();
  std::vector<std::string> str_vec = std::any_cast<std::vector<std::string>>(x);
  EXPECT_EQ(str_vec[0], std::string("this"));
  EXPECT_EQ(str_vec[1], std::string("is"));
  EXPECT_EQ(str_vec[2], std::string("a"));
  EXPECT_EQ(str_vec[3], std::string("test"));
}

TEST(Serializer_ErrorHandling, UnsupportedType) {
  std::any x = true;
  json j;
  j[0] = x;
  std::string str = j.dump();
  std::string ref_str = "[null]";
  EXPECT_EQ(str, ref_str);
}