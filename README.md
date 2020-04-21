# corewar
Play the Corewar game: develop a vm and a compiler

Project in collaboration with @skpn and @tbrizon

## Installation

To clone the repository, type `gcl https://github.com/hehlinge42/corewar.git` in a UNIX repository.

## Introduction

To get a full explanation of the Core War game and its history, follow https://en.wikipedia.org/wiki/Core_War
The subject provided by 42 (if you understand it) is available in the repository
A student made resource `Corewar_Cheat_Sheet` in the folder `resources` provides more information about the virtual machine behaviour and the pseudo-ASM language syntax

The Corewar project features 2 executables:
- `asm`: compiled by the sub Makefile located in the asm repository.This is a compiler of the pseudo-ASM language, which syntax is detailed in the subject and in the `Corewar_Cheat_Sheet.pdf` resource. The compiler parses a .s file and write the corresponding bytecode in a .cor file
- `vm`: compiled by the sub Makefile located in the vm repository. This is a virtual machine that host the Corewar game. It takes as arguments the .cor champions and plays the battle.

## Run

To compile both executables, run `make` at the root of the repository. The corresponding executables provided by 42 are located in the `resources` repository.

### Virtual Machine
To get the full usage of the virtual machine, run `./corewar` in the resources folder. The vm takes as arguments 1 to 4 `.cor` champions. Supported options are the following:
- `-v value`: Activates the verbose level with different levels of precision. Run `-v 31` for full details. Other levels are precised in the usage
- `-d cycle`: dump memory and exit at cycle
- `-dump cycle`: dump memory every x cycles

### ASM
The asm program takes as only argument a pseudo-asm `.s` file: `./asm champion.s` from the asm folder

### Resources
Champions are provided as examples both in the `checker/champ` folder and the `resources/champs` folder. The other folders of the `checker/` contain unit tests.
The `checker/scripts` contains to bash scripts that enable to conduct battery tests.
To know their usage, type `bash test_script_vm.sh` or `bash test_script_asm.sh`.
