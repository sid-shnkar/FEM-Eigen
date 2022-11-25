CXX = g++
CXFLAGS =-g -std=c++11
CFLAGS=-I../../../../nfs_home/nikhilh/eigen-3.3.9

ANALYTICAL = src/analytical/src/
NUMERICAL = src/numerical/src/
SOLUTION = src/generate_solution/src/
BINARY = bin/
OUTPUTDIR = outputs_csv/
CLEANOBJ = $(BINARY)


sdsc: checkbin analytical numerical solution

analytical: $(ANALYTICAL)analytical1.cpp $(ANALYTICAL)analytical2.cpp 
	$(CXX) $(ANALYTICAL)analytical1.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)analytical1.out
	$(CXX) $(ANALYTICAL)analytical2.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)analytical2.out


numerical: $(NUMERICAL)numerical1.cpp $(NUMERICAL)numerical2.cpp 
	$(CXX) $(NUMERICAL)numerical1.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)numerical1.out
	$(CXX) $(NUMERICAL)numerical2.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)numerical2.out


solution: $(SOLUTION)solution_part1.cpp $(SOLUTION)solution_part2.cpp 
	$(CXX) $(SOLUTION)solution_part1.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)solution_part1.out
	$(CXX) $(SOLUTION)solution_part2.cpp $(CXFLAGS) $(CFLAGS) -o $(BINARY)solution_part2.out

checkbin:
	if [ ! -d $(BINARY) ]; then mkdir $(BINARY); fi
	
checkoutputdir:
	if [ ! -d $(OUTPUTDIR) ]; then mkdir $(OUTPUTDIR); fi

clean:
	rm $(CLEANOBJ)

team:
	@echo 200010056 - Vidyasagar Singadi
	@echo 200030056 - Siddharth Shankar
