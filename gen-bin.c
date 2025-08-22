#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
read_src(uint8_t *buf, FILE *src, unsigned int ch)
{
	for (int i = 0; i < 16; i++) {
		char *line = NULL;
		size_t len;
		if (getline(&line, &len, src) < 0) {
			fprintf(stderr,
				"Character %u: failed to read line %d\n",
				ch, i);
			return;
		}

		for (int j = 0; j < 8 && line[j] && line[j] != '\n'; j++)
			buf[i] |= line[j] == 'X' ? (1 << (7 - j)) : 0;

		free(line);
	}
}

static void
convert_char(FILE *font, FILE *src, unsigned int ch)
{
	uint8_t buf[16] = { 0 };

	if (src)
		read_src(buf, src, ch);

	fwrite(buf, sizeof(buf), 1, font);
}

int
main(int argc, const char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <BDF_FILE_PATH>\n", argv[0]);
		return -1;
	}

	FILE *font = fopen(argv[1], "wb");
	if (!font) {
		fprintf(stderr, "failed to open \"%s\"\n", argv[1]);
		return -1;
	}

	for (unsigned int ch = 0; ch < 128; ch++) {
		char *srcName;
		asprintf(&srcName, "src/%u.txt", ch);
		FILE *src = fopen(srcName, "r");
		free(srcName);

		convert_char(font, src, ch);

		if (src)
			fclose(src);
	}

	fclose(font);

	return 0;
}
