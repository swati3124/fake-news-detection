// """
// @author: Shubham Mittal
// """

#ifndef NODE_MAP_LOADER_H
#define NODE_MAP_LOADER_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

template <typename T> class nodeMapLoader {

public:
  typedef T valType;
  std::vector<valType> nodeMap;
  int maxKey;
  int minKey;

  nodeMapLoader(std::string nodeMapFile) noexcept : maxKey(0), minKey(0), nodeMap(std::vector<valType>()) {
    valType val;
    int key;
    int iter=0;
    //std::cout<<nodeMapFile<<"\n";
    std::fstream fin(nodeMapFile, std::fstream::in);
    while(!fin.eof()) {
      fin >> key;
      fin.get();
      fin >> val;

      if (key >= nodeMap.size())
        nodeMap.resize(key + 1, "");
      nodeMap[key] = val;

      minKey = std::min(minKey, key);
      maxKey = std::max(maxKey, key);
      //std::cout<<"Iter: " << iter << "Val: " << val;
      //std::cout<<"\n";
      iter++;
    }
    fin.close();
  };

  valType getVal(int key) const {
    return nodeMap.at(key);
  }

  bool exists(int key) const noexcept {
    return (key <= maxKey) && (key >= minKey);
  }

  int getMaxKey() const noexcept {
    return maxKey;
  }

  int getMinKey() const noexcept {
    return minKey;
  }
};

#endif