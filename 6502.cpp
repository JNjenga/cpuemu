
#include <iostream> 

#include "6502.h"

void init(m6502_t * cpu)
{
	cpu->mem = new uint16_t[(1 << 16)];
	cpu->ac = 0;
	cpu->x = 0;
	cpu->y = 0;
	cpu->sp = 0;
	cpu->pc = 0;
}

void execute_step(m6502_t * cpu)
{
	int opcode = cpu->mem[cpu->pc];
	switch(opcode)
	{
		case is_t::LDA_IM:
			{
				uint16_t value = cpu->mem[cpu->pc + 1];
				cpu->ac = value;
				cpu->pc += 2;
				break;
			}
		case is_t::LDA_ZP:
			{
				uint8_t address = cpu->mem[cpu->pc + 1];
				cpu->ac = cpu->mem[address];
				cpu->pc += 3;
				break;
			}
		case is_t::LDA_ZPX:
			{
				uint16_t address = cpu->mem[cpu->pc + 1] + cpu->x;
				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::LDA_ABS:
			{
				uint16_t address = cpu->mem[cpu->pc + 1];
				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::LDA_ABSX:
			{
				uint16_t address = cpu->mem[cpu->pc + 1] + cpu->x;
				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::LDA_ABSY:
			{
				uint16_t address = cpu->mem[cpu->pc + 1] + cpu->y;
				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::LDA_IX:
			{
				uint16_t address = cpu->mem[cpu->pc + 1];
				address = cpu->mem[address] + cpu->x;

				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::LDA_IY:
			{
				uint16_t address = cpu->mem[cpu->pc + 1];
				address = cpu->mem[address] + cpu->y;

				cpu->ac = cpu->mem[address];
				cpu->pc += 4;
				break;
			}
		case is_t::ADC_IM:
			{
				uint16_t src = cpu->mem[cpu->pc + 1];
				cpu->ac += src;
				cpu->pc += 2;
				break;
			}
		case is_t::ADC_ZP:
			{
				int address = cpu->mem[cpu->pc + 1];
				cpu->ac += cpu->mem[address];
				cpu->pc += 3;
				break;
			}
		case is_t::ADC_ABS:
			{
				uint16_t address = cpu->mem[cpu->pc + 1];
				cpu->ac += cpu->mem[address];
				cpu->pc += 3;
				break;
			}
		case is_t::STA_ABS:
			{
				uint16_t address = cpu->mem[cpu->pc + 1];
				cpu->mem[address] = cpu->ac;
				cpu->pc += 4;
				break;
			}
		default:
			break;
	}
}

void reset(m6502_t * cpu)
{
	for(int i = 0; i < (1<<16) ; i ++)
		cpu->mem[i] = 0;

	cpu->ac = 0;
	cpu->x = 0;
	cpu->y = 0;
	cpu->sp = 0;
	cpu->pc = 0;
}

void terminate(m6502_t * cpu)
{
	delete cpu->mem;
}

void print_cpu(m6502_t * cpu)
{
    std::cout << std::hex;
    std::cout << "pc " << static_cast<int>(cpu->pc)<< "\n";
    std::cout << "ac " << static_cast<int>(cpu->ac) << "\n";
    std::cout << "x " << static_cast<int>(cpu->x)<< "\n";
    std::cout << "y " << static_cast<int>(cpu->y)<< "\n";
	for(int i = 0; i < (1<<8) ; i ++)
	{
		if(i == cpu->pc)
			std::cout << "\033[1;31m" <<cpu->mem[i] << "\033[0m ";
		else
			std::cout << cpu->mem[i] << " ";
	}
	std::cout<< "\n";
}
