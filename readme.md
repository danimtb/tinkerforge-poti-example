## Tinkerforge linear potentiometer example application

Application that connects to a Tinkerforge's linear poti and outputs the read position of the slider.

### Requirements

Needed tools installed in your machine to run the examples:

- Python with `pip` package manager installed
- Conan: `pip install Conan` or download from https://conan.io/downloads
- CMake: https://cmake.org/download
- Compiler of choice: gcc, clang, apple-clang, visual studio (we are using Visual Studio 2017 in this example)

### Building the app

Create a `build` directory and change to it:

```
mkdir build && cd build
```

Install app dependencies tinkerforge, CLI11 and fmt using Conan:

```
conan install ../conanfile.txt
```

Configure the project and build the examples using CMake build system:

```
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build . --config Release
```

Run the examples:

```
Release/tinkerforge-example.exe --help
```
