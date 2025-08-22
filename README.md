# ZMONO816

My monospace 8x16 bitmap font, distributed under OFL-1.1 license without RFN.

## Note

I'm not a professional designer and some parts of this font may look ugly. Use
at your own risk of eye damage.

## Building

The Makefile contains rules for converting the source to binary, bdf and ttf
formats.

- `zmono816.bin`: Binary format, glyphs are stored in ASCII order, each takes
		  2 bytes. Suitable for bare-metal usage. Requires a C compiler
		  to build.
- `zmono816.bdf`: Bitmap Distribution Format, recoginzed by X11 tools. Requires
		  a C compiler to build.
- `zmono816.ttf`: Common TrueType format, converted from `zmono816.bdf` and
		  thus requires fontforge to build.

## Preview

Refer to [this issue](https://github.com/ziyao233/zmono816/issues/1) for a
preview.

## Why

I was developing [loli-loader](https://github.com/ziyao233/loli-loader) and
found there were few bitmap fonts suitable for bare-metal applications with a
clear license.

Linux kernel ships some [8x16 bitmap font](https://github.com/torvalds/linux/blob/master/lib/fonts/font_8x16.c)
under GPL-2.0 license, which isn't appropriate for projects distributed under
MPL, BSD or MIT.
