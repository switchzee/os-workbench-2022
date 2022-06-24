NAME := $(shell basename $(PWD))
export MODULE := M1
all: $(NAME)-64 $(NAME)-32

debug32: $(NAME)-32
	gdb $(NAME)-32

debug64: $(NAME)-64
	gdb $(NAME)-64

run32: $(NAME)-32
	./$(NAME)-32

run64: $(NAME)-64
	./$(NAME)-64

rerun32: clean $(NAME)-32 run32
rerun64: clean $(NAME)-64 run64


include ../Makefile
