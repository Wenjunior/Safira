#![no_std]
#![no_main]

use core::arch::asm;
use core::panic::PanicInfo;

static mut VGA_BUFFER: *mut u8 = 0xB8000 as *mut u8;

fn outb(port: u16, data: u8) {
	unsafe {
		asm!(
			"out dx, al",
			in("dx") port,
			in("al") data
		);
	}
}

fn move_cursor(pos: usize) {
	outb(0x3D4, 0xE);

	outb(0x3D5, (pos >> 8) as u8);

	outb(0x3D4, 0xF);

	outb(0x3D5, (pos & 0xFF) as u8);
}

fn print(string: &[u8]) {
	for (i, &ch) in string.iter().enumerate() {
		unsafe {
			*VGA_BUFFER.offset(i as isize * 2) = ch;

			*VGA_BUFFER.offset(i as isize * 2 + 1) = 0x7;
		}

		move_cursor(i);
	}
}

#[unsafe(no_mangle)]
pub extern "C" fn _start() -> ! {
	print(b"Hello, world!");

	loop {}
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
	loop {}
}