#include "Collision.hpp"
#include <limits>

// Helper function to get the normal vector for an edge
vec2 getEdgeNormal(const vec2 &p1, const vec2 &p2) {
  vec2 edge = {p2.x - p1.x, p2.y - p1.y};
  // The normal is perpendicular to the edge. For (dx, dy), the normal is (-dy,
  // dx) or (dy, -dx). We don't need to normalize it for SAT projection
  // comparison.
  return {-edge.y, edge.x};
}

// Helper function to project a triangle onto an axis
void projectTriangle(const triangle &tri, const vec2 &axis, float &min,
                     float &max) {
  min = std::numeric_limits<float>::max();
  max = std::numeric_limits<float>::lowest();

  for (const auto &point : tri.points) {
    // The projection of a point onto an axis is the dot product
    float projection = (point.x * axis.x) + (point.y * axis.y);
    if (projection < min) {
      min = projection;
    }
    if (projection > max) {
      max = projection;
    }
  }
}

// Helper function to check for overlap between two intervals [min1, max1] and
// [min2, max2]
bool intervalsOverlap(float min1, float max1, float min2, float max2) {
  // If max1 is less than min2, they don't overlap. If max2 is less than min1,
  // they don't overlap. Otherwise, they overlap.
  return !(max1 < min2 || max2 < min1);
}

// Checks for collision between two triangles using the Separating Axis Theorem
// (SAT).
bool isColliding(const triangle &triangle1, const triangle &triangle2) {
  // Get all potential separating axes: normals to the edges of both triangles.
  std::array<vec2, 6> axes;
  axes[0] = getEdgeNormal(triangle1.points[0], triangle1.points[1]);
  axes[1] = getEdgeNormal(triangle1.points[1], triangle1.points[2]);
  axes[2] = getEdgeNormal(triangle1.points[2], triangle1.points[0]);

  axes[3] = getEdgeNormal(triangle2.points[0], triangle2.points[1]);
  axes[4] = getEdgeNormal(triangle2.points[1], triangle2.points[2]);
  axes[5] = getEdgeNormal(triangle2.points[2], triangle2.points[0]);

  // Check each axis for a separating plane
  for (const auto &axis : axes) {
    float min1, max1, min2, max2;

    // Project both triangles onto the current axis
    projectTriangle(triangle1, axis, min1, max1);
    projectTriangle(triangle2, axis, min2, max2);

    // If the projections do not overlap on this axis, the triangles are not
    // colliding.
    if (!intervalsOverlap(min1, max1, min2, max2)) {
      return false; // Found a separating axis
    }
  }

  // If no separating axis was found after checking all edge normals, the
  // triangles are colliding.
  return true;
}