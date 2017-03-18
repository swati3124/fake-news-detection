// """
// @author: Shubham Mittal
// """
#include "tripletParser.h"
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace boost;

tripletParser::tripletParser(string input): reader(input, "text/turtle", "UTF-8", "http://dbpedia.org/") {}

int tripletParser::getKey(unordered_map<string, int> &recMap, unordered_map<string, int> &owlMap, int &key, string str, bool isRelation) {

  int id = 0;
  // For relations, take both dbpedia relations and is_a relations from w3 schools
  if (isRelation) {
    if (istarts_with(str, "http://dbpedia.org/ontology/")) {
      str = str.substr(28); // both resource and ontology uri's have the same length
      if (str.length() == 0) {
        return 0;
      }
      if (owlMap.find(str) == owlMap.end()) {
        owlMap[str] = key;
        id = key;
        key++;
      } else {
        id = owlMap.at(str);
      }
    } else if (istarts_with(str, "http://www.w3.org/1999/02/22-rdf-syntax-ns#type")) {  // w3 schools -- is-a relationship
      if (owlMap.find(str) == owlMap.end()) {
        owlMap[str] = key;
        id = key;
        key++;
      } else {
        id = owlMap.at(str);
      }
    } else {
      return 0;
    }
  } else {
    if (istarts_with(str, "http://dbpedia.org/ontology/") || istarts_with(str, "http://dbpedia.org/resource/")) {
      str = str.substr(28);
      if (str.length() == 0) {
        return 0;
      }
      if (recMap.find(str) == recMap.end()) {
        recMap[str] = key;
        id = key;
        key++;
      } else {
        id = recMap.at(str);
      }
    } else {
      return 0;
    }
  }
  return id;
}

void tripletParser::parseTriplets(unordered_map<string, int> &recMap,unordered_map<string, int> &owlMap, int &recID, int &owlID, vector<string> &edges) {
  // Lambda function to compute the accurate links between nodesfor each triple
  reader.read_triples([&](unique_ptr<rdf::triple> SVOtriple) {
    stringstream sstream;
    int source = getKey(recMap, owlMap, recID, SVOtriple->subject->string, false);
    int destination = getKey(recMap, owlMap, recID, SVOtriple->object->string, false);
    int relation = getKey(recMap, owlMap, owlID, SVOtriple->predicate->string, true);

    if (relation!=0 && destination!=0 && source!=0) {
      sstream << source << "\t" << destination << "\t" << relation;
      edges.push_back(sstream.str());    
    }
  });
}