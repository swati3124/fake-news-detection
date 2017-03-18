// """
// @author: Shubham Mittal
// """

#ifndef EDGE_TYPE_LOADER_H
#define EDGE_TYPE_LOADER_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>

template<typename T>
class edgeTypeLoader {

public:
  typedef T value_type;

private:
  std::vector<value_type> type_map;
  int maxRelation;

public:

  edgeTypeLoader(std::string type_filepath) noexcept : maxRelation(0), type_map(std::vector<value_type>()) {

    std::fstream fin(type_filepath, std::fstream::in);

    value_type val;
    int key;

    while (!fin.eof()) {
      fin >> key;
      fin.get();
      fin >> val;

      if (key >= type_map.size()) {
        type_map.resize(key + 1, "");
      }
      type_map[key] = val;

      if (maxRelation < key) maxRelation = key;
    }

    fin.close();
  };

  int getmaxRelation() const noexcept {
    return maxRelation;
  }

  value_type getVal(int key) const {
    return type_map.at(key);
  }

};
#endif