#include "emulator.h"


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


void emulator_load_rom(Emulator *restrict emu, const char *restrict rom_filename) {
    FILE *fp = fopen(rom_filename, "rb");  // Open the file in binary mode
    if (fp == NULL) {
        printf("File could not be opened.\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    uint8_t *rom = (uint8_t *)malloc(sizeof(uint8_t) * file_size);
    if (rom == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    // Use fread to read the entire file into the rom array
    if (fread(rom, 1, file_size, fp) != file_size) {
        printf("Error reading the file.\n");
        fclose(fp);
        free(rom);
        exit(1);
    }

    fclose(fp);

    // Copy the ROM data into emulator memory starting from address 0x200
    for (size_t i = 0; i < file_size; ++i) {
        emu->memory[0x200 + i] = rom[i];
    }

    free(rom);
}
