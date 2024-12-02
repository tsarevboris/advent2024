# Compile and build a day
cmake -S . -B build && cmake --build build

# Build and run
cmake -S . -B build && cmake --build build && ./build/main
