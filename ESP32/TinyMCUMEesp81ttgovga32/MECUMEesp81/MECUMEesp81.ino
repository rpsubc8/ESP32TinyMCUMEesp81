//Bypass MECUMEesp81 emulator to TTGO VGA32 by ackerman:
//Author: Ackerman
//License: WTFPL
// Load Pfile
// VGA MODE320x200
// Mode 64 colors RGB 6 bits
// VGA Tiny library bitluni 0.3.3 mod convert C
// gbConfig options configuration compile

#include "gbConfig.h"
#include "gbGlobals.h"
#include "PS2Kbd.h"
#include "PS2KeyCode.h"
#include <Arduino.h>

#include "MECUMEesp81.h"
#ifdef use_lib_bitluni_fast
#else
 #include "MartianVGA.h"
 #include "def/Font.h"
#endif 
#include "hardware.h"
#include "driver/timer.h"
#include "soc/timer_group_struct.h"
#include "osd.h"
#include "PS2KeyCode.h"
#include "emuapi.h"
#include "zx81.h"
#include "Z80.h"
#include "osd.h"


//#include "dataFlash/gbrom.h"
//#include "PS2Boot/PS2KeyCode.h"
#ifdef use_lib_bitluni_fast
 #include "vga_6bit.h"
 // VGA output pins
 //#define PIN_RED_LOW    21
 //#define PIN_RED_HIGH   22
 //#define PIN_GREEN_LOW  18
 //#define PIN_GREEN_HIGH 19
 //#define PIN_BLUE_LOW   4
 //#define PIN_BLUE_HIGH  5
 //#define PIN_HSYNC      23
 //#define PIN_VSYNC      15

 #ifdef use_lib_vga8colors
  //DAC 3 bits 8 colores
  // 3 bit pins  
  static const unsigned char pin_config[] = {  
   PIN_RED_HIGH,
   PIN_GREEN_HIGH,  
   PIN_BLUE_HIGH,
   255,
   255,
   255,
   PIN_HSYNC,
   PIN_VSYNC
  };
 #else 
  static const unsigned char pin_config[] = {
   PIN_RED_LOW,
   PIN_RED_HIGH,
   PIN_GREEN_LOW,
   PIN_GREEN_HIGH,
   PIN_BLUE_LOW,
   PIN_BLUE_HIGH,
   PIN_HSYNC,
   PIN_VSYNC
  };
 #endif 

#endif

#ifdef use_lib_bitluni_fast 
 //unsigned char **framebuffer = vga_get_framebuffer();
 //unsigned char **gb_buffer_vga= vga_get_framebuffer();
 unsigned char gb_sync_bits;
#else 
 #ifdef use_lib_bitluni_3bpp
  #ifdef use_lib_bitluni_low_memory
   VGA3BitI vga;
  #else
   VGA3Bit vga;
  #endif 
 #else 
  VGA6Bit vga;
 #endif 
#endif 

unsigned char gb_color_vga[8]=
{
 0, //0x10 00010000 00 00 00
 63, //0xFD 11111101 11 11 11
 49, //0x53 1010011 10 0x31 110001 11  0xFF 11111111 11
 8, //0x5D 1011101 10 0xCC 11001100 11  0x02 10 10
 23, //0xF3 11110011 11 0x3F 111111 11 0x4B 1001011 10
 42, //0xE0 11100000 11   111111
 46, //0xA6 10100110 10 0xFF 11111111 11 0x91 10010001 10
 0x3F
 //58  //0xD0 11010000 11 0xCE 11001110 11  0xFF 1111111 11 
};

unsigned char gb_invert_color=0;

unsigned char gb_load_new_pfile=0;
unsigned char gb_id_cur_pfile=0;

unsigned char XBuf[WIDTH*8];

unsigned char gb_cpunoexe=0;
int gb_cpunoexe_timer_ini;
unsigned int tiempo_ini_cpu,tiempo_fin_cpu;
unsigned int total_tiempo_ms_cpu;
unsigned int tiene_que_tardar;

unsigned int tiempo_ini_vga,tiempo_cur_vga;

unsigned int tiempo_ini_keyboard,tiempo_cur_keyboard;

unsigned char **gb_buffer_vga;
unsigned int **gb_buffer_vga32;

unsigned char gb_delay_tick_cpu_milis= use_lib_delay_tick_cpu_milis;
unsigned char gb_auto_delay_cpu= use_lib_delay_tick_cpu_auto;

