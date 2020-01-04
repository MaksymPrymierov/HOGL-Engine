CXX := g++

INCDIR := include
SRCDIR := src
OBJDIR := obj
BINDIR := bin

LDLIB := -lGL \
         -lglfw \
         -lGLEW \

LDDIR := -L/usr/lib \
         -L/usr/include \

INCS := $(shell find $(INCDIR) -name \*.h)
SRCS := $(shell find $(SRCDIR) -name \*.cpp)
OBJS := $(addprefix $(OBJDIR)/,   \
        $(patsubst %.cpp, %.o,    \
        $(subst src/,, $(SRCS)))) \

.PHONY: clean

TARGET := hogl

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CXX) $^ $(LDDIR) $(LDLIB) -o $(BINDIR)/$@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) -I./$(INCDIR) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR) $(BINDIR)
