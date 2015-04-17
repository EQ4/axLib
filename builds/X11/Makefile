CC = clang++
CC_FLAGS = -std=c++11 

OBJDIR = build
SRC_DIR = ../../source
WIDGET_DIR = ../../axWidgets
INCLUDE_DIR = ../../include


X11_INCLUDE = -I /usr/X11/include/
INCLUDE_SRC = -I $(INCLUDE_DIR) -I/usr/local/include/ -I../../axCore/X11/ $(X11_INCLUDE)


CPP_WIDGETS := $(wildcard $(WIDGET_DIR)/*.cpp)
WIDGETS_OBJ := $(addprefix build/,$(notdir $(CPP_WIDGETS:.cpp=.o)))

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))

LD_FLAGS := 
# CC_FLAGS := 

all: $(OBJ_FILES) $(WIDGETS_OBJ) axX11Core.o
	ar rcs libaxlib.a $(OBJ_FILES) $(WIDGETS_OBJ) axX11Core.o
	# @echo  "${green} ----------------------------------------- ${NC}" 
	# @echo  "${green} Creating lib/libaxServer.a ${NC}" 
   # g++ $(LD_FLAGS) -o $@ $^

#$(SOURCE_DIR)/%.cpp
build/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<
	# @echo  "${green} Build : $< to $@ ${NC}" 

build/%.o: $(WIDGET_DIR)/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

axX11Core.o: ../../axCore/X11/axX11Core.cpp ../../axCore/X11/axX11Core.h 
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c build/axX11Core.o

clean: 
	rm -f $(OBJ_FILES)
	rm -f lib/libaxServer.a




