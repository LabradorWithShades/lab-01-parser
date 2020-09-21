// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <gtest/gtest.h>
#include "JsonTable.hpp"
#include <sstream>
#include <fstream>

TEST(GTest_Check, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(Parse, FromString) {
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

TEST(Parse, FromFile) {
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
    std::ofstream test_file;
    test_file.open("test_file.json", std::ios::out);
    test_file << test_string;
    test_file.close();
    JsonTable table = JsonTable::parseFile("test_file.json");
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

TEST(ErrorHandling, FileDoesNotExist) {
    try {
        JsonTable table = JsonTable::parseFile("incorrect_file_name.json");
    } catch (const std::runtime_error& e) {
        std::string what_str = e.what();
        EXPECT_EQ(what_str, "File \"incorrect_file_name.json\" could not \
be opened!");
    }
}

TEST(ErrorHandling, FileIncorrectCount) {
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
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    std::ofstream test_file;
    test_file.open("test_file.json", std::ios::out);
    test_file << test_string;
    test_file.close();
    try {
        JsonTable table = JsonTable::parseFile("test_file.json");
    } catch (const std::runtime_error& e) {
        std::string what_str = e.what();
        EXPECT_EQ(what_str, "Incorrect JSON file: \"count\" field in \
\"_meta\" field should be equal to \"items\" field size!");
    }
}

TEST(ErrorHandling, FileIncorrectItemsType) {
    std::string test_string =\
R"({
  "items": {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
  }
})";
    std::ofstream test_file;
    test_file.open("test_file.json", std::ios::out);
    test_file << test_string;
    test_file.close();
    try {
        JsonTable table = JsonTable::parseFile("test_file.json");
    } catch (const std::runtime_error& e) {
        std::string what_str = e.what();
        EXPECT_EQ(what_str, "Incorrect JSON file: \"items\" field \
should be an array!");
    }
}

TEST(ErrorHandling, StringIncorrectCount) {
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
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    try {
        JsonTable table = JsonTable::parse(test_string);
    } catch (const std::runtime_error& e) {
        std::string what_str = e.what();
        EXPECT_EQ(what_str, "Incorrect JSON file: \"count\" field in \
\"_meta\" field should be equal to \"items\" field size!");
    }
}

TEST(ErrorHandling, StringIncorrectItemsType) {
    std::string test_string =\
R"({
  "items": {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
  }
})";
    try {
        JsonTable table = JsonTable::parse(test_string);
    } catch (const std::runtime_error& e) {
        std::string what_str = e.what();
        EXPECT_EQ(what_str, "Incorrect JSON file: \"items\" field \
should be an array!");
    }
}
