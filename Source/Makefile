C++ = g++ -Wall -g -D DEBUG $(INCLUDE)

# On Ubuntu 12.04 the glpk library can be automatically installed using the command:
# 	sudo apt-get install libglpk0 libglpk-dev
LIBRARIES = -lglpk -lm
INCLUDE =
# If you installed GLPK manually, please inform the location for the
# header files instead. For instance:
#INCLUDE = -I./glpk-4.47/src

RM = /bin/rm -f

PROGRAM_NAME = cutting-stock

UNIT_TEST_DIR = UnitTests
UNIT_TEST_PROGRAM_NAME = unit-test-suite

######################################################################

MODULES = CuttingStockPattern.o CuttingStockSolver.o CuttingStockLinearRelaxationSolver.o CuttingStockInstance.o CuttingStockMathProgInstance.o CuttingStockInstanceBuilder.o CuttingStockHeuristicIntegerSolver.o CuttingStockExactIntegerSolver.o IntegerKnapsackSolver.o FloatingPointComparer.o Time.o GlpkUtil.o

UNIT_TEST_MODULES = $(UNIT_TEST_DIR)/CuttingStockInstanceTest.o $(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.o $(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.o $(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.o $(UNIT_TEST_DIR)/CuttingStockPatternTest.o $(UNIT_TEST_DIR)/CuttingStockSolutionTest.o $(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.o $(UNIT_TEST_DIR)/FloatingPointComparerTest.o

######################################################################

$(PROGRAM_NAME): Main.cpp $(MODULES)
	@echo "Compiling $(PROGRAM_NAME)..."
	@$(C++) $(MODULES) -o $(PROGRAM_NAME) $< $(LIBRARIES)

run: $(PROGRAM_NAME)
	@./$(PROGRAM_NAME)

######################################################################

# Modules

Time.o: Time.cpp Time.hpp
	@$(C++) -c Time.cpp

FloatingPointComparer.o: FloatingPointComparer.cpp FloatingPointComparer.hpp Comparer.hpp
	@$(C++) -c FloatingPointComparer.cpp

GlpkUtil.o: GlpkUtil.cpp GlpkUtil.hpp
	@$(C++) -c GlpkUtil.cpp

IntegerKnapsackSolver.o: IntegerKnapsackSolver.cpp IntegerKnapsackSolver.hpp Knapsack.hpp Comparer.hpp
	@$(C++) -c IntegerKnapsackSolver.cpp

CuttingStockPattern.o: CuttingStockPattern.cpp CuttingStockPattern.hpp
	@$(C++) -c CuttingStockPattern.cpp

CuttingStockSolver.o: CuttingStockSolver.cpp CuttingStockSolver.hpp CuttingStockPattern.hpp
	@$(C++) -c CuttingStockSolver.cpp

CuttingStockInstance.o: CuttingStockInstance.cpp CuttingStockInstance.hpp
	@$(C++) -c CuttingStockInstance.cpp

CuttingStockMathProgInstance.o: CuttingStockMathProgInstance.cpp CuttingStockMathProgInstance.hpp CuttingStockInstance.hpp
	@$(C++) -c CuttingStockMathProgInstance.cpp

CuttingStockLinearRelaxationSolver.o: CuttingStockLinearRelaxationSolver.cpp CuttingStockLinearRelaxationSolver.hpp CuttingStockInstance.hpp CuttingStockSolver.hpp CuttingStockPattern.hpp IntegerKnapsackSolver.hpp FloatingPointComparer.hpp Time.hpp GlpkUtil.hpp
	@$(C++) -c CuttingStockLinearRelaxationSolver.cpp

CuttingStockHeuristicIntegerSolver.o: CuttingStockHeuristicIntegerSolver.cpp CuttingStockHeuristicIntegerSolver.hpp IntegerSolverBacktrackingMode.hpp CuttingStockLinearRelaxationSolver.hpp CuttingStockInstance.hpp CuttingStockSolver.hpp CuttingStockPattern.hpp Time.hpp GlpkUtil.hpp
	@$(C++) -c CuttingStockHeuristicIntegerSolver.cpp

CuttingStockExactIntegerSolver.o: CuttingStockExactIntegerSolver.cpp CuttingStockExactIntegerSolver.hpp IntegerSolverBacktrackingMode.hpp CuttingStockInstance.hpp CuttingStockMathProgInstance.hpp CuttingStockSolver.hpp CuttingStockPattern.hpp Time.hpp GlpkUtil.hpp
	@$(C++) -c CuttingStockExactIntegerSolver.cpp

CuttingStockInstanceBuilder.o: CuttingStockInstanceBuilder.cpp CuttingStockInstanceBuilder.hpp CuttingStockInstance.hpp
	@$(C++) -c CuttingStockInstanceBuilder.cpp

######################################################################

# Unit Tests

unit-tests: $(UNIT_TEST_PROGRAM_NAME)
	@./$(UNIT_TEST_PROGRAM_NAME)

$(UNIT_TEST_PROGRAM_NAME): UnitTestSuite.cpp $(MODULES) $(UNIT_TEST_MODULES)
	@$(C++) $(MODULES) $(UNIT_TEST_MODULES) -o $(UNIT_TEST_PROGRAM_NAME) $< $(LIBRARIES)

# Unit Test Modules

$(UNIT_TEST_DIR)/FloatingPointComparerTest.o: $(UNIT_TEST_DIR)/FloatingPointComparerTest.cpp $(UNIT_TEST_DIR)/FloatingPointComparerTest.hpp FloatingPointComparer.o
	@$(C++) -c $(UNIT_TEST_DIR)/FloatingPointComparerTest.cpp -o $(UNIT_TEST_DIR)/FloatingPointComparerTest.o

$(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.o: $(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.cpp $(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.hpp IntegerKnapsackSolver.o
	@$(C++) -c $(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.cpp -o $(UNIT_TEST_DIR)/IntegerKnapsackSolverTest.o

$(UNIT_TEST_DIR)/CuttingStockInstanceTest.o: $(UNIT_TEST_DIR)/CuttingStockInstanceTest.cpp $(UNIT_TEST_DIR)/CuttingStockInstanceTest.hpp CuttingStockInstance.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockInstanceTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockInstanceTest.o

$(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.o: $(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.cpp $(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.hpp CuttingStockInstanceBuilder.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockInstanceBuilderTest.o

$(UNIT_TEST_DIR)/CuttingStockPatternTest.o: $(UNIT_TEST_DIR)/CuttingStockPatternTest.cpp $(UNIT_TEST_DIR)/CuttingStockPatternTest.hpp CuttingStockPattern.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockPatternTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockPatternTest.o

$(UNIT_TEST_DIR)/CuttingStockSolutionTest.o: $(UNIT_TEST_DIR)/CuttingStockSolutionTest.cpp $(UNIT_TEST_DIR)/CuttingStockSolutionTest.hpp CuttingStockSolver.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockSolutionTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockSolutionTest.o

$(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.o: $(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.cpp $(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.hpp CuttingStockLinearRelaxationSolver.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockLinearRelaxationSolverTest.o

$(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.o: $(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.cpp $(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.hpp CuttingStockHeuristicIntegerSolver.o
	@$(C++) -c $(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.cpp -o $(UNIT_TEST_DIR)/CuttingStockHeuristicIntegerSolverTest.o


######################################################################

clean:
	@$(RM) *.o */*.o core temp.dat $(PROGRAM_NAME) $(UNIT_TEST_PROGRAM_NAME)
