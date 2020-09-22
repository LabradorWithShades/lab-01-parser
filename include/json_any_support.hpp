// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com
#ifndef INCLUDE_JSON_ANY_SUPPORT_HPP_
#define INCLUDE_JSON_ANY_SUPPORT_HPP_

#include <nlohmann/json.hpp>
#include <any>
#include <string>
#include <vector>

namespace nlohmann {
template <>
struct adl_serializer<std::any> {
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
}// namespace nlohmann

#endif //INCLUDE_JSON_ANY_SUPPORT_HPP_
