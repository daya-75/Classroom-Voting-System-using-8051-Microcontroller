#include <reg51.h>
sbit sw1= P0^0;
sbit sw2= P0^1;
sbit rs=P2^0;
sbit rw=P2^1;
sbit e=P2^2;
sbit reset = P0^3;
sbit pause = P0^2;
void WriteCommandToLCD(unsigned char);
void WriteStringToLCD(unsigned char ch[]);
void WriteDataToLCD(unsigned char);
void WriteData1ToLCD(unsigned char);
void delay(unsigned int);
void main()
{
unsigned int num1 = 0, num2 = 0, total = 0, i = 0, sum = 0;
	bit paused = 0;
	WriteCommandToLCD(0x38); 
  WriteCommandToLCD(0x01); 
	WriteCommandToLCD(0x0C); 
	WriteCommandToLCD(0x80);
	WriteCommandToLCD(0x06);
  WriteStringToLCD("WELCOME TO ");
	WriteCommandToLCD(0xc0);
	WriteStringToLCD("ELECTIONS");
	delay(20);
	P3=0x00;
	
	sw1=0;
	sw2=0;
	total=P3;
	delay(10);
			WriteCommandToLCD(0x01);
	  WriteCommandToLCD(0x80);
	  WriteStringToLCD("total voters = ");
	  WriteCommandToLCD(0xc0);
		WriteDataToLCD((total / 100) + 48);  
    WriteDataToLCD(((total / 10) % 10) + 48); 
    WriteDataToLCD((total % 10) + 48);
		delay(40);
	while(1)
	{
		if(pause == 1)
{
    paused = !paused;  // Toggle pause state
    delay(200);        // Debounce
}

if(paused)
{
    WriteCommandToLCD(0x01);
    WriteCommandToLCD(0x80);
    WriteStringToLCD("ELECTION PAUSED");
    delay(50);
    continue; // Skip rest of the loop
}
if(reset == 1)
{
    // Reset all variables
    num1 = 0;
    num2 = 0;
    sum = 0;
    paused = 0;

    WriteCommandToLCD(0x01);
    WriteCommandToLCD(0x80);
    WriteStringToLCD("RESETTING...");
    delay(50);

    // Restart voting intro
    WriteCommandToLCD(0x01); 
    WriteCommandToLCD(0x80);
    WriteStringToLCD("WELCOME TO ");
    WriteCommandToLCD(0xC0);
    WriteStringToLCD("ELECTIONS");
    delay(40);

    continue; 
}
			P3=0x00;
	total=P3;
	delay(10);

	if(sw1==1 && sw2==0)
	 {
		 num1=num1+1;
		 delay(20);
	 }
	 else if(sw1==0 && sw2==1)
	 {
		 num2=num2+1;
		  delay(20);
	 }
	 else if(sw1==1 && sw2==1)
	 {
		 num1=num1+1;
		  delay(20);
		 num2=num2+1;
		  delay(20);
	 }
	 WriteCommandToLCD(0x01);
	 WriteCommandToLCD(0x80);
		
	 WriteCommandToLCD(0x06);
  WriteStringToLCD("stud1 vote = ");
   WriteData1ToLCD((num1 / 100) + 48);  
    WriteData1ToLCD(((num1 / 10) % 10) + 48); 
    WriteData1ToLCD((num1 % 10) + 48);
	 WriteCommandToLCD(0xc0);
	 WriteStringToLCD("stud2 vote = ");
   WriteData1ToLCD((num2 / 100) + 48);  
    WriteData1ToLCD(((num2 / 10) % 10) + 48); 
    WriteData1ToLCD((num2 % 10) + 48);
		sum=num1+num2;
		if(sum>=total)
		{
				 WriteCommandToLCD(0x01);
	 WriteCommandToLCD(0x80);
				 WriteCommandToLCD(0x06);
			WriteStringToLCD("RESULT");
			if(num1>num2){
				 WriteCommandToLCD(0xc0);
				 WriteStringToLCD("WINNER->>stud1");
			}else{
				 WriteCommandToLCD(0xc0);
				 WriteStringToLCD("WINNER->>stud2");
			}
				
			delay(40);
			break;
		}
		
//	 delay(20);
	}
	while(1);
//}
}
void delay(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	for(j=0;j<1275;j++);
}
	
void WriteCommandToLCD(unsigned char ch) 
{
	e=1; 
	rs=0;
	rw=0;
	P1=ch;
	e=0;
	delay(5);
}
void WriteDataToLCD(unsigned char ch)
{
	e=1;
	rs=1;
	rw=0;
	P1=ch;
	e=0;
	delay(20);
}
void WriteData1ToLCD(unsigned char ch)
{
	e=1;
	rs=1;
	rw=0;
	P1=ch;
	e=0;
	delay(50);
}
void WriteStringToLCD(unsigned char ch[]) 
{
	 int i;
	 for(i=0;ch[i]!='\0';i++)
	{
	    WriteDataToLCD(ch[i]);
	}
}
