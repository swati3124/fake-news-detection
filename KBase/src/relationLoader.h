// """
// @author: Shubham Mittal
// """

#ifndef RELATION_LOADER_H
#define RELATION_LOADER_H

#include "edge_list.h"

#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <map>

class relationLoader {

public:

  const int relationType;
  std::vector<edge_list> edgeMap;
  std::vector<int> edgeTypeCount;
  std::map<int, std::pair<std::set<int>, int> > nodeTypeCount;
  int maxKey, maxRelationCount, edgeCount;
  int entityWithRelationType;
  int entityWithMultipleRelType;
  bool isFileDelimited=false; //TODO---change to accept user input

  relationLoader(std::string edgeListFile, bool isDirGraph = false, int relationType = 671) : maxKey(0), maxRelationCount(0), edgeCount(0), relationType(relationType), entityWithRelationType(-1), entityWithMultipleRelType(0) {
    std::fstream fin(edgeListFile, std::fstream::in);
    //std::cout <<"File::" << edgeListFile <<"\n";
    int source, destination, relation;
    char delimiter;
    int iter=0;

    while(!fin.eof()) {
    //while(iter<100) {
      if (isFileDelimited) {
        fin >> source >> delimiter >> destination >> delimiter >>relation;
      } else {
        fin >> source >> destination >> relation;
      }
      //std::cout<<"Iter: " << iter <<"\tSource:" << source <<"\tdestination" << destination << "relation: " << relation << "\n";
      if (std::max(source, destination) >= edgeMap.size()) { 
        edgeMap.resize(std::max(source, destination) + 1, edge_list());
      }

      if (relation >= edgeTypeCount.size()) {
        edgeTypeCount.resize(relation + 1, 0);
      }
      edgeTypeCount[relation]++;

      // Add Forward & Backward edge
      edgeMap[source].connect_to(destination, relation);
      if (!isDirGraph) 
        edgeMap[destination].connected_by(source, relation);

      if (maxKey < std::max(source, destination)) maxKey = std::max(source, destination);
      if (maxRelationCount < relation) maxRelationCount = relation;

      // Add type count for edge: src - type - dest
      if (relation == relationType) {
        if (nodeTypeCount.find(destination) == nodeTypeCount.end()) {
          nodeTypeCount[destination] = std::pair<std::set<int>, int>();
        }
        nodeTypeCount[destination].second++;
        nodeTypeCount[destination].first.insert(source);
      }
      edgeCount++;
      //std::cout<<"Iter: " << iter <<"\tRelation:" << relation <<"\n";
      iter++;
    }

    fin.close();
  }

  edge_list& get_edges(int source) {
    return edgeMap.at(source);
  }

  int getMaxKey() const {
    return maxKey;
  }

  int getMax_rel() const {
    return maxRelationCount;
  }

  int get_edge_type_count(int relType) const {
    return relType == 0 ? getMaxKey() : edgeTypeCount.at(relType);
  }

  std::set<std::pair<int, int> > get_neighbors_except_rel(int id, int relType = 0,bool isDirGraph = false) {
    std::set<std::pair<int, int> > neighbors;
    for (auto it = get_edges(id).get_forward().cbegin(); it != get_edges(id).get_forward().cend(); ++it) {
      if (relType != it->second) {
        neighbors.insert(*it);
      }
    }
    if (!isDirGraph) {
      for (auto it = get_edges(id).get_backward().cbegin(); it != get_edges(id).get_backward().cend(); ++it) {
        if (relType != it->second) {
          neighbors.insert(*it);
        }
      }
    }
    return neighbors;
  }

  /**
   * Return neighbors of `id` if they are not connected by `discard_rel`.
   */
  std::set<int> get_neighbors(int id, int discard_rel = 0, bool isDirGraph = false) {
    std::set<int> neighbors;
    for (auto it = get_edges(id).get_forward().cbegin(); it != get_edges(id).get_forward().cend(); ++it) {
      if (discard_rel == 0 || discard_rel != it->second) {
        neighbors.insert(it->first);
      }
    }
    if (!isDirGraph) {
      for (auto it = get_edges(id).get_backward().cbegin(); it != get_edges(id).get_backward().cend(); ++it) {
        if (discard_rel == 0 || discard_rel != it->second) {
          neighbors.insert(it->first);
        }
      }
    }
    return neighbors;
  }

  std::set<int> get_neighbors_by_rel(int id, int relation, bool isDirGraph = false) {
    std::set<int> neighbors;
    for (auto it = get_edges(id).get_forward().cbegin(); it != get_edges(id).get_forward().cend(); ++it) {
      if (relation == it->second) {
        neighbors.insert(it->first);
      }
    }
    if (!isDirGraph) {
      for (auto it = get_edges(id).get_backward().cbegin(); it != get_edges(id).get_backward().cend(); ++it) {
        if (relation == it->second) {
          neighbors.insert(it->first);
        }
      }
    }
    return neighbors;
  }

