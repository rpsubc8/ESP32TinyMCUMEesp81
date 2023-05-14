# Tiny MCUME esp81
Modification of the MCUME zx81 emulator (Jean MarcHarvengt) to TTGO VGA32 v1.0, v1.1, v1.2 and v1.4 with ESP32.
<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewManicMiner.gif'></center>
I have made several modifications:
 <ul>
  <li>No PSRAM is used, running on ESP32 with 520 KB RAM (TTGO VGA32 v1.x).</li>
  <li>Use of a single core</li>
  <li>Low-resource OSD.</li>
  <li>Created project compatible with Arduino IDE and Platform IO.</li> 
  <li>Any digital pin can be used for video (hardware.h).</li>
  <li>Emulation video speed menu, VGA, keyboard.</li>
  <li>Support for 64-color (6-bit DAC) and 8-color (3-bit DAC) modes.</li>
  <li>VGA 320x200 and 360x200 bitluni, as well as 320x200 with fabgl parameters.</li>
  <li>Option to remove IEEE rounding calculation (double) from VGA</li>
  <li>Uploading of pfiles.</li>
  <li>The complete bitluni library is not required. I have reduced to the minimum, saving RAM and FLASH, based on Ricardo Massaro's library.</li>
  <li>Hi-res and pseudo hi-res mode support.</li>
  <li>Support CVBS PAL NTSC Black and White on TTGO VGA32 board (pin 26 CLK PS/2)</li>
  <li>The default CVBS mode has no border and comes out in inverted color mode, so that it can be viewed on the largest number of TVs without problems.</li>
  <li>Web Editor and ArduinoDroid (6.3.1) compatible project with tool makeandroid.bat</li>
  <li>The OSD is brought up with the <b>F1</b> key.</li>
  <li>Added keyboard support from usb serial terminal, VStudio monitor or putty.</li>
  <li>
   keyboard mapped
   <pre>
    //Keyboard Matrix
 // Port____Line____Bit__0____1____2____3____4__
 // FEFEh  0  (A8)     SHIFT  Z    X    C    V
 // FDFEh  1  (A9)       A    S    D    F    G
 // FBFEh  2  (A10)      Q    W    E    R    T
 // F7FEh  3  (A11)      1    2    3    4    5
 // EFFEh  4  (A12)      0    9    8    7    6
 // DFFEh  5  (A13)      P    O    I    U    Y
 // BFFEh  6  (A14)    ENTER  L    K    J    H
 // 7FFEh  7  (A15)     SPC   .    M    N    B 
   </pre>
  </li>
 </ul>
 
<br><br>
<h1>Pre-compiled version</h1>
In the precompile folder there are several versions already compiled to be able to be recorded with the flash download tool 3.9.2. with the FLASH demo games.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyMCUMEesp81/tree/main/ESP32/precompile'>https://github.com/rpsubc8/ESP32TinyMCUMEesp81/tree/main/ESP32/precompile</a>
<br><br>
We must choose the ESP32 type:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/flash00.gif'></center>
Subsequently, select the files as shown in the attached screenshot, with the same offset values:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/flash01.gif'></center>
And press start. If everything has been correct, we will only have to restart the ESP32.
 
 
<br><br>
<h1>Requirements</h1>
Required:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4)</li>
  <li>Visual Studio 1.66.1 PLATFORMIO 2.5.0 Espressif32 v3.5.0</li>
  <li>Arduino IDE 1.8.11</li>  
  <li>Arduino bitluni 0.3.3 reduced library (included in project)</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/ttgovga32v12.jpg'></center> 


<br><br>
<h1>ArduinoDroid</h1>
You must run, just once, the script makeandroid.bat, which leaves the entire data structure of the dataFlash directory in the root directory, as well as replacing the main files with .h calls without using the dataFlash data directory.<br>
At the end, the script itself ends up deleting the dataFlash directory.<br>
The script uses fart.exe (find and replace text).<br>
Once, it has been successfully executed, it can be used with the ArduinoDroid.


<br><br>
<h1>Arduino Web Editor</h1>
The makeandroid.bat script must be run once only. Once finished, it is uploaded to the cloud as any other project, either compressed in zip or by files.


<br><br>
<h1>PlatformIO</h1>
PLATFORMIO 2.5.0 must be installed from the Visual Studio extensions. Espressif32 v3.5.0 is also required.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewPlatformIOinstall.gif'></center>
Then the working directory <b>TinyMCUMEesp81ttgovga32</b> will be selected.
We must modify the <b>platformio.ini</b> file the <b>upload_port</b> option to select the COM port where we have our TTGO VGA32 board, if for some reason it is not detected by us.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewPlatformIO.gif'></center>
Then we will proceed to compile and upload to the board. No partitions are used, so we must upload the entire compiled binary.
It is all set up so you don't have to install the bitluni and fabgl libraries.

