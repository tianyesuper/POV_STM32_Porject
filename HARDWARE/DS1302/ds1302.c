#include "ds1302.h"

static void DS1302_IO_OUT(void)
{
	    GPIO_InitTypeDef GPIO_InitStructure;																
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				
		GPIO_Init(GPIOB, &GPIO_InitStructure);	

}
static void DS1302_IO_IN(void)
{
	    GPIO_InitTypeDef GPIO_InitStructure;																
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   
				
		GPIO_Init(GPIOB, &GPIO_InitStructure); 

}
static void DS1302_Write8bit(u8 code)
{
	    unsigned char i;
		DS1302_IO_OUT();						//输出模式
		SCLK =0;						//SCK = 0
		for(i=0;i<8;i++)
		{
			  delay_us(50);	//delay until OSC is stable

			  if(code&0x01) 
					IO_OUT=1;			//I/0  = 1
			  else 
					IO_OUT=0;			//I/0 = 0
			   delay_us(50);	//delay until OSC is stable
			  
			  	SCLK =1;				//SCLK	= 1
			    delay_us(50);	//delay until OSC is stable
																
			 	SCLK =0;			//SCLK = 0
			  code = code >> 1;
		}




}
static u8   DS1302_Read8bit(void)
{
	    u8 i,code;
		u8 temp;
		DS1302_IO_IN();
		code = 0;
		SCLK = 0;						//SCLK = 0
	
		delay_us(50);	//delay until OSC is stable
	
		for(i=0;i<8;i++)
		{
				
			  code = code >>1;
				
			  if(IO_IN==1)
				{
					code = code | 0x80;
				}	
						
					
						
			delay_us(50);	//delay until OSC is stable
			  SCLK = 1;			//SCLK = 1
			delay_us(50);	//delay until OSC is stable
		
			 SCLK = 0;			//SCLK = 0
	
		}
		
		temp = code /16;
		code = code % 16;
		code = code + temp * 10;			//数据的相关转换
		
		return code;

}


void DS1302_WriteByte(  u8 con,u8 pBuffer)
{
	    DSRST=0; 				//关闭DS1302		//CE = 0
		delay_us(50);	//delay until OSC is stable
		SCLK= 0;														//SCK = 0
		delay_us(50);	//delay until OSC is stable
		
		 DSRST=1; 				//使能DS1302		//CE = 1
		delay_us(50);	//delay until OSC is stable
		DS1302_Write8bit(con);		//写控制命令		//发送地址
		DS1302_Write8bit(pBuffer); 		//写入数据			//发送数据
		delay_us(50);	//delay until OSC is stable
		SCLK = 1;
		delay_us(50);	//delay until OSC is stable
		DSRST=0;		 //关闭DS1302
	
}
u8  DS1302_ReadByte(u8 con)
{
	unsigned char code;
	DSRST=0;		   //关闭DS1302					//CE = 0
	delay_us(50);	//delay until OSC is stable
    SCLK = 0;													//SCLK = 0
	delay_us(50);	//delay until OSC is stable
	DSRST=1;          //使能DS1302			//CE = 1;
	delay_us(50);	//delay until OSC is stable
	DS1302_Write8bit(con);   //读取代码				//发送地址
	code= DS1302_Read8bit();  //返回读取数字
	
	//printf("code = %d\r\n" ,code );
	delay_us(50);	//delay until OSC is stable
	SCLK = 1;													//SCLK = 1
	delay_us(50);	//delay until OSC is stable
	DSRST=0;         //关闭DS1302			//CE = 0
	return code;
}
static void DS1302_ReadBurst(unsigned char *rstr)
{
	int i = 0;
	//unsigned char code;
	DSRST=0;		   			//关闭DS1302					//CE = 0
	delay_us(50);	//delay until OSC is stable 
	SCLK = 0;													//SCLK = 0
	delay_us(50);	//delay until OSC is stable
	DSRST=1;          		//使能DS1302			//CE = 1;
	delay_us(50);	//delay until OSC is stable
	DS1302_Write8bit(RdRamBurst);   //读取代码				//发送地址
	
   	for(i = 0 ;i < 7 ; i++)
	{
		rstr[i] = DS1302_Read8bit();
	}
	
	//printf("code = %d\r\n" ,code );
	delay_us(50);	//delay until OSC is stable
	SCLK = 1;													//SCLK = 1
	delay_us(50);	//delay until OSC is stable
	DSRST=0;         //关闭DS1302			//CE = 0

//	for(i = 0 ;i < 7 ; i ++)
	{
	 	//printf("rstr[%d] = %d\r\n",i,rstr[i]);
	}

}

extern void DS1302_WriteTime(TIME_TypeDef* time)
{
	DS1302_WriteByte(WrControl,0x00);  		//关闭写保护，可以写入数据
		
	DS1302_WriteByte(WrYear,time->year);
	DS1302_WriteByte(WrMonth,time->month);
	DS1302_WriteByte(WrDate,time->date);
	DS1302_WriteByte(WrWeek,time->week);
	DS1302_WriteByte(WrHour,time->hour);
	DS1302_WriteByte(WrMin,time->min);
	DS1302_WriteByte(WrSec,time->sec);

	DS1302_WriteByte(WrControl,0x80);  		//开启写保护，禁止写入数据

}
extern void DS1302_ReadTime(TIME_TypeDef* time)
{ 
	  TIME_TypeDef  myTime;
		DS1302_ReadBurst((u8 *)&myTime);
		
		time->year	= myTime.year;
		time->month = myTime.month; 
		time->date	= myTime.date;
	
		time->hour	= myTime.hour;
		time->min	= myTime.min;
		time->sec	= myTime.sec;

}
/*void time_convert(TIME_TypeDef *time_get)
{
	time[0] = '2';															//2
	time[1] = '0';															//0
	time[2] = time_get->year / 10 + '0';		                            //1
	time[3] = time_get->year % 10 + '0';                                    //4
	time[4] = '-';	                                                        //-
	time[5] = time_get->month / 10 + '0';				                    //0
	time[6] = time_get->month % 10 + '0';                                   //4
	time[7] = '-';															//-
	
	time[8] = time_get->date / 10 + '0';                                    //1
	time[9] = time_get->date % 10 + '0';	                                //0
	time[10] = ' ';                                                         // 
	time[11] = time_get->hour / 10 + '0';                                   //1
	time[12] = time_get->hour % 10 + '0';                                   //4
	time[13] = ':';															//:
	time[14] = time_get->min / 10 + '0';                                    //2
	time[15] = time_get->min % 10 + '0';      	                            //1
	time[16] = ':';															//:
	time[17] = time_get->sec / 10 + '0';		                             //3
	time[18] = time_get->sec % 10 + '0';	                                 //0
	time[19] = '\0';															// 
	
	
//	printf("time = %s\r\n",time);
}*/

extern void DS1302_SetupTime(TIME_TypeDef *time)//初始化
{
	 TIME_TypeDef **Time_InitStructure=&time;
	 
	DS1302_WriteByte(WrControl,0x00);  //关闭写保护，可以写入数据了
	delay_us(100);	//delay until OSC is stable
	DS1302_WriteTime(&**Time_InitStructure);
	DS1302_WriteByte(WrControl,0x80);  //开启写保护，禁止写入数据
	
	
}
