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

	fprintf(font, "STARTCHAR ASCII-%u\n", ch);
	fprintf(font, "ENCODING %u\n", ch);
	fputs("SWIDTH 500 0\n", font);
	fputs("DWIDTH 8 0\n", font);
	fputs("BBX 8 16 0 0\n", font);
	fputs("BITMAP\n", font);

	for (int i = 0; i < 16; i++)
		fprintf(font, "%02X\n", buf[i]);

	fputs("ENDCHAR\n", font);
}

int
main(int argc, const char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <BDF_FILE_PATH>\n", argv[0]);
		return -1;
	}

	FILE *font = fopen(argv[1], "w");
	if (!font) {
		fprintf(stderr, "failed to open \"%s\"\n", argv[1]);
		return -1;
	}

	fputs("STARTFONT 2.1\n", font);
	fputs("FONT \"ZMONO816\"\n", font);
	fputs("SIZE 12 96 96\n", font);
	fputs("FONTBOUNDINGBOX 8 16 0 -2\n", font);
	fputs("STARTPROPERTIES 9\n", font);
	fputs("FONT_ASCENT 16\n", font);
	fputs("FONT_DESCENT 0\n", font);
	fputs("CHARSET_REGISTRY ISO10646\n", font);
	fputs("CHARSET_ENCODING 1\n", font);
	fputs("CHARSET_COLLECTIONS \"ASCII\"\n", font);
	fputs("PIXEL_SIZE 16\n", font);
	fputs("POINT_SIZE 120\n", font);
	fputs("RESOLUTION_X 96\n", font);
	fputs("RESOLUTION_Y 96\n", font);
	fputs("ENDPROPERTIES\n", font);
	fputs("CHARS 128\n", font);

	for (unsigned int ch = 0; ch < 128; ch++) {
		char *srcName;
		asprintf(&srcName, "src/%u.txt", ch);
		FILE *src = fopen(srcName, "r");
		free(srcName);

		convert_char(font, src, ch);

		if (src)
			fclose(src);
	}

	fputs("ENDFONT\n", font);
	fclose(font);

	return 0;
}
