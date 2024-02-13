#include "emulator.h"
#include <stdlib.h>

void emulator_execute(Emulator *emu, uint16_t instr) {
	/*types of instructions
		op N N N
		op X N N
		op X Y N
	*/

	uint16_t NNN;
	uint8_t op, X, Y, N, NN;
	op = (uint8_t) (instr >> 12 & 0xF);
	X = (uint8_t) (instr >> 8 & 0xF);
	Y = (uint8_t) (instr >> 4 & 0xF);
	N = (uint8_t) (instr & 0xF);

	NN = (uint8_t) (instr & 0x00FF);
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
			emu->registers[X] = (uint8_t) (rand() & NN);
			break;
		case 0xD:
			// TO DO display
		case 0xE:
			// TO DO keypress
		case 0xF:
			switch (NN) {
				case 0x07:
					emu->registers[X] = emu->delay_timer;
					break;
				case 0x0A:
					// TO DO wait for keypress
					break;
				case 0x15:
					emu->delay_timer = emu->registers[X];
					break;
				case 0x18:
					emu->sound_timer = emu->registers[X];
					break;
				case 0x1E:
					emu->address_register += emu->registers[X];
					break;
				case 0x29:
					emu->address_register = 5 * emu->registers[X];
					break;
				case 0x33:
					emu->memory[emu->address_register] = (emu->registers[X] / 100);
					emu->memory[emu->address_register] = (emu->registers[X] / 10) % 10;
					emu->memory[emu->address_register] = (emu->registers[X]) % 10;
					break;
				case 0x55:
					for (uint8_t i = 0; i <= X; i++) {
						emu->memory[emu->address_register + i] = emu->registers[i];
					}
					break;
				case 0x65:
					for (uint8_t i = 0; i <= X; i++) {
						emu->registers[i] = emu->memory[emu->address_register + i];
					}
					break;
			}
			break;
		case 0x8:
			switch (N) {
				case 0x0:
					emu->registers[X] = emu->registers[Y];
					break;
				case 0x1:
					emu->registers[X] = emu->registers[X] | emu->registers[Y];
					break;
				case 0x2:
					emu->registers[X] = emu->registers[X] & emu->registers[Y];
					break;
				case 0x3:
					emu->registers[X] = emu->registers[X] ^ emu->registers[Y];
					break;
				case 0x4:
					emu->registers[X] = emu->registers[X] + emu->registers[Y];
					emu->registers[0xF] = (uint8_t) (emu->registers[X] < emu->registers[Y]);
					break;
				case 0x5:
					emu->registers[0xF] = (uint8_t) (emu->registers[X] > emu->registers[Y]);
					emu->registers[X] = emu->registers[X] - emu->registers[Y];
					break;
				case 0x6:
					emu->registers[0xF] = emu->registers[X] | 0x01;
					emu->registers[X] = emu->registers[X] >> 1;
					break;
				case 0x7:
					emu->registers[0xF] = (uint8_t) (emu->registers[Y] > emu->registers[X]);
					emu->registers[X] = emu->registers[Y] - emu->registers[X];
					break;
				case 0xE:
					emu->registers[0xF] = emu->registers[X] >> 7;
					emu->registers[X] = emu->registers[X] << 1;
					break;
			}
			break;
	}
}
