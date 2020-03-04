OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH("arm")
ENTRY(start)
PHDRS
{
    load PT_LOAD;
}
SECTIONS {
    . = 0;
    . = ALIGN(4k);
    boot_start = .;
    . = ALIGN(16k);
    .boot . :
    {
        *(.boot.tables);
        *(.boot);
    } :load
    boot_text_start = .;
    .text : {
        *(.text);
        *(.text.unlikely);
    }
    .rodata . :
    {
        *(.rodata);
        *(.rodata.*);
    }
    .note.gnu.build-id . :
    {
        *(.note.gnu.build-id);
    }
    boot_text_end = .;
    .got . :
    {
        got_base = .;
        *(.got);
        *(.got.plt);
    }
    .data . :
    {
        *(.data);
        *(.data.*);
    }
    .bss . :
    {
        *(.bss);
    }
    .rel.dyn . :
    {
        *(.rel.dyn);
    }
    boot_end = .;
    /DISCARD/ :
    {
        *(.eh_frame);
        *(.eh_frame_hdr);
        *(.interp);
        *(.dynamic);
    }
}
