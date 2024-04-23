#CXX := gcc
#
#CXXFLAGS := -Wall -std=c++20 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result
#
#SRCDIR := src
#SOURCES := $(wildcard $(SRCDIR)/*.cpp)
#
#OBJDIR := obj
#OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
#
#TARGET := main
#
#$(TARGET): $(OBJECTS)
#	$(CC) $(CFLAGS) $^ -o $@ -lstdc++
#
#$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
#	$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJDIR):
#	mkdir -p $(OBJDIR)
#
#clean:
#	rm -rf $(OBJDIR) $(TARGET)
#
#.PHONY: clean

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Список исходных файлов
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Преобразование исходных файлов в список объектных файлов
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Имя исполняемого файла
TARGET = $(BINDIR)/main

all: $(TARGET) run

# Компиляция объектных файлов
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean

# Создание директорий obj и bin при их отсутствии
$(shell mkdir -p $(OBJDIR) $(BINDIR))

