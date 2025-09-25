#include "cpu.h"

uint8_t execute(CPU *cpu, uint8_t op)
{
    return instructions[op].execute(cpu);
}

// Memory access
void write_byte(CPU *cpu, uint16_t addr, uint8_t val)
{
    cpu->memory[addr] = val;
}
uint8_t read_byte(CPU *cpu, uint16_t addr)
{
    return cpu->memory[addr];
}

void undefined(CPU* cpu)
{

}

// Helpers
uint8_t read_n8(CPU* cpu)
{
    return read_byte(cpu, cpu->registers.PC++);
}
uint16_t read_n16(CPU* cpu)
{
    uint16_t high = (uint16_t)(read_byte(cpu, cpu->registers.PC++)) << 8;
    uint16_t low = (uint16_t)(read_byte(cpu, cpu->registers.PC++));
    return high | low;
}

void inc_pc(CPU* cpu, uint16_t mc)
{
    cpu->registers.PC += mc;
}

/* Instructions */
const struct instruction instructions[256] = {
    {"NOOP",        noop},      // 0x00
    {"LD BC n16",   ld_bc_n16}, // 0x01
    {"LD [BC] A",   ld_bc_a},   // 0x02
    {"INC BC",      inc_bc},    // 0x03
    {"INC B",       inc_b},     // 0x04
    {"DEC B",       dec_b},     // 0x05
    {"LD B n8",     ld_b_n8},   // 0x06
    {"RLCA",        rlca},  // 0x07
    {"LD [a16] SP", noop},  // 0x08
    {"ADD HL BC",   noop},  // 0x09
    {"LD A [BC]",   noop},  // 0x0A
    {"DEC BC",      noop},  // 0x0B
    {"INC C",       noop},  // 0x0C
    {"DEC C",       noop},  // 0x0D
    {"LD C n8",     noop},  // 0x0E
    {"RRCA",        noop},  // 0x0F
};

//0x00
uint8_t noop(CPU* cpu)
{
    return 1;
}

// 0x01
uint8_t ld_bc_n16(CPU* cpu)
{
    cpu->registers.BC.BC = read_n16(cpu);
    return 3;
}   

// 0x02
uint8_t ld_bc_a(CPU* cpu)
{
    write_byte(cpu, cpu->registers.BC.BC, cpu->registers.AF.A);
    return 2;
}     

// 0x03
uint8_t inc_bc(CPU* cpu)
{
    ++cpu->registers.BC.BC;
    return 2;
}      

// 0x04
uint8_t inc_b(CPU* cpu)
{
    ++cpu->registers.BC.B;
    return 1;
}       

// 0x05
uint8_t dec_b(CPU* cpu)
{
    --cpu->registers.BC.B;
    return 1;
}       

// 0x06
uint8_t ld_b_n8(CPU* cpu)
{
    cpu->registers.BC.B = read_n8(cpu);
    return 2;
}     

// 0x07
uint8_t rlca(CPU* cpu)
{
    uint8_t a = cpu->registers.AF.A;
    uint8_t c = (a & 0x80) >> 7;
    cpu->registers.AF.A = (a << 1) | c;
    cpu->registers.AF.F = 0;
    if (c) cpu->registers.AF.F |= FLAG_C;
    return 1;
}        

// 0x08
uint8_t ld_a16_sp(CPU* cpu)
{
    uint16_t addr = read_n16(cpu);
    write_byte(cpu, addr, (uint8_t)(0xFF & cpu->registers.AF.AF));
    write_byte(cpu, addr + 1, (uint8_t)(cpu->registers.SP >> 8));
    return 5;
}   

// 0x09
uint8_t add_hl_bc(CPU* cpu)
{
    cpu->registers.HL.HL += cpu->registers.BC.BC;
    return 2;
}

// 0x0A
uint8_t ld_a_bc(CPU* cpu)
{
    cpu->registers.AF.A = read_byte(cpu, cpu->registers.BC.BC);
    return 2;
}     

// 0x0B
uint8_t dec_bc(CPU* cpu)
{
    --cpu->registers.BC.BC;
    return 2;
}      

// 0x0C
uint8_t inc_c(CPU* cpu)
{
    ++cpu->registers.BC.C;
    return 1;
}       

// 0x0D
uint8_t dec_c(CPU* cpu)
{
    --cpu->registers.BC.C;
    return 1;
}       

// 0x0E
uint8_t ld_c_n8(CPU* cpu)
{
    cpu->registers.BC.C = read_n8(cpu);
    return 2;
}     

// 0x0F
uint8_t rrca(CPU* cpu)
{
    uint8_t c = 0x01 & cpu->registers.AF.A;
    cpu->registers.AF.A = cpu->registers.AF.A >> 1 | (c << 7);
    cpu->registers.AF.F = 0x00;
    if (c) cpu->registers.AF.F |= FLAG_C;
    return 1;
}        

// 0x10
uint8_t stop_n8(CPU* cpu)
{
    // halt cpu and lcd display until button pressed
    // will eventually increment 2 PC (2 byte instruction)
}     

// 0x11
uint8_t ld_de_n16(CPU* cpu)
{
    cpu->registers.DE.DE = read_n16(cpu);
    cpu->registers.PC += 3;
}   

// 0x12
uint8_t ld_de_a(CPU* cpu)
{
    write_byte(cpu, cpu->registers.DE.DE, cpu->registers.AF.A);
    cpu->registers.PC += 2;
}     

