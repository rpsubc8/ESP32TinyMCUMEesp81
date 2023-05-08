//#define KEYMAP_PRESENT 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "emuapi.h"
#include "gbConfig.h"
#include "gbGlobals.h"
#include "Arduino.h"

//JJ extern "C" {
//JJ  #include "emuapi.h"
//JJ  #include "iopins.h"
//JJ}

//JJ #include "ili9341_t3dma.h"
//#include "logozx80kbd.h"
//#include "logozx81kbd.h"
//JJ #include "bmpjoy.h"
//JJ #include "bmpvbar.h"

//JJ #include "esp_event.h"
//JJ #include "esp_vfs_fat.h"
//JJ #include "driver/sdspi_host.h"
#include <dirent.h>
#include <sys/stat.h>
//JJ #include <driver/adc.h>

//JJ #ifdef HAS_I2CKBD
//JJ #ifdef USE_WIRE
//JJ #include "Wire.h"
//JJ #else
//JJ #include <driver/i2c.h>
//JJ #define ACK_CHECK_EN          0x1              /*!< I2C master will check ack from slave*/
//JJ #define ACK_CHECK_DIS         0x0              /*!< I2C master will not check ack from slave */
//JJ #define ACK_VAL               0x0              /*!< I2C ack value */
//JJ #define NACK_VAL              0x1              /*!< I2C nack value */
//JJ #endif

//JJ #define I2C_FREQ_HZ           400000           /*!< I2C master clock frequency */
//JJ static bool i2cKeyboardPresent = false;
//JJ #endif


//JJ extern ILI9341_t3DMA tft;

//static char romspath[64];
//JJ static int calMinX=-1,calMinY=-1,calMaxX=-1,calMaxY=-1;
//JJ static sdmmc_card_t* card;
//JJ const uint16_t deflogo[] = {
//JJ   0x0000,0x0000
//JJ };
//JJ static const uint16_t * logo = deflogo;
//JJ static const unsigned short * keysw = keyswzx80;

//JJ #define CALIBRATION_FILE    "/sdcard/cal.cfg"

//JJ #define MAX_FILENAME_SIZE   28
//JJ #define MAX_MENULINES       (MKEY_L9)
//JJ #define TEXT_HEIGHT         16
//JJ #define TEXT_WIDTH          8
//JJ #define MENU_FILE_XOFFSET   (6*TEXT_WIDTH)
//JJ #define MENU_FILE_YOFFSET   (2*TEXT_HEIGHT)
//JJ #define MENU_FILE_W         (MAX_FILENAME_SIZE*TEXT_WIDTH)
//JJ #define MENU_FILE_H         (MAX_MENULINES*TEXT_HEIGHT)
//JJ #define MENU_FILE_FGCOLOR   RGBVAL16(0xff,0xff,0xff)
//JJ #define MENU_FILE_BGCOLOR   RGBVAL16(0x00,0x00,0x20)
//JJ #define MENU_JOYS_YOFFSET   (12*TEXT_HEIGHT)
//JJ #define MENU_VBAR_XOFFSET   (0*TEXT_WIDTH)
//JJ #define MENU_VBAR_YOFFSET   (MENU_FILE_YOFFSET)


//JJ #define MKEY_L1             1
//JJ #define MKEY_L2             2
//JJ #define MKEY_L3             3
//JJ #define MKEY_L4             4
//JJ #define MKEY_L5             5
//JJ #define MKEY_L6             6
//JJ #define MKEY_L7             7
//JJ #define MKEY_L8             8
//JJ #define MKEY_L9             9
//JJ #define MKEY_UP             20
//JJ #define MKEY_DOWN           21
//JJ #define MKEY_JOY            22


//JJ const unsigned short menutouchareas[] = {
//JJ   TAREA_XY,MENU_FILE_XOFFSET,MENU_FILE_YOFFSET,
//JJ   TAREA_WH,MENU_FILE_W, TEXT_HEIGHT,
//JJ   TAREA_NEW_COL,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,TEXT_HEIGHT,
//JJ   
//JJ   TAREA_XY,MENU_VBAR_XOFFSET,MENU_VBAR_YOFFSET,
//JJ   TAREA_WH,32,48,
//JJ   TAREA_NEW_COL, 72,72,8,40,
//JJ     
//JJ   TAREA_END};
   
//JJ const unsigned short menutouchactions[] = {
//JJ   MKEY_L1,MKEY_L2,MKEY_L3,MKEY_L4,MKEY_L5,MKEY_L6,MKEY_L7,MKEY_L8,MKEY_L9,
//JJ   MKEY_UP,MKEY_DOWN,ACTION_NONE,MKEY_JOY}; 

  
//JJ static bool menuOn=true;
//JJ static bool callibrationOn=false;
//JJ static int callibrationStep=0;
//JJ static bool menuRedraw=true;
//JJ static int nbFiles=0;
//JJ static int curFile=0;
//JJ static int topFile=0;
//JJ static char selection[MAX_FILENAME_SIZE+1]="";
//JJ static uint8_t prev_zt=0; 

//JJ static int readNbFiles(void) {
//JJ   int totalFiles = 0;
//JJ 
//JJ  DIR* dir = opendir(romspath);
//JJ  while (true) {
//JJ    struct dirent* de = readdir(dir);
//JJ    if (!de) {
//JJ      // no more files
//JJ      break;
//JJ    }    
//JJ    if (de->d_type == DT_REG) {
//JJ      totalFiles++;
//JJ    }
//JJ    else if (de->d_type == DT_DIR) {
//JJ      if ( (strcmp(de->d_name,".")) && (strcmp(de->d_name,"..")) ) {
//JJ        totalFiles++;
//JJ      }
//JJ    }  
//JJ  }
//JJ  closedir(dir);
//JJ   printf("Directory read: %d files",totalFiles);
//JJ   return totalFiles;  
//JJ }

