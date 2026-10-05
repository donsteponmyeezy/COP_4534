#include "tsp_graph.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <limits>

TspGraph::TspGraph()
{
  // Initialize block to zeros
  distance_matrix.fill(0.0);
}

void TspGraph::load_distances(const std::string &file_path)
{
  std::ifstream file(file_path);

  // Fail fast if the file is missing
  if (!file.is_open())
  {
    throw std::runtime_error("Critical Error: Cannot open " + file_path);
  }

  double edge_weight;
  int read_count = 0;

  // Populate the 20x20 matrix
  // The file has exactly 380 items
  for (int row = 0; row < max_cities; ++row)
  {
    for (int col = 0; col < max_cities; ++col)
    {
      // Diagonal elements represent self connections and should always be zero so we skip
      if (row == col)
      {
        continue;
      }

      if (file >> edge_weight)
      {
        // Map the 2D coordinate to the 1D array
        distance_matrix[row * max_cities + col] = edge_weight;
        read_count++;
      }
      else
      {
        // Catch for unexpected file format issues like whitespace or missing data
        throw std::runtime_error("Data corruption or EOF reached too early in " + file_path);
      }
    }
  }

  // Verify structural integrity based on project requirements
  if (read_count != 380)
  {
    throw std::runtime_error("Validation failed: Expected 380 distances, read " + std::to_string(read_count));
  }
}