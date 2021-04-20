#include "font_types.h"
#include "mzapo_regs.h"
#include "mzapo_parlcd.h"

unsigned short *fb;         //  Array of pixels

font_descriptor_t *fdes;    //  Pointer to a font descriptor from font_...c

int scale;                  //  Scale of a character 

void renderText(int state);

void drawText(int x, int y, char *text);