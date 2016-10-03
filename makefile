
# Recommended:
# 	`$ export CXX="clang++3.8"
#

CFLAGS = -std=c++1y -std=gnu++11 -Wall -Werror

termq: build/main.o build/menu.o build/game.o build/Actor.o build/Player.o build/Enemy.o build/Item.o build/Coin.o build/Global.o
	$(CXX) src/*.cpp src/classes/*.cpp src/global/Global.cpp -o bin/termq $(CFLAGS) -lncurses

build/main.o: src/main.cpp
	$(CXX) -c src/main.cpp -o build/main.o $(CFLAGS)

build/Global.o: src/global/Global.cpp src/global/Global.h
	$(CXX) -c src/global/Global.cpp -o build/Global.o $(CFLAGS)

build/menu.o: src/menu.cpp src/menu.h
	$(CXX) -c src/menu.cpp -o build/menu.o $(CFLAGS)

build/game.o: src/game.cpp src/game.h src/menu.h
	$(CXX) -c src/game.cpp -o build/game.o $(CFLAGS)

build/Window.o: src/classes/Window.cpp src/classes/Window.h
	$(CXX) -c src/classes/Window.cpp -o build/Window.o $(CFLAGS)

build/DiagWindow.o: src/classes/DiagWindow.cpp src/classes/DiagWindow.h build/Window.o
	$(CXX) -c src/classes/DiagWindow.cpp -o build/DiagWindow.o $(CFLAGS)

build/Actor.o: src/classes/Actor.cpp src/classes/Actor.h
	$(CXX) -c src/classes/Actor.cpp -o build/Actor.o $(CFLAGS)

build/Player.o: src/classes/Player.cpp src/classes/Player.h build/Actor.o
	$(CXX) -c src/classes/Player.cpp -o build/Player.o $(CFLAGS)

build/Enemy.o: src/classes/Enemy.cpp src/classes/Enemy.h build/Actor.o
	$(CXX) -c src/classes/Enemy.cpp -o build/Enemy.o $(CFLAGS)

build/Item.o: src/classes/Item.cpp src/classes/Item.h
	$(CXX) -c src/classes/Item.cpp -o build/Item.o $(CFLAGS)

build/Coin.o: src/classes/Coin.cpp src/classes/Coin.h build/Item.o
	$(CXX) -c src/classes/Coin.cpp -o build/Coin.o $(CFLAGS)

clean:
	rm -f build/* bin/*
