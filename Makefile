SRCS=$(wildcard src/*.cpp)

ass3: ${SRCS}
	mkdir -p cmake-build
	cd cmake-build; cmake -DCMAKE_BUILD_TYPE=Release ..; make;
	ln -sf cmake-build/data_a5 ass5
