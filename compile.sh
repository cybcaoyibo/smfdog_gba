#by CYB(cybcaoyibo@126.com)

#ffmpeg -i smfdog.gif -f rawvideo smfdog.bin
g++ -o imgconv imgconv.cpp -std=c++0x
./imgconv
arm-none-eabi-gcc -c -o smfdog.o smfdog.c
arm-none-eabi-as -o entry.o entry.S
arm-none-eabi-gcc -c -o entry_c.o -g -mthumb -mcpu=arm7tdmi -msoft-float entry_c.c
arm-none-eabi-ld --gc-sections -o out.elf entry.o entry_c.o smfdog.o /usr/local/arm-none-eabi/lib/thumb/libm.a /usr/local/arm-none-eabi/lib/libc.a /usr/local/lib/gcc/arm-none-eabi/4.9.1/thumb/libgcc.a -T ld.ld
arm-none-eabi-objcopy -O binary out.elf out.gba
