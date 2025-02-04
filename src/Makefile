CXX = g++
OBJS = Forfeit.o Scanner.o Token.o
EXE  = Forfeit
HEADERS = Scanner.hpp Token.hpp TokenType.hpp
CPPFLAGS = -Wall -g -std=c++17

# default target
$(EXE): $(OBJS)
	echo "Linking executable"
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cpp $(HEADERS)
	echo "Compiling $@"
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM