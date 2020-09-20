// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#include "Student.hpp"
void Student::to_json(json& j, const Student& s) {
    j = json{{"name",  s.name },\
             {"group", s.group},\
             {"avg",   s.avg  },\
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
    if (avg.type() == typeid(int))
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(avg)).length());
    else if (avg.type() == typeid(float))
        return static_cast<uint32_t>(\
            std::to_string(std::any_cast<float>(avg)).length());
    else if (avg.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(avg).length());
    else
        return 0;
}

uint32_t Student::getDebtLength() {
    if (debt.type() == typeid(std::string))
        return static_cast<uint32_t>(\
            std::any_cast<std::string>(debt).length());
    else if (debt.type() == typeid(std::vector<std::string>))
        return static_cast<uint32_t>(\
            std::any_cast<std::vector<std::string>>(debt).size() + 6);
    else if (debt.type() == typeid(nullptr_t))
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
        out << "ERROR";
}

void Student::printAvg(std::ostream& out) {
    if (avg.type() == typeid(int))
        out << std::any_cast<int>(avg);
    else if (avg.type() == typeid(float))
        out << out.precision(2) << std::any_cast<float>(avg);
    else if (avg.type() == typeid(std::string))
        out << std::any_cast<std::string>(avg);
    else
        out << "ERROR";
}

void Student::printDebt(std::ostream& out) {
    if (debt.type() == typeid(std::string))
        out << std::any_cast<std::string>(debt);
    else if (debt.type() == typeid(std::vector<std::string>))
        out << std::any_cast<std::vector<std::string>>(debt).size() <<\
               " items";
    else
        out << "ERROR";
}
