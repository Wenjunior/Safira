#![no_std]
#![no_main]

use core::panic::PanicInfo;

#[unsafe(no_mangle)]
pub extern "C" fn _start() -> ! {
	static HELLO_WORLD: &[u8] = b"Hello, world!";

	let vga_buffer = 0xB8000 as *mut u8;

	for (i, &ch) in HELLO_WORLD.iter().enumerate() {
		unsafe {
			*vga_buffer.offset(i as isize * 2) = ch;

			*vga_buffer.offset(i as isize * 2 + 1) = 0x7;
		}
	}

	loop {}
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
	loop {}
}