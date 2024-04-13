compileargs = benchmark/benchmark-engine.cpp engine.cpp bitboardgame.cpp lookuptables.cpp -std=c++20

a: *.cpp
	g++ *.cpp -O3 -o a -std=c++20

benchmark: benchmark/benchmark-engine.cpp engine.cpp bitboardgame.cpp lookuptables.cpp
	g++ $(compileargs) -o benchmark/benchmark-engine
	g++ $(compileargs) -O2 -o benchmark/benchmark-engine-O2
	g++ $(compileargs) -O3 -o benchmark/benchmark-engine-O3
