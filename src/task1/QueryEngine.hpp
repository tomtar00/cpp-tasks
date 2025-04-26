#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// QueryEngine class implements a prefix-based search suggestion system using a
// Trie data structure
class QueryEngine {
public:
  // Adds a new search query to the engine's database
  void add(const std::string &query);

  // Returns all queries that start with the given prefix
  std::vector<std::string> ask(const std::string &prefix) const;

private:
  // TrieNode represents a node in the prefix tree (Trie)
  // Each node contains a map of child nodes indexed by characters
  struct TrieNode {
    bool is_end = false; // Indicates if this node represents the end of a query
    std::string full_query; // Stores the complete query if is_end is true
    std::unordered_map<char, std::unique_ptr<TrieNode>> children; // Child nodes
  };

  std::unique_ptr<TrieNode> m_Root =
      std::make_unique<TrieNode>(); // Root node of the Trie

  // Helper method to recursively collect all queries from a given node
  void collect(const TrieNode *node, std::vector<std::string> &result) const;
};
