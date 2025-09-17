#include "cpu.h"

// Memory access
void write_byte(CPU *cpu, uint16_t addr, uint8_t val)
{
    cpu->memory[addr] = val;
}
uint8_t read_byte(CPU *cpu, uint16_t addr)
{
    return cpu->memory[addr];
}

void noop(void)
{

}

// Load instructions
void ld_r8_r8(CPU *cpu, Reg8 dest, Reg8 src)
{
    uint8_t val = get_reg8(cpu, src);
    set_reg8(cpu, dest, val);
}
void ld_r8_n8(CPU *cpu, Reg8 dest, uint8_t val)
{
    set_reg8(cpu, dest, val);
}
void ld_r16_n16(CPU *cpu, Reg16 dest, uint16_t val)
{
    set_reg16(cpu, dest, val);
}
void ld_hl_r8(CPU *cpu, Reg8 src)
{
    uint8_t val = get_reg8(cpu, src);
    uint16_t addr = cpu->registers.HL.HL;
    write_byte(cpu, addr, val);
}
void ld_hl_n8(CPU *cpu, uint8_t val)
{
    uint16_t addr = cpu->registers.HL.HL;
    write_byte(cpu, addr, val);
}
void ld_r8_hl(CPU *cpu, Reg8 dest)
{
    uint8_t val = read_byte(cpu, cpu->registers.HL.HL);
    set_reg8(cpu, dest, val);
}
void ld_r16_a(CPU *cpu, Reg16 dest)
{
    uint8_t val = get_reg8(cpu, REG_A);
    uint16_t addr = get_reg16(cpu, dest);
    write_byte(cpu, addr, val);
}
void ld_n16_a(CPU *cpu, uint16_t addr)
{
    uint8_t val = get_reg8(cpu, REG_A);
    write_byte(cpu, addr, val);
}
void ldh_n16_a(CPU *cpu, uint16_t addr)
{
    if (addr >= 0xFF00)
    {
        ld_n16_a(cpu, addr);
    }
}
void ldh_c_a(CPU *cpu)
{
    uint8_t ofs = get_reg8(cpu, REG_C);
    uint8_t val = read_byte(cpu, (0xFF00 + ofs));
    set_reg8(cpu, REG_A, val);
}
void ld_a_r16(CPU *cpu, Reg16 src)
{
    uint16_t addr = get_reg16(cpu, src);
    uint8_t val = read_byte(cpu, addr);
    set_reg8(cpu, REG_A, val);
}
void ld_a_n16(CPU *cpu, uint16_t addr)
{
    uint8_t val = read_byte(cpu, addr);
    set_reg8(cpu, REG_A, val);
}
void ldh_a_n16(CPU *cpu, uint16_t addr)
{
    if (addr >= 0xFF00)
    {
        ld_a_n16(cpu, addr);
    }
}
void ldh_a_c(CPU *cpu)
{
    uint8_t ofs = get_reg8(cpu, REG_C);
    uint8_t val = read_byte(cpu, 0xFF00 + ofs);
    set_reg8(cpu, REG_A, val);
}
void ldh_hli_a(CPU *cpu)
{
    ld_r16_a(cpu, REG_HL);
    inc_reg16(cpu, REG_HL);
}
void ldh_hld_a(CPU *cpu)
{
    ld_r16_a(cpu, REG_HL);
    dec_reg16(cpu, REG_HL);   
}
void ldh_a_hld(CPU *cpu)
{
    ld_a_r16(cpu, REG_HL);
    dec_reg16(cpu, REG_HL);
}
void ldh_a_hli(CPU *cpu)
{
    ld_a_r16(cpu, REG_HL);
    dec_reg16(cpu, REG_HL);
}
void ldh_n16_sp(CPU *cpu, uint16_t addr)
{
    write_byte(cpu, addr, cpu->registers.SP & 0xFF);
    write_byte(cpu, addr + 1, cpu->registers.SP >> 8);
}
void ldh_hl_sp_e8(CPU *cpu, int8_t val)
{
    set_reg16(cpu, REG_HL, cpu->registers.SP + val);
}
void ldh_sp_hl(CPU *cpu)
{
    uint16_t val = get_reg16(cpu, REG_HL);
    set_reg16(cpu, REG_SP, val);
}
