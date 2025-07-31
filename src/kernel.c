#define COLUMNS 80
#define LINES 25
#define BYTES_FOR_EACH_CHARACTER 2
#define SCREEN_SIZE COLUMNS * LINES * BYTES_FOR_EACH_CHARACTER

#define LIGHT_GREY 0x07

char *video_memory = (char *) 0xB8000;

void clear_screen() {
	for (int i = 0; i < SCREEN_SIZE; i += BYTES_FOR_EACH_CHARACTER) {
		video_memory[i] = ' ';

		video_memory[i + 1] = LIGHT_GREY;
	}
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
}

void start_kernel() {
	clear_screen();

	puts("Hello, world!");
}