#include <sms.h>

/* built-in functions */
void PSMTXTrans(double dx, double dy, double dz, Mtx mtx);

#define new_J2DPrint __ct__8J2DPrintFP7JUTFontiiQ28JUtility6TColorQ28JUtility6TColor
void new_J2DPrint(J2DPrint *this, JUTFont *font, int x4c, int lineHeight, TColor *colorTop, TColor *colorBot);

#define delete_J2DPrint __dt__8J2DPrintFv
void delete_J2DPrint(J2DPrint *this, int r4);

// color.alpha = printer->color.alpha * alphaMask/0xff
void J2DPrint_print_alpha_va(void *printer, uint8_t alphaMask, const char *fmt, va_list args);
/**********************/

void drawText(int x, int y, int fontSize, uint32_t colorTop, uint32_t colorBot, const char *fmt, ...) {
  Mtx mtx;
  J2DPrint printer;

  va_list args;
  va_start(args, fmt);

  // new J2DPrinter
  new_J2DPrint(&printer, gpSystemFont, 0, fontSize, (TColor*)&colorTop, (TColor*)&colorBot);
  printer.fontWidth = printer.fontHeight = fontSize;

  // mtx = translate(x, y, 0)
  PSMTXTrans(x, y, 0, mtx);
  GXLoadPosMtxImm(mtx, 0);

  // print text
  J2DPrint_print_alpha_va(&printer, 0xff, fmt, args);

  // no need to delete if not allocating memory from heap
  // delete_J2DPrint(&printer, -1);
  va_end(args);
}

/*
  li 9,0x60
  addi 8,1,188
  sth 9,160(1)

  addi 1,1,296
  lmw 28, -16(1)
  lwz 0,4(1)
  mtlr 0
  blr
*/
