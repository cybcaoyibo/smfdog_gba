/* by CYB(cybcaoyibo@126.com) */

SECTIONS {
	. = 0x08000000;
	.text : { * (.text) }
	.data : { * (.data) }
	.bss : { * (.bss) }
}
ENTRY(entry)
