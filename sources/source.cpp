// Copyright 2018 Your Name <your_email>
#include <header.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <iostream>
#include <exception>
#include <nlohmann/json.hpp>

using nlohmann::json;

void from_json(const json& j, Student& s);

int main(int argc, char* argv[]) {
  std::string path;
  try {
    if (argc > 1) {
      path = argv[1];
    } else {
      throw std::runtime_error("There is no argument");
    }

    std::ifstream file{path};

    if (!file) {
      throw std::runtime_error{"Unable to open json: " + path};
    }

    json data;
    file >> data;

    if (!data.at("items").is_array()) {
        throw std::runtime_error("Items is not array");
    }

    if (data.at("_meta").at("count") != data.at("items").size()) {
        throw std::runtime_error("Lenght of items` array is not equal to meta count");
    }

    std::vector<Student> students;
    for (auto const& student : data.at("items")) {
      Student s;
      from_json(student, s);
      students.push_back(s);
    }

    std::cout << "| name          | group  | avg  | debt             |"
              << std::endl;
    std::cout << "|---------------|--------|------|------------------|"
              << std::endl;
    for (auto& i : students) {
      std::cout << "| ";
      std::cout.width(13);
      std::cout << i.Name << " |";
      std::cout.width(8);

      if (i.Group.type() == typeid(int)) {
        std::cout << std::any_cast<int>(i.Group);
      } else {
        std::cout << std::any_cast<std::string>(i.Group);
      }
      std::cout << "|";
      std::cout.width(6);

      if (i.Avg.type() == typeid(std::string)) {
        std::cout << std::any_cast<std::string>(i.Avg);
      } else {
        if (i.Avg.type() == typeid(int)) {
          std::cout << std::any_cast<int>(i.Avg);
        } else {
          std::cout << std::any_cast<double>(i.Avg);
        }
      }
      std::cout << "|";

      if (!i.Debt.has_value()) {
        std::cout << "null";
        std::cout.width(15);
      } else {
        if (i.Debt.type() == typeid(std::string)) {
          std::cout << std::any_cast<std::string>(i.Debt);
          std::cout.width(16);
        } else {
          std::vector<std::string> debts =
              std::any_cast<std::vector<std::string>>(i.Debt);
          for (auto& i : debts) {
            std::cout << i << " ";
          }
        }
      }
      std::cout << "|" << std::endl;
      std::cout << "|---------------|--------|------|------------------|"
                << std::endl;
    }
  }
    catch (const std::runtime_error& error) {
      std::cout << "Error: " << error.what();
    }
  system("pause");
  return 0;
}