#include <stdio.h>
#include "cpu.h"
#include "debug.h"

int main()
{
    CPU cpu;

    cpu.registers.AF.A = 0x00;
    cpu.registers.AF.F = 0x12;
    cpu.registers.HL.L = 0x00;

    set_reg8(&cpu, REG_H, 0x00);

    print_cpu(&cpu);

    return 0;
}