// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include "Student.hpp"
#include <sstream>
void Student::to_json(json& j, const Student& s) {
    j = json{{"name",  s.m_name}, \
             {"group", s.m_group}, \
             {"avg",   s.m_avg}, \
             {"debt",  s.m_debt}};
}

void Student::from_json(const json& j, Student& p) {
    j.at("name").get_to(p.m_name);
    j.at("group").get_to(p.m_group);
    j.at("avg").get_to(p.m_avg);
    j.at("debt").get_to(p.m_debt);
}

uint32_t Student::getNameLength() const {
    return static_cast<uint32_t>(m_name.length());
}

uint32_t Student::getGroupLength() const {
    if (m_group.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(m_group).length());
    else if (m_group.type() == typeid(int))
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(m_group)).length());
    else
        return 0;
}

uint32_t Student::getAvgLength() const {
    if (m_avg.type() == typeid(int)) {
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(m_avg)).length());
    } else if (m_avg.type() == typeid(float)) {
        std::stringstream str_stream;
        str_stream.precision(3);
        str_stream << std::any_cast<float>(m_avg);
        return static_cast<uint32_t>(\
            str_stream.str().length());
    } else if (m_avg.type() == typeid(std::string)) {
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(m_avg).length());
    } else {
        return 0;
    }
}

uint32_t Student::getDebtLength() const {
    if (m_debt.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(m_debt).length());
    else if (m_debt.type() == typeid(std::vector<std::string>))
        return static_cast<uint32_t>(std::to_string(\
       std::any_cast<std::vector<std::string>>(m_debt).size()).length() + 6);
    else if (m_debt.type() == typeid(std::nullptr_t))
        return 4;
    else
        return 0;
}

void Student::printName(std::ostream& out) const {
    out << m_name;
}

void Student::printGroup(std::ostream& out) const {
    if (m_group.type() == typeid(std::string))
        out << std::any_cast<std::string>(m_group);
    else if (m_group.type() == typeid(int))
        out << std::any_cast<int>(m_group);
    else
        out << "ERR";
}

void Student::printAvg(std::ostream& out) const {
    if (m_avg.type() == typeid(int)) {
        out << std::any_cast<int>(m_avg);
    } else if (m_avg.type() == typeid(float)) {
        out.precision(3);
        out << std::any_cast<float>(m_avg);
        out.precision(0);
    } else if (m_avg.type() == typeid(std::string)) {
        out << std::any_cast<std::string>(m_avg);
    } else {
        out << "ERR";
    }
}

void Student::printDebt(std::ostream& out) const {
    if (m_debt.type() == typeid(std::string))
        out << std::any_cast<std::string>(m_debt);
    else if (m_debt.type() == typeid(std::vector<std::string>))
        out << std::any_cast<std::vector<std::string>>(m_debt).size() <<\
               " items";
    else if (m_debt.type() == typeid(std::nullptr_t))
        out << "null";
    else
        out << "ERR";
}
