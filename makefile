all: simulator_Q1 simulator_Q2

simulator_Q1: simulator.cpp
	g++ -o simulator_Q1 simulator.cpp maxHeap1.cpp

simulator_Q2: simulator.cpp
	g++ -o simulator_Q2 simulator.cpp maxHeap2.cpp

clean:
	rm -fr *~  simulator_Q1 simulator_Q2
