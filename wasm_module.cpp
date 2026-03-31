// wasm_module.cpp
#include <emscripten/bind.h>
#include <cmath>

using namespace emscripten;

// Your critical math functions
float halfToFloat(unsigned short h) {
    unsigned int s = (h & 0x8000) >> 15;
    unsigned int e = (h & 0x7c00) >> 10;
    unsigned int f = h & 0x03ff;
    
    if (e == 0) {
        return (s ? -1.0f : 1.0f) * powf(2, -14) * (f / 1024.0f);
    } else if (e == 0x1f) {
        return f ? NAN : (s ? -1.0f : 1.0f) * INFINITY;
    }
    return (s ? -1.0f : 1.0f) * powf(2, e - 15) * (1.0f + f / 1024.0f);
}

// Test function to verify it's working
int add(int a, int b) {
    return a + b;
}

// Export to JavaScript
EMSCRIPTEN_BINDINGS(my_module) {
    function("halfToFloat", &halfToFloat);
    function("add", &add);
}
