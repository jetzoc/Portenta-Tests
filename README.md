# Portenta Tests

A collection of sketches made to test out features of the recent Arduino Portenta H7 board. Brief documentation is included with each ``.ino`` files. 

Main purpose of the repository is to serve as preliminary research to advance the PONIRS project.

Feel free to compile, upload and reproduce results for further verification.

Suggestions are welcome. 

## To execute 
Open ``.ino`` files with the ``Arduino IDE `` (v1.8.13 was used as of this writing). 
1. Install the **Arduino mbed-enabled Boards** library
   - Tools -> Board -> Boards Manager 
   - Search *mbed* or *Portenta H7*
2. Select board and core
   - Tools -> Board -> Arduino Mbed OS Boards -> M7 Core
3. Select COM port
   - Tools -> Port -> COM#
4. Click the checkmark to *Compile* or *Verify*
5. Click on the arrow pointing left to *Upload* or *Flash* firmware to board. 

## Troubleshooting
Portenta does not recieve firmware.
 - Hit the reset button twice to set board in *Bootloader* mode. Onboard LED will blink GREEN multiple times. 

## To do
- Keep posting and maintain organization of repo
- Some SPI peripheral play (in the future :smile:)

