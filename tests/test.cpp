// Copyright 2018 Your Name <your_email>
#include <nlohmann/json.hpp>
#include <header.hpp>
#include <gtest/gtest.h>

using nlohmann::json;

void from_json(const json& j, Student& s);

TEST(Json, Case1) {
  json obj {
      {"name", "Ivanov Petr"},
      {"group", "1"},
      {"avg", "4.25"},
      {"debt", "null"},
  };
  Student s;
  from_json(obj, s);
  EXPECT_EQ(s.Name, "Ivanov Petr");
  EXPECT_EQ(std::any_cast<std::string>(s.Group), "1");
  EXPECT_EQ(std::any_cast<std::string>(s.Avg), "4.25");
  EXPECT_EQ(std::any_cast<std::string>(s.Debt), "null");
}

TEST(Json, Case2) {
  json obj {
      {"name", "Sidorov Ivan"},
      {"group", 31},
      {"avg", 4},
      {"debt", "C++"},
  };
  Student s;
  from_json(obj, s);
  EXPECT_EQ(s.Name, "Sidorov Ivan");
  EXPECT_EQ(std::any_cast<int>(s.Group), 31);
  EXPECT_EQ(std::any_cast<int>(s.Avg), 4);
  EXPECT_EQ(std::any_cast<std::string>(s.Debt), "C++");
}

TEST(Json, Case3) {
  json obj {
      {"name", "Pertov Nikita"},
      {"group", "IU8-31"},
      {"avg", 3.33},
      {"debt", {"C++", "Linux", "Network"}},
  };
  Student s;
  from_json(obj, s);
  EXPECT_EQ(s.Name, "Pertov Nikita");
  EXPECT_EQ(std::any_cast<std::string> (s.Group), "IU8-31");
  EXPECT_EQ(std::any_cast<double>(s.Avg), 3.33);
  std::vector<std::string> debts =
      std::any_cast<std::vector<std::string>>(s.Debt);
  EXPECT_EQ(debts[0], "C++");
  EXPECT_EQ(debts[1], "Linux");
  EXPECT_EQ(debts[2], "Network");
}


