#include "genetic_algorithm.hpp"
#include <numeric>
#include <algorithm>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(const TspGraph &graph)
    : graph_ref(graph), best_cost(0.0)
{
  // Seed PRNG once hardware-side to ensure varied runs
  std::random_device rd;
  rng.seed(rd());
}

void GeneticAlgorithm::run(int num_cities, int pop_size, int num_generations, int mutation_percent)
{
  this->cities = num_cities;
  std::vector<Tour> population(pop_size);

  // Initialize Generation 0 with random permutations
  for (int i = 0; i < pop_size; ++i)
  {
    population[i] = generate_random_tour();
  }
  evaluate_population(population);

  int num_mutations = (pop_size * mutation_percent) / 100;

  // Generation Loop
  for (int gen = 0; gen < num_generations; ++gen)
  {
    // Sort population by cost. Index 0 becomes Elite
    std::sort(population.begin(), population.end());

    std::vector<Tour> next_generation;
    next_generation.reserve(pop_size);

    // Exactly one elite passes strictly unchanged
    next_generation.push_back(population[0]);

    // Mutate copies of Elite and other top performer
    for (int i = 0; i < num_mutations && next_generation.size() < (size_t)pop_size; ++i)
    {
      // Pick a parent from the top 20%
      int parent_idx = rng() % std::max(1, pop_size / 5);
      Tour child = population[parent_idx];
      mutate(child);
      next_generation.push_back(child);
    }

    // Fill the remainder of the generation
    while (next_generation.size() < (size_t)pop_size)
    {
      // 80% chance of Crossover, 20% chance of new tour
      // Add random permutations to maintain genetic diversity and prevent stagnation
      if (rng() % 100 < 80)
      {
        int p1_idx = rng() % (pop_size / 2); // Bias towards better half
        int p2_idx = rng() % (pop_size / 2);
        next_generation.push_back(crossover(population[p1_idx], population[p2_idx]));
      }
      else
      {
        next_generation.push_back(generate_random_tour());
      }
    }

    population = std::move(next_generation);
    evaluate_population(population);
  }

  // After all generations, grab the best solution
  std::sort(population.begin(), population.end());
  best_cost = population[0].cost;
}

Tour GeneticAlgorithm::generate_random_tour()
{
  Tour t;
  t.path.resize(cities);
  std::iota(t.path.begin(), t.path.end(), 0); // Fill 0 to cities-1
  std::shuffle(t.path.begin(), t.path.end(), rng);
  return t;
}

void GeneticAlgorithm::evaluate_population(std::vector<Tour> &population)
{
  for (auto &tour : population)
  {
    double cost = 0.0;
    for (int i = 0; i < cities - 1; ++i)
    {
      cost += graph_ref.get_distance(tour.path[i], tour.path[i + 1]);
    }
    // Return trip to starting city
    cost += graph_ref.get_distance(tour.path[cities - 1], tour.path[0]);
    tour.cost = cost;
  }
}

// Order Crossover (OX1) as a consistent way to cross permutations
Tour GeneticAlgorithm::crossover(const Tour &parent1, const Tour &parent2)
{
  Tour child;
  child.path.assign(cities, -1);

  // Pick random swath from parent 1
  std::uniform_int_distribution<int> dist(0, cities - 1);
  int start = dist(rng);
  int end = dist(rng);
  if (start > end)
    std::swap(start, end);

  // Copy swath
  for (int i = start; i <= end; ++i)
  {
    child.path[i] = parent1.path[i];
  }

  // Fill the rest with parent 2s cities in order, skip ones already in the child
  int child_idx = (end + 1) % cities;
  int p2_idx = (end + 1) % cities;

  for (int i = 0; i < cities; ++i)
  {
    int candidate = parent2.path[p2_idx];

    // Check if candidate is already in child
    bool exists = false;
    for (int j = start; j <= end; ++j)
    {
      if (child.path[j] == candidate)
      {
        exists = true;
        break;
      }
    }

    if (!exists)
    {
      child.path[child_idx] = candidate;
      child_idx = (child_idx + 1) % cities;
    }
    p2_idx = (p2_idx + 1) % cities;
  }
  return child;
}

// Mutate by swapping 2 to 4 cities randomly
void GeneticAlgorithm::mutate(Tour &tour)
{
  std::uniform_int_distribution<int> swap_count_dist(1, 2); // 1 or 2 pairs | 2 or 4 cities
  std::uniform_int_distribution<int> idx_dist(0, cities - 1);

  int swaps = swap_count_dist(rng);
  for (int i = 0; i < swaps; ++i)
  {
    int idx1 = idx_dist(rng);
    int idx2 = idx_dist(rng);
    std::swap(tour.path[idx1], tour.path[idx2]);
  }
}