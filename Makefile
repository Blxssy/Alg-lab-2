CXX := gcc

CXXFLAGS := -Wall -std=c++20 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result

SRCDIR := src
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

OBJDIR := obj
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TARGET := main

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -lstdc++

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
