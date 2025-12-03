CC = gcc
CFLAGS = -Wall -Wextra -I include -ggdb

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

TARGET = comp

# Descobre todos os .c
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Converte src/file.c → build/file.o
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# ============================================
#               TARGET PRINCIPAL
# ============================================

all: $(BIN_DIR)/$(TARGET)

# Link final
$(BIN_DIR)/$(TARGET): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@
	@echo ">> Executável criado em: $(BIN_DIR)/$(TARGET)"

# ============================================
#      COMPILAÇÃO INDIVIDUAL DOS .c → .o
# ============================================

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================
#                  RUN
# ============================================
run: all
	@echo ">> Executando $(BIN_DIR)/$(TARGET)"
	./$(BIN_DIR)./$(TARGET)

# ============================================
#                LIMPEZA
# ============================================

clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BIN_DIR)/$(TARGET)
	@echo ">> Limpeza concluída."

clean-all:
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
	@echo ">> Limpeza total concluída."
