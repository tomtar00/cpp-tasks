#include "QueryEngine.hpp"
#include <unordered_map>

void QueryEngine::add(const std::string &query) {
  // Start from the root node
  TrieNode *current = m_Root.get();

  // For each character in the query, create or traverse the Trie
  for (char c : query) {
    // Create a new node if it doesn't exist
    if (!current->children[c]) {
      current->children[c] = std::make_unique<TrieNode>();
    }
    // Move to the next node
    current = current->children[c].get();
  }

  // Mark the end of the query and store the full query string
  current->is_end = true;
  current->full_query = query;
}

std::vector<std::string> QueryEngine::ask(const std::string &prefix) const {
  // Start from the root and traverse to the prefix node
  const TrieNode *current = m_Root.get();
  for (char c : prefix) {
    // If character not found, return empty result
    if (!current->children.count(c))
      return {};
    current = current->children.at(c).get();
  }

  // Collect all queries that start with the given prefix
  std::vector<std::string> result;
  collect(current, result);
  return result;
}

void QueryEngine::collect(const TrieNode *node,
                          std::vector<std::string> &result) const {
  // If current node is the end of a query, add it to results
  if (node->is_end)
    result.push_back(node->full_query);

  // Recursively collect queries from all child nodes
  for (const auto &[_, child] : node->children) {
    collect(child.get(), result);
  }
}
