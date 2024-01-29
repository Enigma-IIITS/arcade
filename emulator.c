#include "emulator.h"
#include <assert.h>

static void emulator_load_font(Emulator *emu) {
	static const uint8_t FONTSET[80] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80, // F
	};

	size_t len = sizeof(FONTSET) / sizeof(FONTSET[0]);

	for (size_t i = 0; i < len; ++i) {
		emu->memory[i] = FONTSET[i];
	}
}

void emulator_init(Emulator *emu) {
	assert(emu != 0);

	// Zero initialize the emulator memory and registers.
	*emu = (Emulator){0};

	emu->program_counter = 0x200;
	emu->waiting = -1;

	emulator_load_font(emu);
}

void emulator_load_rom(Emulator *restrict emu, const uint8_t *restrict rom, size_t len) {
	for (size_t i = 0; i < len; ++i) {
		emu->memory[0x200 + i] = rom[i];
	}
}

uint16_t emulator_fetch(Emulator *emu) {
	uint8_t instr_h, instr_l;
	instr_h = emu->memory[emu->program_counter];
	instr_l = emu->memory[emu->program_counter + 1];

	uint16_t instr = (instr_h << 8) | instr_l;
	emu->program_counter = emu->program_counter + 2;
	return instr;
}
