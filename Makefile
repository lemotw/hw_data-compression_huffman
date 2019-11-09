CC = gcc
C_FLAG = -g

OBJDIR = ./obj
LIBOBJDIR = ./obj/lib
LIBDIR = ./lib
LIB_OBJFILES =	queue.o \
		bitwise.o \
		huffman.o \
		filebitreader.o

COMPRESS = compress
DECODE = decode


all: $(COMPRESS) $(DECODE)

$(DECODE): decode.o $(LIB_OBJFILES)
	$(CC) $(OBJDIR)/decode.o $(LIBOBJDIR)/*.o -o $(DECODE)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mLink target(decode.o) as excutable file.\e[0m"

decode.o: $(LIB_OBJFILES)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile target(decode.c) to object file.\e[0m"
	$(CC) -c $(C_FLAG) -o $(OBJDIR)/$@ -I $(LIBDIR) decode.c

$(COMPRESS): compress.o $(LIB_OBJFILES)
	$(CC) $(OBJDIR)/compress.o $(LIBOBJDIR)/*.o -o $(COMPRESS)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mLink target(compress.o) as excutable file.\e[0m"

compress.o: $(LIB_OBJFILES)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile target(compress.c) to object file.\e[0m"
	$(CC) -c $(C_FLAG) -o $(OBJDIR)/$@ -I $(LIBDIR) compress.c

$(LIB_OBJFILES): %.o: $(LIBDIR)/%.c $(LIBOBJDIR)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCompile library to object file.\e[0m"
	$(CC) -c $(C_FLAG) $< -o $(LIBOBJDIR)/$@

$(LIBOBJDIR): $(OBJDIR)
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCreate object directory(obj/lib)\e[0m"
	mkdir -p $@

$(OBJDIR):
	@echo -e "\e[42m:::\e[0m \e[38;5;82mCreate object directory(obj/)\e[0m"
	mkdir -p $@

clean:
	@echo -e "\e[41m:::\e[0m \e[91mDeleting object file and execute file.\e[0m"
	rm -f $(OBJDIR)/*.o $(TARGET)
