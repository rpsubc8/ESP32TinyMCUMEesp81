#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H

 //Not use double numbers (IEEE not fpu) calculate vga frequency
 //#define use_lib_fix_double_precision

 //Debug i2s bitluni vga frequency
 //#define use_lib_debug_i2s

 //Use terminal keyboard, putty
 //#define use_lib_keyboard_uart
 
 //timeout read millis
 #define use_lib_keyboard_uart_timeout 0


 //log keyboard remote uart 
 //#define use_lib_log_keyboard_uart


 //Video mode selection VGA
 //Select one mode and deselect other modes
 //360x200 720x400 31.3 Khz 70.3 Hz freq:28322000 pixel_clock:14161000
 #define use_lib_vga360x200x70hz_bitluni
 //320x200 720x400 31.4 Khz 70.0 Hz freq:25175000 pixel_clock:12587500
 //#define use_lib_vga320x200x70hz_bitluni
 //320x200 70Hz freq:12587500 funciona
 //#define use_lib_vga320x200x70hz_fabgl



 #ifdef use_lib_vga360x200x70hz_bitluni
  #define use_lib_vga360x200  
 #else  
  #ifdef use_lib_vga320x200x70hz_bitluni
   #define use_lib_vga320x200
  #else
   #ifdef use_lib_vga320x200x70hz_fabgl
    #define use_lib_vga320x200
    #ifndef use_lib_fix_double_precision
     #define use_lib_fix_double_precision
    #endif    
   #endif
  #endif  
 #endif


 #ifdef use_lib_vga360x200
  //Borde izquierdo para centrar imagen en 360x200
  //Multiplo de 4 pixels, no poner mas de 10 o falla por salirse del buffer
  //valores validos: 0 2 4 6 8 10
  #define use_lib_border_x 4
 #else
  #define use_lib_border_x 0
 #endif 


 //Usa bitluni cvbs video 26 audio 25.Si no usa cvbs, usa VGA
 //#define use_lib_cvbs_bitluni 
 //No uso doble buffer, ahorro memoria
 #define use_lib_cvbs_bitluni_not_backbuffer 
 //Usa borde(40x22) o no(32x22).Si no se usa,corrige defectos en TV
 //#define use_lib_cvbs_bitluni_border
 //Usar buffer de video 2 bpp 4 colores (No usar)
 //#define use_lib_video_2bpp
 
 //mode PAL, NTSC for default
 //#define use_lib_cvbs_pal

 //Use DAC output 5 volts (not 3.2 volts) TTGO VGA32
 #define use_lib_cvbs_ttgo_vga32
 //Advertencia Usar alto brillo en DAC TTGO VGA32 5 volts (PreparaColorCVBS)
 //El valor supera 1 voltio de la norma CVBS
 //#define use_lib_cvbs_ttgo_vga32_bright 

 //Corrige teclados que no se inicializan(solucion dcrespo3D)
 //#define FIX_PERIBOARD_NOT_INITING



 //Usa la libreria bitluni modificada en C tiny fast
 #ifdef use_lib_cvbs_bitluni
  //Default value invert mode
  #define use_lib_invert_color_default_value 1  
 #else
  #define use_lib_tinybitluni_fast
  #define use_lib_vga8colors 
  //Default value invert mode
  #define use_lib_invert_color_default_value 0
 #endif 


 #define use_lib_optimice_width_height

 //milisegundos espera en cada frame 
 #define use_lib_delay_tick_cpu_auto 1
 #define use_lib_delay_tick_cpu_milis 0 
 #define use_lib_keyboard_poll_milis 10
 #define gb_ms_blit_poll 20
 //No necesito vga ms poll pero lo dejo
 #define use_lib_vga_poll_milis 20
 //Poll keyboard remote uart
 #define gb_current_ms_poll_keyboard_uart 50  
 

 //#define gb_ms_vga_poll 20
 //#define gb_ms_keyboard_poll 1
 ////Read keyboard poll x millis
 //#define gb_ms_keyboard 20 
 ////Milisegundos polling vga
 //#define gb_ms_vga 20 


 //Show Time measurement
 //#define use_lib_stats_time_unified

 //Show Logs
 #define use_lib_log_serial
 

 //No usarlo Pruebas
 //#define use_lib_bitluni_3bpp
 
 //No usarlo Pruebas
 //#define use_lib_bitluni_low_memory

#endif

