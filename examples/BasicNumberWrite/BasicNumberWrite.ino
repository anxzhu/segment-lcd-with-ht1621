  #include <HT1621.h> //库
  HT1621 lcd;            
  void setup()
  {
  lcd.begin(4,5,6,10);   //定义 cs wr data led+这几个管脚 difine  cs  write data   backlight  pins  
  lcd.backlighton();   //开背光（关背光是 backlightoff() ） backlight
  lcd.conf();          //配置 config
  lcd.clr();           //清屏 clearscreen
  }
  void loop()
  {
  delay(20);          // 稳定 stability
  lcd.dispnum(3.141); //要显示的数值 the number you want to display
  lcd.bat1();         //开电池电量显示,一共三格电 关闭电量显示是 bat1off()  battery display
  lcd.bat2();         //同bat2off()
  lcd.bat3();         //同bat3off()
  //lcd.lcdon()       lcd显示开  lcd on 
  //lcd.lcdoff()      lcd显示关  为了省电应该同时关闭背光 
  }
