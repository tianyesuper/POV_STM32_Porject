#include "stm32f10x.h"
#include "i2c.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//LED_Drive_V0.2开发板
//LED驱动代码	   
//修改日期:2018/7/31
//版本：V0.0.1
//版权所有，盗版必究。
//All rights reserved											  
////////////////////////////////////////////////////////////////////////////////// 	   
void IIC_Configuration(void)
{
		//先定义结构体
	GPIO_InitTypeDef	 GPIO_InitStructure;
  I2C_InitTypeDef    I2C_InitStructure;
	
	//要开了对应的gpio的时钟还有其他的外设的时钟，然后你配置寄存器才可以，软件仿真里面开时钟先后没有影响，但是实物里面，要先开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能APB2外设的GPIOB的时钟,I2C2是PB_10 SCL，PB_11 SDA上面的复用	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 ,ENABLE);  //开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2 ,ENABLE);  //开启时钟
	//要对上面定义的两个结构体进行定义，首先PB要定义为复用的才行，而且是开漏复用
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11; 	//选择PB_6是SCL引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //管脚频率为50MHZ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	 //输出模式为复用开漏输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);				 //初始化GPIOB寄存器
	
	
	
	//配置I2C
	I2C_InitStructure.I2C_ClockSpeed = 50000;          /*I2C的时钟频率400kHz ，不是I2C输入时钟的频率*/
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;        
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;  /*设置CCR寄存器的，占空比  快速模式下0:Tlow/Thigh = 2；1:Tlow/Thigh = 16/9 */
  I2C_InitStructure.I2C_OwnAddress1 = 0xB0 ;         /*这句话说的是stm32作为从机的时候它的地址，如果没有做从机不用理会这个值*/
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;        /*应答使能 */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; /* */
	I2C_Init(I2C1,&I2C_InitStructure);
	I2C_Init(I2C2,&I2C_InitStructure);
	//使能I2C
	I2C_Cmd(I2C1, ENABLE);
	I2C_Cmd(I2C2, ENABLE);	
}


