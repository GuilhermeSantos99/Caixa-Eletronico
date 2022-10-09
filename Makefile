# Nome do projeto
PROJ_NAME=atm

# Arquivos .cpp
CPP_SOURCE=$(wildcard *.cpp)

# Arquivos .hpp
HPP_SOURCE=$(wildcard *.hpp)

# Arquivos .o (Object files)
OBJ=$(CPP_SOURCE:.c=.o)

# Nome do compilador
CC=g++

# Flags para o compilador
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic	

#
# Compilação e linking
#
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.cpp %.hpp
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.cpp $(HPP_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~
