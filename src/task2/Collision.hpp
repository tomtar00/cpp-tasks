#ifndef TASK2_COLLISION_HPP
#define TASK2_COLLISION_HPP

#include <array>

struct vec2 {
  float x, y;
};

struct triangle {
  std::array<vec2, 3> points;
};

// Checks if two triangles in 2D space are colliding.
bool isColliding(const triangle &triangle1, const triangle &triangle2);

#endif // TASK2_COLLISION_HPP