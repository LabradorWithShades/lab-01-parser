#ifndef INCLUDE_JSON_ANY_SUPPORT_HPP
#define INCLUDE_JSON_ANY_SUPPORT_HPP

#include <nlohmann/json.hpp>
#include <any>
#include <string>
#include <array>

namespace nlohmann {
    template <>
    struct adl_serializer<std::any> {
    static void to_json(json& j, const std::any& any_var) {
        if (any_var.type() == typeid(std::string)) {
            j = std::any_cast<std::string>(any_var);
        } else if (any_var.type() == typeid(int)) {
            j = std::any_cast<int>(any_var);
        } else if (any_var.type() == typeid(float)) {
            j = std::any_cast<float>(any_var);
        } else if (any_var.type() == typeid(std::vector<std::string>)) {
            j = std::any_cast<std::vector<std::string>>(any_var);
        } else {
            j = nullptr;
        }
    }

    static void from_json(const json& j, std::any& any_var) {
        if (j.is_null()) {
            any_var = nullptr;
        } else if (j.is_number_integer()) {
            any_var = j.get<int>();
        } else if (j.is_number_float()) {
            any_var = j.get<float>();
        } else if (j.is_string()) {
            any_var = j.get<std::string>();
        } else if (j.is_array()) {
            std::vector<std::string> v(0);
            for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it) {
                std::string str = it.value();
                v.push_back(str);
            }
            any_var = v;
        }
    }
};
}

#endif //PARSER_JSON_ANY_SUPPORT_HPP
