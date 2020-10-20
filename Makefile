# tool macros
CC := g++
CCFLAG := -Wall -pthread -std=c++11
DBGFLAG := -g
CCOBJFLAG := $(CCFLAG) -c

# path macros
BIN_PATH := bin
SERVER_OBJ_PATH := server/obj
SERVER_SRC_PATH := server/src
CLIENT_OBJ_PATH := client/obj
CLIENT_SRC_PATH := client/src

# compile macros
SERVER_TARGET_NAME := server
SERVER_TARGET := $(BIN_PATH)/$(SERVER_TARGET_NAME)
CLIENT_TARGET_NAME := client
CLIENT_TARGET := $(BIN_PATH)/$(CLIENT_TARGET_NAME)
MAIN_SRC := main.cpp

# src files & obj files
SERVER_SRC := $(foreach x, $(SERVER_SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SERVER_OBJ := $(addprefix $(SERVER_OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SERVER_SRC)))))
CLIENT_SRC := $(foreach x, $(CLIENT_SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
CLIENT_OBJ := $(addprefix $(CLIENT_OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(CLIENT_SRC)))))

# clean files list
DISTCLEAN_LIST := $(SERVER_OBJ) \
				  $(CLIENT_OBJ)
CLEAN_LIST := $(SERVER_TARGET) \
			  $(CLIENT_TARGET) \
			  $(DISTCLEAN_LIST)

# default rule
default: all

# non-phony targets
$(SERVER_TARGET): $(SERVER_OBJ) | $(BIN_PATH)
	$(CC) $(CCFLAG) -o $@ $^

$(SERVER_OBJ_PATH)/%.o: $(SERVER_SRC_PATH)/%.c* | $(SERVER_OBJ_PATH)
	$(CC) $(CCOBJFLAG) -o $@ $<

$(SERVER_OBJ_PATH):
	mkdir $@

$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CC) $(CCFLAG) -o $@ $^

$(CLIENT_OBJ_PATH)/%.o: $(CLIENT_SRC_PATH)/%.c* $(CLIENT_OBJ_PATH)
	$(CC) $(CCOBJFLAG) -o $@ $<

$(CLIENT_OBJ_PATH):
	mkdir $@

$(BIN_PATH):
	mkdir $@

# phony rules
.PHONY: all
all: $(SERVER_TARGET) $(CLIENT_TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)
