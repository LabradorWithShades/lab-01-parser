// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#ifndef INCLUDE_JSONTABLE_HPP_
#define INCLUDE_JSONTABLE_HPP_

#include <vector>
#include <string>

#include "Student.hpp"

class JsonTable {
 public:
  explicit JsonTable(const std::string& s);
  explicit JsonTable(const json& j);
  ~JsonTable();

  void print(std::ostream& out) const;

  static JsonTable parse(const std::string& s);
  static JsonTable parseFile(const std::string& s);

 private:
  std::vector<Student> m_data;
  std::vector<uint32_t> m_maxWidths;
};

std::ostream& operator<<(std::ostream& out, const JsonTable& table);

#endif // INCLUDE_JSONTABLE_HPP_
