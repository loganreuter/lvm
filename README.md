# Logan's Virtual Machine (LVM)
A custom 32-bit virtual machine written in C. The machine is a register based Harvard architecture machine. The machine understands a custom set of Assembly code. (The source code for the virtual machine is in the lvm directory.) This project has multiple goals:
1. Learn about how machines work at a lower level
2. Learn about how virtual machines work
3. Enhance my skills in C
4. Learn about assembly and machine code
5. Build an assembler so I do not need to write out the machine code
6. Build a simple programming language to program the machine
7. See if I can build a simple OS on the machine

### TODO:
- [ ] Figure out why storing a value to R0 causes it to be distorted
- [ ] Decide on the rest of the OpCodes  
- [ ] Decide on the rest of the registers    
- [ ] Implement basic arthimetic functionality  
- [ ] Implement conditional functionality  
- [ ] Implement I/O functionality
- [ ] Implement branching functionality  

## Registers
There are 16 registers with address ranging from x0-xf  
|Addr|Register|Purpose|
|---|---|---|
|x0|R0|General Purpose|
|x1|R1|General Purpose|
|x2|R2|General Purpose|
|x3|R3|General Purpose|
|x4|R4|General Purpose|
|x5|R5|General Purpose|
|x6|R6|General Purpose|
|x7|R7|General Purpose|
|x8|ESP|Stack Register|
|x9|EDP|---|
|xa|RRET|Return Register|
|xb|RPC|Program Counter Register|
|xc|RCND|Condition Register|
|xd|---|---|
|xe|---|---|
|xf|RCNT|---|

## Memory Model

## OpCode
Currently OpCodes are stored in the first nibble (4 bits) of the code. However, if need be that could be increased to 5 or 6 bits.

|Num|Code|Binary|Mode|Description|Example|
|---|---|---|---|---|---|
|1|ADD|0000|0|Adds two registers together and stores the value into a specified register|ADD DR1 R0 R1
||ADDI|0000|1|Adds a register with an immediate number (IMM) and stores the value to a specified register| ADDI DR1 R0 $FF|
|2|SUB|0001|0|||
||SUBI|0001|1|||
|3|MUL|0010|0|||
||MULI|0010|1|||
|4|DIV|0011|0|||
||DIVI|0011|1|||
|5|MOD|0100|0|||
||MODI|0100|1|||
|6|LD|0101|||
|7|LDI|0110||
|8|ST|0111||
|9|STI|1000||