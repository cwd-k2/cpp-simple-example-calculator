CXX	= g++
CXXFLAGS	= -std=c++17
LIBS	= -lX11 -lXft -lfontconfig -lrt -lpthread -lnana -llua
LDFLAGS	=
PROGRAM	= calculator

all:	$(PROGRAM)

$(PROGRAM):	./src/main.cpp
	$(CXX) ./src/main.cpp $(CXXFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)
