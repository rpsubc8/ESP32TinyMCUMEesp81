# Tiny MCUME esp81
Modificación del emulador MCUME zx81 (Jean MarcHarvengt) a la placa TTGO VGA32 v1.0, v1.1, v1.2 y v1.4 con ESP32.
<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewManicMiner.gif'></center>
He realizado varias modificaciones:
<ul> 
 <li>No se usa PSRAM, funcionando en ESP32 de 520 KB de RAM (TTGO VGA32 v1.x)</li> 
 <li>Uso de un sólo core</li>
 <li>OSD de bajos recursos</li>
 <li>Creado proyecto compatible con Arduino IDE y Platform IO</li> 
 <li>Se puede usar cualquier pin digital para el video (hardware.h)</li> 
 <li>Menú de velocidad de video de emulación, VGA, teclado</li>
 <li>Soporte para modo 64 colores.</li>    
 <li>VGA 320x200</li>
 <li>Carga de ficheros pfiles</li>
 <li>No se requiere la libreria de bitluni completa. He reducido a lo mínimo, ahorrando RAM y FLASH, basado en la librería de Ricardo Massaro</li> 
 <li>Soporte modo Hi-res y pseudo hi-res</li> 
 <li>El OSD se saca con la tecla <b>F1</b></li>
 <li>No están todas las teclas mapeadas</li> 
</ul>

<br><br>
<h1>Modo Hi-res</h1>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyMCUMEesp81/main/preview/previewMetropolis.gif'></center>
