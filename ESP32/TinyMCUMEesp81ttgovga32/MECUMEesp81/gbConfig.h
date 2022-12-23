#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H

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
 

 //#define gb_ms_vga_poll 20
 //#define gb_ms_keyboard_poll 1
 ////Read keyboard poll x millis
 //#define gb_ms_keyboard 20 
 ////Milisegundos polling vga
 //#define gb_ms_vga 20 



 //Logs
 #define use_lib_log_serial
 

 //No usarlo Pruebas
 //#define use_lib_bitluni_3bpp
 
 //No usarlo Pruebas
 //#define use_lib_bitluni_low_memory
 
 
 //Delay millis iteration emulate 
 //No usarlo Pruebas
 //#define gb_delay_emulate_ms 0



 //Desplazamiento X en multiplos de 4 pixels (32 bits)
 //Desplazamiento Y en pixels
 //#define gb_add_offset_x 20 
 //#define gb_add_offset_y 40 
#endif
