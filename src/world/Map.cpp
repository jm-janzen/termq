#include "Map.h"

Map::Map(Window *newW) {
    w = newW;
}

Map::~Map() {
    std::map<int, Cell*>::iterator i = cells.begin();
    while (i != cells.end()) {
        delete i->second;
        i++;
    }
    cells.clear();
}

/**
 * Draw all entities in cells.
 */
void Map::draw() {
    w->update();
    for (auto const &c : cells) {
        vec2ui pos = c.second->getEntityPos();
        char   cha = c.second->getEntityChar();
        int    col = c.second->getEntityColo();
        w->draw(pos, cha, col);
    }
    w->refresh();
}

// FIXME return int key for pop reference?
void Map::push(Entity &e) {
    Cell *c = new Cell(e);
    cells.insert(std::make_pair(++iter, c));
}

/**
 * Remove an Entity from within map by its equality.
 */
void Map::rm(Entity &e) {
    for (auto const &c : cells) {
        Entity t = c.second->getEntity();
        if (e == t) {
            cells.erase(c.first);
            delete c.second;
            break;
        }
    }
}

/**
 * Get Cell's entity at `key' and delete it.
 */
Entity Map::pop(int key) {
    auto i = cells.find(key)->first;
    Entity e = cells[i]->getEntity();
    cells.erase(i);

    return e;
}

/**
 * Check specific cell at `vec' for specific type of Entity
 */
bool Map::checkCell(vec2ui const vec, std::string type) {
    bool result = false;
    for (auto const &c : cells) {
        std::string t = c.second->getEntity().getType();
        vec2ui v = c.second->getEntityPos();
        if (t == type && v == vec) {
            result = true;
            break;
        }
    }

    return result == true;
}

/**
 * Get reference to Entity in a specific cell.
 */
Entity Map::getEntity(vec2ui const vec) {
    int key;
    std::map<int, Cell*>::iterator i = cells.begin();
    while (i != cells.end()) {
        i++;
        key = i->first;
        vec2ui v = i->second->getEntityPos();  // segfault
        if (v == vec) break;
    }

    return cells[key]->getEntity();
}

