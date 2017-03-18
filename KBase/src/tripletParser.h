// """
// @author: Shubham Mittal
// """

#include <string>
#include <rdf++.h>
#include <boost/unordered_map.hpp>

class tripletParser {
  rdf::reader reader;
  int getKey(boost::unordered_map<std::string, int> &recMap, boost::unordered_map<std::string, int> &owlMap, int &key, std::string str, bool isRelation = false);

public:
  tripletParser(std::string input);
  void parseTriplets(boost::unordered_map<std::string, int> &recMap, boost::unordered_map<std::string, int> &owlMap,int &recID, int &owlID, std::vector<std::string> &edges);

};