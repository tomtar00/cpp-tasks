#include "QueryEngine.hpp"
#include <iostream>

int main() {
  QueryEngine engine;
  std::string line;

  // Process input commands line by line
  while (std::getline(std::cin, line)) {

    // Handle "add:" command - adds a new query to the engine
    if (line.rfind("add: ", 0) == 0) {
      engine.add(line.substr(5));
    }

    // Handle "ask:" command - retrieves suggestions for a prefix
    else if (line.rfind("ask: ", 0) == 0) {
      auto results = engine.ask(line.substr(5));
      for (const auto &r : results) {
        std::cout << "result: " << r << '\n';
      }
    }
  }

  return 0;
}
