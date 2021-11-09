#### Compiler
CC=gcc
#CFLAGS=-g -m64 -static-libgcc -Wno-write-strings -D__KOREA
CFLAGS=-g -O2 -ffast-math -m64 -static-libgcc -Wno-write-strings -D__KOREA -std=c++11
#CFLAGS=-g -m64 -static-libgcc -Wno-write-strings -D__KOREA
#CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP
CXXFLAGS=$(CFLAGS)

#### Source & object & etc directory
SRC_DIR=$(MAKE_DIR)/src
OBJ_DIR=$(MAKE_DIR)/obj
## Pro*C pre-compile target directory
PRECOMP_DIR=$(MAKE_DIR)/precomp
EXE_DIR=$(MAKE_DIR)/bin
CONF_DIR=$(MAKE_DIR)/conf
SCRIPT_DIR=$(MAKE_DIR)/script

#### Install directory
INSTALL_DIR_EXE=$(INSTALL_DIR)/bin

#### Include file
INCLUDE=-I/usr/include			\
		-I$(SRC_DIR)/include	\
		-I$(SRC_DIR)/socket

#### Library
LDFLAGS=-O2 -ldl -lnsl -lm -lpthread -lrt -lstdc++ -lrdkafka++ 
#-lcppkafka

#### Source directories
SRC_DIRS=$(SRC_DIR)/lib		\
		 $(SRC_DIR)/socket	\
		 $(SRC_DIR)


## C sources
C_SRCS=$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_OBJS=$(subst $(SRC_DIR),$(OBJ_DIR),$(C_SRCS))
C_OBJS:=$(C_OBJS:.c=.o)

## C++ sources
CPP_SRCS=$(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
CPP_OBJS=$(subst $(SRC_DIR),$(OBJ_DIR),$(CPP_SRCS))
CPP_OBJS:=$(CPP_OBJS:.cpp=.o)

#### Execution-file source directory
EXESRC_DIR=$(SRC_DIR)
## EXE OBJS
EXE_SRCS=$(foreach TEMP,$(EXESRC_DIR),$(wildcard $(TEMP)/*.c))
EXE_SRCS+=$(foreach TEMP,$(EXESRC_DIR),$(wildcard $(TEMP)/*.cpp))
EXE_OBJS=$(subst $(SRC_DIR),$(OBJ_DIR),$(EXE_SRCS))
EXE_OBJS:=$(EXE_OBJS:.c=.o)
EXE_OBJS:=$(EXE_OBJS:.cpp=.o)
EXE_FILES=$(subst $(OBJ_DIR),$(EXE_DIR),$(EXE_OBJS))

#### Link objects(exclude execution object)
LINK_OBJS=$(foreach TEMP, $(C_OBJS) $(CPP_OBJS), $(if $(findstring $(TEMP), $(EXE_OBJS)), $(BLANK), $(TEMP)))

#### target target all
all:
	@#$(MAKE) $(MAKEOPTS) -f $(MAKE_DIR)/Makefile $(C_OBJS)
	@$(MAKE) $(MAKEOPTS) -f $(MAKE_DIR)/Makefile $(CPP_OBJS)
	@$(MAKE) -f $(MAKE_DIR)/Makefile $(EXE_FILES)

	@echo ">> compile done"

#### target C compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo ">> C Compiling $<"

	@## Create object directory
	@[ -d $(OBJ_DIR)/$(*D) ] || mkdir -p $(OBJ_DIR)/$(*D)

	@$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

#### target C++ compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo ">> C++ Compiling $<"

	@## Create object directory
	@[ -d $(OBJ_DIR)/$(*D) ] || mkdir -p $(OBJ_DIR)/$(*D)

	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

#### target Execution-file make
$(EXE_FILES):
	@## Create execution-file directory
	@[ -d $(EXE_DIR) ] || mkdir -p $(EXE_DIR)

	@$(CC) -o $(basename $@) $(subst $(EXE_DIR),$(OBJ_DIR),$@) $(LINK_OBJS) $(LDFLAGS) $(LIBS)
	@echo ">> created $(basename $@)"

#### target Install
install:
	@## Create install directory
	@[ -d $(INSTALL_DIR) ] || mkdir -p $(INSTALL_DIR)

	@## Create bin directory
	@[ -d $(INSTALL_DIR_EXE) ] || mkdir -p $(INSTALL_DIR_EXE)
	
	@## Copy files
	@cp $(EXE_DIR)/* $(INSTALL_DIR_EXE)

	@echo ">> Install success"

#### target delete object & execution-file & etc
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(EXE_DIR)