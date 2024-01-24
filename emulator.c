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

void emulator_load_rom(Emulator *restrict emu, const uint8_t *restrict rom, size_t len) {

    FILE *fp ;
    fp = fopen("hexadecimalformatgiver","r");
    //opens the requested file
    if(fp ==NULL)
    {
        printf("file is not opened successfully");
        exit(0);
    }

    fseek(fp,0,SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);
    //searches for the end of the file and makes the fp point to the end of the file
    // stores the value at which the end is there in file_size
    //makes the file pointer point back to the first location it is pointing to 

    char *rom;
    rom = (char*) malloc(sizeof(char)*(file_size+1));
    //dynamically allocated the required space for the data to be stored in an array
    int i = 0 ;
    char character ;
    while(!feof(fp))
    {
      
        character = fgetc(fp);
        rom[i] = character;
        i++;
        
    }
    rom[i] = '\0';
   int j = 0 ;
	  while(j < i-1)
  {
    printf("%c",rom[j]);
    j++;
  }
    
     free(rom);
    fclose(fp);


	for (size_t i = 0; i < len; ++i) {
		emu->memory[0x200 + i] = rom[i];
	}
}
