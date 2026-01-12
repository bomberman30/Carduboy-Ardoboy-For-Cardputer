#pragma once
#include <SD.h>
#include <FS.h>
#include <SPI.h>

/* ===== SD pins ===== */
#define SD_SCK 40
#define SD_MISO 39
#define SD_MOSI 14
#define SD_CS 12

#define EEPROM_DIR "/EEPROM_TO_SD_FILES"
#define EEPROM_SIZE 2048 // שנה לפי הצורך

class EESPROM_TO_SD
{
public:
    int AppID = 0;
    bool haveSDcard = false;

    EESPROM_TO_SD() {}
    ~EESPROM_TO_SD() {}

    void begin(int AppID_For_Save);
    void commit();

    template <typename T>
    void put(uint32_t address, const T &data);

    template <typename T>
    void get(uint32_t address, T &data);

    void write(uint32_t address, uint8_t data);
    uint8_t read(uint32_t address);

private:
    String filePath();
    bool BufferEmpty = true;
    uint8_t buffer[EEPROM_SIZE];
    bool dirty = false;
};

/* ===== global instance ===== */
inline EESPROM_TO_SD EEPROM;

/* ===== begin ===== */
inline void EESPROM_TO_SD::begin(int AppID_For_Save)
{
    AppID = AppID_For_Save;

    SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD mount failed");
        haveSDcard = false;
        return;
    }

    haveSDcard = true;
    if (!SD.exists(EEPROM_DIR))
    {
        SD.mkdir(EEPROM_DIR);
    };

    if (!SD.exists(filePath()))
    {
        File f = SD.open(filePath(), FILE_WRITE);
        f.close(); // create empty file
        BufferEmpty = true;
    }

    // טען קובץ ל־RAM
    File f = SD.open(filePath(), FILE_READ);
    if (f)
    {
        size_t len = min((size_t)EEPROM_SIZE, (size_t)f.size());
        f.read(buffer, len);
        f.close();
        if (len == 0)
        {
            BufferEmpty = true;
        }
        else
        {
            BufferEmpty = false;
        }
    }
    else
    {
        memset(buffer, 0, EEPROM_SIZE);
        BufferEmpty = true;
    }
}

/* ===== commit ===== */
inline void EESPROM_TO_SD::commit()
{
    if (!haveSDcard || !dirty)
        return;

    File f = SD.open(filePath(), FILE_WRITE);
    if (!f)
        return;

    f.seek(0);
    f.write(buffer, EEPROM_SIZE);
    f.close();

    dirty = false;
}

/* ===== EEPROM.write (byte) ===== */
inline void EESPROM_TO_SD::write(uint32_t address, uint8_t data)
{
    if (address >= EEPROM_SIZE)
        return;

    buffer[address] = data;
    dirty = true;
}

/* ===== EEPROM.read (byte) ===== */
inline uint8_t EESPROM_TO_SD::read(uint32_t address)
{
    if (address >= EEPROM_SIZE)
        return 0;
    if (BufferEmpty)
    {
        return 0;
    }
    return buffer[address];
}

/* ===== EEPROM.put ===== */
template <typename T>
void EESPROM_TO_SD::put(uint32_t address, const T &data)
{
    if (BufferEmpty)
    {
        return;
    }
    if (address + sizeof(T) > EEPROM_SIZE)
        return;

    memcpy(&buffer[address], &data, sizeof(T));
    dirty = true;
}

/* ===== EEPROM.get ===== */
template <typename T>
void EESPROM_TO_SD::get(uint32_t address, T &data)
{
    if (address + sizeof(T) > EEPROM_SIZE)
    {
        memset(&data, 0, sizeof(T));
        return;
    }

    memcpy(&data, &buffer[address], sizeof(T));
}

/* ===== filePath ===== */
inline String EESPROM_TO_SD::filePath()
{
    return String(EEPROM_DIR) + "/app_" + String(AppID) + ".txt";
}
