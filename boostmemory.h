#ifndef __BOOSTMEMORY_H
#define __BOOSTMEMORY_H

#include "brain.h"
#include "stdlibs.h"

#include "boost/graph/adjacency_list.hpp"

#include "boost/pending/indirect_cmp.hpp"
#include "boost/pending/integer_range.hpp"

#include "boost/graph/graph_traits.hpp"

#include "boost/graph/graphviz.hpp"

namespace brain {

class BoostMemory : public IMemory {
 private:
  struct link_t {
    typedef boost::edge_property_tag kind;
  };
  struct node_t {
    typedef boost::vertex_property_tag kind;
  };
  struct vertex_index_t {
    typedef boost::vertex_property_tag kind;
  };
  typedef boost::property<node_t, NodePtr> NodeProperty;
  typedef boost::property<link_t, LinkPtr> LinkProperty;

  typedef boost::adjacency_list<boost::vecS, boost::multisetS,
                                boost::bidirectionalS, NodeProperty,
                                LinkProperty>
      Graph;

  Graph g;

  boost::property_map<Graph, link_t>::type links;
  boost::property_map<Graph, node_t>::type nodes;
  boost::property_map<Graph, vertex_index_t>::type vertex_id;

  typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
  typedef boost::graph_traits<Graph>::edge_descriptor Edge;

  std::map<NodeId, Vertex> nodesToVertices;
  IStrategyPtr strategy;

  NodeId maxNodeId;

  // typename GraphTraits::edge_descriptor e;
 public:
  BoostMemory(IStrategyPtr strategy);
  std::string serialize();
  void deserialize(std::string fromString);
  void getVisualization(const char* filename);

  std::list<std::pair<LinkPtr, NodePtr> > getParentLinks(NodePtr node);
  std::list<std::pair<LinkPtr, NodePtr> > getChildrenLinks(NodePtr node);

  NodePtr remember(std::vector<NodePtr>* nodes, std::vector<LinkPtr>* links,
                   int amount, NodeGroupProcessorPtr sender);
};

}  // namespace brain

#endif  // BOOSTMEMORY_H
