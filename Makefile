SRC := $(wildcard src/*.txt)

.PHONY: clean

zmono816.ttf: zmono816.bdf
	./convert-to-ttf.sh zmono816.bdf

zmono816.bdf: gen-bdf $(SRC)
	./gen-bdf zmono816.bdf

gen-bdf: gen-bdf.c
	$(CC) gen-bdf.c -o gen-bdf

clean:
	rm zmono816.bdf zmono816.ttf gen-bdf
