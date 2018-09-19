all: build

build:
	@echo "Building..."
	g++ -o bin/server src/server.cpp -I src/ -Wall
run: build
	@bin/server
clear:
	rm -rf bin/*
