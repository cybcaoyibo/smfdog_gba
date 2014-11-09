SECTIONS {
	. = 0x08000000;
	.text : { * (.text) }
	.rdata : { * (.rdata) }
	.bss : { * (.bss) }
}
ENTRY(entry)
