// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include <JsonTable.hpp>
#include <fstream>

JsonTable::JsonTable(const std::string& s):
    m_data(0) {
  const int name_w = 4;
  const int group_w = 5;
  const int avg_w = 3;
  const int debt_w = 4;
  const int spaces_w = 2;

  m_maxWidths = {name_w + spaces_w, group_w + spaces_w, \
avg_w + spaces_w, debt_w + spaces_w};
  json j = json::parse(s);
  if (!j.at("items").is_array())
    throw std::runtime_error(\
        R"(Incorrect JSON file: "items" field should be an array!)");
  if (j.at("items").size() != j.at("_meta").at("count").get<size_t>())
    throw std::runtime_error(\
        std::string(R"(Incorrect JSON file: "count" field in "_meta" )") + \
        std::string(R"(field should be equal to "items" field size!)"));

  for (json::const_iterator it = j.at("items").cbegin();\
                            it != j.at("items").cend();\
                          ++it) {
    Student student;
    Student::from_json(it.value(), student);
    if (student.getNameLength() + spaces_w > m_maxWidths[0])
        m_maxWidths[0] = student.getNameLength() + spaces_w;
    if (student.getGroupLength() + spaces_w > m_maxWidths[1])
        m_maxWidths[1] = student.getGroupLength() + spaces_w;
    if (student.getAvgLength() + spaces_w > m_maxWidths[2])
        m_maxWidths[2] = student.getAvgLength() + spaces_w;
    if (student.getDebtLength() + 2 > m_maxWidths[3])
        m_maxWidths[3] = student.getDebtLength() + spaces_w;
    m_data.push_back(student);
  }
}

JsonTable::JsonTable(const json& j):
    m_data(0) {
    const int name_w = 4;
    const int group_w = 5;
    const int avg_w = 3;
    const int debt_w = 4;
    const int spaces_w = 2;

    m_maxWidths = {name_w + spaces_w, group_w + spaces_w, \
avg_w + spaces_w, debt_w + spaces_w};
    if (!j.at("items").is_array())
        throw std::runtime_error(\
        R"(Incorrect JSON file: "items" field should be an array!)");
    if (j.at("items").size() != j.at("_meta").at("count").get<size_t>())
        throw std::runtime_error(\
            std::string(R"(Incorrect JSON file: "count" field in "_meta" )") + \
            std::string(R"(field should be equal to "items" field size!)"));


    for (json::const_iterator it = j.at("items").cbegin();\
                              it != j.at("items").cend();\
                            ++it) {
        Student student;
        Student::from_json(it.value(), student);
        if (student.getNameLength() + spaces_w > m_maxWidths[0])
            m_maxWidths[0] = student.getNameLength() + spaces_w;
        if (student.getGroupLength() + spaces_w > m_maxWidths[1])
            m_maxWidths[1] = student.getGroupLength() + spaces_w;
        if (student.getAvgLength() + spaces_w > m_maxWidths[2])
            m_maxWidths[2] = student.getAvgLength() + spaces_w;
        if (student.getDebtLength() + spaces_w > m_maxWidths[3])
            m_maxWidths[3] = student.getDebtLength() + spaces_w;
        m_data.push_back(student);
  }
}

JsonTable::~JsonTable() {
}

void JsonTable::print(std::ostream& out) const {
    const int columnt_count = 4;
    const int name_w = 4;
    const int group_w = 5;
    const int avg_w = 3;
    const int debt_w = 4;
    const int spaces_w = 2;

    std::string separator = "|";
    for (int i = 0; i < columnt_count; ++i) {
        for (uint32_t j = 0; j < m_maxWidths[i]; ++j)
            separator += "-";
        separator += "|";
    }

    out << "| name ";
    for (uint32_t i = 0; i < m_maxWidths[0] - name_w - spaces_w; ++i)
        out << " ";
    out << "| group ";
    for (uint32_t i = 0; i < m_maxWidths[1] - group_w - spaces_w; ++i)
        out << " ";
    out << "| avg ";
    for (uint32_t i = 0; i < m_maxWidths[2] - avg_w - spaces_w; ++i)
        out << " ";
    out << "| debt ";
    for (uint32_t i = 0; i < m_maxWidths[3] - debt_w - spaces_w; ++i)
        out << " ";
    out << "|" << std::endl << separator << std::endl;

    for (size_t i = 0; i < m_data.size(); ++i) {
        out << "| "; m_data[i].printName(out);
        for (uint32_t j = 0;
                      j < m_maxWidths[0] - \
                          m_data[i].getNameLength() - spaces_w + 1;
                    ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printGroup(out);
        for (uint32_t j = 0;\
                      j < m_maxWidths[1] - \
                          m_data[i].getGroupLength() - spaces_w + 1;\
                    ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printAvg(out);
        for (uint32_t j = 0;\
                      j < m_maxWidths[2] - \
                          m_data[i].getAvgLength() - spaces_w + 1;\
                    ++j)
            out << " ";
        out << "|";

        out << " "; m_data[i].printDebt(out);
        for (uint32_t j = 0;\
                      j < m_maxWidths[3] - \
                          m_data[i].getDebtLength() - spaces_w + 1;\
                    ++j)
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
  input_file.open(s, std::ios::in);
  if (!input_file.is_open())
    throw std::runtime_error("File \"" + s + "\" could not be opened!");
  json j;
  input_file >> j;
  input_file.close();
  JsonTable table(j);
  return table;
}

std::ostream& operator<<(std::ostream& out, JsonTable table) {
    table.print(out);
    return out;
}