unsigned char tiempo_vga= 0;
unsigned int gb_cpu_timer_before=0,gb_cpu_timer_cur=0;
unsigned int jj_ini_cpu,jj_end_cpu,jj_ini_vga,jj_end_vga;
unsigned int gb_max_cpu_ticks,gb_min_cpu_ticks,gb_cur_cpu_ticks;
unsigned int gb_max_vga_ticks,gb_min_vga_ticks,gb_cur_vga_ticks;
unsigned int gb_time_blit_cur,gb_time_blit_before;

unsigned char gb_keyboard_cur_poll_ms= use_lib_keyboard_poll_milis;
unsigned char gb_vga_cur_poll_ms= use_lib_vga_poll_milis;
unsigned char gb_blit_cur_poll_ms= gb_ms_blit_poll;

//Funciones
void Setup(void);
void Poll_Keyboard(void);
void PreparaColorVGA(void);
//void SDL_DumpVGA(void);


//****************************
//void SDL_DumpVGA(void)
//{
// #ifdef use_lib_bitluni_fast        
//  //framebuffer = vga_get_framebuffer();  
//  for (int y=0;y<10;y++)
//  {
//   for (int x=0;x<10;x++)
//   {
//    //framebuffer[y][x^2] = vga_get_sync_bits() | 255;
//    framebuffer[y][x^2] = gb_sync_bits | 0x3F;
//   }
//  }
//  //vga_swap_buffers();
// #else
//  for (int y=0;y<10;y++)
//  {
//   for (int x=0;x<10;x++)
//   {     
//    #ifdef use_lib_bitluni_3bpp
//     vga.dotFast(x,y,0x07);
//    #else
//     vga.dotFast(x,y,0x3F);
//    #endif 
//   }
//  }
// #endif 
//}


//**************************************************
void PreparaColorVGA()
{
 #ifdef use_lib_bitluni_fast
  #ifdef use_lib_vga8colors
   for (unsigned char i=0;i<8;i++)
   {  
    gb_color_vga[i] = (gb_color_vga[i] & 0x07) | gb_sync_bits;  
   }  
  #else
   for (unsigned char i=0;i<8;i++)
   {  
    gb_color_vga[i] = gb_color_vga[i] | gb_sync_bits;  
   }
  #endif 
 #else	
  for (unsigned char i=0;i<8;i++)
  {  
   gb_color_vga[i] = (gb_color_vga[i] & vga.RGBAXMask) | vga.SBits;  
  }
 #endif 
}



//Setup principal
void setup()
{ 
 #ifdef use_lib_log_serial
  Serial.begin(115200);         
  Serial.printf("HEAP BEGIN %d\n", ESP.getFreeHeap()); 
 #endif
 
 #ifdef use_lib_bitluni_fast  
  //void vga_init(const int *pin_map, const VgaMode &mode, bool double_buffered)
  //vga_init(pin_config,vga_mode_320x240,false);
  //vga_init(pin_config,vga_mode_320x200,false); //funciona
  //vga_init(pin_config,vga_mode_240x240,false); //funciona  
  vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C     
  //vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C

  //Serial.printf("pin_config size:%d\n",sizeof(pin_config));
  gb_sync_bits= vga_get_sync_bits();
  gb_buffer_vga = vga_get_framebuffer();
  gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
  Serial.printf("Fast Tiny Bitluni\n");
  Serial.printf("vsync_inv_bit:0x%02X hsync_inv_bit:0x%02X\n",vga_get_vsync_inv_bit(),vga_get_hsync_inv_bit());
  Serial.printf("Sync bits:0x%02X\n",gb_sync_bits);
  PreparaColorVGA();
  SDLClear();
  //En 320x200 sale bits:0x80 y deberia ser 0x40
  //En 320x240 sale bits:0xC0
 #else
  #ifdef use_lib_bitluni_3bpp   
   vga.init(vga.MODE320x200, RED_PIN_3B, GRE_PIN_3B, BLU_PIN_3B, HSYNC_PIN, VSYNC_PIN);        
   vga.fillRect(0,0,320,180,BLACK);
   vga.fillRect(0,0,320,180,BLACK);//fix mode fast video
   #ifdef use_lib_bitluni_low_memory
   #else
    Serial.printf("RGBMask:%02X Sbits:%2X\n",vga.RGBAXMask,vga.SBits);   
   #endif 
  #else
   #define RED_PINS_6B 21, 22
   #define GRE_PINS_6B 18, 19
   #define BLU_PINS_6B  4,  5
   const int redPins[] = {RED_PINS_6B};
   const int grePins[] = {GRE_PINS_6B};
   const int bluPins[] = {BLU_PINS_6B}; 
   //vga.init(vga.MODE320x240, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);
   //vga.init(vga.MODE320x200, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);
   vga.init(vga.MODE200x150, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);   
   //vga.setFont(Font6x8);
   //vga.clear(BLACK);
   //vga.clear(0x00);
   gb_buffer_vga= vga.backBuffer;
   gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
   PreparaColorVGA();
   SDLClear();
   
  
   //vga.fillRect(0,0,320,180,0x00);
   //vga.fillRect(0,0,320,180,0x00);//fix mode fast video  
   //vga.fillRect(0,0,200,150,0x00);
   //vga.fillRect(0,0,200,150,0x00);//fix mode fast video  

   //vga.RGBAXMask,vga.SBits  
   Serial.printf("RGBMask:%02X Sbits:%2X\n",vga.RGBAXMask,vga.SBits);
   //RGBMask:3F Sbits:C0 320x240
   //RGBMask:3F Sbits:40 320x200
  #endif 
 #endif 
 
 
 #ifdef use_lib_log_serial
  Serial.printf("VGA %d\n", ESP.getFreeHeap()); 
 #endif

 kb_begin();
 
 memset(keyboard,0xFF,9); //Reseteamos teclado

 tiempo_ini_vga = tiempo_cur_vga= tiempo_ini_keyboard= tiempo_cur_keyboard= millis();
 gb_time_blit_cur= gb_time_blit_before= tiempo_cur_keyboard;
 

 //emu_Init("");
 emu_Init_Flash(0);
 autoload=0;//Para dejar BASIC
 ResetZ80_Flash(0);

 #ifdef use_lib_log_serial  
  Serial.printf("END SETUP %d\n", ESP.getFreeHeap()); 
 #endif 
}

