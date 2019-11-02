all:
	@gcc src/main.c -o bin/main

debug:
	gcc src/main.c -DDEBUG -o bin/main
	@for t in `ls dat/`; do\
		cat dat/$$t | bin/main; \
	done

alloc:
	gcc src/main.c -DMEM_DEBUG -o bin/main
	@for t in `ls dat/`; do\
		cat dat/$$t | bin/main; \
	done


test:
	gcc src/main.c -o bin/main
	@for t in `ls dat/`; do\
		cat dat/$$t | bin/main > out/$$t.res; \
		cmp --silent out/$$t.res res/$$t || echo "error $$t"; \
	done


