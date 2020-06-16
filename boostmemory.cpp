#include "boostmemory.h"

using namespace std;
using namespace brain;
using namespace boost;

BoostMemory::BoostMemory(IStrategyPtr strategy) {
  g = Graph(0);
  links = boost::get(link_t(), g);
  nodes = boost::get(node_t(), g);
  vertex_id = boost::get(vertex_index_t(), g);
  this->strategy = strategy;
  maxNodeId = 1;

  /*
  Vertex v = add_vertex(g);
  Vertex u = add_vertex(g);
  Edge edge = add_edge(v, u, g).first;
  graph_traits<Graph>::out_edge_iterator e, e_end;
  for (tie(e, e_end) = out_edges(v, g); e != e_end; ++e)
  {
      cout << (*e);
  }
  */
}

string BoostMemory::serialize() { return ""; }

void BoostMemory::deserialize(string fromString) {}
/*
void BoostMemory::getVisualization2(const char* filename)
{
    std::fstream output(filename, std::fstream::out);
    //MemoryGraphWriter<Graph, link_t, node_t> writer(&links, &nodes);
    //MemoryGraphWriter writer(&links, &nodes);
    dfs_label_writer writer;

    write_graphviz(output, g, writer, writer, vertex_id);
    output.close();
}
*/
void BoostMemory::getVisualization(const char* filename) {
  fstream out(filename, std::fstream::out);
  out << "Digraph G {" << std::endl;

  graph_traits<Graph>::vertex_iterator i, end;

  for (tie(i, end) = vertices(g); i != end; ++i) {
    NodePtr node = nodes[*i];
    out << node->id;

    out << "[label=\"" << node->id << " (" << node->amount << ")\" ] ";
    //
    out << ";" << std::endl;
  }
  graph_traits<Graph>::edge_iterator ei, edge_end;
  out.precision(1);
  for (tie(ei, edge_end) = edges(g); ei != edge_end; ++ei) {
    out << nodes[source(*ei, g)]->id << "->" << nodes[target(*ei, g)]->id
        << " ";
    out << "[label=\"amount: ";
    out << links[*ei]->amount;
    out << "\\n";
    links[*ei]->offsets->outputToStream(out);
    out << "\" ";
    //
    out << "];" << std::endl;
  }
  out << "}" << std::endl;
  out.close();
}

list<pair<LinkPtr, NodePtr> > BoostMemory::getParentLinks(NodePtr node) {
  Vertex v = nodesToVertices[node->id];
  list<pair<LinkPtr, NodePtr> > result;
  graph_traits<Graph>::out_edge_iterator e, e_end;
  for (tie(e, e_end) = out_edges(v, g); e != e_end; ++e) {
    LinkPtr l = links[*e];
    NodePtr n = nodes[target(*e, g)];
    result.push_back(pair<LinkPtr, NodePtr>(l, n));
  }
  return result;
}

list<pair<LinkPtr, NodePtr> > BoostMemory::getChildrenLinks(NodePtr node) {
  Vertex v = nodesToVertices[node->id];
  list<pair<LinkPtr, NodePtr> > result;
  graph_traits<Graph>::in_edge_iterator e, e_end;
  for (tie(e, e_end) = in_edges(v, g); e != e_end; ++e) {
    LinkPtr l = links[*e];
    NodePtr n = nodes[source(*e, g)];
    result.push_back(pair<LinkPtr, NodePtr>(l, n));
  }
  return result;
}