//JJ static char captureTouchZone(const unsigned short * areas, const unsigned short * actions, int *rx, int *ry, int *rw, int * rh) {
//JJ     uint16_t xt=0;
//JJ     uint16_t yt=0;
//JJ     uint16_t zt=0;
//JJ     bool hDir=true;  
//JJ 
/*JJ  
    if (tft.isTouching())
    {
        if (prev_zt == 0) {
            prev_zt =1;
            tft.readCal(&xt,&yt,&zt);
            if (zt<1000) {
              prev_zt=0; 
              return ACTION_NONE;
            }
            int i=0;
            int k=0;
            int y2=0, y1=0;
            int x2=0, x1=0;
            int x=KEYBOARD_X,y=KEYBOARD_Y;
            int w=TAREA_W_DEF,h=TAREA_H_DEF;
            uint8_t s;
            while ( (s=areas[i++]) != TAREA_END ) {
                if (s == TAREA_XY) {
                    x = areas[i++];
                    y = areas[i++];                    
                    x2 = x;
                    y2 = y;  
                }
                else if (s == TAREA_WH) {
                    w = areas[i++];
                    h = areas[i++];
                }                     
                else if (s == TAREA_NEW_ROW) {
                  hDir = true;
                  y1 = y2;
                  y2 = y1 + h;
                  x2 = x;
                }  
                else if (s == TAREA_NEW_COL) {
                  hDir = false;
                  x1 = x2;
                  x2 = x1 + w;
                  y2 = y;                  
                }
                else { 
                    if (hDir) {
                      x1 = x2;
                      x2 = x1+s;                                                            
                    } else {
                      y1 = y2;
                      y2 = y1+s;                      
                    }
                    if ( (yt >= y1) && (yt < y2) && (xt >= x1) && (xt < x2)  ) {
                        *rx = x1;
                        *ry = y1;
                        *rw = x2-x1;
                        *rh = y2-y1;
                        return (actions[k]);  
                    }
                    k++;
                }                
            }
        } 
        prev_zt =1; 
    } else {
        prev_zt=0; 
    } 
*/
//JJ   
//JJ     return ACTION_NONE;   
//JJ } 

//JJ void toggleMenu(bool on) {
//JJ   if (on) {
//JJ     callibrationOn=false;
//JJ     menuOn=true;
//JJ     menuRedraw=true;  
//JJ    tft.fillScreenNoDma(RGBVAL16(0x00,0x00,0x00));
//JJ    tft.drawTextNoDma(0,0, TITLE, RGBVAL16(0x00,0xff,0xff), RGBVAL16(0x00,0x00,0xff), true);  
//JJ    tft.drawSpriteNoDma(MENU_VBAR_XOFFSET,MENU_VBAR_YOFFSET,(uint16_t*)bmpvbar);
//JJ   } else {
//JJ     menuOn = false;    
//JJ   }
//JJ }


//JJ static void callibrationInit(void) 
//JJ {
//JJ   callibrationOn=true;
//JJ   menuOn=false;
//JJ   callibrationStep = 0;
//JJ   calMinX=0,calMinY=0,calMaxX=0,calMaxY=0;
//JJ  tft.fillScreenNoDma(RGBVAL16(0xff,0xff,0xff));
//JJ  tft.drawTextNoDma(0,100, "          Callibration process:", RGBVAL16(0x00,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
//JJ  tft.drawTextNoDma(0,116, "     Hit the red cross at each corner", RGBVAL16(0x00,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
//JJ  tft.drawTextNoDma(0,0, "+", RGBVAL16(0xff,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
//JJ   prev_zt = 1;  
//JJ }

//JJ static void readCallibration(void) 
//JJ {
//JJ   FILE * file = fopen(CALIBRATION_FILE, "rb");
//JJ   if (file) {
//JJ     fscanf(file,"%d %d %d %d\n",&calMinX,&calMinY,&calMaxX,&calMaxY);
//JJ     fclose(file);
//JJ     printf("Current callibration params: %d %d %d %d\n",calMinX,calMinY,calMaxX,calMaxY);                
//JJ   }
//JJ   else {
//JJ     printf("Callibration read error\n");
//JJ   }  
//JJ  tft.callibrateTouch(calMinX,calMinY,calMaxX,calMaxY);   
//JJ }

//JJ static void writeCallibration(void) 
//JJ {
//JJ //JJ  tft.callibrateTouch(calMinX,calMinY,calMaxX,calMaxY);
//JJ   FILE * file = fopen(CALIBRATION_FILE, "wb");
//JJ   if (file) {
//JJ     fprintf(file,"%d %d %d %d\n",calMinX,calMinY,calMaxX,calMaxY);
//JJ     fclose(file);
//JJ   }
//JJ   else {
//JJ     printf("Callibration write error\n");
//JJ   }  
//JJ }


//JJ bool callibrationActive(void) 
//JJ {
//JJ   return (callibrationOn);
//JJ }



//JJ int handleCallibration(uint16_t bClick) {
//JJ   uint16_t xt=0;
//JJ   uint16_t yt=0;
//JJ   uint16_t zt=0;  
/*JJ  
  if (tft.isTouching()) {
    if (prev_zt == 0) {
      prev_zt = 1;
      tft.readRaw(&xt,&yt,&zt);
      if (zt < 1000) {
        return 0;
      }
      switch (callibrationStep) 
      {
        case 0:
          callibrationStep++;
          tft.drawTextNoDma(0,0, " ", RGBVAL16(0xff,0xff,0xff), RGBVAL16(0xff,0xff,0xff), true);
          tft.drawTextNoDma(ILI9341_TFTREALWIDTH-8,0, "+", RGBVAL16(0xff,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
          calMinX += xt;
          calMinY += yt;          
          break;
        case 1:
          callibrationStep++;
          tft.drawTextNoDma(ILI9341_TFTREALWIDTH-8,0, " ", RGBVAL16(0xff,0xff,0xff), RGBVAL16(0xff,0xff,0xff), true);
          tft.drawTextNoDma(ILI9341_TFTREALWIDTH-8,ILI9341_TFTREALHEIGHT-16, "+", RGBVAL16(0xff,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
          calMaxX += xt;
          calMinY += yt;           
          break;
        case 2:
          callibrationStep++;
          tft.drawTextNoDma(ILI9341_TFTREALWIDTH-8,ILI9341_TFTREALHEIGHT-16, " ", RGBVAL16(0xff,0xff,0xff), RGBVAL16(0xff,0xff,0xff), true);
          tft.drawTextNoDma(0,ILI9341_TFTREALHEIGHT-16, "+", RGBVAL16(0xff,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
          calMaxX += xt;
          calMaxY += yt;
          break;
        case 3:
          tft.fillScreenNoDma(RGBVAL16(0xff,0xff,0xff));
          tft.drawTextNoDma(0,100, "          Callibration done!", RGBVAL16(0x00,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);
          tft.drawTextNoDma(0,116, "        (Click center to exit)", RGBVAL16(0xff,0x00,0x00), RGBVAL16(0xff,0xff,0xff), true);           
          callibrationStep++;
          calMinX += xt;
          calMaxY += yt;       
          break;                 
        case 4:
          if ( (xt > (ILI9341_TFTREALWIDTH/4)) && (xt < (ILI9341_TFTREALWIDTH*3)/4) 
            && (yt > (ILI9341_TFTREALHEIGHT/4)) && (yt < (ILI9341_TFTREALHEIGHT*3)/4) ) {
            calMinX /= 2;
            calMinY /= 2;
            calMaxX /= 2;
            calMaxY /= 2;
            writeCallibration();                       
            toggleMenu(true);
          }
          else {
            callibrationInit();              
          }
          break; 
                           
      }
      vTaskDelay(100 / portTICK_PERIOD_MS); 
    }  
  }
  else {
    prev_zt = 0;
  } 
*/  
//JJ   return 1; 
//JJ }



