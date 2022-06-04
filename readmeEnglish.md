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
  <li>VGA 320x200.</li>
  <li>Uploading of pfiles.</li>
  <li>The complete bitluni library is not required. I have reduced to the minimum, saving RAM and FLASH, based on Ricardo Massaro's library.</li>
  <li>Hi-res and pseudo hi-res mode support.</li>
  <li>The OSD is brought up with the <b>F1</b> key.</li>
  <li>Not all keys are mapped.</li>
 </ul>
 
 
<br>
<h1>Requirements</h1>
Required:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4)</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.1 Espressif32 v3.3.2</li>
  <li>Arduino IDE 1.8.11</li>
  <li>Arduino fabgl 0.9.0 reduced library (included in PLATFORMIO project)</li>
  <li>Arduino bitluni 0.3.3 reduced library (included in project)</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/ttgovga32v12.jpg'></center> 
<br>

<h1>PlatformIO</h1>
PLATFORMIO 2.2.1 must be installed from the Visual Studio extensions. Espressif32 v3.3.2 is also required.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewPlatformIOinstall.gif'></center>
Then the working directory <b>TinyMCUMEesp81ttgovga32</b> will be selected.
We must modify the <b>platformio.ini</b> file the <b>upload_port</b> option to select the COM port where we have our TTGO VGA32 board.
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


<br>
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
 </ul> 


<br><br>
<h1>DIY circuit</h1>
If we don't want to use a TTGO VGA32 v1.x board, we can build it following the <b>fabgl</b> schematic:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/fabglcircuit.gif'></center>


<br><br>
<h1>Tool p2h</h1>
He creado una herramienta muy básica, para convertir los archivos .p en .h en modo lista para ser procesados por el emulador. We only have to put the .p files in the folder <b>input\pfile</b> and run the file
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
