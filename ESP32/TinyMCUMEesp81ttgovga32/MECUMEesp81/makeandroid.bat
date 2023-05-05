@echo off
echo Convert ANDROID PROJECT DATA (WIN32)
echo Delete dataFlash (Borrar dataFlash)
pause
echo Process gbrom.h (Procesar gbrom.h)
fart dataFlash\gbrom.h "rom/zx8" "zx8"
ping -n 2 127.0.0.1>nul
echo Copy gbrom.h (Copiar gbrom.h)
copy/Y dataFlash\gbrom.h
ping -n 2 127.0.0.1>nul
echo Copy roms (Copiar roms)
copy/Y dataFlash\rom\*.h
ping -n 2 127.0.0.1>nul

echo Process gbpfile.h (Procesar gbpfile.h)
fart dataFlash\gbpfile.h "pfile/" --remove
ping -n 2 127.0.0.1>nul
echo Copy gbpfile.h (Copiar gbpfile.h)
copy/Y dataFlash\gbpfile.h
ping -n 2 127.0.0.1>nul
echo Copy pfiles (Copiar pfiles)
copy/Y dataFlash\pfile\*.h
ping -n 2 127.0.0.1>nul

echo Process MECUMEesp81.ino (Procesar MECUMEesp81.ino)
fart MECUMEesp81.ino "dataFlash/gbrom.h" "gbrom.h"
ping -n 2 127.0.0.1>nul
fart MECUMEesp81.ino "dataFlash/gbpfile.h" "gbpfile.h"
ping -n 2 127.0.0.1>nul

echo Process zx81.cpp (Procesar zx81.cpp)
fart zx81.cpp "dataFlash/gbrom.h" "gbrom.h"
ping -n 2 127.0.0.1>nul

echo Delete dataFlash (Borrar dataFlash)
rmdir /S /Q dataFlash
pause