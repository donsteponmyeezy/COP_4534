#include <iostream>
#include <iomanip>
#include <string>
#include "tsp_graph.hpp"
#include "brute_force.hpp"
#include "genetic_algorithm.hpp"
#include "timer.hpp"

int main()
{
  // Interactive User Configuration
  int pop_size, num_generations, mutation_percent;

  std::cout << "--- UWF DSA II: TSP Solver ---\n";
  std::cout << "Enter GA Population Size as an Integer: ";
  std::cin >> pop_size;

  std::cout << "Enter Number of Generations as an Integer: ";
  std::cin >> num_generations;

  std::cout << "Enter Mutation Percentage as an Integer (10 for 10%, etc.): ";
  std::cin >> mutation_percent;
  std::cout << "--------------------------------\n";

  // Load given distances file into graph
  TspGraph graph;
  try
  {
    graph.load_distances("distances.txt");
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  // Table header for required output metrics
  std::cout << std::left
            << std::setw(10) << "Cities"
            << std::setw(15) << "Optimal Cost"
            << std::setw(15) << "BF Time (s)"
            << std::setw(15) << "GA Cost"
            << std::setw(15) << "GA Time (s)"
            << std::setw(15) << "% Optimal"
            << "\n";
  std::cout << std::string(85, '-') << "\n";

  // Hardware Stress Test
  // Start at 10 cities and go up until Brute Force takes > 5 mins (300 seconds)
  int current_cities = 10;
  double bf_time = 0.0;

  while (bf_time <= 300.0)
  {
    // Brute Force Execution
    BruteForce bf_solver(graph);
    Timer bf_timer;

    bf_timer.start();
    bf_solver.run(current_cities);
    bf_time = bf_timer.get_elapsed_seconds();
    double optimal_cost = bf_solver.get_best_cost();

    // Genetic Algorithm Execution
    GeneticAlgorithm ga_solver(graph);
    Timer ga_timer;

    ga_timer.start();
    ga_solver.run(current_cities, pop_size, num_generations, mutation_percent);
    double ga_time = ga_timer.get_elapsed_seconds();
    double ga_cost = ga_solver.get_best_cost();

    // Calculate Metrics
    double percent_optimal = (ga_cost / optimal_cost) * 100.0;

    // Output Required Metrics
    std::cout << std::left
              << std::setw(10) << current_cities
              << std::setw(15) << std::fixed << std::setprecision(2) << optimal_cost
              << std::setw(15) << std::fixed << std::setprecision(6) << bf_time
              << std::setw(15) << std::fixed << std::setprecision(2) << ga_cost
              << std::setw(15) << std::fixed << std::setprecision(6) << ga_time
              << std::setw(15) << std::fixed << std::setprecision(2) << percent_optimal
              << "\n";

    current_cities++;
  }

  std::cout << "--------------------------------\n";
  std::cout << "Brute force wall hit (> 5 minutes). Execution terminated.\n";

  return 0;
}