  int get_neighbor_count_by_rel(int id, int relation, bool isDirGraph = false) {
    int res = 0;
    for (auto it = get_edges(id).get_forward().cbegin(); it != get_edges(id).get_forward().cend(); ++it) {
      if (relation == it->second) {
        res++;
      }
    }
    if (!isDirGraph) {
      for (auto it = get_edges(id).get_backward().cbegin(); it != get_edges(id).get_backward().cend(); ++it) {
        if (relation == it->second) {
          res++;
        }
      }
    }

    return res;
  }

  std::vector<std::pair<int, int> > get_common_neighbor_except_rel(int id1, int id2,int relType = 0,bool isDirGraph = false) {
    std::set<std::pair<int, int> > neighbors_1 = get_neighbors_except_rel(id1, relType, isDirGraph);
    std::set<std::pair<int, int> > neighbors_2 = get_neighbors_except_rel(id2, relType, isDirGraph);

    std::vector<std::pair<int, int> > common_neighbors;

    for (auto it = neighbors_1.cbegin(); it != neighbors_1.cend(); ++it) {
      if (neighbors_2.find(*it) != neighbors_2.end()) {
        common_neighbors.push_back(*it);
      }
    }

    return common_neighbors;
  }

  std::vector<int> get_common_neighbor(int id1, int id2, int discard_rel = 0,
                                                bool isDirGraph = false) {
    std::set<int> neighbors_1 = get_neighbors(id1, discard_rel, isDirGraph);
    std::set<int> neighbors_2 = get_neighbors(id2, discard_rel, isDirGraph);

    std::vector<int> common_neighbors;

    for (auto it = neighbors_1.cbegin(); it != neighbors_1.cend(); ++it) {
      if (neighbors_2.find(*it) != neighbors_2.end()) {
        common_neighbors.push_back(*it);
      }
    }

    return common_neighbors;
  }

  std::vector<int> get_ontology(int id) {
    std::vector<int> types;
    std::set<std::pair<int, int> > &edges = get_edges(id).get_forward();
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      if (it->second == relationType) { // this is an ontology edge
        types.push_back(it->first);
      }
    }
    sort(types.begin(), types.end());
    return types;
  }

  std::set<int> get_ontology_set(int id) {
    std::set<int> types;
    std::set<std::pair<int, int> > &edges = get_edges(id).get_forward();
    for (auto it = edges.begin(); it != edges.end(); ++it) {
      if (it->second == relationType) { // this is an ontology edge
        types.insert(it->first);
      }
    }
    return types;
  }

  /**
   * Return vertices sharing the same ontology set
   */
  std::vector<std::pair<int, std::set<int> > > get_ontology_siblings(int id) {
    std::vector<std::pair<int, std::set<int> > > res;

    std::vector<int> node_ontology = get_ontology(id);
    for (int i = 0; i < node_ontology.size(); i++) {
      res.push_back(std::pair<int, std::set<int> >(node_ontology[i],nodeTypeCount[node_ontology[i]].first));
    }
    return res;
  }

  std::set<int> get_ontology_siblings(int id, double tol) {

    std::set<int> res;

    std::set<int> ontology = get_ontology_set(id);

    for (auto it_ontology = ontology.cbegin(); it_ontology != ontology.cend(); ++it_ontology) {
      for (auto it_entity = nodeTypeCount[*it_ontology].first.cbegin();
           it_entity != nodeTypeCount[*it_ontology].first.cend(); ++it_entity) {
        if (ontology == get_ontology_set(*it_entity)) {
          res.insert(*it_entity);
        }
      }
    }
    return res;
  }

  std::vector<std::pair<int, int> > get_ontology_sibling_count(int id) {
    std::vector<std::pair<int, int> > res;

    std::vector<int> node_ontology = get_ontology(id);
    for (int i = 0; i < node_ontology.size(); i++) {
      res.push_back(std::pair<int, int>(node_ontology[i],nodeTypeCount[node_ontology[i]].second));
    }
    return res;
  }

    std::pair<int, int> get_nentity_with_ontology() {
      if (entityWithRelationType == -1) {
        entityWithRelationType = 0;
        //std::cout<<"maxKey : " << maxKey <<"\n";
        for (int id = 0; id < maxKey; id++) {
          int counter = 0;
          std::set<std::pair<int, int> > &edges = get_edges(id).get_forward();
          for (auto it = edges.begin(); it != edges.end(); ++it)
            if (it->second == relationType) 
              counter++;
          if (counter > 0) entityWithRelationType++;
          if (counter > 1) entityWithMultipleRelType++;
        }
      }
      return std::pair<int, int>(entityWithRelationType, entityWithMultipleRelType);
    }

  int getNodeTypeCount(int id) {
    return nodeTypeCount[id].second;
  }

  inline int get_type_rel() { return relationType; }

    int get_nentity_connected_by_rel(int relation) {
      int counter = 0;
      for (int id = 0; id < maxKey; id++) {
        std::set<std::pair<int, int> > &edges = get_edges(id).get_backward();
        for (auto it = edges.cbegin(); it != edges.cend(); ++it) {
          if (it->second == relation) {
            counter++; // if id is connected by relation type, break;
            break;
          }
        }
      }
      return counter;
    }

    int get_nontology() {
      return get_nentity_connected_by_rel(relationType);
    }
};
#endif