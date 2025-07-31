CC=gcc
BUILD_DIR=build
SOURCE_DIR=src
SOURCES=$(wildcard $(SOURCE_DIR)/*.c)
INCLUDE_DIR=include

.PHONY: build clean

build:
	$(CC) -I$(INCLUDE_DIR) -o $(BUILD_DIR)/main $(SOURCES) -lncurses

clean:
	rm -f $(BUILD_DIR)/main
