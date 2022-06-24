cc = gcc
db = gdb

TARGET = main

compile: $(TARGET).c
	$(cc) -m32 -g $(TARGET).c -o $(TARGET)-32
	$(cc) -m64 -g $(TARGET).c -o $(TARGET)-64


run32: $(TARGET)-32
	./$(TARGET)-32

run64: $(TARGET)-64
	./$(TARGET)-64

clean: $(TARGET)-64 $(TARGET)-32
	rm -f $(TARGET)-64 $(TARGET)-32

debug32:$(TARGET)-32
	$(db) $(TARGET)-32

debug64:$(TARGET)-64
	$(db) $(TARGET)-64

rerun32: clean compile run32
rerun64: clean compile run64