//***************************************
void Poll_Keyboard()
{
 memset(keyboard,0xFF,9);
 gb_show_osd_main_menu = (!keymap[PS2_KC_F1])&0x01;

 if (!keymap[PS2_KC_A]) keyboard[1]= 0xFE;
 if (!keymap[PS2_KC_B]) keyboard[7]= 0xEF;
 if (!keymap[PS2_KC_C]) keyboard[0]= 0xF7;
 if (!keymap[PS2_KC_D]) keyboard[1]= 0xFB;
 if (!keymap[PS2_KC_E]) keyboard[2]= 0xFB;
 if (!keymap[PS2_KC_F]) keyboard[1]= 0xF7;
 if (!keymap[PS2_KC_G]) keyboard[1]= 0xEF;
 if (!keymap[PS2_KC_H]) keyboard[6]= 0xEF;
 if (!keymap[PS2_KC_I]) keyboard[5]= 0xFB;
 if (!keymap[PS2_KC_J]) keyboard[6]= 0xF7;
 if (!keymap[PS2_KC_K]) keyboard[6]= 0xFB;
 if (!keymap[PS2_KC_L]) keyboard[6]= 0xFD;
 if (!keymap[PS2_KC_M]) keyboard[7]= 0xF7;
 if (!keymap[PS2_KC_N]) keyboard[7]= 0xFB;
 if (!keymap[PS2_KC_O]) keyboard[5]= 0xFD;
 if (!keymap[PS2_KC_P]) keyboard[5]= 0xFE;
 if (!keymap[PS2_KC_Q]) keyboard[2]= 0xFE;
 if (!keymap[PS2_KC_R]) keyboard[2]= 0xF7;
 if (!keymap[PS2_KC_S]) keyboard[1]= 0xFD;
 if (!keymap[PS2_KC_T]) keyboard[2]= 0xEF;
 if (!keymap[PS2_KC_U]) keyboard[5]= 0xF7;
 if (!keymap[PS2_KC_V]) keyboard[0]= 0xEF;
 if (!keymap[PS2_KC_W]) keyboard[2]= 0xFD;
 if (!keymap[PS2_KC_X]) keyboard[0]= 0xFB;
 if (!keymap[PS2_KC_Y]) keyboard[5]= 0xEF;
 if (!keymap[PS2_KC_Z]) keyboard[0]= 0xFD;
 if (!keymap[PS2_KC_0]) keyboard[4]= 0xFE;
 if (!keymap[PS2_KC_1]) keyboard[3]= 0xFE;
 if (!keymap[PS2_KC_2]) keyboard[3]= 0xFD;
 if (!keymap[PS2_KC_3]) keyboard[3]= 0xFB;
 if (!keymap[PS2_KC_4]) keyboard[3]= 0xF7;
 if (!keymap[PS2_KC_5]) keyboard[3]= 0xEF;
 if (!keymap[PS2_KC_6]) keyboard[4]= 0xEF;
 if (!keymap[PS2_KC_SPACE]) keyboard[7]= 0xFE;
 if (!keymap[PS2_KC_ENTER]) keyboard[6]= 0xFE;
/*if (!keymap[PS2_KC_7])
if (!keymap[PS2_KC_8])
if (!keymap[PS2_KC_9])
keymap[KEY_BACKSPACE];
keymap[PS2_KC_ESC];
keymap[KEY_CURSOR_LEFT];
keymap[KEY_CURSOR_RIGHT];
keymap[KEY_CURSOR_UP];
keymap[KEY_CURSOR_DOWN];
keymap[PS2_KC_F1];*/
}


