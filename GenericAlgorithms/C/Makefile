SRCS = $(wildcard src/*.c)
BINS = $(SRCS: src)


array: bin/array include/data.h include/array.h

hash: bin/hash_table include/hash.h

dllist: bin/double_linked_list include/data.h include/linked_list.h

all: ${BINS}

bin/%: src/%.c
	@gcc -Iinclude $< -o $@
