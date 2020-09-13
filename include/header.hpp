// Copyright 2018 Your Name <your_email>
#include <string>
#include <any>
#include <nlohmann/json.hpp>

using nlohmann::json;

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

namespace ns {
struct Student {
  std::string Name;
  std::any Group;
  double Avg;
  std::any Debt;
};


#endif // INCLUDE_HEADER_HPP_
