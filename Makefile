# Makefile for GenPass
# Developed by: Caio Gabriel a.k.a. Hav0ck021

# Essentials variables
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS = -lssl -lsodium -lpqxx -luuid

# Path structure
SRC_DIR = src
INC_DIR = include
# Subdirectories for modules
CORE_DIR = core
DOMAIN_DIR = domain
REPOSITORY_DIR = repository
# Build and binary directories
BUILD_DIR = build
BIN_DIR = bin

# Modules files
CORE = $(wildcard $(SRC_DIR)/$(CORE_DIR)/*.cpp)
DOMAIN = $(wildcard $(SRC_DIR)/$(DOMAIN_DIR)/*.cpp)
REPOSITORY = $(wildcard $(SRC_DIR)/$(REPOSITORY_DIR)/*.cpp)
# Source files
SOURCES = $(CORE) $(DOMAIN) $(REPOSITORY)
# Object files and target executable
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/genpass

# Steps to compile and link the project
# Fundamental targets
all: prepare $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking executables..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Specific modules
crypto: $(BUILD_DIR)/$(CORE_DIR)/crypto.o
	@echo "Módulo de criptografia compilado"

database: $(BUILD_DIR)/$(REPOSITORY_DIR)/db.o
	@echo "Módulo de banco de dados compilado"

# Utilities
prepare:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

clean:
	@echo "Cleaning build..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

install:
	@echo "Installing to system..."
	@sudo cp $(TARGET) /usr/local/bin
	@sudo chmod +x /usr/local/bin/genpass

# Linux dependencies (Ubuntu/Debian)
dependencies:
	@echo "Installing dependencies..."
	@sudo apt-get update
	@sudo apt-get install -y \
		util-linux \
		libsodium-dev \
		libpqxx-dev \
		uuid-dev \
 		libgtest-dev

.PHONY: all clean prepare dependencies install