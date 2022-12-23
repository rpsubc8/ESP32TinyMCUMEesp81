//#pragma once
#include "gbConfig.h"

#ifdef use_lib_cvbs_bitluni

#include "driver/i2s.h"

typedef struct
{
  float lineMicros;
  float syncMicros;
  float blankEndMicros;
  float backMicros;
  float shortVSyncMicros;
  float overscanLeftMicros; 
  float overscanRightMicros; 
  float syncVolts; 
  float blankVolts; 
  float blackVolts;
  float whiteVolts;
  short lines;
  short linesFirstTop;
  short linesOverscanTop;
  short linesOverscanBottom;
  float imageAspect;
}TechProperties;

const TechProperties PALProperties = {
  .lineMicros = 64,
  .syncMicros = 4.7,
  .blankEndMicros = 10.4,
  .backMicros = 1.65,
  .shortVSyncMicros = 2.35,
  .overscanLeftMicros = 1.6875,
  .overscanRightMicros = 1.6875,
  .syncVolts = -0.3,
  .blankVolts = 0.0, 
  .blackVolts =  0.005,//specs 0.0,
  .whiteVolts = 0.7,
  .lines = 625,
  .linesFirstTop = 23,
  .linesOverscanTop = 9,
  .linesOverscanBottom = 9,
  .imageAspect = 4./3.
};

const TechProperties NTSCProperties = {
  .lineMicros = 63.492,
  .syncMicros = 4.7,
  .blankEndMicros = 9.2,
  .backMicros = 1.5,
  .shortVSyncMicros = 2.3,   
  .overscanLeftMicros = 0,//1.3, 
  .overscanRightMicros = 0,//1, 
  .syncVolts = -0.286,
  .blankVolts = 0.0, 
  .blackVolts = 0.05, //specs 0.054,
  .whiteVolts = 0.714,  
  .lines = 525,
  .linesFirstTop = 20,
  .linesOverscanTop = 6,
  .linesOverscanBottom = 9,
  .imageAspect = 4./3.
};
  
class CompositeOutput
{
  public:
  int samplesLine;
  int samplesSync;
  int samplesBlank;
  int samplesBack;
  int samplesActive;
  int samplesBlackLeft;
  int samplesBlackRight;

  int samplesVSyncShort;
  int samplesVSyncLong;

  char levelSync;
  char levelBlank;
  char levelBlack;
  char levelWhite;
  char grayValues;

  int targetXres;
  int targetYres;
  int targetYresEven;
  int targetYresOdd;

  int linesEven;
  int linesOdd;
  int linesEvenActive;
  int linesOddActive;
  int linesEvenVisible;
  int linesOddVisible;
  int linesEvenBlankTop;
  int linesEvenBlankBottom;
  int linesOddBlankTop;
  int linesOddBlankBottom;

  float pixelAspect;
    
  unsigned short *line;

  static const i2s_port_t I2S_PORT = (i2s_port_t)I2S_NUM_0;  
    
  enum Mode
  {
    PAL,
    NTSC  
  };
  
  const TechProperties &properties;
  
  #ifdef use_lib_cvbs_ttgo_vga32
   CompositeOutput(Mode mode, int xres, int yres, double Vcc = 5)
    :properties((mode==NTSC) ? NTSCProperties: PALProperties)
  #else
   CompositeOutput(Mode mode, int xres, int yres, double Vcc = 3.3)
    :properties((mode==NTSC) ? NTSCProperties: PALProperties)
  #endif  
  {    
    int linesSyncTop = 5;
    int linesSyncBottom = 3;

    linesOdd = properties.lines / 2;
    linesEven = properties.lines - linesOdd;
    linesEvenActive = linesEven - properties.linesFirstTop - linesSyncBottom;
    linesOddActive = linesOdd - properties.linesFirstTop - linesSyncBottom;
    linesEvenVisible = linesEvenActive - properties.linesOverscanTop - properties.linesOverscanBottom; 
    linesOddVisible = linesOddActive - properties.linesOverscanTop - properties.linesOverscanBottom;

    targetYresOdd = (yres / 2 < linesOddVisible) ? yres / 2 : linesOddVisible;
    targetYresEven = (yres - targetYresOdd < linesEvenVisible) ? yres - targetYresOdd : linesEvenVisible;
    targetYres = targetYresEven + targetYresOdd;
    
    linesEvenBlankTop = properties.linesFirstTop - linesSyncTop + properties.linesOverscanTop + (linesEvenVisible - targetYresEven) / 2;
    linesEvenBlankBottom = linesEven - linesEvenBlankTop - targetYresEven - linesSyncBottom;
    linesOddBlankTop = linesEvenBlankTop;
    linesOddBlankBottom = linesOdd - linesOddBlankTop - targetYresOdd - linesSyncBottom;
    
    double samplesPerSecond = 160000000.0 / 3.0 / 2.0 / 2.0;
    double samplesPerMicro = samplesPerSecond * 0.000001;
    samplesLine = (int)(samplesPerMicro * properties.lineMicros + 1.5) & ~1;
    samplesSync = samplesPerMicro * properties.syncMicros + 0.5;
    samplesBlank = samplesPerMicro * (properties.blankEndMicros - properties.syncMicros + properties.overscanLeftMicros) + 0.5;
    samplesBack = samplesPerMicro * (properties.backMicros + properties.overscanRightMicros) + 0.5;
    samplesActive = samplesLine - samplesSync - samplesBlank - samplesBack;

    targetXres = xres < samplesActive ? xres : samplesActive;

    samplesVSyncShort = samplesPerMicro * properties.shortVSyncMicros + 0.5;
    samplesBlackLeft = (samplesActive - targetXres) / 2;
    samplesBlackRight = samplesActive - targetXres - samplesBlackLeft;
    double dacPerVolt = 255.0 / Vcc;
    levelSync = 0;
    levelBlank = (properties.blankVolts - properties.syncVolts) * dacPerVolt + 0.5;
    levelBlack = (properties.blackVolts - properties.syncVolts) * dacPerVolt + 0.5;
    levelWhite = (properties.whiteVolts - properties.syncVolts) * dacPerVolt + 0.5;
    grayValues = levelWhite - levelBlack + 1;

    pixelAspect = (float(samplesActive) / (linesEvenVisible + linesOddVisible)) / properties.imageAspect;
  }


