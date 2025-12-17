#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <algorithm>

// ===============================
// WARNA BUBBLE SOFT PASTEL
// ===============================
inline sf::Color randomBubbleColor()
{
    return sf::Color(
        140 + std::rand() % 100,
        140 + std::rand() % 100,
        180 + std::rand() % 70,
        210
    );
}

class Particle
{
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;

    sf::CircleShape shape;
    sf::CircleShape highlight;

    Particle(float x, float y)
    {
        // SIZE 
        radius = 12.f;

        // 🫧 SIZE BESAR
        radius = 24.f;

        position = { x, y };
        velocity = {
            static_cast<float>(std::rand() % 120 - 60),
            static_cast<float>(std::rand() % 120 - 60)
        };

        shape.setRadius(radius);
        shape.setOrigin({ radius, radius });
        shape.setFillColor(randomBubbleColor());
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(sf::Color(255, 255, 255, 140));
        shape.setPosition(position);

        highlight.setRadius(radius * 0.45f);
        highlight.setOrigin({ highlight.getRadius(), highlight.getRadius() });
        highlight.setFillColor(sf::Color(255, 255, 255, 80));
        highlight.setPosition({
            position.x - radius * 0.35f,
            position.y - radius * 0.35f
        });
    }

    // ===============================
    // UPDATE
    // ===============================
    void update(float dt, int width, int height)
    {
        // Batasi kecepatan (biar smooth)
        float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        float maxSpeed = 120.f;
        if (speed > maxSpeed)
            velocity = velocity / speed * maxSpeed;

        position += velocity * dt;

        // Pantulan dinding
        if (position.x < radius || position.x > width - radius)
            velocity.x *= -1.f;
        if (position.y < radius || position.y > height - radius)
            velocity.y *= -1.f;

        shape.setPosition(position);
        highlight.setPosition({
            position.x - radius * 0.35f,
            position.y - radius * 0.35f
        });
    }

    // ===============================
    // COLLISION KUAT & ANTI NUMPUK
    // ===============================
    void resolveCollision(Particle& other)
    {
        sf::Vector2f delta = other.position - position;
        float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

        float minDist = radius + other.radius;

        if (dist > 0.f && dist < minDist)
        {
            sf::Vector2f normal = delta / dist;
            float penetration = minDist - dist;
            float correction = penetration * 0.8f;
            position -= normal * correction;
            other.position += normal * correction;

            float impulse = 1.2f;
            sf::Vector2f relativeVelocity = velocity - other.velocity;
            float velAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

            if (velAlongNormal > 0)
                return;

            sf::Vector2f impulseVec = normal * impulse;
            velocity -= impulseVec;
            other.velocity += impulseVec;

            // Warna berubah
            sf::Color c = randomBubbleColor();
            shape.setFillColor(c);
            other.shape.setFillColor(c);
        }
    }

    // ===============================
    // DRAW
    // ===============================
    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
        window.draw(highlight);
    }
};
#endif