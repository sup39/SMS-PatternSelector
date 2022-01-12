#include <sms.h>
#include <stdio.h>
// asm ("#include \"macros.inc\"");

typedef struct {} TGraphWeb;
extern struct {} __vt__11TBossWanwan, __vt__11TFireWanwan;
extern uint8_t pattern[4];
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

J2DTextBox textbox;
const JUTRect textboxRect = {10, 320-40, 800, 320+20};
uint8_t press[4];
uint8_t cursor;
char *fmt = "Pattern %c%X%c%X%c%X   ";

void onSetup() {
  J2DTextBox_Create(&textbox, 0, &textboxRect, GameFont, fmt, 2, 0);
}

int onUpdate(void) {
  // asm ("mr r29, r3"); // 800F9B74
  #define REGISTER_BUTTON(button, pressed, ACTION) \
    if (ControllerOne.buttons == (button)) { \
      if (!pressed) { \
        pressed = 1; \
        ACTION; \
      } \
    } else { \
      pressed = 0; \
    }
  REGISTER_BUTTON(PRESS_L|PRESS_DL, press[0], cursor=(cursor+3)%4)
  REGISTER_BUTTON(PRESS_L|PRESS_DR, press[1], cursor=(cursor+1)%4)
  REGISTER_BUTTON(PRESS_L|PRESS_DU, press[2],
   if(cursor==0)cursor=1; pattern[cursor-1]=pattern[cursor-1]>=4?0:pattern[cursor-1]+1)
  REGISTER_BUTTON(PRESS_L|PRESS_DD, press[3],
   if(cursor==0)cursor=1; pattern[cursor-1]=pattern[cursor-1]==0?4:pattern[cursor-1]-1)
}
void onDraw2D(J2DGrafContext* graphics) {
  snprintf(J2DTextBox_GetStringPtr(&textbox), 24, fmt,
    cursor==1 ? '#' : ' ',
    pattern[0],
    cursor==2 ? '#' : ' ',
    pattern[1],
    cursor==3 ? '#' : ' ',
    pattern[2]
  );
  J2DScreen_Draw((J2DScreen*)&textbox, 0, 0, graphics, 0x81);
}