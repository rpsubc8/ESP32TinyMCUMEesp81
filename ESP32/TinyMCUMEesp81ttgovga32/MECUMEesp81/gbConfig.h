#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H
 

 //Corrige teclados que no se inicializan(solucion dcrespo3D)
 //#define FIX_PERIBOARD_NOT_INITING

 //milisegundos espera en cada frame 
 #define use_lib_delay_tick_cpu_auto 1
 #define use_lib_delay_tick_cpu_milis 0 
 #define use_lib_keyboard_poll_milis 10
 #define gb_ms_blit_poll 0
 //No necesito vga ms poll pero lo dejo
 #define use_lib_vga_poll_milis 20
 

 //#define gb_ms_vga_poll 20
 //#define gb_ms_keyboard_poll 1
 ////Read keyboard poll x millis
 //#define gb_ms_keyboard 20 
 ////Milisegundos polling vga
 //#define gb_ms_vga 20 



 //Usa la libreria bitluni modificada en C tiny fast
 #define use_lib_bitluni_fast


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
