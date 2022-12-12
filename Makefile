.PHONY: washer clean

CC = gcc

SRC_COMMON 	= src_common/
SRC_TABLE 	= src_table/
SRC_WASHER 	= src_washer/
SRC_WHIPER 	= src_whiper/

COMPILER_KEY  ?= SEMAF

washer: $(SRC_WASHER)*.c
	$(CC) $(SRC_WASHER)*.c $(SRC_COMMON)*.o $(SRC_TABLE)*.o -o washer_test.out

common.o: $(SRC_COMMON)*.c
	$(CC) $(SRC_COMMON)*.c -c -o $(SRC_COMMON)*.o

table.o: $(SRC_TABLE)*.c
	$(CC) $(SRC_TABLE)*.c -c -o $(SRC_TABLE)*.o -D$(COMPILER_KEY)

clean:
	rm -rf *.o