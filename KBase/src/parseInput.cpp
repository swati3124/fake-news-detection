// """
// @author: Shubham Mittal
// """
#include "tripletParser.h"

#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

using namespace std;
using namespace boost;
using namespace boost::filesystem;

void flushMap(unordered_map<string, int> &map, string file_path) {
  std::fstream fs(file_path, std::fstream::out);
  for (unordered_map<string, int>::const_iterator iter = map.cbegin(); iter != map.cend(); iter++) {
    fs << iter->second << "\t" << iter->first << endl;
  }
  fs.close();
}

int main(int argc, char* argv[]) {

  if (argc<2) {
    cout<<"Input data file not provided. Exiting !\n";
    return -1;
  }
  // Parse Input
  // All dbpedia resources are represented by rec's and ontologies by owl
  int recID = 1, owlID = 1;
  vector<string> edges;
  unordered_map<string, int> recMap = unordered_map<string, int>();
  unordered_map<string, int> owlMap = unordered_map<string, int>();

  try{
    path p (argv[1]);
    if (exists(p)) {
      if (is_regular_file(p)) {
        //cout <<p.string()<<"\n";
        tripletParser tParser(p.string());
        tParser.parseTriplets(recMap, owlMap, recID, owlID, edges);
        cout << p << " processed.\n";
      }
      else
        cout << "File does not conform to correct input\n";
    }
  } catch (std::exception &e) {
      cout << e.what();
      return -1;
  }

  flushMap(recMap, "nodeMap");
  flushMap(owlMap, "edgeMap");

  if (argc<3 || (argc==3 && atoi(argv[2])==1)) {
      // Remove edges already added
      cout << "Remove edges that have already been added ... \n";
      sort(edges.begin(), edges.end()); // Can be too expensive - do only if insisted
      edges.erase(unique(edges.begin(), edges.end()), edges.end());
    }

  //flushVector(edges, "edgelist");
  std::fstream fs("edgelist", std::fstream::out);
  for (vector<string>::const_iterator iter = edges.cbegin(); iter != edges.cend(); iter++) {
    fs << *iter << endl;
  }
  fs.close();

  cout << "Graph successfuly generated with " << recID << " nodes, " << edges.size() << " edges and " << owlID << " edge types\n";

  return 0;
}