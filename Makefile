# Makefile para GenPass (Linux)
# ===========================

# Configurações essenciais
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS = -lssl -lcrypto -lsodium -lsqlite3 -loath

# Estrutura de diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Arquivos fonte (adicione os novos módulos aqui)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/genpass

# Regra principal
all: prepare $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "🔗 Linkando executável..."
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "🔨 Compilando $<..."
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Módulos específicos (exemplos)
crypto: $(BUILD_DIR)/crypto.o
	@echo "🛡  Módulo de criptografia compilado"

database: $(BUILD_DIR)/db.o
	@echo "💾 Módulo de banco de dados compilado"

# Utilitários
prepare:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

clean:
	@echo "🧹 Limpando build..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

install:
	@echo "📦 Instalando no sistema..."
	@sudo cp $(TARGET) /usr/local/bin
	@sudo chmod +x /usr/local/bin/genpass

# Dependências para Linux (Ubuntu/Debian)
deps:
	@echo "📦 Instalando dependências..."
	@sudo apt-get update
	@sudo apt-get install -y \
		libssl-dev \
		libsodium-dev \
		sqlite3 \
		libsqlite3-dev \
		oath-toolkit \
		liboath-dev

.PHONY: all clean prepare deps install