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
uint16_t get_reg16(CPU *cpu, Reg16 r)
{
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