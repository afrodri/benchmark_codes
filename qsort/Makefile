
CC = ~/x-tools/mipsel-sde-elf/bin/mipsel-sde-elf-gcc
CFLAGS = -nostartfiles

all: qsort.out rd_qsort.out qsortO3.out rd_qsortO3.out

qsortO3.out : qsort.c
	$(CC) $(CFLAGS) -O3 $^ -o $@

rd_qsortO3.out : rd_qsort.c
	$(CC) $(CFLAGS) -O3 $^ -o $@

qsort.out : qsort.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

rd_qsort.out : rd_qsort.c
	$(CC) $(CFLAGS) -O0 $^ -o $@

# tmr_matmat.c -nostartfiles -o tmr_matmat.out
