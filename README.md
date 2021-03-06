# Another RISC-V ISA simulator.

**This code is suitable to hard refactor at any time**

This is another RISC-V ISA simulator, this is coded in SystemC + TLM-2.

Brief description of the modules:

* CPU: Top entity that includes all other modules.
* Memory: Memory highly based on TLM-2 example with read file capability
* Registers: Implements the register file and PC
* RISC_V_execute: Executes every ISA instruction
* Instruction: Decodes instruction and acces to any instruction field

Current performance is about 166000 instructions / sec in a Core-i5@2.2Ghz

Helper classes:
* Performance: Performance indicators stores here (singleton class)
* Log: Log class to log them all (singleton class)


## TODO
This is a preliminar and incomplete version.

Task to do:
* implement all missing instructions (RISC_V_execute)
* still unresolved data memory access (need to implement hierarchical socket
  from CPU to RISC_V_execute)
* Implement CSRs
* Add full support to .elf and .hex filetypes to memory.h
(only partial .hex support)
* Connect some TLM peripherals
* Test, test, test & test. I'm sure there are a lot of bugs in the code

## compile
In order to compile the project you need SystemC-2.3.2 installed in your system.
Just change SYSTEMC path in Makefile.

```
$ make
```

Then, you need to modifiy your LD_LIBRARY_PATH environtment variable to add
path systemc library. In my case:
```
$ export LD_LIBRARY_PATH=/home/marius/Work/RiscV/code/systemc-2.3.2/lib-linux64
```

And then you can execute the simulator:
```
$ ./RISCV_TLM asm/BasicLoop.hex
```

## Test
In the asm directory there are some basic assembly examples.

I "compile" one file with the follwing command:
```
$ cd asm
$ riscv32-unknown-linux-gnu-as  EternalLoop.asm
$ objcopy -O ihex a.out EternalLoop.hex
$ cd ..
$ ./RISCV_SCTLM asm/EternalLoop.hex
```
This example needs that you hit Ctr+C to stop execution.

## Documentation
The code is documented using doxygen. In the doc folder there is a Doxygen.cfg
file ready to be used.

## Contribute
There are several ways to contribute to this project:
* Test
* Pull request are welcome (see TODO list)
* Good documentation

##  License

Copyright (C) 2018 Màrius Montón ([\@mariusmonton](https://twitter.com/mariusmonton/))

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
