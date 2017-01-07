#ifndef GAME_H
#define GAME_H

#include <stdint.h> // Use <inttype.h> if portability important

/*
 * TODO
 *  Move vectors, rect to separate, generic header unrelated to
 *  game_area.
 */

struct vec2ui {
    uint_fast8_t x, y;

    bool operator==(const vec2ui &a) const {
        return (a.x == x && a.y == y);
    }
    bool operator>(const vec2ui &a) const {
        return (a.x > x && a.y > y);
    }
    bool operator<(const vec2ui &a) const {
        return (a.x < x && a.y < y);
    }
};

struct vec2i {
    int_fast8_t x, y;

    bool operator==(const vec2i &a) const {
        return (a.x == x && a.y == y);
    }
    bool operator>(const vec2i &a) const {
        return (a.x > x && a.y > y);
    }
    bool operator<(const vec2i &a) const {
        return (a.x < x && a.y < y);
    }
};

struct rect {
    vec2i offset, bounds;

    int_fast8_t top()     const { return offset.y; }
    int_fast8_t bot()     const { return height() - offset.y ; }
    int_fast8_t left()    const { return offset.x; }
    int_fast8_t right()   const { return width() - offset.x; }
    int_fast8_t width()   const { return bounds.x; }
    int_fast8_t height()  const { return bounds.y; }

    int_fast8_t area()  const { return width() * height() - top() * bot(); }

    bool contains(vec2i a)  const {
        return (a.x >= offset.x && a.x < right())
            && (a.y >= offset.y && a.y < bot());
    }

};

const rect game_area = {
    {1, 1},
    {80, 40}
};


int startGame();

#endif

