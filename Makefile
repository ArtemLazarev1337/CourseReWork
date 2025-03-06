CC = clang++
CCFLAGS = -Wall -Wextra -std=c++11 -g
TARGET = coursework

DIR_SRC = ./src/
DIR_OBJ = ./obj/

SRC = $(wildcard $(DIR_SRC)*.cpp)
OBJ = $(patsubst $(DIR_SRC)%.cpp, $(DIR_OBJ)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(TARGET)

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	@rm -f $(TARGET) $(DIR_OBJ)*.o

run:
	@make -s clean && make -s && ./$(TARGET)
