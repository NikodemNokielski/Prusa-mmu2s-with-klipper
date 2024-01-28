# Prusa-mmu2s-with-klipper
Prusa mmu2s with klipper

1. Install Kiauh:
https://github.com/dw-0/kiauh

2. Using WinSCP copy this file:
https://github.com/dw-0/kiauh/blob/master/resources/gcode_shell_command.py
into direction:
/home/pi/klipper/klippy/extras/gcode_shell_command.py

3. Get python2 and pip2:
https://linux.how2shout.com/how-to-install-python-2-7-on-ubuntu-20-04-lt

4. Install PySerial:
https://pyserial.readthedocs.io/en/latest/pyserial.html#overview

5. Copy this folder:
https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/tree/main/myMacros/MMU2s
to the directory (using WinSCP):
/home/NikodemPrusa/klipper/klippy
 
6. Copy:
https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/blob/main/macros.cfg
into your macros.cfg (add at the end of the file)

7. Change file directory in macros to your file directory fir every file:
/home/NikodemPrusa/klipper/klippy/myMacros/MMU2s/TS0.py

8. Using Arduino Ide compile and load sketches into the MMU (chose arduino Leonardo as a microcontroller).

The system still has a lot of bugs. I have no idea how to change if filament is loaded into the nozzle. Also the buttons are disabled. Sometimes it won't load filament at the start of the print due to the problem with reloading the same filament twice. You also can disabled print pause while filament runout detection to save some time.

Probably i will upload a video later.

![image](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/04858723-99d5-48a9-be44-70bf6a57c24a)

![403626386_1021344292500667_704135952184276242_n](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/d4b7dca7-9e4c-4d6d-8f82-3011242e2e39)

![393132014_1696404574180072_4611702322408807657_n](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/87a3739b-9517-40b5-bd15-508e481a6dd5)

![403636684_1116560659503349_4539307847851425793_n](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/13bc30a3-5061-45a3-8cb7-3a84ff5c55c2)

![403641154_356360843743890_4936173854624341152_n](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/21d8625e-8c80-4b92-b859-e191c210ab27)

![403647244_704005551816145_685969250459773515_n](https://github.com/NikodemNokielski/Prusa-mmu2s-with-klipper/assets/67480958/5073b67b-d83d-4ad9-9de4-5a8527579240)
