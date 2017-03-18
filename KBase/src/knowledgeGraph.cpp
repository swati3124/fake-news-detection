// """
// @author: Shubham Mittal
// """

#include "nodeMapLoader.h"
#include "edgeTypeLoader.h"
#include "relationLoader.h"
#include "socket_server.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int main(int argc, char* argv[]) {

  if (argc<4) {
    cout<<"Input files not provided. Provide files in the order of edge-relations, node-map, edge-types & an integer value for whether the file is delimited or not. Exiting !\n";
    return -1;
  }

  path relationsFile (argv[1]);
  path nodesFile (argv[2]);
  path edgetypesFile (argv[3]);

  if (!exists(relationsFile) || !exists(nodesFile) || !exists(edgetypesFile)) {
    cout<<"One of files do not exist. Specify proper path. Exiting !\n";
    return -1;
  }
  cout << "Loading nodeMap ...";
  // Load nodeMap
  nodeMapLoader<string> nodes(nodesFile.string());
  cout << nodes.maxKey << " nodes loaded successfully !\n";

  cout << "Loading edge-types ...";
  // Load edgeTypes
  edgeTypeLoader<string> edgetypes(edgetypesFile.string());
  cout << " " << edgetypes.getmaxRelation() << " relations loaded successfully !\n";

  // Use 'true' for a directed edge between Source and Object
  relationLoader edges(relationsFile.string(), false, 671);
  // Loading relations
  cout << edges.edgeCount << " edges loaded with " << edges.maxRelationCount <<" relations\n";

  pair<int, int> entity_labels = edges.get_nentity_with_ontology();
  /*cout << entity_labels.first << " out of " << nodes.maxKey <<
  " have valid entity label\n";
  cout << entity_labels.second << " out of " << entity_labels.first << " have more than one entity label\n";*/

  if (nodes.maxKey != edges.getMaxKey()) {
    cerr << "Warning: #Node does not match in NodeList (" << nodes.maxKey << ")" << " and EdgeList (" << edges.getMaxKey() <<")";
  }

  if (edgetypes.getmaxRelation() != edges.maxRelationCount) {
    cerr << "Warning: #EdgeTypes does not match in TypeList (" << edgetypes.getmaxRelation() << ")"
    << " and edgelist (" << edges.maxRelationCount <<")";
  }

  graph<string, string> g(nodes, edges, edgetypes);

  cout << "Graph constructed\n";

  socket_server server(10);
  server.start("/tmp/knowledgeGraph", g);
  return 0;
}