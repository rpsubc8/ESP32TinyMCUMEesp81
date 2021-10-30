#ifndef _GB_PFILE_H
 #define _GB_PFILE_H

 #include <stddef.h>
 #include "pfile/zxgal.h"
 #include "pfile/frog.h"
 #include "pfile/3dmaze.h"
 #include "pfile/manicminer.h"
 #include "pfile/slc.h"
 #include "pfile/hrdemo3d.h"
 #include "pfile/hires.h"
 #include "pfile/hiresinvaders.h"
 #include "pfile/hiressnake.h"
 #include "pfile/hirespacman.h"
 #include "pfile/hiresfortyniner.h"
 #include "pfile/hiresmetropolis.h"
 #include "pfile/hiresjbracing.h"
 #include "pfile/goodbyeworld.h"
 #include "pfile/smrzx81.h"
 #include "pfile/192bytesfix4.h"
 #include "pfile/helloworld.h"
 #include "pfile/jsw1k.h"
 #include "pfile/twirldemo.h"
 #include "pfile/spaceinvaders.h"
 #include "pfile/puckman.h"
 #include "pfile/checkmem.h"
 #include "pfile/16kram.h"
 #include "pfile/ifyouwanttobe.h"
 #include "pfile/1kchess.h"
 #include "pfile/gulp2.h" 
 #include "pfile/antattack.h"
 #include "pfile/onelittleghost.h"
 #include "pfile/krazykonginter.h" 
 
 #define max_list_pfile 29
 
 //tapes
 //Titulos
 static const char * gb_list_pfile_title[max_list_pfile]={
  "zxgal",
  "frog",
  "3dmaze",
  "manicminer",
  "slc",
  "hrdemo3D",
  "hires",
  "hiresinvaders",
  "hiressnake",
  "hirespacman",
  "hiresfortyniner",
  "hiresmetropolis",
  "hiresjbrazing",
  "goodbyeworld",
  "smrzx81",
  "192bytesfix4",
  "helloworld",
  "jsw1k",
  "twirldemo",
  "spaceinvaders",
  "puckman",
  "checkmem",
  "16kram",
  "ifyouwanttobe",
  "1kchess",
  "gulp2",
  "antattack",
  "onelittleghost",
  "krazykonginter"
 };
 
 //Tamanio en bytes
 static const int gb_list_pfile_size[max_list_pfile]={
  3562,
  1262,
  10553,
  11448,
  372,
  13496,
  7545,
  9296,
  16206,
  13597,
  13868,
  16137,
  9494,
  14855,
  8721,
  9290,
  4709,
  615,
  12711,
  2664,
  10535,
  1296,
  4533,
  2353,
  941,
  6116,
  16167,
  15884,
  7563
 };
 
 //Datos
 static const unsigned char * gb_list_pfile_data[max_list_pfile]={
  zx_pfile_zxprog,
  zx_pfile_frog,
  zx_pfile_3dmaze,
  zx_pfile_manicminer,
  zx_pfile_slc,
  zx_pfile_hrdemo3d,
  zx_pfile_hires,
  zx_pfile_hiresinvaders,
  zx_pfile_hiressnake,
  zx_pfile_hirespacman,
  zx_pfile_hiresfortyminer,
  zx_pfile_metropolis,
  zx_pfile_jbracing,
  zx_pfile_goodbyeworld,
  zx_pfile_smrzx81,
  zx_pfile_192bytesfix4,
  zx_pfile_helloworld,
  zx_pfile_jsw1k,
  zx_pfile_twirldemo,
  zx_pfile_spaceinvaders,
  zx_pfile_puckman,
  zx_pfile_checkmem,
  zx_pfile_16kram,
  zx_pfile_ifyouwanttobe,
  zx_pfile_1kchess,
  zx_pfile_gulp2,
  zx_pfile_antattack,
  zx_pfile_onelittleghost,
  zx_pfile_KrazyKongInter
 };


#endif
