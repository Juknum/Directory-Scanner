SOURCES_DIR = sources
HEADERS_DIR = headers

BUILD_DIR   = build
BIN_DIR     = $(BUILD_DIR)/bin
OBJECTS_DIR = ${BUILD_DIR}/objects

EXEC = projet

CC      = gcc
CFLAGS  = -I./$(HEADERS_DIR) -std=c11 -Wall -pedantic
LDFLAGS =
LIBS    = -lm

ifdef OPENSSL_MD5
CFLAGS += -DOPENSSL_MD5
LIBS   += -lcrypto
else
CFLAGS += -DBSD_MD5
LIBS   += -lbsd
endif

# Get sources
SOURCES = $(notdir $(wildcard $(SOURCES_DIR)/*.c))
SOURCES_BLACKLISTED = 

# Filtering
SOURCES := $(filter-out $(SOURCES_BLACKLISTED), $(SOURCES))
OBJECTS  = $(SOURCES: %.c = $(OBJECTS_DIR)/%.o)

.PHONY: clean clean-all

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJECTS)
	[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(EXEC) $^ $(LIBS)

$(OBJECTS): $(OBJECTS_DIR)/%.o : $(SOURCES_DIR)/%.c
	[ -d $(OBJECTS_DIR) ] || mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJECTS_DIR)

clean-all: clean
	rm -rf $(BIN_DIR)