#include "Math.h"

#include "Converter.h"

size_t HashDouble(double value) {
    FConverter16 cvt;
    cvt.real = value;
    return cvt.integer & 0xfffffff8;
}