  void init()
  {

    //static const i2s_pin_config_t jj_pin_config = {
    // .bck_io_num = 26,
    // .ws_io_num = 26,
    // .data_out_num = 26,
    // .data_in_num = I2S_PIN_NO_CHANGE
    //};
    
    line = (unsigned short*)malloc(sizeof(unsigned short) * samplesLine);
    i2s_config_t i2s_config = {
       .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),
       .sample_rate = 1000000,  //not really used
       .bits_per_sample = (i2s_bits_per_sample_t)I2S_BITS_PER_SAMPLE_16BIT, 
       .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
       .communication_format = I2S_COMM_FORMAT_I2S_MSB,
       .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
       .dma_buf_count = 2,
       .dma_buf_len = samplesLine  //a buffer per line
    };
    
    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);    //start i2s driver
    
    i2s_set_dac_mode(I2S_DAC_CHANNEL_LEFT_EN); //Sobra GPIO26

    i2s_set_pin(I2S_PORT, NULL);                           //use internal DAC
    
    i2s_set_dac_mode(I2S_DAC_CHANNEL_LEFT_EN); //Sobra GPIO26

    //i2s_set_pin(I2S_PORT, &jj_pin_config);
    i2s_set_sample_rates(I2S_PORT, 1000000);               //dummy sample rate, since the function fails at high values
  
    //this is the hack that enables the highest sampling rate possible ~13MHz, have fun
    SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_A_V, 1, I2S_CLKM_DIV_A_S);
    SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_B_V, 1, I2S_CLKM_DIV_B_S);
    SET_PERI_REG_BITS(I2S_CLKM_CONF_REG(0), I2S_CLKM_DIV_NUM_V, 2, I2S_CLKM_DIV_NUM_S); 
    SET_PERI_REG_BITS(I2S_SAMPLE_RATE_CONF_REG(0), I2S_TX_BCK_DIV_NUM_V, 2, I2S_TX_BCK_DIV_NUM_S);



