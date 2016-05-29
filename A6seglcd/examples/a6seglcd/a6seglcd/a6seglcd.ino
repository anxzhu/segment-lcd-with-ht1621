  #include <A6seglcd.h> //库
  a6seglcd lcd;         //   
  void setup()
  {
  lcd.run(4,5,6,10);   //定义  cs（片选）  write（写） data（数据）   backlight（背光） 这 4个引脚  （vcc  gnd 接arduino的 vcc  gnd）
  lcd.backlighton();   //开背光（关背光是 backlightoff() ）
  lcd.conf();          //配置 偏压  输出
  lcd.clr();           //清屏
  }
  void loop()
  {
  delay(20);          // 稳定 stable
  lcd.dispnum(0.123);  //要显示的数值the number you want to diaplay
  lcd.bat1();         //开电池电量显示,一共三格电 关闭电量显示是 bat1off()   ,for battery display,  same to bat1off()
  lcd.bat2();         //bat2off()
  lcd.bat3();         //bat3off()
   
  }
