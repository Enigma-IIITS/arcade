#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define MEMORY_SIZE (4 * 1024)

typedef struct {
	uint8_t memory[MEMORY_SIZE];
	uint8_t registers[16];

	/// A 16-bit register called I.
	uint16_t address_register;

	uint8_t delay_timer;
	uint8_t sound_timer;

	uint16_t program_counter;
	uint8_t stack_pointer;

	uint16_t stack[16];

	uint16_t keyboard;
	uint8_t display[8 * 32];

	int8_t waiting;
} Emulator;

/// Initialize the emulator state.
void emulator_init(Emulator *emu);

/// Load the given ROM source into the emulator memory.
void emulator_load_rom(Emulator *restrict emu, const uint8_t *restrict rom, size_t len);

/// Perform one tick on both the timers.
void emulator_tick_timers(Emulator *emu);

/// Fetch the next instruction.
uint16_t emulator_fetch(Emulator *emu);

/// Execute the given instruction.
void emulator_execute(Emulator *emu, uint16_t instr);

/// Perform one fetch-decode-execute cycle.
void emulator_cycle(Emulator *emu);

#endif // EMULATOR_H_
