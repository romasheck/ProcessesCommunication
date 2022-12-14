CC = gcc

SRC_COMMON_DIR 	= src/common
SRC_TABLE_DIR 	= src/table
SRC_WASHER_DIR 	= src/washer
SRC_WHIPER_DIR 	= src/whiper

OBJ_DIR = build/obj
OUT_DIR = build/out

objects = $(addprefix $(OBJ_DIR)/, wwcommon.o file_work.o hash.o table.o)

COMPILER_KEY ?= SEMAF

all:
	echo "U cann't use me without purpose."
	echo "Valid purposes: washer, whiper, washer_on, whiper_on, clean_obj, clean_out, clean_all"

washer: $(objects)
	$(CC) $(SRC_WASHER_DIR)/*.c $(objects) -o $(OUT_DIR)/washer.out

whiper: $(objects)
	$(CC) $(SRC_WHIPER_DIR)/*.c $(objects) -o $(OUT_DIR)/whiper.out

$(OBJ_DIR)/wwcommon.o:
	$(CC) $(SRC_COMMON_DIR)/wwcommon.c -c $< -o $@

$(OBJ_DIR)/file_work.o:
	$(CC) $(SRC_COMMON_DIR)/file_work.c -c $< -o $@

$(OBJ_DIR)/hash.o:
	$(CC) $(SRC_COMMON_DIR)/hash.c -c $< -o $@

$(OBJ_DIR)/table.o:
	$(CC) $(SRC_TABLE_DIR)/table.c -c -D$(COMPILER_KEY) -c $< -o $@

washing: $(objects)
	$(CC) $(SRC_WASHER_DIR)/*.c $(objects) -o $(OUT_DIR)/washer.out
	$(CC) $(SRC_WHIPER_DIR)/*.c $(objects) -o $(OUT_DIR)/whiper.out

#$(OBJ_DIR)/%.o: $(SRC_COMMON_DIR)/%.c
#	$(CC) -c $< -o $@

washer_on:
	./$(OUT_DIR)/washer.out

whiper_on:
	./$(OUT_DIR)/whiper.out

washing_on: washer_on whiper_on

clean_obj:
	rm $(OBJ_DIR)/*

clean_out:
	rm $(OUT_DIR)/*

clean_tmp:
	ipcrm
	cat emty > file

clean_all:
	rm $(OBJ_DIR)/*
	rm $(OUT_DIR)/*
	ipcrm
	cat emty>file