//JJ bool menuActive(void) 
//JJ {
//JJ   return (menuOn);
//JJ }

//JJ int handleMenu(uint16_t bClick)
//JJ {
//JJ   int action = ACTION_NONE;
/*JJ

  char newpath[80];
  strcpy(newpath, romspath);
  strcat(newpath, "/");
  strcat(newpath, selection);
  
  struct stat st;
  bool newPathIsDir = false;
  if(stat(newpath,&st) == 0)
    if((st.st_mode & S_IFDIR) != 0)
      newPathIsDir = true;

  int rx=0,ry=0,rw=0,rh=0;
  char c = captureTouchZone(menutouchareas, menutouchactions, &rx,&ry,&rw,&rh);
  if ( ( (bClick & MASK_JOY2_BTN) || (bClick & MASK_KEY_USER1) )  && (newPathIsDir) ) {
      menuRedraw=true;
      strcpy(romspath,newpath);
      curFile = 0;
      nbFiles = readNbFiles();     
  }
  else if ( (c >= MKEY_L1) && (c <= MKEY_L9) ) {
    if ( (topFile+(int)c-1) <= (nbFiles-1)  )
    {
      curFile = topFile + (int)c -1;
      menuRedraw=true;
     //tft.drawRectNoDma( rx,ry,rw,rh, KEYBOARD_HIT_COLOR );
    }
  }
  else if ( (bClick & MASK_JOY2_BTN) ) {
      menuRedraw=true;
      action = ACTION_RUNTFT;       
  }
  else if (bClick & MASK_JOY2_UP) {
    if (curFile!=0) {
      menuRedraw=true;
      curFile--;
    }
  }
  else if ( (bClick & MASK_JOY2_RIGHT) || (c == MKEY_UP) ) {
    if ((curFile-9)>=0) {
      menuRedraw=true;
      curFile -= 9;
    } else if (curFile!=0) {
      menuRedraw=true;
      curFile--;
    }
  }  
  else if (bClick & MASK_JOY2_DOWN)  {
    if ((curFile<(nbFiles-1)) && (nbFiles)) {
      curFile++;
      menuRedraw=true;
    }
  }
  else if ( (bClick & MASK_JOY2_LEFT) || (c == MKEY_DOWN) ) {
    if ((curFile<(nbFiles-9)) && (nbFiles)) {
      curFile += 9;
      menuRedraw=true;
    }
    else if ((curFile<(nbFiles-1)) && (nbFiles)) {
      curFile++;
      menuRedraw=true;
    }
  }
  else if ( (bClick & MASK_KEY_USER1) || (c == MKEY_JOY) ) {
    emu_SwapJoysticks(0);
    menuRedraw=true;  
  }   

    
  if (menuRedraw && nbFiles) {
         
    int fileIndex = 0;
    DIR* dir = opendir(romspath);
//JJ    tft.drawRectNoDma(MENU_FILE_XOFFSET,MENU_FILE_YOFFSET, MENU_FILE_W, MENU_FILE_H, MENU_FILE_BGCOLOR);
//    if (curFile <= (MAX_MENULINES/2-1)) topFile=0;
//    else topFile=curFile-(MAX_MENULINES/2);
    if (curFile <= (MAX_MENULINES-1)) topFile=0;
    else topFile=curFile-(MAX_MENULINES/2);
    
    int i=0;
    while (i<MAX_MENULINES) {
      struct dirent* de = readdir(dir);
      if (!de) {
        break;
      }     
      if ( (de->d_type == DT_REG) || ((de->d_type == DT_DIR) && (strcmp(de->d_name,".")) && (strcmp(de->d_name,"..")) ) ) {
        if (fileIndex >= topFile) {              
          if ((i+topFile) < nbFiles ) {
            if ((i+topFile)==curFile) {
              tft.drawTextNoDma(MENU_FILE_XOFFSET,i*TEXT_HEIGHT+MENU_FILE_YOFFSET, de->d_name, RGBVAL16(0xff,0xff,0x00), RGBVAL16(0xff,0x00,0x00), true);
              strcpy(selection,de->d_name);            
            }
            else {
              tft.drawTextNoDma(MENU_FILE_XOFFSET,i*TEXT_HEIGHT+MENU_FILE_YOFFSET, de->d_name, MENU_FILE_FGCOLOR, MENU_FILE_BGCOLOR, true);      
            }
          }
          i++; 
        }
        fileIndex++;    
      }
    }
    closedir(dir);
    
    tft.drawSpriteNoDma(0,MENU_JOYS_YOFFSET,(uint16_t*)bmpjoy);  
    tft.drawTextNoDma(48,MENU_JOYS_YOFFSET+8, (emu_SwapJoysticks(1)?(char*)"SWAP=1":(char*)"SWAP=0"), RGBVAL16(0x00,0xff,0xff), RGBVAL16(0xff,0x00,0x00), false);

    menuRedraw=false;     
  }

*/
//JJ   return (action);  
//JJ }

//JJ char * menuSelection(void)
//JJ {
//JJ   return (selection);  
//JJ }
  
//JJ #ifdef HAS_I2CKBD
//JJ #ifdef USE_WIRE
//JJ #else
//JJ static esp_err_t i2c_master_read_slave_reg(i2c_port_t i2c_num, uint8_t i2c_addr, uint8_t* data_rd, size_t size)
//JJ {
//JJ     if (size == 0) {
//JJ         return ESP_OK;
//JJ     }
//JJ     i2c_cmd_handle_t cmd = i2c_cmd_link_create();
//JJ     i2c_master_start(cmd);
//JJ     i2c_master_write_byte(cmd, ( i2c_addr << 1 ) | I2C_MASTER_READ, ACK_CHECK_EN);
//JJ     if (size > 1) {
//JJ         i2c_master_read(cmd, data_rd, size - 1, (i2c_ack_type_t)ACK_VAL);
//JJ     }
//JJ     i2c_master_read_byte(cmd, data_rd + size - 1, (i2c_ack_type_t)NACK_VAL);
//JJ     i2c_master_stop(cmd);
//JJ     esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
//JJ     i2c_cmd_link_delete(cmd);
//JJ     return ret;
//JJ }
//JJ #endif
//JJ #endif


