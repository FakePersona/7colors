TARGET		= 7colors
C_FILES	= $(wildcard *.c)
H_FILES	= $(wildcard *.h)
O_FILES = 	$(C_FILES:%.c=%.o)

all: $(TARGET)

$(O_FILES): %.o: %.c $(H_files) Makefile
	gcc -Wall -Wextra $*.c -c

$(TARGET): %: $(O_FILES) Makefile
	gcc -Wall -Wextra $(O_FILES) -o $*

clean:
	-rm -f $(O_FILES) $(TARGET) *.orig
	-rm -rf *.dSYM

