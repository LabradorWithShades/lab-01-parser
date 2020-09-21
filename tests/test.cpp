// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <gtest/gtest.h>
#include "JsonTable.hpp"
#include <sstream>

TEST(GTest_Check, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(ParseFromString, FromReadme) {
    std::string test_string =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    JsonTable table = JsonTable::parse(test_string);
    std::stringstream str_stream;
    str_stream << table;
    std::string ref_string =\
R"(| name          | group  | avg  | debt    |
|---------------|--------|------|---------|
| Ivanov Petr   | 1      | 4.25 | null    |
|---------------|--------|------|---------|
| Sidorov Ivan  | 31     | 4    | C++     |
|---------------|--------|------|---------|
| Petrov Nikita | IU8-31 | 3.33 | 3 items |
|---------------|--------|------|---------|
)";
    EXPECT_EQ(str_stream.str(), ref_string);
}
