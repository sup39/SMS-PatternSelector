#include <sms.h>
#include "draw.h"

typedef struct {} TGraphWeb;
extern struct {} __vt__11TBossWanwan, __vt__11TFireWanwan;
extern uint8_t pattern[3];
extern uint8_t cursor;
extern uint16_t lastButton;

int getRandomNextIndex__9TGraphWebCFiiUl(TGraphWeb *graphWeb, int curIndex, int prevIndex, uint32_t r6);
typedef struct {
  void *__vt__;
  char *name;
} This;

/*
  Note that I have to set r6 to this(r31) before calling this function.
  In NTSC-J 1.0, I put `0424F324 7fe6fb78` first and then call this function at 8024F32C
*/
int getRandomNextIndex(TGraphWeb *graphWeb, int curIndex, int prevIndex, This *this) {
  uint32_t pid;
  if (this->__vt__ == &__vt__11TFireWanwan) {
    switch(this->name[19]) {
      case '2':
        pid = pattern[0];
        switch (curIndex) {
          case 33: // prevIndex==34
            switch (pid) {
              case 1: return 69; // up
              case 2:
              case 3: return 32; // right
              default: goto fallback;
            }
          case 29: // prevIndex==30
            switch (pid) {
              case 2: return 98; // up
              case 3: return 28; // right
              default: goto fallback;
            }
          default: goto fallback;
        }
      case '0':
        pid = pattern[1];
        switch (curIndex) {
          case 38: // prevIndex==39
            switch (pid) {
              case 1: return 80; // up
              case 2:
              case 3:
              case 4: return 37; // right
              default: goto fallback;
            }
          case 33: // prevIndex==34
            switch (pid) {
              case 2: return 69; // up
              case 3:
              case 4: return 32; // right
              default: goto fallback;
            }
          case 29: // prevIndex==30
            switch (pid) {
              case 3: return 98; // up
              case 4: return 28; // right
              default: goto fallback;
            }
          default: goto fallback;
        }
      case '1':
        pid = pattern[2];
        switch (curIndex) {
          case 8:
            switch (pid) {
              case 1: return 81; // down
              case 2:
              case 3: return 7; // left
              default: goto fallback;
            }
          case 2:
            switch (pid) {
              case 2: return 54; // down
              case 3: return 1; // left
              default: goto fallback;
            }
          default: goto fallback;
        }
      default: goto fallback;
    }
  } else if (this->__vt__ == &__vt__11TBossWanwan) {
    if (prevIndex != -1) goto fallback;
    pid = pattern[0];
    if (pid == 0) goto fallback;
    switch (pid%3) {
      case 1: return 30; // left
      case 2: return 110; // middle
      case 0: return 32; // right
    }
  }

fallback:
  return getRandomNextIndex__9TGraphWebCFiiUl(graphWeb, curIndex, prevIndex, -1);
}

void onDraw2D(J2DGrafContext* graphics) {
  J2DGrafContext_Setup2D(graphics);

  #define REGISTER_BUTTON(button, ACTION) \
    if (ControllerOne.buttons == (button) && (lastButton & (button)) != (button)) { \
      ACTION; \
    }
  REGISTER_BUTTON(PRESS_L|PRESS_DL, cursor=(cursor+3)%4)
  REGISTER_BUTTON(PRESS_L|PRESS_DR, cursor=(cursor+1)%4)
  REGISTER_BUTTON(PRESS_L|PRESS_DU,
   if(cursor==3) cursor=0; pattern[cursor] = pattern[cursor]>=4 ? 0 : pattern[cursor]+1)
  REGISTER_BUTTON(PRESS_L|PRESS_DD,
   if(cursor==3) cursor=0; pattern[cursor] = pattern[cursor]==0 ? 4 : pattern[cursor]-1)

  // void drawText(int x, int y, int fontSize, uint32_t colorTop, uint32_t colorBot, const char *fmt, ...)
  drawText(16, 320, 20, 0xffffffff, 0xffffffff, "Pattern %c%X%c%X%c%X",
    cursor==0 ? '#' : ' ',
    pattern[0],
    cursor==1 ? '#' : ' ',
    pattern[1],
    cursor==2 ? '#' : ' ',
    pattern[2]
  );

  // next
  lastButton = ControllerOne.buttons;

  // restore
  J2DGrafContext_Setup2D(graphics);
}
