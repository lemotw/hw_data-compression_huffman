CC = gcc
C_FLAG = -g

OBJDIR = ./obj
LIBDIR = ./lib
LIB_OBJFILES =	queue.o \
		bitwise.o \
		huffman.o
TARGET = main

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(OBJDIR)/*.o -o $(TARGET)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mLink target(main.o) as excutable file.\e[0m"

main.o: $(LIB_OBJFILES)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile target(main.c) to object file.\e[0m"
	$(CC) -c $(C_FLAG) -o $(OBJDIR)/$@ -I $(LIBDIR) main.c

$(LIB_OBJFILES): %.o: $(LIBDIR)/%.c $(OBJDIR)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile library to object file.\e[0m"
	$(CC) -c $(C_FLAG) $< -o $(OBJDIR)/$@

$(OBJDIR):
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCreate object directory(obj/)\e[0m"
	mkdir -p $@

clean:
	@echo -e "\e[41m:::\e[0m \e[91mDeleting object file and execute file.\e[0m"
	rm -f $(OBJDIR)/*.o $(TARGET)
