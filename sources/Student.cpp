// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include "Student.hpp"
#include <sstream>
void Student::to_json(json& j, const Student& s) {
    j = json{{"name",  s.name }, \
             {"group", s.group}, \
             {"avg",   s.avg  }, \
             {"debt",  s.debt }};
}

void Student::from_json(const json& j, Student& p) {
    j.at("name").get_to(p.name);
    j.at("group").get_to(p.group);
    j.at("avg").get_to(p.avg);
    j.at("debt").get_to(p.debt);
}

uint32_t Student::getNameLength() {
    return static_cast<uint32_t>(name.length());
}

uint32_t Student::getGroupLength() {
    if (group.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(group).length());
    else if (group.type() == typeid(int))
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(group)).length());
    else
        return 0;
}

uint32_t Student::getAvgLength() {
    if (avg.type() == typeid(int)) {
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(avg)).length());
    } else if (avg.type() == typeid(float)) {
        std::stringstream str_stream;
        str_stream.precision(3);
        str_stream << std::any_cast<float>(avg);
        return static_cast<uint32_t>(\
            str_stream.str().length());
    } else if (avg.type() == typeid(std::string)) {
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(avg).length());
    } else {
        return 0;
    }
}

uint32_t Student::getDebtLength() {
    if (debt.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(debt).length());
    else if (debt.type() == typeid(std::vector<std::string>))
        return static_cast<uint32_t>(\
            std::to_string(\
            std::any_cast<std::vector<std::string>>(\
            debt).size()).length() + 6);
    else if (debt.type() == typeid(std::nullptr_t))
        return 4;
    else
        return 0;
}

void Student::printName(std::ostream& out) {
    out << name;
}

void Student::printGroup(std::ostream& out) {
    if (group.type() == typeid(std::string))
        out << std::any_cast<std::string>(group);
    else if (group.type() == typeid(int))
        out << std::any_cast<int>(group);
    else
        out << "ERR";
}

void Student::printAvg(std::ostream& out) {
    if (avg.type() == typeid(int)) {
        out << std::any_cast<int>(avg);
    } else if (avg.type() == typeid(float)) {
        out.precision(3);
        out << std::any_cast<float>(avg);
        out.precision(0);
    } else if (avg.type() == typeid(std::string)) {
        out << std::any_cast<std::string>(avg);
    } else {
        out << "ERR";
    }
}

void Student::printDebt(std::ostream& out) {
    if (debt.type() == typeid(std::string))
        out << std::any_cast<std::string>(debt);
    else if (debt.type() == typeid(std::vector<std::string>))
        out << std::any_cast<std::vector<std::string>>(debt).size() <<\
               " items";
    else if (debt.type() == typeid(std::nullptr_t))
        out << "null";
    else
        out << "ERR";
}
