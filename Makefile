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
abortedbafrecords.cpp \
activationtime.cpp \
amacallslostdata.cpp \
anicpnindicator.cpp \
bafdefines.cpp \
baffile.cpp \
baflostblockwrite.cpp \
bafprp.cpp \
bafrecords.cpp \
bafrecordstimeerror.cpp \
base64.cpp \
bearercaps.cpp \
callcountinfoanon.cpp \
callcountinfodeliv.cpp \
callednumber.cpp \
calledpartyoffhook.cpp \
callingnumber.cpp \
callslostdata.cpp \
calltype.cpp \
carrierconnectdate.cpp \
carrierconnecttime.cpp \
carrierelapsedtime.cpp \
classfeaturecode.cpp \
classfunctions.cpp \
compat.cpp \
completionindicator.cpp \
consoleoutput.cpp \
countrycode.cpp \
crc32.cpp \
dateafter.cpp \
datebefore.cpp \
date.cpp \
dialednumber.cpp \
dialingpresubindicator.cpp \
duplicate.cpp \
duration.cpp \
emailoutput.cpp \
fileblocks.cpp \
fileoutput.cpp \
filesequenceno.cpp \
flaggedbafrecords.cpp \
forwardtonumber.cpp \
genericid.cpp \
ibafrecord.cpp \
icinccalleventstatus.cpp \
icincindicator.cpp \
icincroutingindicator.cpp \
ifield.cpp \
lata.cpp \
linenumber.cpp \
linenumbertype.cpp \
location.cpp \
lrn.cpp \
mailer.cpp \
modulenumber.cpp \
mssqloutput.cpp \
networkinterworking.cpp \
nooutput.cpp \
number.cpp \
numberidentity.cpp \
numberofamacalls.cpp \
numberofcalls.cpp \
numberofrecords.cpp \
numorigcalls.cpp \
numoutgoingcalls.cpp \
numtermcalls.cpp \
numtrunklegsused.cpp \
operatoraction.cpp \
output.cpp \
overseasindicator.cpp \
partyid.cpp \
presentdate.cpp \
presenttime.cpp \
rao.cpp \
recordofficeid.cpp \
recordofficetype.cpp \
releasecauseindicator.cpp \
rtime.cpp \
screenlistfeatstat.cpp \
screenlistsizedrcw.cpp \
screenlistsizescfa.cpp \
screenlistsizescr.cpp \
sensorid.cpp \
sensortype.cpp \
servicefeature.cpp \
servicelogicid.cpp \
serviceproviderid.cpp \
servicetraffic.cpp \
significantdigits.cpp \
sigsuppservusage.cpp \
structuretype.cpp \
studyindicator.cpp \
supportinginfo.cpp \
timeafter.cpp \
timebefore.cpp \
timingindicator.cpp \
traceraudittype.cpp \
trunkgroupnumber.cpp \
trunkidentification.cpp 


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
