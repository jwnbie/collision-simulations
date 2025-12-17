#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Particle.hpp"
#include "Quadtree.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int PARTICLE_COUNT = 500;

// === PHYSICS TUNING ===
constexpr float FIXED_DT = 1.f / 200.f;
constexpr int COLLISION_PASSES = 2;
constexpr float CORNER_PUSH = 40.f;   // anti-stuck impulse

float randSign()
{
    return (std::rand() % 2 == 0) ? -1.f : 1.f;
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(
        sf::VideoMode({ WIDTH, HEIGHT }),

        "Bubble Collision"
    );

    window.setFramerateLimit(1000);
        "Bubble Collision - Active & Fast"
    );

    window.setFramerateLimit(144);

    // ===============================
    // INIT PARTICLES
    // ===============================
    std::vector<Particle> particles;
    particles.reserve(PARTICLE_COUNT);

    for (int i = 0; i < PARTICLE_COUNT; ++i)
    {
        Particle p(
            static_cast<float>(std::rand() % (WIDTH - 80) + 40),
            static_cast<float>(std::rand() % (HEIGHT - 80) + 40)
        );
        p.velocity *= 1.2f;
        p.velocity *= 1.9f;
        particles.push_back(p);
    }

    bool useQuadtree = true;
    sf::Clock clock;
    float accumulator = 0.f;

    // ===============================
    // MAIN LOOP
    // ===============================
    while (window.isOpen())
    {
        accumulator += clock.restart().asSeconds();

        // ===============================
        // EVENT
        // ===============================
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
            {
                auto key = event->getIf<sf::Event::KeyPressed>();
                if (key && key->code == sf::Keyboard::Key::Space)
                {
                    useQuadtree = !useQuadtree;
                    std::cout << (useQuadtree
                        ? "[MODE] QUADTREE\n"
                        : "[MODE] BRUTE FORCE\n");
                }
            }
        }

        // ===============================
        // FIXED PHYSICS
        // ===============================
        while (accumulator >= FIXED_DT)
        {
            // UPDATE
            for (auto& p : particles)
                p.update(FIXED_DT, WIDTH, HEIGHT);

            // ===============================
            // WALL + CORNER HANDLING
            // ===============================
            for (auto& p : particles)
            {
                bool hitX = false;
                bool hitY = false;

                if (p.position.x - p.radius < 0.f)
                {
                    p.position.x = p.radius;
                    p.velocity.x = std::abs(p.velocity.x);
                    hitX = true;
                }
                else if (p.position.x + p.radius > WIDTH)
                {
                    p.position.x = WIDTH - p.radius;
                    p.velocity.x = -std::abs(p.velocity.x);
                    hitX = true;
                }

                if (p.position.y - p.radius < 0.f)
                {
                    p.position.y = p.radius;
                    p.velocity.y = std::abs(p.velocity.y);
                    hitY = true;
                }
                else if (p.position.y + p.radius > HEIGHT)
                {
                    p.position.y = HEIGHT - p.radius;
                    p.velocity.y = -std::abs(p.velocity.y);
                    hitY = true;
                }

                // 🧨 ANTI DIAM DI POJOK
                if (hitX && hitY)
                {
                    p.velocity.x += randSign() * CORNER_PUSH;
                    p.velocity.y += randSign() * CORNER_PUSH;
                }
            }

            // ===============================
            // COLLISION
            // ===============================
            for (int pass = 0; pass < COLLISION_PASSES; ++pass)
            {
                if (!useQuadtree)
                {
                    for (size_t i = 0; i < particles.size(); ++i)
                        for (size_t j = i + 1; j < particles.size(); ++j)
                            particles[i].resolveCollision(particles[j]);
                }
                else
                {
                    Quadtree qt(
                        Boundary(
                            WIDTH / 2.f,
                            HEIGHT / 2.f,
                            WIDTH / 2.f,
                            HEIGHT / 2.f
                        ),
                        4
                    );

                    for (auto& p : particles)
                        qt.insert(&p);

                    for (auto& p : particles)
                    {
                        Boundary range(
                            p.position.x,
                            p.position.y,
                            p.radius * 3.f,
                            p.radius * 3.f
                        );

                        std::vector<Particle*> found;
                        qt.query(range, found);

                        for (auto* other : found)
                            if (&p != other)
                                p.resolveCollision(*other);
                    }
                }
            }

            accumulator -= FIXED_DT;
        }

        // ===============================
        // DRAW
        // ===============================
        window.clear(sf::Color(10, 10, 30));
        for (auto& p : particles)
            p.draw(window);
        window.display();
    }

    return 0;
}