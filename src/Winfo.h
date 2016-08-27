#include <ncurses.h>
#include <array>

#ifndef WINFO_H
#define WINFO_H

class Winfo {
    public:
        Winfo(); // ctor

        void update();
        void clear();
        void delete_w();

        void bindWindow(WINDOW&);
        void push(std::string);

        void setBounds(rect);
        rect getBounds();
    private:
        rect bounds; // see game.h
        WINDOW *winfo;

        int cursor_pos = 0;
        std::array<std::string, 9> messages;
};

#endif

