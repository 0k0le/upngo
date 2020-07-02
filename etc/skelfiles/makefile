# General compilation flags
UNI_FLAGS = -Wextra -Wall
VERSION = release

# Src file locations
SRC_DIR = src
OBJ_DIR = bin-int/$(VERSION)
#OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/func.o
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/func.c

# App info
APP_NAME = *PRJNAME*
APP_DIR = bin/$(VERSION)

# Compiler
CC = gcc

debug: VERSION = debug
debug: UNI_FLAGS += -D_DEBUG
all: $(SRC_FILES)
	$(CC) $(SRC_FILES) $(UNI_FLAGS) -o $(APP_DIR)/$(APP_NAME) 

debug: all
