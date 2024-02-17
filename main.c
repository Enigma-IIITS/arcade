#include "emulator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

uint8_t *rom_loader(const char *rom_filename, size_t *rom_len) {
	// Open the file in binary mode
	FILE *fp = fopen(rom_filename, "rb");
	if (fp == NULL) {
		printf("File could not be opened.\n");
		exit(1);
	}

	// Checks the size of the file
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	rewind(fp);

	*rom_len = (size_t) file_size;

	// Allocates the nessasary amount of space
	uint8_t *rom = (uint8_t *) malloc(sizeof(uint8_t) * (size_t) file_size);
	if (rom == NULL) {
		printf("Memory allocation failed.\n");
		exit(1);
	}

	// Read the entire file into the rom array
	if (fread(rom, 1, (size_t) file_size, fp) != (size_t) file_size) {
		printf("Error reading the file.\n");
		fclose(fp);
		free(rom);
		exit(1);
	}

	fclose(fp);
	return rom;
}

int main(void) {
	srand((unsigned int) time(0));

	size_t rom_len = 0;

	const char *rom_file = "./assets/roms/PONG2";
	uint8_t *rom_data = rom_loader(rom_file, &rom_len);

	const int screenWidth = 640;
    const int screenHeight = 320;
    InitWindow(screenWidth, screenHeight, "CHIP-8 Emulator");

	// Initialize an emulator instance
	Emulator emu = {0};
	emulator_init(&emu);

	// Load the ROM into the emulator memory and free the temp buffer
	emulator_load_rom(&emu, rom_data, rom_len);
	free(rom_data);

	while (!WindowShouldClose()) {
        
        chip8_emulate_cycle(&emu);

        
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        

        EndDrawing();
    }

    
    CloseWindow();

	// Work with the emulator here...

	return 0;
}
