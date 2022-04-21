#include <sms.h>
#include "draw.h"
#include "PatternSelector.h"

static uint8_t pattern[3];
static uint8_t cursor;
static uint16_t lastButton;
static char cursorUI[6] = {
  // [0]3, [1]2, [2]1, [3]0
  ' ', ' ', ' ', '#', ' ', ' '
};
static int8_t patterns[][4] = {
  /**** case '2' ****/
  // [0] 33: up, right
  69, 32, 32, -1,
  // [1] 29: up, right
  -1, 98, 28, -1,
  /**** case '0' ****/
  // [2] 38: up, right
  80, 37, 37, 37,
  // [3] 33: up, right
  -1, 69, 32, 32,
  // [4] 29: up, right
  -1, -1, 98, 28,
  /**** case '1' ****/
  // [5]  8: down, left
  81,  7,  7, -1,
  // [6]  2: down, left
  -1, 54,  1, -1,
  /**** PV4 ****/
  // [7]: left, middle, right
  30, 110, 32, -1,
};

/*
  Note that I have to set r6 to this(r31) before calling this function.
  In NTSC-J 1.0, I put `0424F324 7fe6fb78` first and then call this function at 8024F32C
*/
int getRandomNextIndex(TGraphWeb *graphWeb, int curIndex, int prevIndex, This *this) {
  int pid, idx;
  if (this->__vt__ == &__vt__11TFireWanwan) {
    switch(this->name[19]) {
      case '2':
        pid = pattern[0];
        switch (curIndex) {
          case 33: idx = 0; goto end;
          case 29: idx = 1; goto end;
          default: goto fallback;
        }
      case '0':
        pid = pattern[1];
        switch (curIndex) {
          case 38: idx = 2; goto end;
          case 33: idx = 3; goto end;
          case 29: idx = 4; goto end;
          default: goto fallback;
        }
      case '1':
        pid = pattern[2];
        switch (curIndex) {
          case 8: idx = 5; goto end;
          case 2: idx = 6; goto end;
          default: goto fallback;
        }
      default: goto fallback;
    }
  } else if (this->__vt__ == &__vt__11TBossWanwan) {
    if (prevIndex != -1) goto fallback;
    pid = pattern[0];
    idx = 7; goto end;
  }

fallback:
  return getRandomNextIndex__9TGraphWebCFiiUl(graphWeb, curIndex, prevIndex, -1);

end:
  if (pid == 0) goto fallback;
  int ans = patterns[idx][pid-1];
  if (ans == -1) goto fallback;
  return ans;
}

static void handleCursor(int button, int dx) {
  if (ControllerOne.buttons == (button) && (lastButton & (button)) != (button)) {
    cursor = (cursor+dx)%4;
  }
}
static void handlePattern(int button, int dx) {
  if (ControllerOne.buttons == (button) && (lastButton & (button)) != (button)) {
    if (cursor == 3) cursor = 0;
    pattern[cursor] = (pattern[cursor]+dx)%5;
  }
}
void onDraw2D(J2DGrafContext* graphics) {
  J2DGrafContext_Setup2D(graphics);

  handleCursor(PRESS_L|PRESS_DR, 1); // +1 %4
  handleCursor(PRESS_L|PRESS_DL, 3); // -1 %4
  handlePattern(PRESS_L|PRESS_DU, 1); // +1 %5
  handlePattern(PRESS_L|PRESS_DD, 4); // -1 %5

  // void drawText(int x, int y, int fontSize, uint32_t colorTop, uint32_t colorBot, const char *fmt, ...)
  char *csStr = cursorUI+(3-cursor);
  drawText(16, 320, 20, 0xffffffff, 0xffffffff, "Pattern %c%X%c%X%c%X",
    csStr[0],
    pattern[0],
    csStr[1],
    pattern[1],
    csStr[2],
    pattern[2]
  );

  // next
  lastButton = ControllerOne.buttons;

  // restore
  J2DGrafContext_Setup2D(graphics);
}