//JJ desactivar DAC
// Disable DAC1
REG_CLR_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_XPD_DAC);
REG_SET_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_DAC_XPD_FORCE);
// Disable DAC2
//REG_CLR_BIT(RTC_IO_PAD_DAC2_REG, RTC_IO_PDAC2_XPD_DAC);
//REG_SET_BIT(RTC_IO_PAD_DAC2_REG, RTC_IO_PDAC2_DAC_XPD_FORCE);
  }

  void sendLine()
  {
    esp_err_t error = ESP_OK;
    size_t bytes_written = 0;
    size_t bytes_to_write = samplesLine * sizeof(unsigned short);
    size_t cursor = 0;
    while (error == ESP_OK && bytes_to_write > 0) {
      error = i2s_write(I2S_PORT, (const char *)line + cursor, bytes_to_write, &bytes_written, portMAX_DELAY);
      bytes_to_write -= bytes_written;
      cursor += bytes_written;
    }
  }

  inline void fillValues(int &i, unsigned char value, int count)
  {
    for(int j = 0; j < count; j++)
      line[i++^1] = value << 8;
  }

 #ifdef use_lib_video_2bpp
  
  //unsigned char gb_aux_color_2bpp[4]={0,18,36,53};

  void fillLine(char *pixels)
  {
    int i = 0;
    unsigned char aux;
    unsigned int offs=0;

    fillValues(i, levelSync, samplesSync);
    fillValues(i, levelBlank, samplesBlank);
    fillValues(i, levelBlack, samplesBlackLeft);
    for(int x = 0; x < (targetXres >> 3); x++) //DIV 2 y DIV 4
    {
      //short pix = (levelBlack + pixels[x]) << 8;
      //line[i++^1] = pix;
      //line[i++^1]   = pix;

      aux= ((pixels[offs]>>6) & 0x03)<<4;
      //aux= gb_aux_color_2bpp[((pixels[offs]>>6) & 0x03)];
      //aux= gb_const_colorNormal[aux];      
      short pix = (levelBlack + aux) << 8;
      line[i++^1] = pix;
      line[i++^1] = pix;

      aux= ((pixels[offs]>>4) & 0x03)<<4;
      //aux= gb_aux_color_2bpp[((pixels[offs]>>4) & 0x03)];
      //aux= gb_const_colorNormal[aux];
      //aux= aux<<2;
      pix = (levelBlack + aux) << 8;
      line[i++^1] = pix;
      line[i++^1] = pix;

      aux= ((pixels[offs]>>2) & 0x03)<<4;      
      //aux= gb_aux_color_2bpp[((pixels[offs]>>2) & 0x03)];
      pix = (levelBlack + aux) << 8;
      line[i++^1] = pix;
      line[i++^1] = pix;      

      aux= (pixels[offs] & 0x03)<<4;      
      //aux= gb_aux_color_2bpp[(pixels[offs] & 0x03)];
      pix = (levelBlack + aux) << 8;
      line[i++^1] = pix;
      line[i++^1] = pix;

      offs++;      
    }
    fillValues(i, levelBlack, samplesBlackRight);
    fillValues(i, levelBlank, samplesBack);
  } 
 #else
  void fillLine(char *pixels)
  {
    int i = 0;
    fillValues(i, levelSync, samplesSync);
    fillValues(i, levelBlank, samplesBlank);
    fillValues(i, levelBlack, samplesBlackLeft);
    for(int x = 0; x < targetXres / 2; x++)
    {
      short pix = (levelBlack + pixels[x]) << 8;
      line[i++^1] = pix;
      line[i++^1]   = pix;
    }
    fillValues(i, levelBlack, samplesBlackRight);
    fillValues(i, levelBlank, samplesBack);
  }
 #endif 

  void fillLong(int &i)
  {
    fillValues(i, levelSync, samplesLine / 2 - samplesVSyncShort);
    fillValues(i, levelBlank, samplesVSyncShort);
  }
  
  void fillShort(int &i)
  {
    fillValues(i, levelSync, samplesVSyncShort);
    fillValues(i, levelBlank, samplesLine / 2 - samplesVSyncShort);  
  }
  
  void fillBlank()
  {
    int i = 0;
    fillValues(i, levelSync, samplesSync);
    fillValues(i, levelBlank, samplesBlank);
    fillValues(i, levelBlack, samplesActive);
    fillValues(i, levelBlank, samplesBack);
  }

  void fillHalfBlank(int &i)
  {
    fillValues(i, levelSync, samplesSync);
    fillValues(i, levelBlank, samplesLine / 2 - samplesSync);  
  }
  
  void sendFrameHalfResolution(char ***frame)
  {
    //Even Halfframe    
    int i = 0;
    fillLong(i); fillLong(i);
    sendLine(); sendLine();
    i = 0;
    fillLong(i); fillShort(i);
    sendLine();
    i = 0;
    fillShort(i); fillShort(i);
    sendLine(); sendLine();
    fillBlank();
    for(int y = 0; y < linesEvenBlankTop; y++)
      sendLine();
    for(int y = 0; y < targetYresEven; y++)
    {
      char *pixels = (*frame)[y];
      fillLine(pixels);
      sendLine();
    }
    fillBlank();
    for(int y = 0; y < linesEvenBlankBottom; y++)
      sendLine();
    i = 0;
    fillShort(i); fillShort(i);
    sendLine(); sendLine();
    i = 0;
    fillShort(i); 
    //odd half frame
    fillLong(i);
    sendLine(); 
    i = 0;
    fillLong(i); fillLong(i);
    sendLine(); sendLine();
    i = 0;
    fillShort(i); fillShort(i);
    sendLine(); sendLine();
    i = 0;
    fillShort(i); fillValues(i, levelBlank, samplesLine / 2);
    sendLine();

    fillBlank();
    for(int y = 0; y < linesOddBlankTop; y++)
      sendLine();
    for(int y = 0; y < targetYresOdd; y++)
    {
      char *pixels = (*frame)[y];
      fillLine(pixels);
      sendLine();
    }
    fillBlank();
    for(int y = 0; y < linesOddBlankBottom; y++)
      sendLine();
    i = 0;
    fillHalfBlank(i); fillShort(i);
    sendLine(); 
    i = 0;
    fillShort(i); fillShort(i);
    sendLine(); sendLine();
  }
};

#endif

