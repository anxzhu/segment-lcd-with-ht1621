
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