#define COLUMNS 80
#define LINES 25
#define BYTES_FOR_EACH_CHARACTER 2
#define SCREEN_SIZE COLUMNS * LINES * BYTES_FOR_EACH_CHARACTER

#define LIGHT_GREY 0x07

#define CURSOR_COMMAND_PORT 0x3D4
#define RECV_LOWER_BITS 14
#define RECV_HIGHER_BITS 15
#define CURSOR_DATA_PORT 0x3D5

extern void outb(short port, char data);

char *video_memory = (char *) 0xB8000;

void clear_screen() {
	for (int i = 0; i < SCREEN_SIZE; i += BYTES_FOR_EACH_CHARACTER) {
		video_memory[i] = ' ';

		video_memory[i + 1] = LIGHT_GREY;
	}
}

void move_cursor(int pos) {
	outb(CURSOR_COMMAND_PORT, RECV_LOWER_BITS);

	outb(CURSOR_DATA_PORT, ((pos >> 8) & 0xFF));

	outb(CURSOR_COMMAND_PORT, RECV_HIGHER_BITS);

	outb(CURSOR_DATA_PORT, pos & 0xFF);
}

void puts(const char *STRING) {
	int i = 0;

	int j = 0;

	while (STRING[i] != '\0') {
		video_memory[j] = STRING[i];

		video_memory[j + 1] = LIGHT_GREY;

		i++;

		j += 2;
	}

	move_cursor(i);
}

void start_kernel() {
	clear_screen();

	puts("Hello, world!");
}
