#include "sms.h"
#include <stdarg.h>

/* color.alpha = printer->color.alpha * alphaMask/0xff */
void J2DPrint_print_alpha_va(void *printer, uint8_t alphaMask, const char *fmt, va_list args);

JUTResFont font;
void setup(void *this) {
  // old instruction @ 8010e418
  setup2__12TMarDirectorFv(this);

  // setup font
  __ct__10JUTResFontFPC7ResFONTP10JKRArchive(&font, GameFont, NULL);
}

void drawText(int x, int y, int fontSize, uint32_t colorTop, uint32_t colorBot, const char *fmt, ...) {
  Mtx mtx;
  J2DPrint printer;

  va_list args;
  va_start(args, fmt);

  // new J2DPrinter
  __ct__8J2DPrintFP7JUTFontiiQ28JUtility6TColorQ28JUtility6TColor(&printer, font, 0, fontSize, &colorTop, &colorBot);
  printer.fontWidth = printer.fontHeight = fontSize;

  // set mtx
  PSMTXIdentity(mtx);
  mtx[0][3] = x; // translateX
  mtx[1][3] = y; // translateY
  GXLoadPosMtxImm(mtx, 0);

  // print text
  J2DPrint_print_alpha_va(&printer, 0xff, fmt, args);

  va_end(args);
  __dt__8J2DPrintFv(&printer);
}
