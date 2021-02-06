#define E6502_IMPLEMENTATION 
#include <iostream>
#include <cassert>
#include "6502.h"

void test_instrucitons();

int main()
{
	test_instrucitons();
	return 0;
}


void test_instrucitons()
{
	m6502_t cpu;
	init(&cpu);

	// LDA
	cpu.mem[0] = is_t::LDA_IM;
	cpu.mem[1] = 200;
	execute_step(&cpu);
	assert(cpu.ac == 200);

	reset(&cpu);

	cpu.mem[200] = 6;

	cpu.mem[0] = is_t::LDA_ZP;
	cpu.mem[1] = 200;
	execute_step(&cpu);
	assert(cpu.ac == 6);
	reset(&cpu);

	cpu.mem[210] = 23;

	cpu.mem[0] = is_t::LDA_ZPX;
	cpu.x = 200;
	cpu.mem[1] = 10;
	execute_step(&cpu);
	assert(cpu.ac == 23);
	reset(&cpu);

	terminate(&cpu);
}
