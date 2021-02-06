#ifndef EMU_6502_H_
#define EMU_6502_H_

#include <cstdint>

struct m6502_t
{
	uint8_t ac;
	uint8_t x;
	uint8_t y;
	uint8_t sp;
	uint16_t pc;
	uint16_t st;
	uint16_t * mem;
};

enum is_t
{
	LDA_IM,LDA_ZP, LDA_ZPX, LDA_ZPY,
	LDA_ABS, LDA_ABSX, LDA_ABSY, LDA_IX,LDA_IY,
	ADC_IM, ADC_ZP, ADC_ZPX, ADC_ZPY,
	ADC_ABS, ADC_ABSX, ADC_ABSY, ADC_IX, ADC_IY,
	STA_ABS, STA_ZP, STA_ZPX, STA_ZPY, STA_IX, STA_IY,
};

void init(m6502_t * cpu);
void execute_step(m6502_t * cpu);
void reset(m6502_t * cpu);
void terminate(m6502_t * cpu);
void print_cpu(m6502_t * cpu);

#endif
