#include <boost/graph/adjacency_list.hpp> // for customizable graphs

int main(int,char*[])
{
  /*
  * The generic class for a graph in Boost is adjacency_list.
  * Up to 7 template parameters can be given, for example:
  *
  * typedef boost::adjacency_list<
  *                       boost::listS,          // out-edges stored in a std::list
  *                       boost::vecS,           // vertex set stored here
  *                       boost::undirectedS,    // bidirectional graph.
  *                       boost::no_property,    // vertex properties
  *                       EdgeWeightProperty,    // edge properties
  *                       boost::no_property,    // graph properties
  *                       boost::listS           // edge storage
  *                       > graph_t;
  *
  * The 'S' at the end of the choices (vecS, etc.) stands for 'S'elector.
  */

  {
  // Construct a graph with the vertices container as a vector
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph;

  // Create a graph with 3 vertices.
  Graph g(3);

  // The graph behaves as a new user would expect if the vertex container type is vector.
  // That is, vertices can be indexed with an unsigned int.
  add_edge(0, 1, g);
  add_edge(1, 2, g);
  }

  {
  // Construct a graph with the vertices container as a set
  typedef boost::adjacency_list<boost::vecS, boost::setS, boost::bidirectionalS> Graph;

  // Since the vertex container type is not a vector, the vertices can NOT be
  // indexed with an unsigned int. I.e. the following will not work:
  //Graph g(3); // 3 vertices add_edge(0, 1, g); add_edge(1, 2, g);

  // Instead, you must add vertices individually so that you get a handle to
  // them (a way to reference them, Boost calls this a "vertex_descriptor"),
  // and then add the edges by referencing these descriptors. Note this is a
  // very generic method, so it would work just as well with a vecS vertex
  // container.

  Graph g; // Create a graph.
  boost::graph_traits<Graph>::vertex_descriptor v0 = add_vertex(g);
  boost::graph_traits<Graph>::vertex_descriptor v1 = add_vertex(g);
  boost::graph_traits<Graph>::vertex_descriptor v2 = add_vertex(g);

  add_edge(v0, v1, g);
  add_edge(v1, v2, g);

  }


  return EXIT_SUCCESS;
}
