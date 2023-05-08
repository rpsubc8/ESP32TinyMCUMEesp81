#ifndef EMUAPI_H
 #define EMUAPI_H

#include "gbConfig.h"
#include "zx81.h"

//JJ #define INVX        1
//#define INVY        1
//JJ #define HAS_SND     1
//#define CUSTOM_SND  1
//JJ #define HAS_I2CKBD  1
//JJ #define USE_WIRE    1

// Title:     <                                        >
//JJ #define TITLE "          ZX81/ZX80 Emulator            "
//JJ #define ROMSDIR "z81"

//#define emu_Init(ROM) {z81_Start(ROM); z81_Init(); }
//JJ #define emu_Step(x) {z81_Step();}
#define emu_Input(x) {}

#define VID_FRAME_SKIP       0x1
//JJ #define PALETTE_SIZE         2
//JJ #define SINGLELINE_RENDERING 1
//JJ #define TFT_VBUFFER_YCROP    0

//JJ #define ACTION_NONE          0
//JJ #define ACTION_MAXKBDVAL     225
//JJ #define ACTION_EXITKBD       128
//JJ #define ACTION_RUNTFT        129

//JJ #ifdef KEYMAP_PRESENT
//JJ #define TAREA_W_DEF          32
//JJ #define TAREA_H_DEF          32
//JJ #define TAREA_END            255
//JJ #define TAREA_NEW_ROW        254
//JJ #define TAREA_NEW_COL        253
//JJ #define TAREA_XY             252
//JJ #define TAREA_WH             251
//JJ 
//JJ #define KEYBOARD_X           10
//JJ #define KEYBOARD_Y           8
//JJ #define KEYBOARD_KEY_H       40
//JJ #define KEYBOARD_KEY_W       30
//JJ #define KEYBOARD_HIT_COLOR   RGBVAL16(0xff,0x00,0x00)
//JJ 
//JJ const unsigned short keyswzx80[] = {
//JJ   TAREA_XY,KEYBOARD_X,KEYBOARD_Y+16,
//JJ   TAREA_WH,KEYBOARD_KEY_W,KEYBOARD_KEY_H-6,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_END};
//JJ 
//JJ const unsigned short keyswzx81[] = {
//JJ   TAREA_XY,KEYBOARD_X,KEYBOARD_Y,
//JJ   TAREA_WH,KEYBOARD_KEY_W,KEYBOARD_KEY_H,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_NEW_ROW,30,30,30,30,30,30,30,30,30,30,
//JJ   TAREA_END};
//JJ      
//JJ const unsigned short keys[] = {
//JJ   30,31,32,33,34,35,36,37,38,39,
//JJ   20,26, 8,21,23,28,25,12,18,19,
//JJ    4, 9, 7,22, 4,11,13,14,15,40,
//JJ   25, 6,27,29,224,5,17,16,225,44 
//JJ   };  
//JJ 
//JJ #ifdef HAS_I2CKBD
//JJ const unsigned short i2ckeys[] = {
//JJ      0X0080,0X0008,0X0180,0X0108,0X0280,0X0208,0X0380,0X0308,0X0480,0X0408,
//JJ      0X0040,0X0004,0X0140,0X0104,0X0240,0X0204,0X0340,0X0304,0X0440,0X0404,
//JJ      0X0020,0X0002,0X0120,0X0102,0X0220,0X0202,0X0320,0X0302,0X0420,0X0402,
//JJ      0X0010,0X0001,0X0110,0X0101,0X0210,0X0201,0X0310,0X0301,0X0410,0X0401,
//JJ   };
//JJ #endif
//JJ    
//JJ #endif

//JJ #define MASK_JOY2_RIGHT 0x0001
//JJ #define MASK_JOY2_LEFT  0x0002
//JJ #define MASK_JOY2_UP    0x0004
//JJ #define MASK_JOY2_DOWN  0x0008
//JJ #define MASK_JOY2_BTN   0x0010
//JJ #define MASK_KEY_USER1  0x0020
//JJ #define MASK_KEY_USER2  0x0040
//JJ #define MASK_KEY_USER3  0x0080
//JJ #define MASK_JOY1_RIGHT 0x0100
//JJ #define MASK_JOY1_LEFT  0x0200
//JJ #define MASK_JOY1_UP    0x0400
//JJ #define MASK_JOY1_DOWN  0x0800
//JJ #define MASK_JOY1_BTN   0x1000
//JJ #define MASK_KEY_USER4  0x2000

//void emu_Init(char *ROM);

//JJ extern void emu_init(void);
//extern void emu_printf(char * text);
//extern void emu_printi(int val);
//JJ extern void * emu_Malloc(int size);
//JJ extern void emu_Free(void * pt);

//extern int emu_FileOpen(char * filename);
//extern int emu_FileRead(char * buf, int size);
//extern unsigned char emu_FileGetc(void);
//extern int emu_FileSeek(int seek);
//extern void emu_FileClose(void);
//extern int emu_FileSize(char * filename);
//extern int emu_LoadFile(char * filename, char * buf, int size);
//extern int emu_LoadFileSeek(char * filename, char * buf, int size, int seek);

//JJ extern void emu_InitJoysticks(void);
//JJ extern int emu_SwapJoysticks(int statusOnly);
//JJ extern unsigned short emu_DebounceLocalKeys(void);
//JJ extern int emu_ReadKeys(void);
//JJ extern int emu_GetPad(void);
//JJ extern int emu_ReadAnalogJoyX(int min, int max);
//JJ extern int emu_ReadAnalogJoyY(int min, int max);
//JJ extern int emu_ReadI2CKeyboard(void);
//JJ extern int emu_setKeymap(int index);

//JJ extern void emu_sndInit();
//JJ extern void emu_sndPlaySound(int chan, int volume, int freq);
//JJ extern void emu_sndPlayBuzz(int size, int val);

//JJ extern void emu_SetPaletteEntry(unsigned char r, unsigned char g, unsigned char b, int index);
//JJ extern void emu_DrawScreen(unsigned char * VBuf, int width, int height, int stride);
extern void emu_DrawLine(unsigned char * VBuf, int width, int height, int line);
extern void emu_DrawVsync(void);
//JJextern int emu_FrameSkip(void);
//JJ extern void * emu_LineBuffer(int line);

#ifdef use_lib_optimice_width_height
 //void IRAM_ATTR jj_direct_writeLine(unsigned char y, unsigned char *buf); 
 void jj_direct_writeLine(unsigned char y, unsigned char *buf); 
#else
 //void IRAM_ATTR jj_direct_writeLine(int width, int height, int y, unsigned char *buf);
 void jj_direct_writeLine(int width, int height, int y, unsigned char *buf);
#endif
//void jj_fast_putpixel(short int x,short int y,unsigned char c);
void emu_Init_Flash(unsigned char id);

#endif





