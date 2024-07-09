# Define the default target (optional)
.PHONY: all
all: build

# Define the build target
.PHONY: build
build:
	mkdir -p build
	cd build && cmake ..
	cd build && make

# Define the run target
.PHONY: run
run: build
	./build/voxel

# Define the clean target
.PHONY: clean
clean:
	rm -rf build