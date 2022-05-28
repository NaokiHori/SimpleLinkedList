PRJCT_ROOT := ..
CC 		     := cc
CFLAGS     := -O0 -g -std=c99 -Wall -Wextra
# directly include src of the project
# to access to the static functions
INCLUDES   := -Iinclude \
							-I$(PRJCT_ROOT)/include \
							-I$(PRJCT_ROOT)/src
LIBS			 := -L/usr/local/lib \
							-lcunit
SRC_DFLT   := ../src/memory.c
SRCS1      := $(SRC_DFLT) src/get_nitems.c
SRCS2      := $(SRC_DFLT) src/find.c
SRCS3      := $(SRC_DFLT) src/insert.c
SRCS4      := $(SRC_DFLT) src/remove.c
TARGET1    := test_get_nitems.out
TARGET2    := test_find.out
TARGET3    := test_insert.out
TARGET4    := test_remove.out

all: get_nitems find insert remove

get_nitems:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS1) -o $(TARGET1) $(LIBS)

find:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS2) -o $(TARGET2) $(LIBS)

insert:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS3) -o $(TARGET3) $(LIBS)

remove:
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS4) -o $(TARGET4) $(LIBS)

clean:
	$(RM) *.out *.xml

