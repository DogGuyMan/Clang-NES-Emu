/**
 * @file bus.c
 * @brief CPU memory bus implementation.
 */
#include "bus/bus.h"

u8 bus_cpu_read(Bus *bus, u16 addr) {
    (void)bus;
    (void)addr;
    /* TODO: implement address decoding */
    return 0;
}

void bus_cpu_write(Bus *bus, u16 addr, u8 val) {
    (void)bus;
    (void)addr;
    (void)val;
    /* TODO: implement address decoding */
}
