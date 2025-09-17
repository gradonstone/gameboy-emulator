#include "registers.h"
#include "cpu.h"

uint8_t get_reg8(CPU *cpu, Reg8 r)
{
    switch (r)
    {
        case REG_A: return cpu->registers.AF.A;
        case REG_B: return cpu->registers.BC.B;
        case REG_C: return cpu->registers.BC.C;
        case REG_D: return cpu->registers.DE.D;
        case REG_E: return cpu->registers.DE.E;
        case REG_H: return cpu->registers.HL.H;
        case REG_L: return cpu->registers.HL.L;
    }
    return 0;
}

void set_reg8(CPU *cpu, Reg8 r, uint8_t val)
{
    switch (r)
    {
        case REG_A: cpu->registers.AF.A = val; break;
        case REG_B: cpu->registers.BC.B = val; break;
        case REG_C: cpu->registers.BC.C = val; break;
        case REG_D: cpu->registers.DE.D = val; break;
        case REG_E: cpu->registers.DE.E = val; break;
        case REG_H: cpu->registers.HL.H = val; break;
        case REG_L: cpu->registers.HL.L = val; break;
    }
}

uint16_t get_reg16(CPU *cpu, Reg16 r)
{
    switch (r)
    {
        case REG_AB: return cpu->registers.AF.AF;
        case REG_BC: return cpu->registers.BC.BC;
        case REG_DE: return cpu->registers.DE.DE;
        case REG_HL: return cpu->registers.HL.HL;
        case REG_SP: return cpu->registers.SP;
        case REG_PC: return cpu->registers.PC;
    }
    return 0;
}

void set_reg16(CPU *cpu, Reg16 r, uint16_t val)
{
    switch (r)
    {
        case REG_AB: cpu->registers.AF.AF = val; break;
        case REG_BC: cpu->registers.BC.BC = val; break;
        case REG_DE: cpu->registers.DE.DE = val; break;
        case REG_HL: cpu->registers.HL.HL = val; break;
        case REG_SP: cpu->registers.SP = val; break;
        case REG_PC: cpu->registers.PC = val; break;
    } 
}

void inc_reg8(CPU *cpu, Reg8 r)
{
    switch (r)
    {
        case REG_A: ++cpu->registers.AF.A; break;
        case REG_B: ++cpu->registers.BC.B; break;
        case REG_C: ++cpu->registers.BC.C; break;
        case REG_D: ++cpu->registers.DE.D; break;
        case REG_E: ++cpu->registers.DE.E; break;
        case REG_H: ++cpu->registers.HL.H; break;
        case REG_L: ++cpu->registers.HL.L; break;
        default:
            break;
    }
}
void inc_reg16(CPU *cpu, Reg16 r)
{
    switch (r)
    {
        case REG_AB: ++cpu->registers.AF.AF; break;
        case REG_BC: ++cpu->registers.BC.BC; break;
        case REG_DE: ++cpu->registers.DE.DE; break;
        case REG_HL: ++cpu->registers.HL.HL; break;
        default:
            break;
    }
}

void dec_reg16(CPU *cpu, Reg16 r)
{
    switch (r)
    {
        case REG_AB: --cpu->registers.AF.AF; break;
        case REG_BC: --cpu->registers.BC.BC; break;
        case REG_DE: --cpu->registers.DE.DE; break;
        case REG_HL: --cpu->registers.HL.HL; break;
        default:
            break;
    }
}