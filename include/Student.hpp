// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include "json_any_support.hpp"

using nlohmann::json;

class Student {
 public:
  uint32_t getNameLength();
  uint32_t getGroupLength();
  uint32_t getAvgLength();
  uint32_t getDebtLength();

  void printName(std::ostream& out);
  void printGroup(std::ostream& out);
  void printAvg(std::ostream& out);
  void printDebt(std::ostream& out);

  static void to_json(json& j, const Student& s);
  static void from_json(const json& j, Student& p);

 private:
  std::string name;
  std::any    group;
  std::any    avg;
  std::any    debt;
};

#endif// INCLUDE_STUDENT_HPP_