SRC := $(wildcard src/*.txt)

.PHONY: clean

zmono816.ttf: zmono816.bdf
	./convert-to-ttf.sh zmono816.bdf

zmono816.bdf: gen-bdf $(SRC)
	./gen-bdf zmono816.bdf

zmono816.bin: gen-bin $(SRC)
	./gen-bin zmono816.bin

gen-bdf: gen-bdf.c
	$(CC) gen-bdf.c -o gen-bdf

gen-bin: gen-bin.c
	$(CC) gen-bin.c -o gen-bin

clean:
	rm zmono816.bdf zmono816.ttf gen-bdf
