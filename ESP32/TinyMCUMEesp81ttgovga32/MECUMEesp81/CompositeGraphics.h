//#pragma once
#include "gbConfig.h"

#ifdef use_lib_cvbs_bitluni

class CompositeGraphics
{ 
  public:
  int xres;
  int yres;
  char **frame;
  char **backbuffer;
  char **zbuffer;
  
  CompositeGraphics(int w, int h, int initialTrinagleBufferSize = 0)
    :xres(w), 
    yres(h)
  {
  }
  
  void init()
  {
    frame = (char**)malloc(yres * sizeof(char*));
    #ifdef use_lib_cvbs_bitluni_not_backbuffer
    #else
     backbuffer = (char**)malloc(yres * sizeof(char*));
    #endif 
    //not enough memory for z-buffer implementation
    //zbuffer = (char**)malloc(yres * sizeof(char*));
    for(int y = 0; y < yres; y++)
    {
      #ifdef use_lib_video_2bpp
       frame[y] = (char*)malloc(xres>>2); //2 bits color DIV 4
      #else
       frame[y] = (char*)malloc(xres);
      #endif 
      #ifdef use_lib_cvbs_bitluni_not_backbuffer
      #else       
       backbuffer[y] = (char*)malloc(xres);
      #endif 
      //zbuffer[y] = (char*)malloc(xres);
    }

    #ifdef use_lib_cvbs_bitluni_not_backbuffer
     backbuffer= frame;
    #endif    
  }


  inline void begin(int clear = -1, bool clearZ = true)
  {
   if(clear > -1)
   {
    for(int y = 0; y < yres; y++)
    {
     #ifdef use_lib_video_2bpp
      for(int x = 0; x < (xres>>2); x++)
      {
       unsigned aux= (clear<<6)|(clear<<4)|(clear<<2)|(clear&0x03);
       backbuffer[y][x] = aux;
      }     
     #else
      for(int x = 0; x < xres; x++)
      {
       backbuffer[y][x] = clear;
      }
     #endif 
    }
   }
  }

  inline void end()
  {
    char **b = backbuffer;
    backbuffer = frame;
    frame = b;    
  }
 
  void fillRect(int x, int y, int w, int h, int color)
  {
    if(x < 0)
    {
      w += x;
      x = 0;
    }
    if(y < 0)
    {
      h += y;
      y = 0;
    }
    if(x + w > xres)
      w = xres - x;
    if(y + h > yres)
      h = yres - y;
    
    #ifdef use_lib_video_2bpp
    #else
     for(int j = y; j < y + h; j++)
     {
      for(int i = x; i < x + w; i++)
      {      
       backbuffer[j][i] = color;
      }
     }
    #endif 
  }

};

#endif

