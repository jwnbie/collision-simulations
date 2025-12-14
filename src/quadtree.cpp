#include "Quadtree.hpp"
#include "Particle.hpp"

Quadtree::Quadtree(const Boundary& b, int cap)
    : boundary(b), capacity(cap), divided(false),
      northeast(nullptr), northwest(nullptr), southeast(nullptr), southwest(nullptr) {}

Quadtree::~Quadtree() {
    delete northeast;
    delete northwest;
    delete southeast;
    delete southwest;
}

bool Quadtree::insert(Particle* p) {
    if (!boundary.contains(p)) return false;

    if (points.size() < capacity) {
        points.push_back(p);
        return true;
    }

    if (!divided) subdivide();

    if (northeast->insert(p)) return true;
    if (northwest->insert(p)) return true;
    if (southeast->insert(p)) return true;
    if (southwest->insert(p)) return true;

    return false;  // Tidak seharusnya terjadi
}

void Quadtree::subdivide() {
    float x = boundary.x;
    float y = boundary.y;
    float w = boundary.w / 2;
    float h = boundary.h / 2;

    northeast = new Quadtree(Boundary(x + w, y - h, w, h));
    northwest = new Quadtree(Boundary(x - w, y - h, w, h));
    southeast = new Quadtree(Boundary(x + w, y + h, w, h));
    southwest = new Quadtree(Boundary(x - w, y + h, w, h));

    divided = true;
}

void Quadtree::query(const Boundary& range, std::vector<Particle*>& found) {
    if (!boundary.intersects(range)) return;

    for (auto p : points) {
        if (range.contains(p)) found.push_back(p);
    }

    if (divided) {
        northeast->query(range, found);
        northwest->query(range, found);
        southeast->query(range, found);
        southwest->query(range, found);
    }
}