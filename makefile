EXEC = algEvolutivo

# Compilador
CXX = g++

SRC = mainAlgEvolutivo.cpp control_functions.cpp greedy1.cpp
OBJ = $(SRC:.cpp=.o)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $(OBJ)

# Regla para compilar archivos .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@