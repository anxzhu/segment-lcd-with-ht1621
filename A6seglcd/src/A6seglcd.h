/*********************************************************************
This is a library for 6 segments lcd based on ht1621 drivers

  You can download all the source file at
  ------> https://www.github.com/anxzhu

Written by anxzhu@qq.com   for OCROBOT.  
MIT license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/
#ifndef  A6SEGLCD_H_
#define A6SEGLCD_H_   //防止重复包含

#define  BIAS     0x52             //0b1000 0101 0010  1/3duty 4com
#define  SYSDIS   0X00             //0b1000 0000 0000  关振系统荡器和LCD偏压发生器
#define  SYSEN    0X02             //0b1000 0000 0010 打开系统振荡器
#define  LCDOFF   0X04             //0b1000 0000 0100  关LCD偏压
#define  LCDON    0X06             //0b1000 0000 0110  打开LCD偏压
#define  XTAL     0x28             //0b1000 0010 1000 外部接时钟
#define  RC256    0X30             //0b1000 0011 0000  内部时钟
#define  TONEON   0X12             //0b1000 0001 0010  打开声音输出
#define  TONEOFF  0X10             //0b1000 0001 0000 关闭声音输出
#define  WDTDIS1  0X0A             //0b1000 0000 1010  禁止看门狗

class  a6seglcd
{
public:
	int cs;
	int wr;
	int dat;
	int backlight;
	a6seglcd();
	void run(int cs, int wr, int dat,int backlight);
	void conf();//
	void clr();//
	void display(unsigned char addr, unsigned char sdata);//
	void backlighton();//
	void backlightoff();//
	void wrone(unsigned char addr, unsigned char sdata);
	void wrclrdata(unsigned char addr, unsigned char sdata);
	void wrCLR(unsigned char len);
	void wrDATA(unsigned char data, unsigned char cnt);
	void wrCMD(unsigned char CMD);
	void bat1();
	void bat1off();
	void bat2();	
	void bat2off();
	void bat3();
	void bat3off();
	void dispnum(float num);
	void lcdon();
	void lcdoff();
private:
	int _cs;
	int _wr;
	int _dat;
	int _backlight;
};
#endif