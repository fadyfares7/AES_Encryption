#include <stdio.h>
#include <time.h>
void ByteToWordV();
void ByteToWordH();
void WordVToByte();
void WordHToByte();
void printByteArray();
void printVWordArray();
void printHWordArray();
void keyExpansion();
unsigned long SubWord(unsigned long x,int i);
unsigned char input[16];
int n=1,m=1,TestCounter,CasesCounter;
unsigned long inputW_Vertical[4];
unsigned long inputW_Horizontal[4];
unsigned long ExpandedKey[44];
const unsigned char RC[10]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36};
const unsigned char Substitute [16][16]={
	{0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
	{0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
	{0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
	{0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
	{0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
	{0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
	{0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
	{0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
	{0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
	{0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
	{0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
	{0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
	{0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
	{0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
	{0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
	{0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
};
clock_t start;
clock_t end;
int main(void)
{
	
int i;
int RoundCounter=0;
scanf_s("%d",&n);
for(CasesCounter=0;CasesCounter<n;CasesCounter++)
{
//taking input into word array
	for(i=0;i<4;i++)
	{
		scanf_s("%8x",&inputW_Vertical[i]);
		
	}

	//taking key into word array
	for(i=0;i<4;i++)
	{
		scanf_s("%8x",&ExpandedKey[i]);
	}
	
	scanf_s("%d",&m);
	
//start calculations 
	start = clock() ;

	keyExpansion();
	for(TestCounter=0;TestCounter<m;TestCounter++)
	{
	RoundCounter=0;
//Add Round key
	inputW_Vertical[0]=inputW_Vertical[0]^ExpandedKey[RoundCounter*4];
	inputW_Vertical[1]=inputW_Vertical[1]^ExpandedKey[RoundCounter*4+1];
	inputW_Vertical[2]=inputW_Vertical[2]^ExpandedKey[RoundCounter*4+2];
	inputW_Vertical[3]=inputW_Vertical[3]^ExpandedKey[RoundCounter*4+3];
	WordVToByte();

for(RoundCounter=1;RoundCounter<=9;RoundCounter++)
{
//1-Subistute
	for(i=0;i<16;i++)
	{
		input[i]=Substitute[(input[i]&0xF0)>>4][input[i]&0x0F];
	}

	ByteToWordH();

//2-shift rows
	inputW_Horizontal[1] = (inputW_Horizontal[1] <<8 ) | (inputW_Horizontal[1] >> (sizeof(inputW_Horizontal[1])*8 - 8));
	inputW_Horizontal[2] = (inputW_Horizontal[2] <<16 ) | (inputW_Horizontal[2] >> (sizeof(inputW_Horizontal[2])*8 - 16));
	inputW_Horizontal[3] = (inputW_Horizontal[3] <<24 ) | (inputW_Horizontal[3] >> (sizeof(inputW_Horizontal[3])*8 - 24));
	WordHToByte();

//3-Mix columns
	for(i=0;i<4;i++)
	{
		unsigned char S0=input[i*4];
		unsigned char S1=input[i*4+1];
		unsigned char S2=input[i*4+2];
		unsigned char S3=input[i*4+3];
		unsigned char temp=S0 ^S1 ^S2 ^S3; 
		if(((S0^S1)&0x80) ==0x0)
		{
		input[i*4]=S0 ^ temp ^ ((S0 ^S1)<<1);
		}
		else
		{
		input[i*4]=S0 ^ temp ^ (((S0 ^S1)<<1)^0x1b);
		}
		if(((S1 ^S2)&0x80)==0)
		{
		input[i*4+1]=S1 ^ temp ^ ((S1 ^S2)<<1);
		}
		else
		{
			input[i*4+1]=S1 ^ temp ^ (((S1 ^S2)<<1)^0x1b);
		}
		if(((S2 ^S3)&0x80) ==0)
		{
		input[i*4+2]=S2 ^ temp ^ ((S2 ^S3)<<1);
		}
		else
		{
		input[i*4+2]=S2 ^ temp ^ (((S2 ^S3)<<1)^0x1b);
		}
		if(((S3 ^S0)&0x80) ==0)
		{
		input[i*4+3]=S3^ temp ^ ((S3 ^S0)<<1);
		}
		else
		{
			input[i*4+3]=S3^ temp ^ (((S3 ^S0)<<1)^0x1b);
		}
	}

	ByteToWordV();

//4-Add Round key
	//Add Round key
	inputW_Vertical[0]=inputW_Vertical[0]^ExpandedKey[RoundCounter*4];
	inputW_Vertical[1]=inputW_Vertical[1]^ExpandedKey[RoundCounter*4+1];
	inputW_Vertical[2]=inputW_Vertical[2]^ExpandedKey[RoundCounter*4+2];
	inputW_Vertical[3]=inputW_Vertical[3]^ExpandedKey[RoundCounter*4+3];
	

	WordVToByte();

}

//Round 10
//1-Subistute
	for(i=0;i<16;i++)
	{
		input[i]=Substitute[(input[i]&0xF0)>>4][input[i]&0x0F];
	}

	ByteToWordH();
//2-shift rows
	inputW_Horizontal[1] = (inputW_Horizontal[1] <<8 ) | (inputW_Horizontal[1] >> (sizeof(inputW_Horizontal[1])*8 - 8));
	inputW_Horizontal[2] = (inputW_Horizontal[2] <<16 ) | (inputW_Horizontal[2] >> (sizeof(inputW_Horizontal[2])*8 - 16));
	inputW_Horizontal[3] = (inputW_Horizontal[3] <<24 ) | (inputW_Horizontal[3] >> (sizeof(inputW_Horizontal[3])*8 - 24));
	WordHToByte();
	ByteToWordV();
//4-Add Round key
	//Add Round key
	inputW_Vertical[0]=inputW_Vertical[0]^ExpandedKey[RoundCounter*4];
	inputW_Vertical[1]=inputW_Vertical[1]^ExpandedKey[RoundCounter*4+1];
	inputW_Vertical[2]=inputW_Vertical[2]^ExpandedKey[RoundCounter*4+2];
	inputW_Vertical[3]=inputW_Vertical[3]^ExpandedKey[RoundCounter*4+3];

	WordVToByte();
	}
	end = clock() ;
	printByteArray();

//printf("\nelapsed time: %.20f\n",((long double)end-start)/CLOCKS_PER_SEC);
}
return 0;
	
}
void keyExpansion()
{
	int i;
	unsigned long t;
	for(i=4;i<44;i++)
	{
		
		t=ExpandedKey[i-1];
		if(i%4==0)
		{
			t=SubWord(t,i);
		}
		ExpandedKey[i]=(ExpandedKey[i-4] ^ t);	

	}
}
unsigned long SubWord(unsigned long t1,int i)
{
	unsigned long retBack=0,x;
	unsigned char temp[4];
	unsigned char s0,s1,s2,s3;
	x=t1;
	x = ((x <<8 ) | x >> (sizeof(x)*8 - 8)); //shift bits
	s0=(x>>24);
	s1=(x>>16);
	s2=(x>>8);
	s3=(x);
	temp[0]=Substitute[(s0&0xF0)>>4][s0&0x0F]; //sub bytes
	temp[1]=Substitute[(s1&0xF0)>>4][s1&0x0F];
	temp[2]=Substitute[(s2&0xF0)>>4][s2&0x0F];
	temp[3]=Substitute[(s3&0xF0)>>4][s3&0x0F];
	x=temp[3]| temp[2]<<8 |temp[1]<<16| temp[0]<<24; //return back to temp word
	retBack|=RC[(i/4)-1]<<24;
	retBack=(x^retBack);
	return retBack;
}
void ByteToWordV()
{
	int i;
	for(i=0;i<4;i++)
	{
		inputW_Vertical[i]=input[(i*4)+3]| input[(i*4)+2]<<8 |input[(i*4)+1]<<16| input[(i*4)]<<24;
		
	}
}
void ByteToWordH()
{
	int i;
	for(i=0;i<4;i++)
	{
		inputW_Horizontal[i]=input[i+12]| input[i+8]<<8 |input[i+4]<<16| input[i]<<24;
	}
}
void WordVToByte()
{
	int i;
	for(i=0;i<4;i++)
	{
		input[i*4]=inputW_Vertical[i]>>24;
		input[i*4+1]=inputW_Vertical[i]>>16;
		input[i*4+2]=inputW_Vertical[i]>>8;
		input[i*4+3]=inputW_Vertical[i];
	}
}
void WordHToByte()
{
	int i;
	for(i=0;i<4;i++)
	{
		input[i]=inputW_Horizontal[i]>>24;
		input[i+4]=inputW_Horizontal[i]>>16;
		input[i+8]=inputW_Horizontal[i]>>8;
		input[i+12]=inputW_Horizontal[i];
	}
}

void printByteArray()
{
	int i;
	for(i=0;i<16;i++)
	{
		printf("%02x",input[i]);
		
	}
	printf("\n");
}
void printVWordArray()
{
	int i;
	for(i=0;i<4;i++)
	{
		printf("%08x",inputW_Vertical[i]);
		
	}
}
void printHWordArray()
{
	int i;
	for(i=0;i<4;i++)
	{
		printf("%08x\n",inputW_Horizontal[i]);
		
	}
}