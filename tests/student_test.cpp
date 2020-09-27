// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <gtest/gtest.h>
#include <Student.hpp>
#include <nlohmann/json.hpp>
#include <json_any_support.hpp>
#include <string>
#include <sstream>
#include <any>

TEST(Student_Parse, FromJson) {
  json j = json::parse(R"({
  "name": "Ivanov Petr",
  "group": "1",
  "avg": "4.25",
  "debt": null
})");
  Student s;
  Student::from_json(j, s);
  EXPECT_EQ(s.getName(), std::string("Ivanov Petr"));
  EXPECT_EQ(std::any_cast<std::string>(s.getGroup()), "1");
  EXPECT_EQ(std::any_cast<std::string>(s.getAvg()), "4.25");
  EXPECT_EQ(std::any_cast<std::nullptr_t>(s.getDebt()), nullptr);

  j = json::parse(R"({
  "name": "Sidorov Ivan",
  "group": 31,
  "avg": 4,
  "debt": "C++"
})");
  Student::from_json(j, s);
  EXPECT_EQ(s.getName(), std::string("Sidorov Ivan"));
  EXPECT_EQ(std::any_cast<int>(s.getGroup()), 31);
  EXPECT_EQ(std::any_cast<int>(s.getAvg()), 4);
  EXPECT_EQ(std::any_cast<std::string>(s.getDebt()), "C++");

  j = json::parse(R"({
  "name": "Petrov Nikita",
  "group": "IU8-31",
  "avg": 3.33,
  "debt": [
    "C++",
    "Linux",
    "Network"
  ]
})");
  Student::from_json(j, s);
  EXPECT_EQ(s.getName(), std::string("Petrov Nikita"));
  EXPECT_EQ(std::any_cast<std::string>(s.getGroup()), "IU8-31");
  EXPECT_FLOAT_EQ(std::any_cast<float>(s.getAvg()), 3.33f);
  EXPECT_EQ(std::any_cast<std::vector<std::string>>(s.getDebt()),
            std::vector<std::string>({"C++", "Linux", "Network"}));
}

TEST(Student_Parse, ToJson) {
  json j;
  json j_ref = json::parse(R"({
  "name": "Ivanov Petr",
  "group": "1",
  "avg": "4.25",
  "debt": null
})");
  Student s;
  s.setName(std::string("Ivanov Petr"));
  s.setGroup(std::string("1"));
  s.setAvg(std::string("4.25"));
  s.setDebt(nullptr);
  Student::to_json(j, s);
  EXPECT_EQ(j, j_ref);

  j_ref = json::parse(R"({
  "name": "Sidorov Ivan",
  "group": 31,
  "avg": 4,
  "debt": "C++"
})");
  s.setName(std::string("Sidorov Ivan"));
  s.setGroup(31);
  s.setAvg(4);
  s.setDebt(std::string("C++"));
  Student::to_json(j, s);
  EXPECT_EQ(j, j_ref);

  j_ref = json::parse(R"({
  "name": "Petrov Nikita",
  "group": "IU8-31",
  "avg": 3.3299999237060547,
  "debt": [
    "A",
    "B",
    "C"
  ]
})");
  s.setName(std::string("Petrov Nikita"));
  s.setGroup(std::string("IU8-31"));
  s.setAvg(3.33f);
  s.setDebt(std::vector<std::string>({std::string("A"),
                                      std::string("B"),
                                      std::string("C")}));
  Student::to_json(j, s);
  EXPECT_EQ(j, j_ref);
}

TEST(Student_Lengths, NameLength) {
  Student s;
  s.setName("Test name 1");
  EXPECT_EQ(s.getNameLength(), 11);
  s.setName("Test name number 2");
  EXPECT_EQ(s.getNameLength(), 18);
}

TEST(Student_Lengths, GroupLength) {
  Student s;
  s.setGroup(std::string("Test group 1"));
  EXPECT_EQ(s.getGroupLength(), 12);
  s.setGroup(5);
  EXPECT_EQ(s.getGroupLength(), 1);
}

TEST(Student_Lengths, AvgLength) {
  Student s;
  s.setAvg(std::string("5.33"));
  EXPECT_EQ(s.getAvgLength(), 4);
  s.setAvg(4.33f);
  EXPECT_EQ(s.getAvgLength(), 4);
  s.setAvg(5);
  EXPECT_EQ(s.getAvgLength(), 1);
}

TEST(Student_Lengths, DebtLength) {
  Student s;
  s.setDebt(nullptr);
  EXPECT_EQ(s.getDebtLength(), 4);
  s.setDebt(std::string("C++"));
  EXPECT_EQ(s.getDebtLength(), 3);
  s.setDebt(std::vector<std::string>({"A", "B", "C"}));
  EXPECT_EQ(s.getDebtLength(), 7);
}

TEST(Student_Print, PrintName) {
  std::stringstream str_stream;
  Student s;
  s.setName("Anton Popov");
  s.printName(str_stream);
  EXPECT_EQ(str_stream.str(), "Anton Popov");
}

TEST(Student_Print, PrintGroup) {
  std::stringstream str_stream;
  Student s;
  s.setGroup(std::string("IU8-31"));
  s.printGroup(str_stream);
  EXPECT_EQ(str_stream.str(), "IU8-31");
  str_stream.str(std::string());
  s.setGroup(5);
  s.printGroup(str_stream);
  EXPECT_EQ(str_stream.str(), "5");
}

TEST(Student_Print, PrintAvg) {
  std::stringstream str_stream;
  Student s;
  s.setAvg(std::string("5.3"));
  s.printAvg(str_stream);
  EXPECT_EQ(str_stream.str(), "5.3");
  str_stream.str(std::string());
  s.setAvg(3.7f);
  s.printAvg(str_stream);
  EXPECT_EQ(str_stream.str(), "3.7");
  str_stream.str(std::string());
  s.setAvg(4);
  s.printAvg(str_stream);
  EXPECT_EQ(str_stream.str(), "4");
}

TEST(Student_Print, PrintDebt) {
  std::stringstream str_stream;
  Student s;
  s.setDebt(nullptr);
  s.printDebt(str_stream);
  EXPECT_EQ(str_stream.str(), "null");
  str_stream.str(std::string());
  s.setDebt(std::string("C++"));
  s.printDebt(str_stream);
  EXPECT_EQ(str_stream.str(), "C++");
  str_stream.str(std::string());
  s.setDebt(std::vector<std::string>({"A", "B", "C"}));
  s.printDebt(str_stream);
  EXPECT_EQ(str_stream.str(), "3 items");
}

TEST(Student_ErrorHandling, WrongGroupType) {
  Student s;
  std::stringstream str_stream;
  s.setGroup(true);
  EXPECT_EQ(s.getGroupLength(), 0);
  s.printGroup(str_stream);
  EXPECT_EQ(str_stream.str(), "ERR");
}

TEST(Student_ErrorHandling, WrongAvgType) {
  Student s;
  std::stringstream str_stream;
  s.setAvg(true);
  EXPECT_EQ(s.getAvgLength(), 0);
  s.printAvg(str_stream);
  EXPECT_EQ(str_stream.str(), "ERR");
}

TEST(Student_ErrorHandling, WrongDebtType) {
  Student s;
  std::stringstream str_stream;
  s.setDebt(true);
  EXPECT_EQ(s.getDebtLength(), 0);
  s.printDebt(str_stream);
  EXPECT_EQ(str_stream.str(), "ERR");
}
