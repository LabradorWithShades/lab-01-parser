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

  static void to_json(json& j, const Student& s);
  static void from_json(const json& j, Student& p);

  inline std::string getName() const { return m_name; }
  inline std::any getGroup() const { return m_group; }
  inline std::any getAvg() const { return m_avg; }
  inline std::any getDebt() const { return m_debt; }

  inline void setName(std::string name) { m_name = name; }
  inline void setGroup(std::any group) { m_group = group; }
  inline void setAvg(std::any avg) { m_avg = avg; }
  inline void setDebt(std::any debt) { m_debt = debt; }

 private:
  std::string m_name = "John Doe";
  std::any    m_group = "IU00-00";
  std::any    m_avg = 0.00;
  std::any    m_debt = nullptr;
};
#endif// INCLUDE_STUDENT_HPP_
