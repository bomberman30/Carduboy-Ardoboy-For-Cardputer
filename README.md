# Carduboy-Ardoboy-For-Cardputer
A modified Arduboy games library for the Cardputer, allowing you to play Arduboy games on Cardputer and ADV.
EEPROM saves are converted to SD‑card saves.
All required libraries are included in the lib folder.
Note: In some games, music may not work. (arduboy Tone or Playtone not compatible with esp32.  i don't think i can code it. they are in lib folder just to not break the code)

# How To Play?
Copy the game files from "bin_output" directory to your SD card and install the bin files via Bruce Launcher APP (you can install launcher via M5Burner or web flash see more info https://github.com/bmorcelli/Launcher)


# Keys
- Arrow keys: movement
- Z and X: Arduboy A and B buttons
- 1: change color
- +: volume up
- –: volume down


# why EEPROM_TO_SD
I created this library because I don’t use the default EEPROM implementation on the ESP32.
On the ESP32, “EEPROM” is actually stored in flash memory, and whenever you flash a new game, all the saved data gets erased.
To avoid losing game saves, every EEPROM write that an Arduboy game performs is redirected to the SD card instead, where the data is stored permanently.

# License

+  Each game has its own license — check it before using it in your project.
+ you can freely play in the games in personal use only


# dependency
+ M5GFX : MIT https://github.com/m5stack/M5GFX
+ M5Unified : MIT https://github.com/m5stack/M5Unified
