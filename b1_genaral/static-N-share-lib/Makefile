.PHONY: obj shared

SHARED_LIB_NAME := libhello.so

CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin

LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

CC := gcc
C_FLAGS := -c -fPIC -o
 
# Create object files
obj:
	$(CC) $(C_FLAGS) $(OBJ_DIR)/main.o $(CUR_DIR)/main.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/hello_minh.o $(SRC_DIR)/hello_minh.c -I $(INC_DIR)
	$(CC) $(C_FLAGS) $(OBJ_DIR)/hello_world.o $(SRC_DIR)/hello_world.c -I $(INC_DIR)

# Create static lib
static:
	ar rcs $(LIB_STATIC_DIR)/libhello.a $(OBJ_DIR)/hello_minh.o $(OBJ_DIR)/hello_world.o

# Create shared-lib
shared:
	$(CC) -shared $(OBJ_DIR)/* -o $(LIB_SHARED_DIR)/$(SHARED_LIB_NAME)

linkingSharedLib: obj shared
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lhello -o $(BIN_DIR)/hello

linkingStaticLib: obj static 
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lhello -o $(BIN_DIR)/exam

clean: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED_DIR)/*
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/*
