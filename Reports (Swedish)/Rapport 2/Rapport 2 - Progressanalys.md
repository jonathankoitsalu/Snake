# i2c Snake med online highscore

# PROGRESSRAPPORT

Av Jonathan Koitsalu, Ahmed Alhasani, Daniel Johansson, William  Hansen

## Table of Contents

[TOC]

## Systemskiss och Kretschema

![](https://i.imgur.com/HL31Gf9.png)


## SystemÄndringar

* Display:

Prototypen skulle byggas på adafruits LCD OLED display([LCD OLED 0.96″ 128×64 SPI/I2C](https://www.electrokit.com/produkt/lcd-oled-0-96-128x64/).
Efter studie av datablad och adafruits displaybibliotek anses utvecklingen av ett nytt c bibliotek för denna display för tidskrävande för fullbordandet av dom önskade målen. 
Ett alternativ har hittats i "sizable":s OLED display (https://sizable.se/P.LZ7/0.96%22-i2c-oled-vit) med ett tillhörande C bibliotek (https://github.com/Matiasus/SSD1306) som enklare kan anpassas för projektets ändamål. Gruppen har därmed kommit överens om att byta till denna skärm.

* WiFi:

För att koppla upp snake spelet till webservern vill gruppen använda sig av "AT-kommandon" (https://www.electronicshub.org/esp8266-at-commands/#Basic_ESP8266_AT_Commands) som, vid aktivering, skickar meddelanden från arduino-uart till esp01s WiFi-modul (https://www.kjell.com/se/produkter/el-verktyg/arduino/moduler/wifi-modul-for-arduino-esp8266-p87947). För närvarande finns funktion för att skicka AT-kommandon med en score upp till webservern. Nästa steg som är under implementering är att göra detta med hjälp av egenbyggd uart-kod som körs på arduinon.

Om det skulle behövas kan en ESP32 användas med kod som hämtar in uart-meddelanden och skickar dessa vidare med hjälp av WiFi- och HTTP bibliotek. Detta kommer endast användas om gruppen stöter på några problem med AT-kommandon.


## Kod

var god se bifogad kod.

## Nytt Tidsestimat

![](https://i.imgur.com/tYNJgSR.png)

![](https://i.imgur.com/dXXShx4.png)

![](https://i.imgur.com/76o3lC9.png)

![](https://i.imgur.com/R3LLUK7.png)

![](https://i.imgur.com/LxebTtz.png)


## Nya Avgränsningar

* Bibliotek:

Efter närmare studie av datablad och displaybiliotek så beslutas att arbeta med ett displaybibliotek som inte tillhör adafruit då det är mer lätthanterligt och på så sätt går att anpassa för projektets ändamål. Tankar om att smida ett eget bibliotek finns men tacklas i så fall efter att en fungerande snakePrototyp fåtts ihop.


## Tester

### Fullbordade tester

* Display: testa C bibliotek mot display.
* Kommunikation:
    * AT-kommandon från Arduino till ESP01s(WiFi modul) som skickar data till webserver.
    * ESP32 med 3:e parts bibliotek skickar data till webserver.

### Återstående tester

* kommunikation:

    * Skicka requests från arduino till webserver med egen uart implementation för att ändra hemsidans high score.

    * Skicka kommandon från webbsidan till arudino för att ändra spelkonfigurationer.



* knappar: Testa 5 interruptstyrda knappar.

* snake: 
    * Testa snakemeny
    * Testa snakespelets funktionalitet lokalt
    * testa Highscore lokalt på displayen och mot hemsidan











