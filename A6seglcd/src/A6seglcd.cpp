/*********************************************************************
This is a library for 6 segments lcd based on ht1621 drivers

  You can download all the source file at
  ------> https://www.github.com/anxzhu

*********************************************************************/

#include <Arduino.h>
#include "A6seglcd.h"
#include "floatToString.h"
#include "stdio.h"
unsigned char battery[3];
a6seglcd::a6seglcd()
{
}                           
void a6seglcd::run(int cs,int wr,int dat,int backlight)
{
	pinMode(cs, OUTPUT);
	pinMode(wr, OUTPUT);
	pinMode(dat, OUTPUT);
	pinMode(backlight, OUTPUT);
	_cs=cs;
	_wr=wr;
	_dat=dat;
	_backlight=backlight;
}
void a6seglcd::wrDATA(unsigned char data, unsigned char cnt) {
	unsigned char i;
	for (i = 0; i < cnt; i++) {
		digitalWrite(_wr, LOW);
		delayMicroseconds(4);
		if (data & 0x80) {
			digitalWrite(_dat, HIGH);
		}
		else
		{
			digitalWrite(_dat, LOW);
		}
		digitalWrite(_wr, HIGH);
		delayMicroseconds(4);
		data <<= 1;
	}
}
void a6seglcd::wrclrdata(unsigned char addr, unsigned char sdata)
{
	addr <<= 2;
	digitalWrite(_cs, LOW);
	wrDATA(0xa0, 3);
	wrDATA(addr, 6);
	wrDATA(sdata, 8);
	digitalWrite(_cs, HIGH);
}

void a6seglcd::lcdon()
{
	wrCMD(LCDON);
}

void a6seglcd::lcdoff()
{
	wrCMD(LCDOFF);
}

void a6seglcd::wrone(unsigned char addr, unsigned char sdata)
{
	addr <<= 2;
	digitalWrite(_cs, LOW);
	wrDATA(0xa0, 3);
	wrDATA(addr, 6);
	wrDATA(sdata, 8);
	digitalWrite(_cs, HIGH);
}
void a6seglcd::backlighton()
{
	digitalWrite(_backlight, HIGH);
	delay(1);
}
void a6seglcd::backlightoff()
{
	digitalWrite(_backlight, LOW);
	delay(1);
}
void a6seglcd::wrCMD(unsigned char CMD) {  //100
	digitalWrite(_cs, LOW);
	wrDATA(0x80, 4);
	wrDATA(CMD, 8);
	digitalWrite(_cs, HIGH);
}
void a6seglcd::conf()
{
	wrCMD(BIAS);
	wrCMD(RC256);
	wrCMD(SYSDIS);
	wrCMD(WDTDIS1);
	wrCMD(SYSEN);
	wrCMD(LCDON);
	
}
void a6seglcd::wrCLR(unsigned char len) {
	unsigned char addr = 0;
	unsigned char i;
	for (i = 0; i < len; i++) {
		wrclrdata(addr, 0x00);
		addr = addr + 2;
	}
}
void a6seglcd::bat1() {  //电池顶
	battery[0]=0x80;//wrone(10, 0x80);// c.bat3();//电池底部
}
void a6seglcd::bat1off() {  //电池顶
	battery[0]=0x00; //wrone(10, 0x80);// c.bat3();//电池底部
}
void a6seglcd::bat2() {  //电池中
	battery[1]=0x80;//wrone(8, 0x80);
}
void a6seglcd::bat2off() {  //电池中
	battery[1]=0x00;//wrone(8, 0x80);
}
void a6seglcd::bat3() {  //电池底
	battery[2]=0x80;//wrone(6, 0x80);
}
void a6seglcd::bat3off() {  //电池中
	battery[2]=0x00;//wrone(6, 0x80);
}
void a6seglcd::clr(){
	
	wrCLR(16);
	
}
void a6seglcd::display(unsigned char addr, unsigned char sdata){
	
	wrone(addr,sdata);
}
void a6seglcd::dispnum(float num){//传入显示的数据，最高位为小数点和电量显示，显示数据为0.001-99999.9
	char buffer1[12];//
	
	floatToString(buffer1,num,4);
	String buffer=buffer1;
	int dpposition;
	dpposition=buffer.indexOf('.');//寻找小数点位置  取前七位 因为最多显示七位
	//为6  整数 如123456.
	//5    一位小数 12345.6
	//4    两位小数 1234.56
	//3    三位小数 123.456
	//2    三位小数 12.345
	//1    三位小数 1.234
	//unsigned char lednum[10]={0x7D,0x60,0x3E,0x7A,0x63,0x5B,0x5F,0x70,0x7F,0x7B};//显示 0 1 2 3 4 5 6 7 8 9
	unsigned  int i;
	for(i=0;i<7;i++){
		
		if(buffer[i]=='0'){
			buffer[i]=0x7D;
		}
		else if(buffer[i]=='1') {
			buffer[i]=0x60;
		}
		else if (buffer[i]=='2'){
			buffer[i]=0x3e;
		}
		else if (buffer[i]=='3'){
			buffer[i]=0x7a;
		}
		else if(buffer[i]=='4') {
			buffer[i]=0x63;
		}
		else if(buffer[i]=='5') {
			buffer[i]=0x5b;
		}else if(buffer[i]=='6') {
			buffer[i]=0x5f;
		}
		else if (buffer[i]=='7'){
			buffer[i]=0x70;
		}
		else if (buffer[i]=='8'){
			buffer[i]=0x7f;
		}
		else if (buffer[i]=='9'){
			buffer[i]=0x7b;
		}
		else if (buffer[i]=='.'){
			buffer[i]=0xff;
		}
	}
	switch  (dpposition){
	case  6:
		wrone(0,buffer[5]);//123456.
		wrone(2,buffer[4]);
		wrone(4,buffer[3]);
		wrone(6,buffer[2]|battery[2]);
		wrone(8,buffer[1]|battery[1]);
		wrone(10,buffer[0]|battery[0]);
		break;
	case  5:
		wrone(0,(buffer[6]|0x80));//12345.6
		wrone(2,buffer[4]);
		wrone(4,buffer[3]);
		wrone(6,buffer[2]|battery[2]);
		wrone(8,buffer[1]|battery[1]);
		wrone(10,buffer[0]|battery[0]);
		break;
	case  4:
		wrone(0,buffer[6]);//1234.56
		wrone(2,(buffer[5]|0x80));
		wrone(4,buffer[3]);
		wrone(6, buffer[2]|battery[2]);//
		wrone(8,buffer[1]|battery[1]);
		wrone(10,buffer[0]|battery[0]);
		break;
	case  3:
		wrone(0,buffer[6]);//123.456
		wrone(2,buffer[5]);
		wrone(4,(buffer[4]|0x80));
		wrone(6,buffer[2]|battery[2]);
		wrone(8,buffer[1]|battery[1]);
		wrone(10,buffer[0]|battery[0]);
		break;
		
	case  2:
		wrone(0,buffer[5]);//12.345
		wrone(2,buffer[4]);
		wrone(4,(buffer[3]|0x80));
		wrone(6,buffer[1]|battery[2]);
		wrone(8,buffer[0]|battery[1]);
		wrone(10,0x00|battery[0]);
		break;
	case  1:
		wrone(0,buffer[4]);//1.234
		wrone(2,buffer[3]);
		wrone(4,(buffer[2]|0x80));
		wrone(6,buffer[0]|battery[2]);
		wrone(8,0x00|battery[1]);
		wrone(10,0x00|battery[0]);
		
		break;
	    default:
		break;
		
	}
	
	
	
	
}