//JJ void emu_init(void)
//JJ {
//JJ  printf("emu_init\n");
//JJ  fflush(stdout);
/*JJ
  esp_err_t ret = 0;

  printf("mounting sd...\n");

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  host.max_freq_khz = 10000;
  //host.slot = HSPI_HOST;
  
  sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
  slot_config.gpio_miso = SPIN_NUM_MISO;
  slot_config.gpio_mosi = SPIN_NUM_MOSI;
  slot_config.gpio_sck  = SPIN_NUM_CLK;
  slot_config.gpio_cs = SPIN_NUM_CS;
  slot_config.dma_channel = 2;

 
  esp_vfs_fat_sdmmc_mount_config_t mount_config = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024
  };
  

  while((ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card)) != ESP_OK) {
    printf("retrying\n");
    vTaskDelay(500 / portTICK_PERIOD_MS);   
  }

  strcpy(romspath,"/sdcard/");
  strcat(romspath,ROMSDIR);
  printf("dir is : %s\n",romspath);

  nbFiles = readNbFiles(); 
  printf("SD initialized, files found: %d\n",nbFiles);

 
  tft.touchBegin();
  //uint16_t xt=0;
  //uint16_t yt=0;
  //uint16_t zt=0;  
  //tft.readRo(&xt,&yt,&zt);


  emu_InitJoysticks();
  readCallibration();
  
  if ((tft.isTouching()) || (emu_ReadKeys() & MASK_JOY2_BTN) ) {
    callibrationInit();
  } else  {
    toggleMenu(true);
  }

#ifdef HAS_I2CKBD
  uint8_t msg[7]={0,0,0,0,0,0,0};
  
#ifdef USE_WIRE
  Wire.begin(I2C_SDA_IO, I2C_SCL_IO);
  Wire.requestFrom(8, 7, I2C_FREQ_HZ);  // request 5 bytes from slave device #8 
  int i = 0;
  int hitindex=-1;
  while (Wire.available() && (i<7) ) { // slave may send less than requested
    uint8_t b = Wire.read(); // receive a byte
    if (b != 0xff) hitindex=i; 
    msg[i++] = b;        
  }  
#else
  int i2c_master_port = I2C_NUM_1;
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = I2C_SDA_IO;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = I2C_SCL_IO;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = I2C_FREQ_HZ;
  i2c_param_config((i2c_port_t)i2c_master_port, &conf);
  if (i2c_driver_install((i2c_port_t)i2c_master_port, conf.mode,0, 0, 0) != ESP_OK)
    printf("I2C Failed initialized\n");
  
  if (i2c_master_read_slave_reg( I2C_NUM_1, 8, &msg[0], 7 ) != ESP_OK) 
      printf("I2C Failed \n");    
#endif  




  if ( (msg[0] == 0xff) && (msg[1] == 0xff) && 
       (msg[2] == 0xff) && (msg[3] == 0xff) && 
       (msg[4] == 0xff) && (msg[5] == 0xff) && (msg[6] == 0xff)) {
    i2cKeyboardPresent = true;
    printf("i2C keyboard found\n");            
  }
#endif 

*/
//JJ 
//JJ }


//void emu_printf(char * text)
//{
// #ifdef use_lib_log_serial
//  Serial.printf("%s\r\n",text);
//  //fflush(stdout);
// #endif 
//}


//void emu_printi(int val)
//{
// #ifdef use_lib_log_serial
//  Serial.printf("%d\n",val);
// #endif 
//}

//void emu_Init(char *ROM)
//{
// autoload=1;
// zx80=0;
// ramsize=48;     
//     
// z81_Start(ROM);
// 
// autoload=1;
// zx80=0;
// ramsize=48;
// 
// z81_Init(); 
//}

//*********************************************
void emu_Init_Flash(unsigned char id)
{
 autoload=1;
 zx80=0;
 ramsize=48;     
 
 z81_Start_Flash(id);
 
 //autoload=1;
 autoload=1;
 zx80=0;
 ramsize=48;
 
 z81_Init_Flash(id);
}

//JJ void * emu_Malloc(int size)
//JJ {
//JJ   void * retval =  malloc(size);
//JJ   if (!retval) {
//JJ     printf("failled to allocate %d\n",size);
//JJ   }
//JJ   else {
//JJ     printf("could allocate %d\n",size); 
//JJ   }
//JJ   
//JJ   return retval;
//JJ }

//JJ void emu_Free(void * pt)
//JJ {
//JJ  free(pt);
//JJ }


//static FILE * lastfileOpened;


//int emu_FileOpen(char * filename)
//{
//  int retval = 0;
//
//  char filepath[80];  
////JJ  strcpy(filepath, romspath);
////JJ  strcat(filepath, "/");
////JJ  strcat(filepath, filename);
//  //printf("FileOpen...%s\n",filepath);
//  
//  strcpy(filepath,filename);
//  #ifdef use_lib_log_serial
//   Serial.printf("romspath %s\n",romspath);
//   //fflush(stdout);
//  #endif 
//    
//  lastfileOpened = fopen(filepath, "rb");
//  if (lastfileOpened) {
//    retval = 1;
//    #ifdef use_lib_log_serial
//     Serial.printf("lastfileOpened\n");
//     //fflush(stdout);    
//    #endif 
//  }
//  else {
//   #ifdef use_lib_log_serial
//    Serial.printf("FileOpen failed %s\n",filepath);
//    //fflush(stdout);
//   #endif 
//  }
//  return (retval);
//}

//int emu_FileRead(char * buf, int size)
//{
//  int retval = fread(buf, 1, size, lastfileOpened);
//  if (retval != size) 
//  {
//   #ifdef use_lib_log_serial
//    Serial.printf("FileRead failed\n");
//    //fflush(stdout);
//   #endif 
//  }
//  #ifdef use_lib_log_serial
//   Serial.printf("FileRead size:%d %d\n",retval,size);
//   //fflush(stdout);
//  #endif 
//  return (retval);     
//}

//unsigned char emu_FileGetc(void) {
//  unsigned char c;
//  int retval = fread(&c, 1, 1, lastfileOpened);
//  if (retval != 1)
//  {
//   #ifdef use_lib_log_serial
//    Serial.printf("emu_FileGetc failed\n");
//   #endif 
//  }  
//  return c; 
//}


//void emu_FileClose(void)
//{
//  fclose(lastfileOpened);  
//}