NodePtr BoostMemory::remember(vector<NodePtr>* nodesVector,
                              vector<LinkPtr>* linksVector, int amount,
                              NodeGroupProcessorPtr sender) {
  // vector<Vertex> v(nodesVector->size());
  list<Vertex> targets;
  list<int> closestLink;
  map<Vertex, float> deltas;
  // vector<Vertex> targetVert;
  float inf = (float)(1 << 20);

  for (int i = 0; i < nodesVector->size(); i++) {
    if (nodesToVertices.find((*nodesVector)[i]->id) == nodesToVertices.end()) {
      Vertex vv = add_vertex(g);
      nodes[vv] = (*nodesVector)[i];
      (*nodesVector)[i]->amount = 1;
      nodesToVertices[(*nodesVector)[i]->id] = vv;
    }
  }

  graph_traits<Graph>::out_edge_iterator e, e_end;

  float minDelta = inf;

  for (tie(e, e_end) = out_edges(nodesToVertices[(*nodesVector)[0]->id], g);
       e != e_end; ++e) {
    if (in_degree(target(*e, g), g) == nodesVector->size()) {
      targets.push_back(target(*e, g));
    }
  }

  vector<list<Vertex>::iterator> toDelete;

  for (int i = 1; i < nodesVector->size(); i++) {
    Vertex v = nodesToVertices[(*nodesVector)[i]->id];
    toDelete.clear();
    for (list<Vertex>::iterator it = targets.begin(); it != targets.end();
         it++) {
      std::pair<Edge, bool> res = edge(v, *it, g);
      if (!res.second) {
        toDelete.push_back(it);
      }
    }
    for (int i = 0; i < toDelete.size(); i++) {
      targets.erase(toDelete[i]);
    }
  }

  set<LinkPtr> usedLinks;
  float minSum = inf;
  Vertex bestTarget = NULL;
  vector<Edge> curAssignation(linksVector->size());
  vector<Edge> bestAssignation(linksVector->size());
  bool wasAssignation = false;
  for (list<Vertex>::iterator it = targets.begin(); it != targets.end(); it++) {
    float deltaSum = 0.0f;
    usedLinks.clear();
    int j = 0;
    graph_traits<Graph>::in_edge_iterator e, e_end;
    int assigned = 0;
    for (tie(e, e_end) = in_edges(*it, g); e != e_end; ++e, j++) {
      minDelta = inf;
      LinkPtr lp = links[*e];
      LinkPtr curLink;
      int ii;
      for (int i = 0; i < linksVector->size(); i++) {
        if (usedLinks.find((*linksVector)[i]) != usedLinks.end()) continue;
        float delta =
            lp->offsets->getDelta((*linksVector)[i]->offsets, strategy);
        if (delta < minDelta) {
          minDelta = delta;
          ii = i;
          curLink = (*linksVector)[i];
        }
      }
      deltaSum += minDelta;
      if (minDelta < inf) {
        usedLinks.insert(curLink);
        curAssignation[ii] = *e;
        assigned++;
      } else {
        break;
      }
    }
    if (assigned == nodesVector->size() && deltaSum < minSum) {
      minSum = deltaSum;
      bestTarget = *it;
      for (int i = 0; i < linksVector->size(); i++) {
        bestAssignation[i] = curAssignation[i];
      }
      wasAssignation = true;
    }
  }

  if (!wasAssignation || !bestTarget ||
      minSum > strategy->getMaxDelta() * (float)linksVector->size()) {
    // create new node
    NodePtr newNode(new Node());
    newNode->id = maxNodeId++;
    newNode->amount = amount;
    bestTarget = add_vertex(g);
    nodes[bestTarget] = newNode;

    nodesToVertices[newNode->id] = bestTarget;
    Edge inserted;
    bool insRes;

    for (int i = 0; i < linksVector->size(); i++) {
      tie(inserted, insRes) =
          add_edge(nodesToVertices[(*nodesVector)[i]->id], bestTarget, g);
      if (!insRes) {
        throw "Insert edge failed!";
      }
      (*linksVector)[i]->amount = 1;
      links[inserted] = (*linksVector)[i];
    }
  } else {
    // Update
    for (int i = 0; i < bestAssignation.size(); i++) {
      LinkPtr lp = links[bestAssignation[i]];
      lp->offsets->makeAverage(((*linksVector)[i])->offsets,
                               1.0f / (float)((*linksVector)[i])->amount);
      lp->amount++;
    }
    nodes[bestTarget]->amount++;
  }
  // return node
  NodePtr result = nodes[bestTarget];
  if (!result.get()) throw "Remember failed!";
  return result;
}
