#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.hpp"

// Struktur untuk mendefinisikan batas kotak (AABB)
struct Boundary {
    float x; // Pusat X
    float y; // Pusat Y
    float w; // Setengah Lebar (Half Width)
    float h; // Setengah Tinggi (Half Height)

    Boundary(float cx = 0, float cy = 0, float cw = 0, float ch = 0)
        : x(cx), y(cy), w(cw), h(ch) {}

    bool contains(Particle* p) const {
        return (p->position.x >= x - w && p->position.x <= x + w &&
                p->position.y >= y - h && p->position.y <= y + h);
    }

    bool intersects(const Boundary& range) const {
        return !(range.x - range.w > x + w || range.x + range.w < x - w ||
                 range.y - range.h > y + h || range.y + range.h < y - h);
    }
};

class Quadtree {
public:
    Boundary boundary;
    int capacity;
    std::vector<Particle*> points;
    bool divided;

    Quadtree* northeast;
    Quadtree* northwest;
    Quadtree* southeast;
    Quadtree* southwest;

    Quadtree(const Boundary& boundary, int cap = 4);
    ~Quadtree();

    bool insert(Particle* p);
    void subdivide();
    void query(const Boundary& range, std::vector<Particle*>& found);
};

#endif