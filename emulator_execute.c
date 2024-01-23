#include "emulator.h"

void emulator_execute(Emulator *emu, uint16_t instr) {
	
	/*types of instructions
		op N N N
		op X N N
		op X Y N
	*/

	uint16_t NNN;
	uint8_t op, X, Y, N, NN;
	op = (instr & 0xF000) >> 12;
	X = (instr & 0x0F00) >> 8;
	Y = (instr & 0x00F0) >> 4;
	N = (instr & 0x000F);

	NN = (instr & 0x00FF);
	NNN = (instr & 0x0FFF);

	switch (op) {

		case 0x0:
			if (N == 0x0) {
				// TO DO clear screen
			} else {
				emu->program_counter = emu->stack[emu->stack_pointer];
				emu->stack_pointer = emu->stack_pointer - 1;
			}
			break;
		case 0x1:
			emu->program_counter = NNN;
			break;
		case 0x2:
			emu->stack_pointer = emu->stack_pointer + 1;
			emu->stack[emu->stack_pointer] = emu->program_counter;
			emu->program_counter = NNN;
			break;
		case 0x3:
			if (emu->registers[X] == NN)
				emu->program_counter += 2;
			break;
		case 0x4:
			if (emu->registers[X] != NN)
				emu->program_counter += 2;
			break;
		case 0x5:
			if (emu->registers[X] == emu->registers[Y])
				emu->program_counter += 2;
			break;
		case 0x6:
			emu->registers[X] = NN;
			break;
		case 0x7:
			emu->registers[X] += NN;
			break;
		case 0x9:
			if (emu->registers[X] != emu->registers[Y])
				emu->program_counter += 2;
			break;
		case 0xA:
			emu->address_register = NNN;
			break;
		case 0xB:
			emu->program_counter = NNN + emu->registers[0];
			break;
		case 0xC:
			emu->registers[X] = rand() & NN;
			break;
		case 0xD:
			// TO DO display
		case 0xE:
			// TO DO keypress
		case 0xF:
		case 0x8:
			break;
	}
}
