#pragma once

// Specs found at:
// http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf
// https://gbdev.io/pandocs

#include "registers.h"

typedef struct CPU {
    registers registers;
    uint8_t memory[0x10000];
} CPU;

// Memory operations
void write_byte(CPU *cpu, uint16_t addr, uint8_t val);
uint8_t read_byte(CPU *cpu, uint16_t addr);

// No operation
void noop(void);

// Load instructions
void ld_r8_r8(CPU *cpu, Reg8 dest, Reg8 src);
void ld_r8_n8(CPU *cpu, Reg8 dest, uint8_t val);
void ld_r16_n16(CPU *cpu, Reg16 dest, uint16_t val);
void ld_hl_r8(CPU *cpu, Reg8 src);
void ld_hl_n8(CPU *cpu, uint8_t val);
void ld_r8_hl(CPU *cpu, Reg8 dest);
void ld_r16_a(CPU *cpu, Reg16 dest);
void ld_n16_a(CPU *cpu, uint16_t addr);
void ldh_n16_a(CPU *cpu, uint16_t addr);
void ldh_c_a(CPU *cpu);
void ld_a_r16(CPU *cpu, Reg16 src);
void ld_a_n16(CPU *cpu, uint16_t *val);
void ldh_a_n16(CPU *cpu, uint16_t *val);
void ldh_a_c(CPU *cpu);
void ldh_hli_a(CPU *cpu);
void ldh_hld_a(CPU *cpu);
void ldh_a_hld(CPU *cpu);
void ldh_a_hli(CPU *cpu);
void ldh_n16_sp(CPU *cpu, uint16_t* dest);
void ldh_hl_sp_e8(CPU *cpu);
void ldh_sp_hl(CPU *cpu);
