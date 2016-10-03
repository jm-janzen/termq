
# Recommended:
# 	`$ CXX="clang++3.8"
#

CFLAGS = -std=c++1y -std=gnu++11 -Wall -Werror

termq: build/main.o build/menu.o build/game.o build/Actor.o build/Player.o build/Enemy.o build/Item.o build/Coin.o build/Global.o
	$(CXX) src/*.cpp src/classes/*.cpp src/global/Global.cpp -o bin/termq $(CFLAGS) -lncurses

build/main.o: src/main.cpp
	$(CXX) -c -o build/main.o src/main.cpp $(CFLAGS)

build/Global.o: src/global/Global.cpp src/global/Global.h
	$(CXX) -c -o build/Global.o src/global/Global.cpp $(CFLAGS)

build/menu.o: src/menu.cpp src/menu.h
	$(CXX) -c -o build/menu.o src/menu.cpp $(CFLAGS)

build/game.o: src/game.cpp src/game.h src/menu.h
	$(CXX) -c -o build/game.o src/game.cpp $(CFLAGS)

build/Window.o: src/classes/Window.cpp src/classes/Window.h
	$(CXX) -c -o build/Window.o src/classes/Window.cpp $(CFLAGS)

build/DiagWindow.o: src/classes/DiagWindow.cpp src/classes/DiagWindow.h build/Window.o
	$(CXX) -c -o build/DiagWindow.o src/classes/DiagWindow.cpp $(CFLAGS)

build/Actor.o: src/classes/Actor.cpp src/classes/Actor.h
	$(CXX) -c -o build/Actor.o src/classes/Actor.cpp $(CFLAGS)

build/Player.o: src/classes/Player.cpp src/classes/Player.h build/Actor.o
	$(CXX) -c -o build/Player.o src/classes/Player.cpp $(CFLAGS)

build/Enemy.o: src/classes/Enemy.cpp src/classes/Enemy.h build/Actor.o
	$(CXX) -c -o build/Enemy.o src/classes/Enemy.cpp $(CFLAGS)

build/Item.o: src/classes/Item.cpp src/classes/Item.h
	$(CXX) -c -o build/Item.o src/classes/Item.cpp $(CFLAGS)

build/Coin.o: src/classes/Coin.cpp src/classes/Coin.h build/Item.o
	$(CXX) -c -o build/Coin.o src/classes/Coin.cpp $(CFLAGS)

clean:
	rm -f build/* bin/*