<br><br>
<h1>Arduino IDE</h1>
The whole project is compatible with the Arduino 1.8.11 framework.
We only have to open the <b>MECUMEesp81.ino</b> from the <b>MECUMEesp81</b> directory.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewArduinoIDEpreferences.gif'></center>
We must install the spressif extensions in the additional card url manager <b>https://dl.espressif.com/dl/package_esp32_index.json</b>.<br>
The project is now ready, so no bitluni or fabgl libraries are needed.
We must deactivate the PSRAM option, and in case of exceeding 1 MB of binary, select 4 MB of partition when uploading. Although the code does not use PSRAM, if the option is active and our ESP32 does not have it, an exception will be generated and it will restart in loop mode.


<br><br>
<h1>Modo Hi-res</h1>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewMetropolis.gif'></center>


<br><br>
<h1>UART keyboard</h1>
If the option <b>use_lib_keyboard_uart</b> is activated, it allows to use the PC keyboard from the VStudio monitor or from the putty (115200 bauds), in a simple way, since it is not by reading SCANCODE down, up: 
<ul>
 <li><b>TAB key or F2 key:</b> Display OSD</li> 
 <li><b>Space:</b> Space bar</li>
 <li><b>ENTER:</b> Send ENTER on the ZX81</li>
 <li><b>+:</b> Send ALT_GR</li>
 <li><b>-:</b> Send SHIFT LEFT</li>
 <li><b>.:</b> Send .</li> 
 <li><b>Up:</b> SHIFT + 7 and Kempston Up</li>
 <li><b>Down:</b> SHIFT + 6 and Kempston Down</li>
 <li><b>Right:</b> Kempston right</li>
 <li><b>Left:</b> Kempston left</li>
 <li><b>A..Z, a..z: </b> a..z</li>
 <li><b>0..9: </b> 0..9</li>
</ul>
From the Arduino IDE, this functionality is not allowed, since the serial monitor requires sending the ENTER for each action.


<br><br>
<h1>Options</h1>
The <b>gbConfig.h</b> file options are selected:
 <ul>
  <li><b>use_lib_vga8colors:</b> Forces to use RGB 8-color mode (3 pins). Outputs 8 colors, as opposed to 64 in normal mode (6 pins RRGGBB).</li>   
  <li><b>use_lib_log_serial:</b> Logs are sent by usb serial port</li> 
  <li><b>use_lib_keyboard_poll_milis:</b> The number of polling milliseconds for the keyboard must be specified.</li>
  <li><b>gb_delay_emulate_ms:</b> Milliseconds of waiting for each completed frame.</li>
  <li><b>use_lib_delay_tick_cpu_auto:</b> If set to 1, the CPU autotunes itself to 20 ms per frame.</li>
  <li><b>use_lib_delay_tick_cpu_milis:</b> If use_lib_delay_tick_cpu_auto is set to 0, whatever we define here will be the wait in milliseconds per frame.</li>
  <li><b>FIX_PERIBOARD_NOT_INITING:</b> Solution made by <b>dcrespo3D</b> for initialization on some keyboards.</li>  
 <li><b>use_lib_cvbs_bitluni:</b> If it is active, it does not use VGA code, nor does it generate VGA output. Use the modified CVBS Bitluni library. If it is commented out, use all the VGA code. In the TTGO VGA32 package, pin 26 is being used, that is, the CLK of the PS/2 connector of the mouse.</li>
 <li><b>use_lib_cvbs_bitluni_not_backbuffer:</b> Does not use double buffering in CVBS, saving memory. May cause visual defects (flickering).</li> 
 <li><b>use_lib_cvbs_pal:</b> If it is activated together with use_lib_cvbs_bitluni, the video output will be in PAL standard, if not NTSC.</li>
 <li><b>use_lib_cvbs_ttgo_vga32:</b> The TTGO VGA32 board uses a 5 volt output, instead of 3v. Therefore, said line must be uncommented if the TV output is used, in order to reduce the DAC output to 1 volt.</li>
 <li><b>use_lib_cvbs_ttgo_vga32_bright:</b> If the DAC output on the 5v TTGO VGA32 is very low, activating this option can increase the brightness a bit. Use with care, as the CVBS standard is 1 volt.</li>
 <li><b>use_lib_invert_color_default_value:</b> It allows color inversion, that is, white for black. In CVBS mode, it is inverted by default. Its values are 1 or 0.</li>
 <li><b>use_lib_stats_time_unified</b> Allows you to view serial port traces with fps, as well as current, minimum and maximum microseconds per frame. The same for video.</li>
 <li><b>use_lib_fix_double_precision</b> It doesn't use the VGA video frequency calculation with the ESP32 itself, avoiding possible accuracy problems with the mantissa. This is useful for ESP32's that miscalculate the frequency.</li>
 <li><b>use_lib_debug_i2s</b> Plot with video mode calculations.</li>
 <li><b>use_lib_vga360x200x70hz_bitluni</b> 360x200 video mode with bitluni parameters.</li>
 <li><b>use_lib_vga320x200x70hz_bitluni</b> 320x200 video mode with bitluni parameters.</li>
 <li><b>use_lib_vga320x200x70hz_fabgl</b> 320x200 mode with fabgl parameters.</li>
 <li><b>use_lib_border_x</b> Scrolls the screen in multiples of 4 pixels, useful for 360x200 video mode. Do not exceed a value of 10, as this will overflow the buffer.</li> 
 <li><b>use_lib_keyboard_uart:</b> Allows you to use the PC keyboard from the PC via the VStudio monitor terminal or from putty, without having to have a keyboard. Useful for not having to use the physical PS/2 keyboard and for development.</li>
 </ul> 


