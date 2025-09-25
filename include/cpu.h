#pragma once

// Specs found at:
// http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
// https://gbdev.io/pandocs

// CPU Instructions
// https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7#LD_r8,n8

// OP Codes
// https://gbdev.io/gb-opcodes/optables/

#include "registers.h"

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

typedef struct CPU {
    registers registers;
    uint8_t memory[0x10000]; /* 65536 bytes */
    // May need a status indicator for halted?
} CPU;

struct instruction {
    char* name;
    uint8_t (*execute)(CPU*); // returns M-cycles (4 ticks)
};

extern const struct instruction instructions[256];

uint8_t execute(CPU *cpu, uint8_t op);

// Memory operations
void write_byte(CPU *cpu, uint16_t addr, uint8_t val);
uint8_t read_byte(CPU *cpu, uint16_t addr);

uint8_t noop(CPU* cpu);        // 0x00
uint8_t ld_bc_n16(CPU* cpu);   // 0x01
uint8_t ld_bc_a(CPU* cpu);     // 0x02
uint8_t inc_bc(CPU* cpu);      // 0x03
uint8_t inc_b(CPU* cpu);       // 0x04
uint8_t dec_b(CPU* cpu);       // 0x05
uint8_t ld_b_n8(CPU* cpu);     // 0x06
uint8_t rlca(CPU* cpu);        // 0x07
uint8_t ld_a16_sp(CPU* cpu);   // 0x08
uint8_t add_hl_bc(CPU* cpu);   // 0x09
uint8_t ld_a_bc(CPU* cpu);     // 0x0A
uint8_t dec_bc(CPU* cpu);      // 0x0B
uint8_t inc_c(CPU* cpu);       // 0x0C
uint8_t dec_c(CPU* cpu);       // 0x0D
uint8_t ld_c_n8(CPU* cpu);     // 0x0E
uint8_t rrca(CPU* cpu);        // 0x0F

uint8_t stop_n8(CPU* cpu);     // 0x10
uint8_t ld_de_n16(CPU* cpu);   // 0x11
uint8_t ld_de_a(CPU* cpu);     // 0x12
uint8_t inc_de(CPU* cpu);      // 0x13
uint8_t inc_d(CPU* cpu);       // 0x14
uint8_t dec_d(CPU* cpu);       // 0x15
uint8_t ld_d_n8(CPU* cpu);     // 0x16
uint8_t rla(CPU* cpu);         // 0x17
uint8_t jr_e8(CPU* cpu);       // 0x18
uint8_t add_hl_de(CPU* cpu);   // 0x19
uint8_t ld_a_de_byte(CPU* cpu);// 0x1A
uint8_t dec_de(CPU* cpu);      // 0x1B
uint8_t inc_e(CPU* cpu);       // 0x1C
uint8_t dec_e(CPU* cpu);       // 0x1D
uint8_t ld_e_n8(CPU* cpu);     // 0x1E
uint8_t rra(CPU* cpu);         // 0x1F

uint8_t jr_nz_e8(CPU* cpu);    // 0x20
uint8_t ld_hl_n16(CPU* cpu);   // 0x21
uint8_t ld_hli_a(CPU* cpu);    // 0x22
uint8_t inc_hl(CPU* cpu);      // 0x23
uint8_t inc_h(CPU* cpu);       // 0x24
uint8_t dec_h(CPU* cpu);       // 0x25
uint8_t ld_h_n8(CPU* cpu);     // 0x26
uint8_t daa(CPU* cpu);         // 0x27
uint8_t jr_z_e8(CPU* cpu);     // 0x28
uint8_t add_hl_hl(CPU* cpu);   // 0x29
uint8_t ld_a_hli(CPU* cpu);    // 0x2A
uint8_t dec_hl(CPU* cpu);      // 0x2B
uint8_t inc_l(CPU* cpu);       // 0x2C
uint8_t dec_l(CPU* cpu);       // 0x2D
uint8_t ld_l_n8(CPU* cpu);     // 0x2E
uint8_t cpl(CPU* cpu);         // 0x2F

uint8_t jr_nc_e8(CPU* cpu);    // 0x30
uint8_t ld_sp_n16(CPU* cpu);   // 0x31
uint8_t ld_hld_a(CPU* cpu);    // 0x32
uint8_t inc_sp(CPU* cpu);      // 0x33
uint8_t inc_hl(CPU* cpu);      // 0x34
uint8_t dec_hl(CPU* cpu);      // 0x35
uint8_t ld_hl_n8(CPU* cpu);    // 0x36
uint8_t scf(CPU* cpu);         // 0x37
uint8_t jr_c_e8(CPU* cpu);     // 0x38
uint8_t add_hl_sp(CPU* cpu);   // 0x39
uint8_t ld_a_hld(CPU* cpu);    // 0x3A
uint8_t dec_sp(CPU* cpu);      // 0x3B
uint8_t inc_a(CPU* cpu);       // 0x3C
uint8_t dec_a(CPU* cpu);       // 0x3D
uint8_t ld_a_n8(CPU* cpu);     // 0x3E
uint8_t ccf(CPU* cpu);         // 0x3F

void undefined(CPU* cpu);