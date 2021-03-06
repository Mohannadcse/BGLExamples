#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/array.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>

template <typename EdgeWeightMap>
struct positive_edge_weight {
  positive_edge_weight() { }
  positive_edge_weight(EdgeWeightMap weight) : m_weight(weight) { }
  template <typename Edge>
  bool operator()(const Edge& e) const {
    return 0 < get(m_weight, e);
  }
  EdgeWeightMap m_weight;
};

int main()
{
  using namespace boost;

  typedef adjacency_list<vecS, vecS, directedS,
    no_property, property<edge_weight_t, int> > Graph;
  typedef property_map<Graph, edge_weight_t>::type EdgeWeightMap;

  enum { A, B, C, D, E, N };
  const char* name = "ABCDE";
  Graph g(N);
  add_edge(A, B, 2, g);
  add_edge(A, C, 0, g);
  add_edge(C, D, 1, g);
  add_edge(C, E, 0, g);
  add_edge(D, B, 3, g);
  add_edge(E, C, 0, g);

  positive_edge_weight<EdgeWeightMap> filter(get(edge_weight, g));
  filtered_graph<Graph, positive_edge_weight<EdgeWeightMap> > filteredGraph(g, filter);

  boost::print_graph(filteredGraph, name);
  return 0;
}