//int emu_FileSize(char * filename) 
//{
//  int filesize=0;
//  char filepath[80];
////JJ  strcpy(filepath, romspath);
////JJ  strcat(filepath, "/");
//  strcat(filepath, filename);
//  #ifdef use_lib_log_serial
//   Serial.printf("FileSize...%s\n",filepath);   
//   //fflush(stdout);
//  #endif 
//
//  FILE * file = fopen(filepath, "rb");
//  if (file) {
//    fseek(file, 0L, SEEK_END);
//    filesize = ftell(file);
//    //fseek(file, 0L, SEEK_SET);
//    #ifdef use_lib_log_serial
//     Serial.printf("filesize is...%d\n",filesize);    
//     //fflush(stdout);
//    #endif 
//    fclose(file);    
//  }
// 
//  return(filesize);  
//}

//int emu_FileSeek(int seek) 
//{
//  fseek(lastfileOpened, seek, SEEK_SET);     
//  return (seek);
//}

//int emu_LoadFile(char * filename, char * buf, int size)
//{
//  int filesize = 0;
//    
//  char filepath[80];
//  strcpy(filepath, romspath);
//  strcat(filepath, "/");
//  strcat(filepath, filename);
//  #ifdef use_lib_log_serial
//   Serial.printf("LoadFile...%s\n",filepath);  
//  #endif 
//
//  filesize = emu_FileSize(filename);
//  FILE * file = fopen(filepath, "rb");
//  if (file) {
//    if (size >= filesize)
//    {
//      if (fread(buf, 1, filesize, file) != filesize) 
//      {
//       #ifdef use_lib_log_serial
//        Serial.printf("File read failed\n");
//       #endif 
//      }        
//    }
//    fclose(file);
//  }
//  
//  return(filesize);
//}

//int emu_LoadFileSeek(char * filename, char * buf, int size, int seek)
//{
//  int filesize = 0;
//    
//  char filepath[80];
//  strcpy(filepath, romspath);
//  strcat(filepath, "/");
//  strcat(filepath, filename);
//  #ifdef use_lib_log_serial
//   Serial.printf("LoadFileSeek...%d bytes at %d from %s\n",size,seek,filepath); 
//  #endif 
//
//  FILE * file = fopen(filepath, "rb");
//  if (file) {
//    fseek(file, seek, SEEK_SET);       
//    if (fread(buf, size, 1, file) != size) 
//    {
//     #ifdef use_lib_log_serial
//      Serial.printf("File read failed\n");
//     #endif 
//    }        
//    fclose(file);
//  }
//  
//  return(filesize);
//}

//JJ static int keypadval=0; 
//JJ static bool joySwapped = false;
//JJ static uint16_t bLastState;
//JJ static int xRef;
//JJ static int yRef;

//JJ int emu_ReadAnalogJoyX(int min, int max) 
//JJ {
//JJ   int val; //adc1_get_raw((adc1_channel_t)PIN_JOY2_A1X);  
/*JJ
  
  adc2_get_raw((adc2_channel_t)PIN_JOY2_A1X, ADC_WIDTH_BIT_12,&val);
  //printf("refX:%d X:%d\n",xRef,val); 
  val = val-xRef;
  //val = ((val*140)/100);
  if ( (val > -xRef/4) && (val < xRef/4) ) val = 0;
#if INVX
  val = xRef-val;
#else
  val = val+xRef;
#endif  

*/

//JJ   return (val*(max-min))/(xRef*2);
//JJ }

//JJ int emu_ReadAnalogJoyY(int min, int max) 
//JJ {
//JJ   int val; //= adc1_get_raw((adc1_channel_t)PIN_JOY2_A2Y);
/*JJ
  
  adc2_get_raw((adc2_channel_t)PIN_JOY2_A2Y, ADC_WIDTH_BIT_12,&val);
  //printf("refY:%d Y:%d\n",yRef,val); 
  val = val-yRef;
  //val = ((val*120)/100);
  if ( (val > -yRef/4) && (val < yRef/4) ) val = 0;
#if INVY
  val = yRef-val;
#else
  val = val+yRef;
#endif  

*/
//JJ   return (val*(max-min))/(yRef*2);
//JJ }


//JJ static uint16_t readAnalogJoystick(void)
//JJ {
//JJ   uint16_t joysval = 0;
/*JJ  

  int xReading = emu_ReadAnalogJoyX(0,256);
  if (xReading > 128) joysval |= MASK_JOY2_LEFT;
  else if (xReading < 128) joysval |= MASK_JOY2_RIGHT;
  
  int yReading = emu_ReadAnalogJoyY(0,256);
  if (yReading < 128) joysval |= MASK_JOY2_UP;
  else if (yReading > 128) joysval |= MASK_JOY2_DOWN;
  
  joysval |= ((gpio_get_level((gpio_num_t)PIN_JOY2_BTN) == 1) ? 0 : MASK_JOY2_BTN);

*/
//JJ   return (joysval);     
//JJ }


//JJ int emu_SwapJoysticks(int statusOnly) {
//JJ   if (!statusOnly) {
//JJ     if (joySwapped) {
//JJ       joySwapped = false;
//JJ     }
//JJ     else {
//JJ       joySwapped = true;
//JJ     }
//JJ   }
//JJ   return(joySwapped?1:0);
//JJ }

//JJ int emu_GetPad(void) 
//JJ {
//JJ   return(keypadval|((joySwapped?1:0)<<7));
//JJ }

//JJ int emu_ReadKeys(void) 
//JJ {
//JJ   uint16_t retval;
/*JJ  
  uint16_t j1 = readAnalogJoystick();

  uint16_t j2 = 0;

  if (joySwapped) {
    retval = ((j1 << 8) | j2);
  }
  else {
    retval = ((j2 << 8) | j1);
  }

  if (gpio_get_level((gpio_num_t)PIN_KEY_USER1) == 0 ) retval |= MASK_KEY_USER1;
  if (gpio_get_level((gpio_num_t)PIN_KEY_USER2) == 0 ) retval |= MASK_KEY_USER2;
  if (gpio_get_level((gpio_num_t)PIN_KEY_USER3) == 0 ) retval |= MASK_KEY_USER3;
  if (gpio_get_level((gpio_num_t)PIN_KEY_USER4) == 0 ) retval |= MASK_KEY_USER4;

  //printf("%d\n",retval);   
*/  
//JJ   return (retval);
//JJ }

//JJ unsigned short emu_DebounceLocalKeys(void)
//JJ {  
//JJ   uint16_t bCurState = emu_ReadKeys();
//JJ   uint16_t bClick = bCurState & ~bLastState;
//JJ   bLastState = bCurState;
//JJ 
//JJ   return (bClick);
//JJ }


