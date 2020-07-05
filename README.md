# Amber Fuzz

Amber Fuzz is a graphics tool developed during the Google Summer of Code. It takes an [Amber](https://github.com/google/amber) script as input and outputs a new script by fuzzing the reference shaders.

## Dependencies

The folder containing `spirv-as`, `spirv-dis` and `spirv-fuzz` must be in the `PATH` environment variable.

## Build

```
mkdir build && cd build
cmake ..
cmake --build .
```

## Run

```
./amber-fuzz script.amber
```
