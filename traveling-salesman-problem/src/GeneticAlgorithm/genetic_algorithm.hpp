#pragma once

#include "tsp_graph.hpp"
#include <vector>
#include <random>

// Struct to bind permutation to physical cost, keeps cache locality
struct Tour
{
  std::vector<int> path;
  double cost;

  // Overload < operator for fast population sorting
  bool operator<(const Tour &other) const
  {
    return cost < other.cost;
  }
};

class GeneticAlgorithm
{
public:
  GeneticAlgorithm(const TspGraph &graph);

  // Execute GA
  // mutation_percent is an integer. 10 means 10% chance to mutate
  void run(int num_cities, int pop_size, int num_generations, int mutation_percent);

  double get_best_cost() const { return best_cost; }

private:
  const TspGraph &graph_ref;
  int cities;
  double best_cost;

  std::mt19937 rng; // RNG using Mersenne Twister as used in previous projects

  // GA helper functions
  void evaluate_population(std::vector<Tour> &population);
  void mutate(Tour &tour);
  Tour crossover(const Tour &parent1, const Tour &parent2);
  Tour generate_random_tour();
};