CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -Wno-deprecated-declarations -I.
AR=ar
ARFLAGS=rcs
RM=rm -f

# Automatically find all .c files in the current directory, excluding the test folder
SRC=$(filter-out test/%, $(wildcard *.c))

# Corresponding object files
OBJ=$(SRC:.c=.o)

# Name of the library
LIB=libhblk_crypto.a

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $(LIB) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIB)

.PHONY: clean