#ffmpeg -i smfdog.gif -f rawvideo smgdog.bin
g++ -o imgconv imgconv.cpp -std=c++0x
./imgconv
arm-none-eabi-gcc -c -o smfdog.o smfdog.c
arm-none-eabi-as -o entry.o entry.S
arm-none-eabi-gcc -c -o entry_c.o -O3 -marm -mcpu=arm7tdmi -msoft-float entry_c.c
arm-none-eabi-ld --gc-sections -s -o out.elf entry.o entry_c.o smfdog.o /usr/local/arm-none-eabi/lib/libm.a /usr/local/arm-none-eabi/lib/libc.a /usr/local/lib/gcc/arm-none-eabi/4.9.1/libgcc.a -T ld.ld
arm-none-eabi-objcopy -O binary out.elf out.gba
