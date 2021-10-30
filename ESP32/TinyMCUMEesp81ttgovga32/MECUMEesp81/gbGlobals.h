#ifndef GB_GLOBALS_H
 #define GB_GLOBALS_H

 //#include <SDL/SDL.h>
 //extern SDL_Surface *screen;
 


 extern volatile unsigned char keymap[256];
 extern volatile unsigned char oldKeymap[256];


 extern unsigned char gb_show_osd_main_menu;
 extern unsigned char gb_load_new_pfile;
 extern unsigned char gb_id_cur_pfile;



 extern unsigned char **gb_buffer_vga; //Puntero video 8 bits
 extern unsigned int **gb_buffer_vga32; //Puntero video 32 bits

 extern unsigned char gb_delay_tick_cpu_milis;
 extern unsigned char gb_auto_delay_cpu;

 //fast bitluni
 extern unsigned char gb_sync_bits;



 extern unsigned char gb_keyboard_cur_poll_ms;
 extern unsigned char gb_vga_cur_poll_ms;
 extern unsigned char gb_blit_cur_poll_ms;


 extern unsigned char gb_color_vga[8];










 extern short int fb_width;
 extern short int fb_height;
 extern unsigned char keyboard[9];

 extern int zx80;
 extern unsigned short int pc;
 extern int ramsize;
 extern int autoload;

 extern const unsigned char zx81rom[];
 extern const unsigned char zx80rom[];
//begin common_h

typedef unsigned char byte;
//typedef unsigned short word;

#define WIDTH  320
#define HEIGHT 192
#define BORDER 32

#define CYCLES_PER_FRAME 65000//3500000/50


//full internal image with overscan (but not hsync/vsync areas)
#define ZX_VID_MARGIN		55
#define ZX_VID_HMARGIN		(8*8)
#define ZX_VID_FULLWIDTH	(2*ZX_VID_HMARGIN+32*8)	//sic
#define ZX_VID_FULLHEIGHT	(2*ZX_VID_MARGIN+192)


//AY board types
//#define AY_TYPE_NONE		0
//#define AY_TYPE_QUICKSILVA	1
//#define AY_TYPE_ZONX		2


extern unsigned char * mem;
extern unsigned char *memptr[64];
extern int memattr[64];
extern unsigned long tstates,tsmax;
extern int vsync_visuals;
//JJ extern int ramsize;
extern int interrupted;
extern int nmigen,hsyncgen,vsync;
//JJ extern int autoload;
//JJ extern int zx80;

//extern void sighandler(int a);
//extern unsigned int in(int h,int l);
//extern unsigned int out(int h,int l,int a);
//extern void do_interrupt();
//extern void save_p(int a);
//JJ extern void load_p(int a);
//void load_p(int a);
//extern void do_interrupt();
//extern void reset81();
//extern void frame_pause(void);
//extern void bitbufBlit(unsigned char * buf);
//end common_h



extern unsigned char scrnbmp_new[ZX_VID_FULLWIDTH*ZX_VID_FULLHEIGHT/8]; //written
extern unsigned char XBuf[WIDTH*8];

extern unsigned int gb_time_blit_cur,gb_time_blit_before; 

extern unsigned char gb_invert_color;

#endif

 
