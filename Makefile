CXX=g++
INC=-I/usr/lib/ -I/usr/include/
SRC=src
OBJ=obj
LIB=-lGL -lglfw

SRCS := $(wildcard $(SRC)/*.cpp)
INCS := $(wildcard $(INC)/*.h)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

.PHONY: clean

target=hogl

$(target): $(OBJS)
	$(CXX) $^ $(INC) $(LIB) -o $@

$(OBJS): $(SRCS) $(INCS)
	mkdir -p obj
	$(CXX) -c $(SRCS) -o $@

clean:
	$(RM) $(OBJS) $(target)
