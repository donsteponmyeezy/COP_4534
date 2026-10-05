#pragma once

#include <array>
#include <string>

class TspGraph
{
public:
  // Simple graph for 20 cities. Distances stored in flat 1D array for O(1) access
  static constexpr int max_cities = 20;

  TspGraph();

  // Loads the 380 edges from distances.txt into the 20x20 matrix
  void load_distances(const std::string &file_path);

  // O(1) contiguous memory lookup. Inline for zero function-call overhead
  inline double get_distance(int city_a, int city_b) const
  {
    return distance_matrix[city_a * max_cities + city_b];
  }

private:
  // 1D array representing a 20x20 grid
  // index = row * max_cities + column
  std::array<double, max_cities * max_cities> distance_matrix;
};