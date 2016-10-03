
# Recommended:
# 	`$ export CXX="clang++3.8"
#

CFLAGS = -std=c++1y -std=gnu++11 -Wall -Werror

termq: build/main.o build/menu.o build/game.o \
	build/Actor.o build/Player.o build/Enemy.o \
	build/Item.o build/Coin.o build/Global.o
	$(CXX) src/*.cpp src/classes/*.cpp -o bin/termq $(CFLAGS) -lncurses

build/main.o:
	$(CXX) -c src/main.cpp -o build/main.o $(CFLAGS)

build/Global.o:
	$(CXX) -c src/global/Global.cpp -o build/Global.o $(CFLAGS)

build/menu.o:
	$(CXX) -c src/menu.cpp -o build/menu.o $(CFLAGS)

build/game.o:
	$(CXX) -c src/game.cpp -o build/game.o $(CFLAGS)

build/Window.o:
	$(CXX) -c src/classes/Window.cpp -o build/Window.o $(CFLAGS)

build/DiagWindow.o:
	$(CXX) -c src/classes/DiagWindow.cpp -o build/DiagWindow.o $(CFLAGS)

build/Actor.o:
	$(CXX) -c src/classes/Actor.cpp -o build/Actor.o $(CFLAGS)

build/Player.o:
	$(CXX) -c src/classes/Player.cpp -o build/Player.o $(CFLAGS)

build/Enemy.o:
	$(CXX) -c src/classes/Enemy.cpp -o build/Enemy.o $(CFLAGS)

build/Item.o:
	$(CXX) -c src/classes/Item.cpp -o build/Item.o $(CFLAGS)

build/Coin.o:
	$(CXX) -c src/classes/Coin.cpp -o build/Coin.o $(CFLAGS)

clean:
	rm -f build/* bin/*
