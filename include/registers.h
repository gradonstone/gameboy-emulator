#pragma once
#include <stdint.h>

typedef struct CPU CPU;

typedef union {
    struct { uint8_t F, A; };
    uint16_t AF;
} reg_af;

typedef union {
    struct { uint8_t C, B; };
    uint16_t BC;
} reg_bc;

typedef union {
    struct { uint8_t E, D; };
    uint16_t DE;
} reg_de;

typedef union {
    struct { uint8_t L, H; };
    uint16_t HL;
} reg_hl;

typedef struct {
    reg_af AF;
    reg_bc BC;
    reg_de DE;
    reg_hl HL;
    uint16_t SP; // Stack pointers
    uint16_t PC; // Program counter
} registers;


// F register
typedef enum {
    FLAG_Z = 1 << 7, // Zero
    FLAG_N = 1 << 6, // Subtraction
    FLAG_H = 1 << 5, // Half carry
    FLAG_C = 1 << 4 // Carry
} FLAGS_MASK;

typedef enum Reg8 {
    REG_B, REG_C, REG_D, REG_E, REG_H, REG_L, REG_A
} Reg8;

typedef enum {
    REG_AB, REG_BC, REG_DE, REG_HL, REG_SP, REG_PC
} Reg16;

uint8_t get_reg8(CPU *cpu, Reg8 r);
uint16_t get_reg16(CPU *cpu, Reg16 r);
void set_reg8(CPU *cpu, Reg8 r, uint8_t val);
void set_reg16(CPU *cpu, Reg16 r, uint16_t val);
void inc_reg8(CPU *cpu, Reg8 r);
void inc_reg16(CPU *cpu, Reg16 r);
void dec_reg16(CPU *cpu, Reg16 r);