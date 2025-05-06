#ifndef RENDER_H
#define RENDER_H

#include "display.h"

#define SCREEN_PRESET_CHANGE 0
#define SCREEN_PRESET_EDIT 1
#define SCREEN_PEDAL_PARAMS 2

// Funções de renderização para diferentes telas
void renderPresetChange(Display& display, int page, int beforeScreen, int beforePage);

int renderPresetEdit(Display& display, int page, int beforeScreen, int beforePage);

int renderPedalParams(Display& display, int page, int beforeScreen, int beforePage);

#endif // RENDER_H