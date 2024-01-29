#include "emulator.h"

uint_8* rom_loader()
{
	FILE *fp = fopen(rom_filename, "rb");  // Open the file in binary mode
    if (fp == NULL) {
        printf("File could not be opened.\n");
        exit(1);
    }
//checks the size of the file
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

//allocates the nessasary amount of space 
    uint8_t *rom = (uint8_t *)malloc(sizeof(uint8_t) * file_size);
    if (rom == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

 // read the entire file into the rom array
    if (fread(rom, 1, file_size, fp) != file_size) {
        printf("Error reading the file.\n");
        fclose(fp);
        free(rom);
        exit(1);
    }

    fclose(fp);
	return rom;
}


int main(void) {
	return 0;
}
