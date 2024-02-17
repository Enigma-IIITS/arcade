# raylib
For the raylib you need to install ray lib on your PC
Best method is (which i have found) go the raylib github repo ----> download version 4.0 installer.exe from the releases ------> it automatically installs notpad++ for raylib which is best for compiling raylib files as to do so in vs code requiers a lot of configuration files ------> run the code on notepad++

# arcade
A CHIP-8 virtual machine in C.

## Instructions
```shell
$ gcc -ggdb -Wpedantic -Werror -Wall -Wextra -Wconversion -std=c17 emulator.c emulator_execute.c main.c
$ ./a.out
```

## To-Do
- [x] Add memory and register management
- [ ] Implement ROM file loading
- [x] Add CHIP-8 hexadecimal font
- [ ] Implement instruction decoding and execution
- [ ] Add an interface for audio, display and keyboard IO
- [ ] Setup raylib window, rendering and keyboard input
- [ ] Implement audio, display and keyboard related instructions
- [ ] Fix timer delays

## Contribution Guidelines
- Try not to commit any binary files. If you have to, use git-lfs.
- Use `PascalCase` for type names, type aliases and `snake_case` for function and variable names.
- Format all the source files using `clang-format` before making a commit.
