#include "Collision.hpp"
#include <SFML/Graphics.hpp>

// Helper function to convert our vec2 to SFML's Vector2f
sf::Vector2f toSFML(const vec2 &v) { return sf::Vector2f(v.x, v.y); }

// Helper function to convert our triangle to an SFML ConvexShape
sf::ConvexShape toSFML(const triangle &t, const sf::Color &color) {
  sf::ConvexShape shape;
  shape.setPointCount(3);
  shape.setPoint(0, toSFML(t.points[0]));
  shape.setPoint(1, toSFML(t.points[1]));
  shape.setPoint(2, toSFML(t.points[2]));
  shape.setFillColor(color);
  shape.setOutlineColor(sf::Color::Black);
  shape.setOutlineThickness(1);
  return shape;
}

int main() {
  // Window dimensions
  const int windowWidth = 800;
  const int windowHeight = 600;

  // Create the SFML window
  sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                          "Task 2: Triangle Collision");
  window.setFramerateLimit(60);

  // Define the two triangles
  triangle triangle1{.points = {vec2{100.0f, 100.0f}, vec2{200.0f, 100.0f},
                                vec2{150.0f, 200.0f}}};
  triangle triangle2{.points = {vec2{300.0f, 300.0f}, vec2{400.0f, 300.0f},
                                vec2{350.0f, 400.0f}}};

  // Store the original color
  sf::Color normalColor = sf::Color::Green;
  sf::Color collisionColor = sf::Color::Red;

  // Create SFML shapes for drawing
  sf::ConvexShape sf_triangle1 = toSFML(triangle1, normalColor);
  sf::ConvexShape sf_triangle2 = toSFML(triangle2, normalColor);

  // Movement speed for the controllable triangle
  float moveSpeed = 5.0f;

  // Game loop
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    // Handle Input (Control triangle2)
    vec2 movement = {0.0f, 0.0f};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
      movement.x -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
      movement.x += moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
      movement.y -= moveSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
      movement.y += moveSpeed;
    }

    // Apply movement to triangle2's points
    for (int i = 0; i < 3; ++i) {
      triangle2.points[i].x += movement.x;
      triangle2.points[i].y += movement.y;
    }

    // Update the SFML shape's position
    sf_triangle2.setPoint(0, toSFML(triangle2.points[0]));
    sf_triangle2.setPoint(1, toSFML(triangle2.points[1]));
    sf_triangle2.setPoint(2, toSFML(triangle2.points[2]));

    // Collision Detection
    bool collision = isColliding(triangle1, triangle2);

    // Signal Collision
    if (collision) {
      sf_triangle1.setFillColor(collisionColor);
      sf_triangle2.setFillColor(collisionColor);
    } else {
      sf_triangle1.setFillColor(normalColor);
      sf_triangle2.setFillColor(normalColor);
    }

    // Drawing
    window.clear(sf::Color::White);
    window.draw(sf_triangle1);
    window.draw(sf_triangle2);
    window.display();
  }

  return 0;
}