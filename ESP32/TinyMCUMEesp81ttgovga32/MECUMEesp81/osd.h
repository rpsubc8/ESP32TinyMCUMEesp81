#ifndef OSDFILE_H
 #define OSDFILE_H

 #include "gbConfig.h"
 
 void changeSna2Flash(unsigned char id);
 void do_tinyOSD(void);
 //void SDLAssignSDLSurfaceOSD(SDL_Surface *surface,SDL_Event * ptrEvent);
 void SDLActivarOSDMainMenu();
 //void SDLOSDClear(void);
 //SDL_Surface * SDLOSDGetSurface();
 void SDLEsperaTeclado(void);
 void SDLClear(void);
 void SDLSetBorder(void);
 
 #ifdef use_lib_cvbs_bitluni
  void SDLClearCVBS(void);
  void SDLSetBorderCVBS(void);
 #endif

#endif