void IIC_Byte_Write( bool iic_x, u8 Device_Address, u8 pBuffer, u8 Word_Address)
{
	if(iic_x)
	{
				 //IIC_Wait_EEprom();                 /*等待总线空闲，等待设备器件空闲（其中需要软件清除SR1的AF位，即应答成功）*/
			
			 I2C_GenerateSTART(I2C2, ENABLE);   /*发送一个s，也就是起始信号，因为前面的函数没有终止，这次开始也是需要重新的一个开始信号*/
			 //EV5事件
			 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT)); /*判断EV5,看下函数定义可以发现，该事件是SB=1，MSL=1，BUSY=1 
																																	意思是起始条件已经发送了，然后是主模式，总线在通讯*/
			 
			 I2C_Send7bitAddress(I2C2, Device_Address, I2C_Direction_Transmitter);  /*发送器件地址，最后一个参数表示地址bit0为0，意思
																																							是写操作，同时由于写了DR寄存器，故会清除SB位变成0*/
			
			 //EV6 EV8_1（该事件判断同时判断了EV8_1事件）
			 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));/*判断EV6和EV8_1的条件，此时SB=0，ADDR=1地址发送结束，
																																					 TXE=1数据寄存器DR为空，BUSY=1总不空闲,MSL=1主模式,TRA=1
																																							数据已经发送了（因为是写操作，其实是地址数据已经发送了）
																																							如果是主收模式，这里的EV6，TRA=1表示数据还没收到，0表示
																																							收到数据，注意这里TRA=1表示已经发送了，ADDR=1才是发送完成
																																							了,做完该事件，ADDR=0了又*/                                                                           
			 
			 I2C_SendData(I2C2,Word_Address);      /*EV8_1事件，因为这一步时候DR已经为空，该事件是写入data1，对于EEPROM来说这个data1是要写入
																						字节的的地址，data2是要写入的内容，data1为8位1k的有效字节是低7位，2kbit的有效字节是8位，32页，
																						每页8个字节，一共2k位，16kbit需要11位？怎么送？用硬件的A1，2，3接GPIO来选择存储的页*/
															 
			 
			 //EV8事件
			 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING)); /*为下一步执行EV8事件，判断TXE=1 DR寄存器为空，准备写入DR寄存器
																																			 data2，注意此时也判定TRA=1意思是data1已经发送了不表示发送完成，
																																			 移位寄存器非空表示数还在发，另外BTF=0说明data1字节发送没完成，
																																			 NOSTRETCH为0时候，BTF=1还表示新数据要被发送了（意味着字节发送）
																																			 完成了但是新数据还没有写入到DR里面，这里的EV8事件对于的一段一直
																																			 是有数据发送的，不存在BTF=1的情况*/ 
																																																																																																			
			 I2C_SendData(I2C2,pBuffer);                                    /*数据寄存器DR为空，这里是写入data2，该步骤隶属于EV8事件*/
			
			/*EV8_2事件（这里就发送两个data，所以就只有一个EV8事件，
				EV8_1—data1，EV8_1—data2，EV8_2和EV8的区别是检测的
				差个BTF,且EV8_2不写DR而是程序要求停止）*/
				
			 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); /*EV8_2的事件判断和EV8事件不一样，TRA=1表示data2已经发送了，
																																				BTF=1字节发送结束，说明这一时刻没有字节在发送，其实表示在
																																				data2正在发送的时候，没有data3写入到DR里面， 然后现在该轮到要
																																				发送data3了，但是DR里面是空的（其实发送data2的时候，中间某时
																																				刻DR就已经空了）*/
																																																																			
			 I2C_GenerateSTOP(I2C2,ENABLE);                                  /*EV8_2事件中的程序写停止*/
	}
	else
	{
					 //IIC_Wait_EEprom();                 /*等待总线空闲，等待设备器件空闲（其中需要软件清除SR1的AF位，即应答成功）*/
				
				 I2C_GenerateSTART(I2C1, ENABLE);   /*发送一个s，也就是起始信号，因为前面的函数没有终止，这次开始也是需要重新的一个开始信号*/
				 //EV5事件
				 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); /*判断EV5,看下函数定义可以发现，该事件是SB=1，MSL=1，BUSY=1 
																																		意思是起始条件已经发送了，然后是主模式，总线在通讯*/
				 
				 I2C_Send7bitAddress(I2C1, Device_Address, I2C_Direction_Transmitter);  /*发送器件地址，最后一个参数表示地址bit0为0，意思
																																								是写操作，同时由于写了DR寄存器，故会清除SB位变成0*/
				
				 //EV6 EV8_1（该事件判断同时判断了EV8_1事件）
				 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));/*判断EV6和EV8_1的条件，此时SB=0，ADDR=1地址发送结束，
																																						 TXE=1数据寄存器DR为空，BUSY=1总不空闲,MSL=1主模式,TRA=1
																																								数据已经发送了（因为是写操作，其实是地址数据已经发送了）
																																								如果是主收模式，这里的EV6，TRA=1表示数据还没收到，0表示
																																								收到数据，注意这里TRA=1表示已经发送了，ADDR=1才是发送完成
																																								了,做完该事件，ADDR=0了又*/                                                                           
				 
				 I2C_SendData(I2C1,Word_Address);      /*EV8_1事件，因为这一步时候DR已经为空，该事件是写入data1，对于EEPROM来说这个data1是要写入
																							字节的的地址，data2是要写入的内容，data1为8位1k的有效字节是低7位，2kbit的有效字节是8位，32页，
																							每页8个字节，一共2k位，16kbit需要11位？怎么送？用硬件的A1，2，3接GPIO来选择存储的页*/
																 
				 
				 //EV8事件
				 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)); /*为下一步执行EV8事件，判断TXE=1 DR寄存器为空，准备写入DR寄存器
																																				 data2，注意此时也判定TRA=1意思是data1已经发送了不表示发送完成，
																																				 移位寄存器非空表示数还在发，另外BTF=0说明data1字节发送没完成，
																																				 NOSTRETCH为0时候，BTF=1还表示新数据要被发送了（意味着字节发送）
																																				 完成了但是新数据还没有写入到DR里面，这里的EV8事件对于的一段一直
																																				 是有数据发送的，不存在BTF=1的情况*/ 
																																																																																																				
				 I2C_SendData(I2C1,pBuffer);                                    /*数据寄存器DR为空，这里是写入data2，该步骤隶属于EV8事件*/
				
				/*EV8_2事件（这里就发送两个data，所以就只有一个EV8事件，
					EV8_1—data1，EV8_1—data2，EV8_2和EV8的区别是检测的
					差个BTF,且EV8_2不写DR而是程序要求停止）*/
					
				 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); /*EV8_2的事件判断和EV8事件不一样，TRA=1表示data2已经发送了，
																																					BTF=1字节发送结束，说明这一时刻没有字节在发送，其实表示在
																																					data2正在发送的时候，没有data3写入到DR里面， 然后现在该轮到要
																																					发送data3了，但是DR里面是空的（其实发送data2的时候，中间某时
																																					刻DR就已经空了）*/
																																																																				
				 I2C_GenerateSTOP(I2C1,ENABLE);                                  /*EV8_2事件中的程序写停止*/	
	}
}
void IIC_Wait_EEprom( bool iic_x, u8 Device_Address)
{
	if(iic_x)
	{
						vu16 SR1_Tmp = 0;

					do
					{
						/* Send START condition */
						I2C_GenerateSTART(I2C2, ENABLE);
						/* Read I2C1 SR1 register */
						SR1_Tmp = I2C_ReadRegister(I2C2, I2C_Register_SR1);
						/* Send EEPROM address for write */
						I2C_Send7bitAddress(I2C2,  Device_Address, I2C_Direction_Transmitter); //问题是这句话只是写入了地址到DR寄存器里面，这离下一句的while
																																									//判断时间很短，要是数据还没发完，设备也没响应，也就是ADDR=0，
																																									//就已经到了while里面的读SR1了，那岂不是出不去while了？
					}while(!(I2C_ReadRegister(I2C2, I2C_Register_SR1) & 0x0002));
					
					/* Clear AF flag */
					I2C_ClearFlag(I2C2, I2C_FLAG_AF);	
						
						
	}
	else
	{
						vu16 SR1_Tmp = 0;

					do
					{
						/* Send START condition */
						I2C_GenerateSTART(I2C1, ENABLE);
						/* Read I2C1 SR1 register */
						SR1_Tmp = I2C_ReadRegister(I2C1, I2C_Register_SR1);
						/* Send EEPROM address for write */
						I2C_Send7bitAddress(I2C1,  Device_Address, I2C_Direction_Transmitter); //问题是这句话只是写入了地址到DR寄存器里面，这离下一句的while
																																									//判断时间很短，要是数据还没发完，设备也没响应，也就是ADDR=0，
																																									//就已经到了while里面的读SR1了，那岂不是出不去while了？
					}while(!(I2C_ReadRegister(I2C1, I2C_Register_SR1) & 0x0002));
					
					/* Clear AF flag */
					I2C_ClearFlag(I2C1, I2C_FLAG_AF);	
						
						
		
	}
	
	
	
}
void IIC_Byte_Read(  bool iic_x, u8 Device_Address, u8* pRead, u8 Word_Address)
{
	if(iic_x)
	{
		/*首先写操作，发送设备地址写操作，找到设备应答了，写入要读数据的地址*/
   //IIC_Wait_EEprom(); 
   I2C_GenerateSTART(I2C2, ENABLE);
	
	 //EV5事件
   while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C2, Device_Address, I2C_Direction_Transmitter); 
	
	 //EV6 EV8_1事件（该事件判断同时判断了EV8_1事件）
	 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	 {}
	 I2C_SendData(I2C2,Word_Address); 
		 
	 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //采用EV8_2的判断条件反应此时已经收到ACK，Word_Address发送完成。
	 
	/*给Start条件，发送设备地址读操作，找到设备应答了，收数据，主机不应答，终止*/
	 I2C_GenerateSTART(I2C2, ENABLE);
		 
	//EV5事件
   while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C2, Device_Address, I2C_Direction_Receiver ); 
	
  //EV6事件
	 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		 
	//EV6_1事件，没有标志位，要设置ACK失能和停止位产生
	 I2C2->CR1 &= 0xFBFF ;   //失能ACK
	 I2C2->CR1 |= 0x0020 ;   //使能Stop
	
	//EV7事件，读DR寄存器
	 while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
	 * pRead = I2C2->DR;		
		
	}
	else
	{
		/*首先写操作，发送设备地址写操作，找到设备应答了，写入要读数据的地址*/
   //IIC_Wait_EEprom(); 
   I2C_GenerateSTART(I2C1, ENABLE);
	
	 //EV5事件
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C1, Device_Address, I2C_Direction_Transmitter); 
	
	 //EV6 EV8_1事件（该事件判断同时判断了EV8_1事件）
	 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
	 {}
	 I2C_SendData(I2C1,Word_Address); 
		 
	 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); //采用EV8_2的判断条件反应此时已经收到ACK，Word_Address发送完成。
	 
	/*给Start条件，发送设备地址读操作，找到设备应答了，收数据，主机不应答，终止*/
	 I2C_GenerateSTART(I2C1, ENABLE);
		 
	//EV5事件
   while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT));
   I2C_Send7bitAddress(I2C1, Device_Address, I2C_Direction_Receiver ); 
	
  //EV6事件
	 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
		 
	//EV6_1事件，没有标志位，要设置ACK失能和停止位产生
	 I2C1->CR1 &= 0xFBFF ;   //失能ACK
	 I2C1->CR1 |= 0x0020 ;   //使能Stop
	
	//EV7事件，读DR寄存器
	 while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
	 * pRead = I2C1->DR;			
	}
}