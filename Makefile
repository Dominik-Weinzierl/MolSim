CC=clang
CXX=clang++
CMAKE=cmake
OUTPUT="./build"
SOURCE="."

all: build_cmake

build_cmake: create_folder
	$(CMAKE) -S$(SOURCE) -B$(OUTPUT) -D BUILD_DOCUMENTATION=OFF -D CMAKE_C_COMPILER=$(CC)  -D CMAKE_CXX_COMPILER=$(CXX)

build_with_doc: create_folder
	$(CMAKE) -S$(SOURCE) -B$(OUTPUT) -D BUILD_DOCUMENTATION=ON -D CMAKE_C_COMPILER=$(CC)  -D CMAKE_CXX_COMPILER=$(CXX)

create_folder:
	@if [ -d "$(OUTPUT)" ]; then rm -rf $(OUTPUT); fi
	@mkdir $(OUTPUT)
	@echo "Build folder created -> $(OUTPUT)";

clean:
	@rm -rf $(OUTPUT)
	@echo "Build folder removed!";