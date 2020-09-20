// Copyright 2020 Your Name <your_email>
#include <header.hpp>
#include <string>
#include <nlohmann/json.hpp>

using nlohmann::json;

void from_json(const json& j, Student& s) {
  j.at("name").get_to(s.Name);

  if (j.at("group").is_number_integer()) {
    int var = j.at("group");
    s.Group = var;
  } else {
    std::string var = j.at("group");
    s.Group = var;
  }

  if (j.at("avg").is_string()) {
    std::string var = j.at("avg");
    s.Avg = var;
  } else {
    if (j.at("avg").is_number_integer()) {
      int var = j.at("avg");
      s.Avg = var;
    } else {
      double var = j.at("avg");
      s.Avg = var;
    }
  }
  if (j.at("debt").is_null()) {
  } else {
    if (j.at("debt").is_string()) {
      std::string var = j.at("debt");
      s.Debt = var;
    } else {
      std::vector<std::string> debts = j.at("debt");
      s.Debt = debts;
    }
  }
}