// 0x13
uint8_t inc_de(CPU* cpu)
{
    ++cpu->registers.AF.A; 
    cpu->registers.PC += 2;
}      

// 0x14
uint8_t inc_d(CPU* cpu)
{
    ++cpu->registers.DE.D;
    ++cpu->registers.PC;
}       

// 0x15
uint8_t dec_d(CPU* cpu)
{
    --cpu->registers.DE.D;
    ++cpu->registers.PC;
}       

// 0x16
uint8_t ld_d_n8(CPU* cpu)
{
    cpu->registers.DE.D = read_n8(cpu);
    cpu->registers.PC += 2;
}     

/* FIX CARRY */
// 0x17
uint8_t rla(CPU* cpu)
{
    uint8_t c = (0x80 & cpu->registers.AF.A) >> 7;
    cpu->registers.AF.A = cpu->registers.AF.A << 1;
    cpu->registers.AF.F = 0;
    if (c) cpu->registers.AF.F |= FLAG_C;
    ++cpu->registers.PC;
}         

// 0x18
uint8_t jr_e8(CPU* cpu)
{
    int8_t off = (int8_t)read_n8(cpu);
    return 2;
}       

// 0x19
uint8_t add_hl_de(CPU* cpu)
{
    uint16_t addr = read_n16(cpu);
    write_byte(cpu, addr, (uint8_t)(0xFF & cpu->registers.AF.AF));
    write_byte(cpu, addr + 1, (uint8_t)(cpu->registers.SP >> 8));
    return 2;
}   

// 0x1A
uint8_t ld_a_de_byte(CPU* cpu)
{
    cpu->registers.AF.A = read_byte(cpu, cpu->registers.DE.DE);
    return 2;
}     

// 0x1B
uint8_t dec_de(CPU* cpu)
{
    --cpu->registers.DE.DE;
    return 2;
}      

// 0x1C
uint8_t inc_e(CPU* cpu)
{
    ++cpu->registers.DE.E;
    return 1;
}       

// 0x1D
uint8_t dec_e(CPU* cpu)
{
    --cpu->registers.DE.E;
    return 1;
}       

// 0x1E
uint8_t ld_e_n8(CPU* cpu)
{
    cpu->registers.DE.E = read_n8(cpu);
    return 2;
}     

// 0x1F
uint8_t rra(CPU* cpu)
{
    uint8_t c = cpu->registers.AF.A & 0x01;
    cpu->registers.AF.A >>= 1;
    cpu->registers.AF.A |= ((cpu->registers.AF.F & FLAG_C) << 3);
    cpu->registers.AF.F = 0;
    if (c) cpu->registers.AF.F |= FLAG_C;
    return 1;
}         

// 0x20
uint8_t jr_nz_e8(CPU* cpu)
{
    uint8_t flags = cpu->registers.AF.F;
    if (flags & FLAG_N && flags & FLAG_Z)
    {
        cpu->registers.PC = (int16_t)cpu->registers.PC + (int16_t)read_n8(cpu);
        return 3;
    }
    return 2;
}    

// 0x21
uint8_t ld_hl_n16(CPU* cpu)
{

}   

// 0x22
uint8_t ld_hli_a(CPU* cpu)
{

}    

// 0x23
uint8_t inc_hl(CPU* cpu)
{

}      

// 0x24
uint8_t inc_h(CPU* cpu)
{

}       

// 0x25
uint8_t dec_h(CPU* cpu)
{

}       

// 0x26
uint8_t ld_h_n8(CPU* cpu)
{

}     

// 0x27
uint8_t daa(CPU* cpu)
{

}         

// 0x28
uint8_t jr_z_e8(CPU* cpu)
{

}     

// 0x29
uint8_t add_hl_hl(CPU* cpu)
{

}   

// 0x2A
uint8_t ld_a_hli(CPU* cpu)
{

}    

// 0x2B
uint8_t dec_hl(CPU* cpu)
{

}      

// 0x2C
uint8_t inc_l(CPU* cpu)
{

}       

// 0x2D
uint8_t dec_l(CPU* cpu)
{

}       

// 0x2E
uint8_t ld_l_n8(CPU* cpu)
{

}     

// 0x2F
uint8_t cpl(CPU* cpu)
{

}         

// 0x30
uint8_t jr_nc_e8(CPU* cpu)
{

}    

// 0x31
uint8_t ld_sp_n16(CPU* cpu)
{

}   

// 0x32
uint8_t ld_hld_a(CPU* cpu)
{

}    

// 0x33
uint8_t inc_sp(CPU* cpu)
{

}      

// 0x34
uint8_t inc_hl(CPU* cpu)
{

}      

// 0x35
uint8_t dec_hl(CPU* cpu)
{

}      

// 0x36
uint8_t ld_hl_n8(CPU* cpu)
{

}    

// 0x37
uint8_t scf(CPU* cpu)
{

}         

// 0x38
uint8_t jr_c_e8(CPU* cpu)
{

}     

// 0x39
uint8_t add_hl_sp(CPU* cpu)
{

}   

// 0x3A
uint8_t ld_a_hld(CPU* cpu)
{

}    

// 0x3B
uint8_t dec_sp(CPU* cpu)
{

}      

// 0x3C
uint8_t inc_a(CPU* cpu)
{

}       

// 0x3D
uint8_t dec_a(CPU* cpu)
{

}       

// 0x3E
uint8_t ld_a_n8(CPU* cpu)
{

}     

// 0x3F
uint8_t ccf(CPU* cpu)
{

}         