//JJ int emu_ReadI2CKeyboard(void) {
//JJ  int retval=0;
  
  /*JJ
  
#ifdef HAS_I2CKBD 
  if (i2cKeyboardPresent) {
    uint8_t msg[7]; 
#ifdef USE_WIRE
    Wire.requestFrom(8, 7, I2C_FREQ_HZ);    // request 5 bytes from slave device #8 
    int i = 0;
    int hitindex=-1;
    while (Wire.available() && (i<7) ) { // slave may send less than requested
      uint8_t b = Wire.read(); // receive a byte
      if (b != 0xff) hitindex=i; 
      msg[i++] = b;        
    } 
#else
    if (i2c_master_read_slave_reg( I2C_NUM_1, 8, &msg[0], 7 ) != ESP_OK) 
      printf("I2C Failed \n");
    int hitindex=-1;
    int i = 0;
    while (i<7) {
      if (msg[i] != 0xff) hitindex=i;
      i++;
    }
#endif     
    //printf("I2C 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
    //  msg[0],msg[1],msg[2],msg[3],msg[4],msg[5],msg[6]);  
    if ((hitindex >=0 ) && (hitindex <=6 )) {
      unsigned short match = ((~msg[hitindex])&0x00FF) | (hitindex<<8);
      for (i=0; i<sizeof(i2ckeys); i++) {
        if (match == i2ckeys[i]) {
          //printf("I2C %d\n",keys[i]);          
          return (keys[i]);
        }
      }
    }    
  }
#endif

*/
//JJ  return(retval);
//JJ}

//JJ void emu_InitJoysticks(void) {  
/*JJ     
  gpio_set_direction((gpio_num_t)PIN_JOY2_BTN, GPIO_MODE_INPUT);
  gpio_set_pull_mode((gpio_num_t)PIN_JOY2_BTN, GPIO_PULLUP_ONLY);
  gpio_set_direction((gpio_num_t)PIN_KEY_USER1, GPIO_MODE_INPUT);
  gpio_set_pull_mode((gpio_num_t)PIN_KEY_USER1, GPIO_PULLUP_ONLY);
  gpio_set_direction((gpio_num_t)PIN_KEY_USER2, GPIO_MODE_INPUT);
  gpio_set_pull_mode((gpio_num_t)PIN_KEY_USER2, GPIO_PULLUP_ONLY);
  gpio_set_direction((gpio_num_t)PIN_KEY_USER3, GPIO_MODE_INPUT);
  gpio_set_pull_mode((gpio_num_t)PIN_KEY_USER3, GPIO_PULLUP_ONLY);
  gpio_set_direction((gpio_num_t)PIN_KEY_USER4, GPIO_MODE_INPUT);
  gpio_set_pull_mode((gpio_num_t)PIN_KEY_USER4, GPIO_PULLUP_ONLY);

  //adc1_config_channel_atten((adc1_channel_t)PIN_JOY2_A1X,ADC_ATTEN_DB_11);
  //adc1_config_channel_atten((adc1_channel_t)PIN_JOY2_A2Y,ADC_ATTEN_DB_11);
  adc2_config_channel_atten((adc2_channel_t)PIN_JOY2_A1X,ADC_ATTEN_DB_11);
  adc2_config_channel_atten((adc2_channel_t)PIN_JOY2_A2Y,ADC_ATTEN_DB_11);
  xRef=0; yRef=0;
  for (int i=0; i<10; i++) {
    int val;
    adc2_get_raw((adc2_channel_t)PIN_JOY2_A1X, ADC_WIDTH_BIT_12, &val);
    //val = adc1_get_raw((adc1_channel_t)PIN_JOY2_A1X);
    xRef += val;
    adc2_get_raw((adc2_channel_t)PIN_JOY2_A2Y,ADC_WIDTH_BIT_12, &val);
    //val = adc1_get_raw((adc1_channel_t)PIN_JOY2_A2Y); 
    yRef += val;
    vTaskDelay(20 / portTICK_PERIOD_MS); 
  }
  xRef /= 10;
  yRef /= 10;

  printf("refs: %d %d\n",xRef,yRef); 
  */
//JJ }



//JJ static bool vkbKeepOn = false;
//JJ static bool vkbActive = false;
//JJ static bool vkeyRefresh=false;
//JJ static bool exitVkbd = false;
//JJ static uint8_t keyPressCount=0; 


//JJ bool virtualkeyboardIsActive(void) {
//JJ    return (vkbActive);
//JJ}

//JJ void toggleVirtualkeyboard(bool keepOn) {     
/*JJ     
    if (keepOn) {      
        tft.drawSpriteNoDma(0,0,(uint16_t*)logo);
        //prev_zt = 0;
        vkbKeepOn = true;
        vkbActive = true;
        exitVkbd = false;  
    }
    else {
        vkbKeepOn = false;
        if ( (vkbActive) ) {
            tft.fillScreenNoDma( RGBVAL16(0x00,0x00,0x00) );
#ifdef DMA_FULLgpio_get_level
            tft.begin();
            tft.refresh();
#endif                        
            //prev_zt = 0; 
            vkbActive = false;
            exitVkbd = false;
        }
        else {
#ifdef DMA_FULL          
            tft.stop();
            tft.begin();      
            tft.start();
#endif                       
            tft.drawSpriteNoDma(0,0,(uint16_t*)logo);           
            //prev_zt = 0;
            vkbActive = true;
            exitVkbd = false;
        }
    }   
    */
//JJ }

 
//JJ void handleVirtualkeyboard() {
//JJ   int rx=0,ry=0,rw=0,rh=0;

/*JJ
    if (keyPressCount == 0) {
      keypadval = 0;      
    } else {
      keyPressCount--;
    }

    if ( (!virtualkeyboardIsActive()) && (tft.isTouching()) && (!keyPressCount) ) {
        toggleVirtualkeyboard(false);
        return;
    }
    
    if ( ( (vkbKeepOn) || (virtualkeyboardIsActive())  )  ) {
        char c = captureTouchZone(keysw, keys, &rx,&ry,&rw,&rh);
        if (c) {
            tft.drawRectNoDma( rx,ry,rw,rh, KEYBOARD_HIT_COLOR );
            if ( (c >=1) && (c <= ACTION_MAXKBDVAL) ) {
              keypadval = c;
              keyPressCount = 10;
              vTaskDelay(50 / portTICK_PERIOD_MS); 
              vkeyRefresh = true;
              exitVkbd = true;
            }
            else if (c == ACTION_EXITKBD) {
              vkeyRefresh = true;
              exitVkbd = true;  
            }
        }   
     }    
     
    if (vkeyRefresh) {
        vkeyRefresh = false;
        tft.drawSpriteNoDma(0,0,(uint16_t*)logo, rx, ry, rw, rh);
    }  
         
    if ( (exitVkbd) && (vkbActive) ) {      
        if (!vkbKeepOn) {             
            toggleVirtualkeyboard(false);
        }
        else {         
            toggleVirtualkeyboard(true);           
        } 
    }     
    */
