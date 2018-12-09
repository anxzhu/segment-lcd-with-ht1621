# HT1621 7 segment LCD Arduino library
Arduino library for 7-segment lcds based on the HT1621 driver.

Based on the bitbanging efforts by [anxzhu](https://github.com/anxzhu) (2016-2018).  
APIs rewritten in 2018 to follow the LiquidCrystal format by [valerio\new](https://github.com/5N44P).

## APIs

* `void begin(int cs_p, int wr_p, int data_p,[int backlight_p])`  
Starts the lcd with the pin assignement declared. The backlight pin is optional

* `void clear()`
* `void backlighton()`
* `void backlightoff()`
* `void battlevel(int level)`
* `void print(long num)`
* `void print(float num)`
* `void print(float num, int precision)`
* `void display()`
* `void noDisplay()`



## Internal functioning

° -> 0x33 = 10 + 20 + 01 + 02  
C -> 0x1D = 10 + 01 + 04 + 08

```
  ___10___
 |        |
 01       20
 |___02___|
 |        |
 04       40
 |___08___|

```