//Loop main
void loop() 
{ 
 //SDL_DumpVGA();
 //while (!done)
 //{
 
 if (gb_load_new_pfile == 1)
 {
  gb_load_new_pfile =0;
  emu_Init_Flash(gb_id_cur_pfile);
 }     

 if (gb_cpunoexe == 0)
 {  
  tiempo_cur_keyboard= millis();  
  if ((tiempo_cur_keyboard-tiempo_ini_keyboard)>= gb_keyboard_cur_poll_ms) //20 ms
  {
   tiempo_ini_keyboard= tiempo_cur_keyboard; 
   Poll_Keyboard();
  }  
  tiempo_ini_cpu= millis();
  jj_ini_cpu = micros();
  
  z81_Step(); //Metodo rapido llamada

  jj_end_cpu = micros();
  tiempo_fin_cpu = millis();
  total_tiempo_ms_cpu=tiempo_fin_cpu-tiempo_ini_cpu;

  gb_cur_cpu_ticks= (jj_end_cpu-jj_ini_cpu);
  if (gb_cur_cpu_ticks>gb_max_cpu_ticks)
   gb_max_cpu_ticks= gb_cur_cpu_ticks;
  if (gb_cur_cpu_ticks<gb_min_cpu_ticks)   
   gb_min_cpu_ticks= gb_cur_cpu_ticks;  
 }

 if (gb_show_osd_main_menu == 1)
 {
  do_tinyOSD();
 }


 if (gb_cpunoexe == 0)
 {
  gb_cpunoexe=1;        
  gb_cpunoexe_timer_ini= millis();  
  if (gb_auto_delay_cpu==1)
  {
   tiene_que_tardar= 20-total_tiempo_ms_cpu;
   if (tiene_que_tardar>20){
    tiene_que_tardar=0;
   }
  }
  else
  {
   tiene_que_tardar= gb_delay_tick_cpu_milis;
  }  
 }
 else
 {
  if ((millis()-gb_cpunoexe_timer_ini)>=tiene_que_tardar)
  {
   gb_cpunoexe=0;      
  }
  gb_cpunoexe=0;
 }

 tiempo_cur_vga= millis();
 if ((tiempo_cur_vga-tiempo_ini_vga)>= gb_vga_cur_poll_ms) //20
 {
  tiempo_ini_vga= tiempo_cur_vga;
  jj_ini_vga = micros();
  


  jj_end_vga = micros();
  tiempo_vga=1;
  gb_cur_vga_ticks= (jj_end_vga-jj_ini_vga);
  if (gb_cur_vga_ticks>gb_max_vga_ticks)
   gb_max_vga_ticks= gb_cur_vga_ticks;
  if (gb_cur_vga_ticks<gb_min_vga_ticks)   
   gb_min_vga_ticks= gb_cur_vga_ticks;  
 }



 gb_cpu_timer_cur= millis();
 if ((gb_cpu_timer_cur-gb_cpu_timer_before)>1000)
 {
  gb_cpu_timer_before= gb_cpu_timer_cur;
  if (tiempo_vga == 1)
  {
   Serial.printf("c:%u m:%u mx:%u vc:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks, gb_cur_vga_ticks,gb_min_vga_ticks,gb_max_vga_ticks);
   //Reseteo VGA
   gb_min_vga_ticks= 1000000;
   gb_max_vga_ticks= 0;
   gb_cur_vga_ticks= 0;   
   tiempo_vga=0;
  }
  else
  {//Imprimo CPU
   Serial.printf("c:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks);
  }

  //Reseteo CPU a 1 segundo
  gb_min_cpu_ticks= 1000000;
  gb_max_cpu_ticks= 0;
  gb_cur_cpu_ticks= 0;   
 }

 //}
}