//JJ }

//JJ int emu_setKeymap(int index) {
//JJ   if (index) {
//JJ     //logo = logozx81kbd;
//JJ     keysw = keyswzx81;      
//JJ   }
//JJ   else {
//JJ     //logo = logozx80kbd;
//JJ     keysw = keyswzx80;  
//JJ   }
//JJ   return 0;
//JJ }



//JJ static unsigned short palette16[PALETTE_SIZE];
unsigned char fskip=0;

//JJ void emu_SetPaletteEntry(unsigned char r, unsigned char g, unsigned char b, int index)
//JJ{
/*JJ     
  if (index<PALETTE_SIZE) {
    //printf("%d: %d %d %d\n", index, r,g,b);
    palette16[index] = RGBVAL16(r,g,b);    
  }
  */
//JJ}

void emu_DrawVsync(void)
{
  //printf("sync %d\n",skip);
  //printf("vsync\n");
  //fflush(stdout);
  fskip += 1;
  fskip &= VID_FRAME_SKIP;
}

//***************************************************************************
//void jj_fast_putpixel(short int x,short int y,unsigned char c)
//{
// //if ((x<0)||(y<0)||(x >= 320) || (y >= 200))
// //{
// // //printf("Clip x:%d y:%d\n",x,y);
// // //fflush(stdout);
// // return;
// //}
// #ifdef use_lib_tinybitluni_fast
//  gb_buffer_vga[y][x^2]= gb_color_vga[c];
// #else
//  #ifdef use_lib_cvbs_bitluni
//   //gb_buffer_cvbs[y][x]= gb_color_cvbs[(c==0)?0:7];
//   gb_buffer_cvbs[y][x]= gb_color_cvbs[(c & 0x01)];
//  #endif
// #endif 
// 
// //Uint8* p = (Uint8*)screen->pixels + (y * screen->pitch) + x;
// //*p= c;
//}


//JJ int fb_width = 320;
//JJ int fb_height = 240;
short int fb_width = 320;
short int fb_height = 200;
//JJ int fb_stride = fb_width+16;
//unsigned char framebuffer[100000];

//*******************************************************************
//void jj_writeLine(int width, int height, int y, unsigned char *buf) {
//  if ( (height<fb_height) && (height > 2) ) y += (fb_height-height)/2;
//  uint8_t * dst=&framebuffer[y*fb_stride];    
//  if (width > fb_width) {
//    int step = ((width << 8)/fb_width);
//    int pos = 0;
//    for (int i=0; i<fb_width; i++)
//    {
//      *dst++ = buf[pos >> 8];
//      pos +=step;
//    }        
//  }
//  else if ((width*2) == fb_width) {
//    for (int i=0; i<width; i++)
//    {
//      *dst++=*buf;
//      *dst++=*buf++;
//    }     
//  }
//  else {
//    if (width <= fb_width) {
//      dst += (fb_width-width)/2;
//    }
//    for (int i=0; i<width; i++)
//    {
//      *dst++=*buf++;
//    }
//  }
//}


#ifdef use_lib_optimice_width_height
 //void IRAM_ATTR jj_direct_writeLine(unsigned char y, unsigned char *buf)
 void jj_direct_writeLine(unsigned char y, unsigned char *buf)
 {
  int auxY,auxX;
  unsigned char aColor;
  unsigned int a0,a1,a2,a3,a32;
  
  //if ( (HEIGHT<fb_height) && (HEIGHT > 2) )
  //{
  // //y += (fb_height-HEIGHT)/2;
  // y += (fb_height-HEIGHT)>>1; //DIV 2
  //}
  auxY= y;  
  #ifdef use_lib_tinybitluni_fast   
   auxX= use_lib_border_x; //360x200 4x4=16 pixels borde izquierda      
  #else
   auxX= 0; //Si es cvbs o cualquier cosa
  #endif 
  
  //if (WIDTH <= fb_width) 
  //{
  // //dst += (fb_width-width)/2;
  // //auxX += (fb_width-WIDTH)/2;
  // auxX += (fb_width-WIDTH)>>1; //DIV 2
  //}

  #ifdef use_lib_cvbs_bitluni   
   #ifdef use_lib_cvbs_bitluni_border    
    //Con borde
    buf= buf+8; //Me salto columna 0, 8 pixels
    for (unsigned char i=0;i<80;i++)
    {//40 columnas 40x8=320
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }     
     a0= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }     
     a1= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }     
     a2= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }     
     a3= gb_color_cvbs[(aColor & 0x01)];

     a32= a0 | a1<<8 | a2<<16 | a3<<24;
     gb_buffer_cvbs32[auxY][auxX]= a32;
     auxX++;     
    }
   #else
    //Sin borde
    buf= buf+40; //4x8=32 sumo 1 5x8=40
   
    //while (auxX<32)
    while (auxX<8)
    {
     //gb_buffer_cvbs[auxY][auxX]= 0;
     gb_buffer_cvbs32[auxY][auxX]= 0;
     auxX++;
    }

    //for (int i=0;i<32;i++)
    //{
    // gb_buffer_cvbs[auxY][auxX]= 0;
    // auxX++;
    // *buf++;
    //}

    //for (int i=0;i<256;i++)
    for (unsigned char i=0;i<64;i++)
    {//32x8=256
     aColor= *buf++;
     //if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
     //aColor= gb_color_cvbs[((aColor==0)?0:7)];
     //gb_buffer_cvbs[auxY][auxX]= aColor;

     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
     //a0= gb_color_cvbs[((aColor==0)?0:7)];
     a0= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
     //a1= gb_color_cvbs[((aColor==0)?0:7)];
     a1= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
     //a2= gb_color_cvbs[((aColor==0)?0:7)];
     a2= gb_color_cvbs[(aColor & 0x01)];
     aColor= *buf++;
     if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
     //a3= gb_color_cvbs[((aColor==0)?0:7)];
     a3= gb_color_cvbs[(aColor & 0x01)];

     a32= a0 | a1<<8 | a2<<16 | a3<<24;
     gb_buffer_cvbs32[auxY][auxX]= a32;
     auxX++;
    }

    //while (auxX<320)
    while (auxX<80)
    {
     //gb_buffer_cvbs[auxY][auxX]= 0;
     gb_buffer_cvbs32[auxY][auxX]= 0;
     auxX++;
    }
   #endif

   //for (int i=240;i<320;i++)
   //{
   // gb_buffer_cvbs[auxY][auxX]= 0;
   // auxX++;
   // *buf++;
   //}   

   //for (int i=0; i<WIDTH; i++)
   /*
   for (unsigned char i=0; i<80; i++)
   {//80 x 4 = 320       
    if ((i<4)||(i>73))
    {
     a32= 0;
     *buf+=4;
    }
    else
    {
    aColor= *buf++;  
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }     
    a0= gb_color_cvbs[((aColor==0)?0:7)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    a1= gb_color_cvbs[((aColor==0)?0:7)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    a2= gb_color_cvbs[((aColor==0)?0:7)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    a3= gb_color_cvbs[((aColor==0)?0:7)];    
    a32= a0 | (a1<<8) | (a2<<16) | (a3<<24);
    }
                        
    gb_buffer_cvbs32[auxY][auxX]= a32;
    auxX++;    
   }    
   */      
  #else
   buf = buf+8; //Quitamos posicion 0 (8 pixels)
   for (unsigned char i=0; i<80; i++)
   {//80 x 4 = 320   
    //*dst++=*buf++;   
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }   
    //jj_fast_putpixel(auxX,auxY,(aColor==0)?0:7);
    //gb_buffer_vga[auxY][auxX^2]= gb_color_vga[((aColor==0)?0:7)];
 
    //a0= gb_color_vga[((aColor==0)?0:7)];
    a0= gb_color_vga[(aColor & 0x01)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    //a1= gb_color_vga[((aColor==0)?0:7)];
    a1= gb_color_vga[(aColor & 0x01)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    //a2= gb_color_vga[((aColor==0)?0:7)];
    a2= gb_color_vga[(aColor & 0x01)];
    aColor= *buf++;
    if (gb_invert_color == 1){ aColor=  ((~aColor)&0x01); }
    //a3= gb_color_vga[((aColor==0)?0:7)];
    a3= gb_color_vga[(aColor & 0x01)];
                     
    a32= a2 | (a3<<8) | (a0<<16) | (a1<<24);
    gb_buffer_vga32[auxY][auxX]= a32;

    auxX++;    
   }        
  #endif     
 }
