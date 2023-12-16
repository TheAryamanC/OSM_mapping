/*graph.h*/

/// <summary>
/// Header file for graph.cpp
/// <summary>

// Import relevant files & libraries
#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
using namespace std;

// Graph object
class graph
{
private:
  vector<long long>    Vertices;
  map<long long, int>  Vertex2Index;
  vector<map<int, double>> Edges;
  int EdgeCount;
  int _LookupVertex(long long v) const;

public:
  // constructor
  graph();

  int NumVertices() const;

  int NumEdges() const;

  bool addVertex(long long v);

  bool addEdge(long long from, long long to, double weight);

  bool getWeight(long long from, long long to, double& weight) const;

  set<long long> neighbors(long long v) const;

  vector<long long> getVertices() const;

  void print(ostream& output) const;
};
