#include "brute_force.hpp"
#include <limits>

BruteForce::BruteForce(const TspGraph &graph) : graph_ref(graph), best_cost(0.0) {}

void BruteForce::run(int num_cities)
{
  num_elements = num_cities;
  s.resize(num_elements);
  best_cost = std::numeric_limits<double>::max();

  // Initialize the array (0, 1, 2, ..., n-1)
  for (int i = 0; i < num_elements; ++i)
  {
    s[i] = i;
  }

  // Evaluate base permutation
  evaluate_cost();

  // Generate the next permutation until none are left
  while (perm1())
  {
    evaluate_cost();
  }
}

// Implements the iterative algorithm from the project requirements
bool BruteForce::perm1()
{
  int m, k, p, q;
  m = num_elements - 2;

  // Add bounds check (m >= 0) to prevent segmentation fault on the final permutation
  while (m >= 0 && s[m] > s[m + 1])
  {
    m = m - 1;
  }

  // If m < 0, the array is strictly descending. End-condition for permutation generation
  if (m < 0)
  {
    return false;
  }

  k = num_elements - 1;
  while (s[m] > s[k])
  {
    k = k - 1;
  }

  swap(m, k);

  p = m + 1;
  q = num_elements - 1;

  while (p < q)
  {
    swap(p, q);
    p++;
    q--;
  }

  // Indicates a successful permutation generation
  return true;
}

void BruteForce::swap(int p, int q)
{
  int temp = s[p];
  s[p] = s[q];
  s[q] = temp;
}

void BruteForce::evaluate_cost()
{
  double current_cost = 0.0;

  // Sum of edges from city to city
  for (int i = 0; i < num_elements - 1; ++i)
  {
    current_cost += graph_ref.get_distance(s[i], s[i + 1]);
  }

  // Add the edge returning from last city back to first city to complete tour
  current_cost += graph_ref.get_distance(s[num_elements - 1], s[0]);

  if (current_cost < best_cost)
  {
    best_cost = current_cost;
  }
}