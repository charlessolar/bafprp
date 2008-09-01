CPP = /usr/bin/gcc
BINARY = bafprp

INCLUDE = -I. -Iinclude
LD=-Llibs
LDFLAGS=-lodbc -lstdc++

OPT_FLAGS = -O3 -pipe -s -funroll-loops -fno-rtti
DEBUG_FLAGS = -g -ggdb3

SOURCE_DIR = src

OBJECTS = \
1030.cpp \
110.cpp \
1.cpp \
20.cpp \
220.cpp \
221.cpp \
28.cpp \
360.cpp \
364.cpp \
500.cpp \
614.cpp \
625.cpp \
653.cpp \
76.cpp \
79.cpp \
9000.cpp \
9013.cpp \
9014.cpp \
9102.cpp \
96.cpp \
bafdefines.cpp \
baffile.cpp \
bafprp.cpp \
bafrecords.cpp \
base64.cpp \
compat.cpp \
consoleoutput.cpp \
crc32.cpp \
duplicate.cpp \
emailoutput.cpp \
fileoutput.cpp \
ibafrecord.cpp \
ifield.cpp \
mailer.cpp \
mssqloutput.cpp \
mysqloutput.cpp \
nooutput.cpp \
output.cpp \
field_defs.cpp \
date_dt.cpp \
duration_dt.cpp \
number_dt.cpp \
phonenumber_dt.cpp \
switch_dt.cpp \
time_dt.cpp 


BIN_DIR = bin

#CFLAGS = $(DEBUG_FLAGS)
CFLAGS = $(OPT_FLAGS)
 
CFLAGS += -v -fpermissive -D_LINUX -DNDEBUG -fPIC \
-Wno-deprecated -static-libgcc

OBJ_LINUX := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)
	$(MAKE) bafprp

bafprp: $(OBJ_LINUX)
	$(CPP) $(INCLUDE) $(CFLAGS) $(OBJ_LINUX) $(LDFLAGS) -o$(BIN_DIR)/$(BINARY)

install: bafprp
	cp $(BIN_DIR)/$(BINARY) /usr/bin/$(BINARY)
	mkdir -p /var/log/bafprp

uninstall:
	rm -f /usr/bin/$(BINARY)
	rm -rf /var/log/bafprp

default: all

clean:
	rm -rf $(BIN_DIR)/*.o