<br><br>
<h1>DIY circuit</h1>
If we don't want to use a TTGO VGA32 v1.x board, we can build it following the <b>fabgl</b> schematic:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/fabglcircuit.gif'></center>
In the case of wanting cvbs video output, instead of VGA, we must take a direct cable from pin 26 of the PS/2 connector of the mouse, activating the option <b>use_lib_cvbs_pal</b>, as well as <b>use_lib_cvbs_ttgo_vga32 </b> of the <b>gbConfig.h</b>. If we do not activate this option, the output will be more than 1 volt, having to be reduced with a voltage reducer (potentiometer).
<center><img src='preview/ps2.gif'></center>
The PS/2 connector is seen from the board's own jack, that is, the female jack. The pin on PS/2 is CLK, that is, 5.
<center><img src='preview/ttgops2cvbs.gif'></center>
In this image you can see the internal SOT23 mosfet of the TTGO VGA32 board, so that the output at CLK (pin 5) is 5 volts.
 


<br><br>
<h1>Test DAC cvbs</h1>
For TTGO VGA32 as the output is 5v, either we do voltage reduction or we can reduce the scale of the DAC. At 3.3v output, with a maximum value of 77, it would already give us 0.99v, which would be 1v. If we have 5v output, with 50, we already have 0.97v, which would be 1v. In this way, we no longer need step-down resistors, it is the direct wire. As long as we don't go over 77 in 3.3v or 50 in 5v, we won't have a problem, especially if we only need 2 colors (black and white).
We can do tests with a multimeter, especially on the TTGO VGA32 v1.x:
<pre>
//ESP32 Pin 26
//DAC - Voltaje
//  0 - 0.06
// 38 - 0.52
// 77 - 1
//255 - 3.17

#include <Arduino.h>
#include <driver/dac.h>

const int arrayValue[4]={0,38,77,255};
unsigned char cont=0;

void setup() {
 Serial.begin(115200);
 dac_output_enable(DAC_CHANNEL_2);
}

void loop() {
 dac_output_voltage(DAC_CHANNEL_2, arrayValue[cont]);
 Serial.printf("%d\n",arrayValue[cont]);
 delay(4000);
 cont++;
 cont &= 0x03;
}
</pre>
The maximum values when writing to the video buffer on an ESP32 board is 54, while for TTGO VGA32 v1.x it would be 35.


<br><br>
<h1>Tool p2h</h1>
I have created a very basic tool, to convert .p files to .h in ready mode to be processed by the emulator. We only have to put the .p files in the folder <b>input\pfile</b> and run the file
 <b>p2h.exe</b> file, so that an output will be generated in the <b>dataFlash</b> directory.
 For testing purposes, a file has been left in the <b>pfile</b> directory.
 a new customized list. It is also recommended to delete the files in the <b>MECUMEesp81\dataFlash\pfile</b> directory to have a clean project.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyMCUMEesp81/tree/main/tools'>Tool p2h</a>
<br><br>
<pre>
 input/
  pfile/ 
 output/
  dataFlash/
   pfile/
</pre>
Afterwards we must copy the dataFlash directory into the project <b>TinyMCUMEesp81ttgovga32\MECUMEesp81</b> overwriting the previous dataFlash folder.It is recommended to clean the project and recompile.<br>
This tool is very simple, and does not control errors, so it is recommended to leave the files with very simple names and as simple as possible. 
simple names and as simple as possible.<br>
The project in PLATFORM.IO is prepared for 2 MB of Flash.
If we need the 4MB of flash, we will have to modify the entry in the <b>platformio.ini</b> file.
<pre>board_build.partitions = huge_app.csv</pre>
In the Arduino IDE, we must choose the <b>Partition Scheme (Huge APP)</b> option.
