make:
	mkdir -p ./bin
	nasm -f elf32 -o ./bin/boot ./src/boot.asm
	gcc -fno-builtin -m32 -o ./bin/kernel -c ./src/kernel.c
	ld -T ./src/link.ld -m elf_i386 -o ./bin/safira ./bin/boot ./bin/kernel
	qemu-system-i386 -kernel ./bin/safira