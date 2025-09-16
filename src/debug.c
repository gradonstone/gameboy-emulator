#include "debug.h"
#include <stdio.h>

void print_cpu(const CPU *cpu)
{
    printf("CPU State:\n");
    printf("  A: 0x%02X  F: 0x%02x\n", cpu->registers.AF.A, cpu->registers.AF.F);
    printf("  B: 0x%02X  C: 0x%02x\n", cpu->registers.BC.B, cpu->registers.BC.C);
    printf("  D: 0x%02X  E: 0x%02x\n", cpu->registers.DE.D, cpu->registers.DE.E);
    printf("  H: 0x%02X  L: 0x%02x\n", cpu->registers.HL.H, cpu->registers.HL.L);
}