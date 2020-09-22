// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <string>
#include "json_any_support.hpp"

using nlohmann::json;

class Student {
 public:
  uint32_t getNameLength() const;
  uint32_t getGroupLength() const;
  uint32_t getAvgLength() const;
  uint32_t getDebtLength() const;

  void printName(std::ostream& out) const;
  void printGroup(std::ostream& out) const;
  void printAvg(std::ostream& out) const;
  void printDebt(std::ostream& out) const;

  static void from_json(const json& j, Student& p);

 private:
  std::string name;
  std::any    group;
  std::any    avg;
  std::any    debt;
};
#endif// INCLUDE_STUDENT_HPP_
