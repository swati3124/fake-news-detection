// """
// @author: Shubham Mittal
// """

#ifndef EDGE_LIST
#define EDGE_LIST

#include <vector>
#include <fstream>
#include <algorithm>
#include <utility>
#include <set>

class edge_list {
  /* Edge pairs are <node,rel>, the other endpoint is the index of the container */
  std::set< std::pair<int, int> > forward; /* Directed edge*/
  std::set< std::pair<int, int> > backward; /* Reversed edge for mimicking undirected graph */
  std::set<int> in_neighbors;
  std::set<int> out_neighbors;
  std::set<int> neighbors;

public:

  edge_list() : forward(std::set< std::pair<int, int> >()),
                backward(std::set< std::pair<int, int> >()){}

  inline void connect_to(int target, int rel) {
    forward.insert(std::pair<int, int>(target, rel));
    out_neighbors.insert(target);
    neighbors.insert(target);
  }
  inline void connected_by(int source, int rel) {
    backward.insert(std::pair<int, int>(source, rel));
    in_neighbors.insert(source);
    neighbors.insert(source);
  }
  inline void disconnect_to(int target, int rel) {
    forward.erase(std::pair<int, int>(target, rel));
  }
  inline void disconnected_by(int source, int rel) {
    backward.erase(std::pair<int, int>(source, rel));
  }

  std::set< std::pair<int, int> >& get_forward() noexcept {return forward;}
  std::set< std::pair<int, int> >& get_backward() noexcept {return backward;}

  const std::set<int> &get_in_neighbors()  noexcept { return in_neighbors; }

  const std::set<int> &get_out_neighbors()  noexcept { return out_neighbors; }

  const std::set<int> &get_neighbors() noexcept {
    return neighbors;
  }

  inline size_t get_in_deg() noexcept {
    return in_neighbors.size();
  }

  inline size_t get_out_deg() noexcept {
    return out_neighbors.size();
  }

  inline size_t get_deg() noexcept {
    return neighbors.size();
  }

};
#endif