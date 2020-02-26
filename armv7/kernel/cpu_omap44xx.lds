OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH("arm")
PHDRS {
    bsp_image PT_LOAD;
    app_image 0x60000000;
    dynamic PT_DYNAMIC;
}
ENTRY(bsp_start)
SECTIONS {
    . = 0;
    . = ALIGN(4k);
    kernel_first_byte = .;
    kernel_init_start = .;
    .text.bsp : { *(.text.bsp); } :bsp_image
    .data.bsp : { *(.data.bsp); }
    . = ALIGN(4k);
    .text.vectors : { *(.text.vectors); }
    . = ALIGN(4k);
    .text : { *(.text); }
    .text.unlikely : { *(.text.unlikely); }
    .rodata . : { *(.rodata); }
    .dynsym . : { *(.dynsym); }
    .dynstr . : { *(.dynstr); }
    .gnu.hash . : { *(.gnu.hash); }
    .dynamic . : { *(.dynamic); } :bsp_image :dynamic
    build_id_nhdr = .;
    .note.gnu.build-id . : { *(.note.gnu.build-id); } :bsp_image
    kernel_text_final_byte = .;
    . = ALIGN(4k);
    .got . : {
        got_base = .;
        *(.got);
    } :bsp_image :app_image
    .bss . : { *(.bss); }
    kernel_final_byte = .;
    /DISCARD/ : {
        *(.eh_frame);
        *(.eh_frame_hdr);
        *(.interp);
    }
}
