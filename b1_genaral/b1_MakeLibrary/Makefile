.PHONY: obj static linkingStatic clean 

INC_DIR := ./inc
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
LIB_STATIC := ./lib/static
LIB_SHARE := ./lib/share

CC := gcc
C_FLAGS := -c -fPIC -o
STATIC := ar rcs

obj: 
	$(CC) $(C_FLAGS) $(OBJ_DIR)/main.o ./main.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/input.o $(SRC_DIR)/input.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/output.o $(SRC_DIR)/output.c -I $(INC_DIR)

static:
	$(STATIC) $(LIB_STATIC)/libmain.a $(OBJ_DIR)/input.o $(OBJ_DIR)/output.o

share:
	$(CC) -shared $(OBJ_DIR)/* -o $(LIB_SHARE)/libmain.so 

linkingStatic: obj static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -lmain -o $(BIN_DIR)/static_main

linkingShare: obj share
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARE) -lmain -o $(BIN_DIR)/share_main
clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_SHARE)/*
	rm -rf $(LIB_STATIC)/*
