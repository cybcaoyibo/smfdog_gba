/* by CYB(cybcaoyibo@126.com) */

SECTIONS {
	. = 0x08000000;
	.text : { * (.text) }
	.data : { * (.data) }
	. = 0x03000000;
	.bss : { * (.bss) }
}
ENTRY(entry)
