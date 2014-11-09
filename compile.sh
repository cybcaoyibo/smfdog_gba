arm-none-eabi-as -o entry.o entry.S
arm-none-eabi-gcc -c -o entry_c.o -O3 -marm -mcpu=arm7tdmi entry_c.c
arm-none-eabi-ld -s --gc-sections -o out.elf entry.o entry_c.o -T ld.ld
arm-none-eabi-objcopy -O binary out.elf out.gba