#else
//*******************************************************************
void IRAM_ATTR jj_direct_writeLine(int width, int height, int y, unsigned char *buf) 
{
  int auxY,auxX;
  unsigned char aColor;     
  if ( (height<fb_height) && (height > 2) )
  {
   //y += (fb_height-height)/2;
   y += (fb_height-height)>>1; //DIV 2
  }
  //uint8_t * dst=&framebuffer[y*fb_stride];
  auxY= y;
  auxX= 0;
  if (width > fb_width) {
    int step = ((width << 8)/fb_width);
    int pos = 0;
    for (int i=0; i<fb_width; i++)
    {
      //*dst++ = buf[pos >> 8];
      aColor= buf[pos >> 8];
      if (gb_invert_color == 1){
       aColor= (~aColor)&0x01;
      }
      //jj_fast_putpixel(auxX,auxY,(aColor==0)?0:7);
      gb_buffer_vga[auxY][auxX^2]= gb_color_vga[((aColor==0)?0:7)];
      auxX++;
      pos +=step;
    }        
  }
  else if ((width*2) == fb_width) {
    for (int i=0; i<width; i++)
    {
      //*dst++=*buf;
      //*dst++=*buf++;
      aColor= *buf;
      if (gb_invert_color == 1){
       aColor= (~aColor)&0x01;
      }      
      //jj_fast_putpixel(auxX,auxY,(aColor==0)?0:7);
      gb_buffer_vga[auxY][auxX^2]= gb_color_vga[((aColor==0)?0:7)];
      auxX++;
      
      aColor= *buf++;
      //jj_fast_putpixel(auxX,auxY,(aColor==0)?0:7);
      if (gb_invert_color == 1){
       aColor= (~aColor)&0x01;
      }      
      gb_buffer_vga[auxY][auxX^2]= gb_color_vga[((aColor==0)?0:7)];
      auxX++;      
    }     
  }
  else {
    if (width <= fb_width) 
    {
      //dst += (fb_width-width)/2;
      //auxX += (fb_width-width)/2;
      auxX += (fb_width-width)>>1;
    }
    for (int i=0; i<width; i++)
    {
      //*dst++=*buf++;
      aColor= *buf++;
      if (gb_invert_color == 1){
       aColor= (~aColor)&0x01;
      }      
      //jj_fast_putpixel(auxX,auxY,(aColor==0)?0:7);
      gb_buffer_vga[auxY][auxX^2]= gb_color_vga[((aColor==0)?0:7)];
      auxX++;            
    }
  }
}
#endif

#ifdef use_lib_optimice_width_height
#else
//*************************************************************************
void emu_DrawLine(unsigned char * VBuf, int width, int height, int line) 
{
/*JJ
  if (fskip==0) {
    tft.writeLine(width,height,line, VBuf, palette16);
  }
  */ 
 if (fskip==0)
 {
  //jj_writeLine(width,height,line,VBuf);
  jj_direct_writeLine(width,height,line,VBuf);
 }
}  
#endif

//JJ void emu_DrawScreen(unsigned char * VBuf, int width, int height, int stride) 
//JJ {  
 /*JJ
  if (fskip==0) {
    tft.writeScreen(width,height-TFT_VBUFFER_YCROP,stride, VBuf+(TFT_VBUFFER_YCROP/2)*stride, palette16);
  }
  */
//JJ }

//JJ int emu_FrameSkip(void)
//JJ{
//JJ  return fskip;
//JJ}

//JJ void * emu_LineBuffer(int line)
//JJ {
//JJ      /*JJ
//JJ   return (void*)tft.getLineBuffer(line);
//JJ   */
//JJ   return NULL;
//JJ }

//JJ #ifdef HAS_SND
//JJ #include "AudioPlaySystem.h"
//JJ extern AudioPlaySystem audio;

//JJ void emu_sndInit() {
//JJ }

//JJ void emu_sndPlaySound(int chan, int volume, int freq)
//JJ {
     /*JJ
  if (chan < 6) {
    audio.sound(chan, freq, volume); 
  } 
  */
//JJ }

//JJ void emu_sndPlayBuzz(int size, int val) {
//JJ   //mymixer.buzz(size,val);  
//JJ }
//JJ #endif

