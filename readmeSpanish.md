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
 <li>Soporte para modo 64 colores (DAC 6 bits) y 8 colores (DAC 3 bits).</li>    
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


<br>
<h1>Opciones</h1>
El archivo <b>gbConfig.h</b> se seleccionan las opciones:
<ul> 
 <li><b>use_lib_vga8colors:</b> Obliga a usar RGB modo de 8 colores (3 pines). Saca 8 colores, frente a los 64 del modo normal (6 pines RRGGBB).</li>   
 <li><b>use_lib_log_serial:</b> Se envian logs por puerto serie usb</li> 
 <li><b>use_lib_keyboard_poll_milis:</b> Se debe especificar el número de milisegundos de polling para el teclado.</li> 
 <li><b>gb_delay_emulate_ms:</b> Milisegundos de espera por cada frame completado.</li>
 <li><b>use_lib_delay_tick_cpu_auto:</b> Si está a 1, la CPU se autoajusta a 20 ms por frame.</li>
 <li><b>use_lib_delay_tick_cpu_milis:</b> Si use_lib_delay_tick_cpu_auto está a 0, lo que definamos aqui, será la espera en milisegundos por frame.</li>
 <li><b>FIX_PERIBOARD_NOT_INITING:</b> Solución realizada por <b>dcrespo3D</b> para la inicialización en algunos teclados.</li>
</ul>

<br><br>
<h1>Tool p2h</h1>
He creado una herramienta muy básica, para convertir los archivos .p en .h en modo lista para ser procesados por el emulador. Tan sólo tenemos que dejar los archivos .p en la carpeta <b>input\pfile</b> y ejecutar el archivo <b>p2h.exe</b>, de forma que se generará una salida en el directorio <b>dataFlash</b>. Para pruebas, se ha dejado un archivo en el directorio <b>pfile</b>, que se recomienda borrar en caso de realizar una nueva lista personalizada. También se recomienda borrar los archivos del directorio <b>MECUMEesp81\dataFlash\pfile</b> para tener un proyecto limpio.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyMCUMEesp81/tree/main/tools'>Tool p2h</a>
<br><br>
<pre>
 input/
  pfile/ 
 output/
  dataFlash/
   pfile/
</pre>
Posteriormente debemos copiar el directorio <b>dataFlash</b> en el proyecto <b>TinyMCUMEesp81ttgovga32\MECUMEesp81</b> sobreescribiendo la carpeta dataFlash previa. Se recomienda limpiar el proyecto y volver a compilar.<br>
Esta herramienta es muy simple, y no controla los errores, por lo que se recomienda dejarle los archivos con nombres muy simples y lo más sencillo posible.<br>
El proyecto en PLATFORM.IO está preparado para 2 MB de Flash. Si necesitamos los 4MB de flash, tendremos que modificar la entrada del archivo <b>platformio.ini</b>
<pre>board_build.partitions = huge_app.csv</pre>
En el Arduino IDE, debemos elegir la opción <b>Partition Scheme (Huge APP)</b>.
