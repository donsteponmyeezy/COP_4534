#pragma once

#include "tsp_graph.hpp"
#include <vector>

class BruteForce
{
public:
  // Pass the graph by constant reference to avoid copying 400 doubles
  BruteForce(const TspGraph &graph);

  // Executes the brute force search for the given number of cities
  void run(int num_cities);

  double get_best_cost() const { return best_cost; }

private:
  const TspGraph &graph_ref;
  std::vector<int> s; // The external int array requested by the spec
  int num_elements;
  double best_cost;

  // The required algorithm. Returns bool to signal when permutations are exhausted.
  bool perm1();

  // Helper to maintain state of 's'
  void swap(int p, int q);

  // Replaces printS(s) to evaluate the actual TSP cost
  void evaluate_cost();
};