EXEC = algEvolutivo
EXEC1 = ACOElite

# Compilador
CXX = g++

OBJ_DIR = build

SRC = src/mainAlgEvolutivo.cpp src/control_functions.cpp src/greedy1.cpp
SRC1 = src/mainACOElite.cpp src/control_functions.cpp src/greedy1.cpp src/acoElite.cpp

OBJ = $(SRC:.cpp=.o)
OBJ1 = $(SRC1:.cpp=.o)


all: $(EXEC) $(EXEC1)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^

$(EXEC1): $(OBJ1)
	$(CXX) -o $@ $^

# Regla para compilar archivos .cpp en .o
&(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar
clean:
	rm -rf $(OBJ_DIR) $(EXEC) $(EXEC1)