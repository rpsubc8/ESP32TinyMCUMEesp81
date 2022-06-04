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
  
