/*******************************************************************************
Copyright 2016-2018 anxzhu (github.com/anxzhu)
Copyright 2018 Valerio Nappi (github.com/5N44P) (changes)
Based on segment-lcd-with-ht1621 from anxzhu (2016-2018)
(https://github.com/anxzhu/segment-lcd-with-ht1621)

Partially rewritten and extended by Valerio Nappi (github.com/5N44P) in 2018

This file is part of the HT1621 arduino library, and thus under the MIT license.
More info on the project and the license conditions on :
https://github.com/5N44P/ht1621-7-seg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false) {
	int digit;
	float tens = 0.1;
	int tenscount = 0;
	int i;
	float tempfloat = value;
	int c = 0;
	int charcount = 1;
	int extra = 0;
	float d = 0.5;
	if (value < 0)
	d *= -1.0;
	for (i = 0; i < places; i++)
	d/= 10.0;
	tempfloat +=  d;
	if (value < 0)
	tempfloat *= -1.0;
	while ((tens * 10.0) <= tempfloat) {
		tens *= 10.0;
		tenscount += 1;
	}
	if (tenscount > 0)
	charcount += tenscount;
	else
	charcount += 1;
	if (value < 0)
	charcount += 1;
	charcount += 1 + places;
	minwidth += 1;
	if (minwidth > charcount){
		extra = minwidth - charcount;
		charcount = minwidth;
	}
	if (extra > 0 and rightjustify) {
		for (int i = 0; i< extra; i++) {
			outstr[c++] = ' ';
		}
	}
	if (value < 0)
	outstr[c++] = '-';
	if (tenscount == 0)
	outstr[c++] = '0';
	for (i=0; i< tenscount; i++) {
		digit = (int) (tempfloat/tens);
		itoa(digit, &outstr[c++], 10);
		tempfloat = tempfloat - ((float)digit * tens);
		tens /= 10.0;
	}
	if (places > 0)
	outstr[c++] = '.';
	for (i = 0; i < places; i++) {
		tempfloat *= 10.0;
		digit = (int) tempfloat;
		itoa(digit, &outstr[c++], 10);
		// once written, subtract off that digit
		tempfloat = tempfloat - (float) digit;
	}
	if (extra > 0 and not rightjustify) {
		for (int i = 0; i< extra; i++) {
			outstr[c++] = ' ';
		}
	}
	outstr[c++] = '\0';
	return outstr;
}
