# Portenta Tests

A collection of sketches made to test out features of the recent Arduino Portenta H7 board. Brief documentation is included within each ``.ino`` file. Oscilloscope captures and schematics are included in folders labeled *docs* for each project.

Main purpose of the repository is to serve as preliminary research to advance the PONIRS project.

Feel free to compile, upload, and reproduce results for further verification.

Suggestions are welcome.

## To execute
### Arduino IDE (version 1.8.13) on Windows
Open ``.ino`` files with the ``Arduino IDE`` (v1.8.13 was used as of this writing).
1. Install the **Arduino mbed-enabled Boards** library
   - Tools -> Board -> Boards Manager
   - Search *mbed* or *Portenta H7*
2. Select board and core
   - Tools -> Board -> Arduino Mbed OS Boards -> M7 Core
3. Select COM port
   - Tools -> Port -> COM#
4. Click the checkmark :heavy_check_mark: to *Compile* or *Verify*
5. Click on the arrow pointing left :arrow_right: to *Upload* or *Flash* firmware to board.

### Arduino Pro IDE (version Alpha 0.1.3) on Linux
Open ``.ino`` files with the ``Arduino Pro IDE``
1. Install the **Arduino mbed-enabled Boards** library
   - Tools -> Board -> Boards Manager
   - Search *mbed* or *Portenta H7*
2. Select board and core
   - Drop down menu
      - Arduino Portenta H7 (M7 core) at */dev/ttyACM#*
3. Click the checkmark :heavy_check_mark: to *Compile* or *Verify*
4. Click on the arrow pointing right :arrow_right: to *Upload* or *Flash* firmware to board.

## Troubleshooting
Portenta does not receive firmware.
 - Hit the reset button twice to set board in *Bootloader* mode. Onboard LED will blink GREEN multiple times.

Portenta is not detected by Arduino IDE or computer.
 - Disconnect any jumper wires from board (isolate board from everything)
 - Make sure device is found by ``Device Manager`` or ``lsusb`` (Linux)
 - Make sure **USB Type-C** cable is usable for data transfer

## Notes
  - To flash to the **M4** core:
     1.  Write to M7 to start M4 clocks
          - ``LL_RCC_ForceCM4Boot();          // bootM4() is an alias as well``
     2. Follow the steps above for preferred IDE/environment
     3. Select M4 core accordingly.

  - Installing ``Arduino IDE`` or ``Arduino Pro IDE`` is beyond the scope of this doc.
  - Arudino IDEs uses ``dfu-util``or **Device Firmware Upgrade Utilities** to flash the board.
      - For more info on this awesome tool see: [dfu-util Homepage](http://dfu-util.sourceforge.net/)

## To do
- Keep posting and maintain organization of repo
- Some SPI peripheral play (in the future :smile:)
