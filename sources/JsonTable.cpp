// Copyright 2020 LabradorWithShades 70892548+LabradorWithShades@users.noreply.github.com
#include <JsonTable.hpp>
#include <fstream>

JsonTable::JsonTable(const std::string& s):
    m_data(0) {
  m_maxWidths = {4 + 2, 5 + 2, 3 + 2, 4 + 2};
  json j = json::parse(s);
  if (!j.at("items").is_array())
    throw std::runtime_error(R"(Incorrect JSON file: "items" field should be an array!)");
  if (j.at("items").size() != j.at("_meta").at("count").get<size_t>())
    throw std::runtime_error(R"(Incorrect JSON file: "count" field in "_meta" field should be equal to "items" field size!)");

  for (json::const_iterator it = j.at("items").cbegin(); it != j.at("items").cend(); ++it) {
    Student student;
    Student::from_json(it.value(), student);
    if (student.getNameLength() + 2 > m_maxWidths[0])
        m_maxWidths[0] = student.getNameLength() + 2;
    if (student.getGroupLength() + 2 > m_maxWidths[1])
        m_maxWidths[1] = student.getGroupLength() + 2;
    if (student.getAvgLength() + 2 > m_maxWidths[2])
        m_maxWidths[2] = student.getAvgLength() + 2;
    if (student.getDebtLength() + 2 > m_maxWidths[3])
        m_maxWidths[3] = student.getDebtLength() + 2;
    m_data.push_back(student);
  }
}

JsonTable::JsonTable(const json& j):
    m_data(0) {
    m_maxWidths = {6, 7, 5, 6};
    if (!j.at("items").is_array())
        throw std::runtime_error(R"(Incorrect JSON file: "items" field should be an array!)");
    if (j.at("items").size() != j.at("_meta").at("count").get<size_t>())
        throw std::runtime_error(R"(Incorrect JSON file: "count" field in "_meta" field should be equal to "items" field size!)");

    for (json::const_iterator it = j.at("items").cbegin(); it != j.at("items").cend(); ++it) {
        Student student;
        Student::from_json(it.value(), student);
        if (student.getNameLength() + 2 > m_maxWidths[0])
            m_maxWidths[0] = student.getNameLength() + 2;
        if (student.getGroupLength() + 2 > m_maxWidths[1])
            m_maxWidths[1] = student.getGroupLength() + 2;
        if (student.getAvgLength() + 2 > m_maxWidths[2])
            m_maxWidths[2] = student.getAvgLength() + 2;
        if (student.getDebtLength() + 2 > m_maxWidths[3])
            m_maxWidths[3] = student.getDebtLength() + 2;
        m_data.push_back(student);
  }
}

JsonTable::~JsonTable() {

}

void JsonTable::print(std::ostream& out) {
    std::string separator = "|";
    for (int i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < m_maxWidths[i]; ++j)
            separator += " ";
        separator += "|";
    }

    out << "| name ";
    for (uint32_t i = 0; i < m_maxWidths[0] - 6; ++i)
        out << " ";
    out << "| group ";
    for (uint32_t i = 0; i < m_maxWidths[0] - 7; ++i)
        out << " ";
    out << "| avg ";
    for (uint32_t i = 0; i < m_maxWidths[0] - 5; ++i)
        out << " ";
    out << "| debt ";
    for (uint32_t i = 0; i < m_maxWidths[0] - 6; ++i)
        out << " ";
    out << std::endl << separator << std::endl;

    for (size_t i = 0; i < m_data.size(); ++i) {
        out << " "; m_data[i].printName(out);
        for (uint32_t j = 0; j < m_maxWidths[0] - m_data[i].getNameLength() - 1; ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printGroup(out);
        for (uint32_t j = 0; j < m_maxWidths[1] - m_data[i].getGroupLength() - 1; ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printAvg(out);
        for (uint32_t j = 0; j < m_maxWidths[2] - m_data[i].getAvgLength() - 1; ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printDebt(out);
        for (uint32_t j = 0; j < m_maxWidths[3] - m_data[i].getDebtLength() - 1; ++j)
            out << " ";
        out << "|";

        out << std::endl << separator << std::endl;
    }
}

JsonTable JsonTable::parse(const std::string& s) {
  JsonTable table(s);
  return table;
}

JsonTable JsonTable::parseFile(const std::string& s) {
  std::ifstream input_file;
  input_file.open(s, std::ios::in | std::ios::ate);
  if (!input_file.is_open())
    throw std::runtime_error("File \"" + s + "\" could not be opened!");
  json j;
  input_file >> j;
  JsonTable table(j);
  return table;
}
