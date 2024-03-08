#include "i2c.h"
#include "e4.h"

//�洢WM8978��Ƶ��������ļĴ���ֵ
static uint16_t WM8978_REGVAL_TBL[58]=
{
	0X0000,0X0000,0X0000,0X0000,0X0050,0X0000,0X0140,0X0000,
	0X0000,0X0000,0X0000,0X00FF,0X00FF,0X0000,0X0100,0X00FF,
	0X00FF,0X0000,0X012C,0X002C,0X002C,0X002C,0X002C,0X0000,
	0X0032,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,0X0000,
	0X0038,0X000B,0X0032,0X0000,0X0008,0X000C,0X0093,0X00E9,
	0X0000,0X0000,0X0000,0X0000,0X0003,0X0010,0X0010,0X0100,
	0X0100,0X0002,0X0001,0X0001,0X0039,0X0039,0X0039,0X0039,
	0X0001,0X0001
}; 




/*********************************************************************************************************
дwm8978�Ĵ���
**********************************************************************************************************/
void WM8978_Write_Reg(uint8_t reg,uint16_t val)
{ 	
			uint32_t time = 10000;
		 
			/* wait until I2C bus is idle */
			while(i2c_flag_get(I2C2, I2C_FLAG_I2CBSY));
			i2c_delay(time);
		
			/* send a start condition to I2C bus */
			i2c_start_on_bus(I2C2);
			i2c_delay(time);
			
			/* wait until SBSEND bit is set */
			while(!i2c_flag_get(I2C2, I2C_FLAG_SBSEND));
			i2c_delay(time);
			
			/* send slave address to I2C bus */
			i2c_master_addressing(I2C2, WM8978_ADDRESS, I2C_TRANSMITTER);
			i2c_delay(time); 
			
			/* wait until ADDSEND bit is set */
			while(!i2c_flag_get(I2C2, I2C_FLAG_ADDSEND));
			i2c_delay(time);
			
			/* clear the ADDSEND bit */
			i2c_flag_clear(I2C2,I2C_FLAG_ADDSEND);
			i2c_delay(time);  
			
			/* wait until the transmit data buffer is empty */
			while(SET != i2c_flag_get(I2C2, I2C_FLAG_TBE));
			i2c_delay(time);
			
			/* send the EEPROM's internal address to write to : only one byte address */
			i2c_data_transmit(I2C2, ((reg<<1)|((val>>8)&0X01)));
			i2c_delay(time);
			
			/* wait until BTC bit is set */
			while(!i2c_flag_get(I2C2, I2C_FLAG_BTC));
			i2c_delay(time);
			
			/* send the byte to be written */
			i2c_data_transmit(I2C2, (uint8_t)(val&0XFF)); 
			i2c_delay(time);
			
			/* wait until BTC bit is set */
			while(!i2c_flag_get(I2C2, I2C_FLAG_BTC));
			i2c_delay(time);

			/* send a stop condition to I2C bus */
			i2c_stop_on_bus(I2C2);
			i2c_delay(time);
			
			/* wait until the stop condition is finished */
			while(I2C_CTL0(I2C2)&0x0200);
			i2c_delay(time);
			
			WM8978_REGVAL_TBL[reg]=val;
} 

/********************************************************************************************************
//��ʼ��wm8978
*********************************************************************************************************/
void WM8978_Init(void)
{
			WM8978_Write_Reg(0,0);										//��λWM8978
			WM8978_Write_Reg(1,0X1B);									//R1,MICEN����Ϊ1(MICʹ��),BIASEN����Ϊ1(ģ��������),VMIDSEL[1:0]����Ϊ:11(5K)
			WM8978_Write_Reg(2,0X1B0);								//R2,ROUT1,LOUT1���ʹ��(�������Թ���),BOOSTENR,BOOSTENLʹ��
			WM8978_Write_Reg(3,0X6C);									//R3,LOUT2,ROUT2���ʹ��(���ȹ���),RMIX,LMIXʹ��	
			WM8978_Write_Reg(6,0);										//R6,MCLK���ⲿ�ṩ
			WM8978_Write_Reg(43,1<<4);								//R43,INVROUT2����,��������
			WM8978_Write_Reg(47,1<<8);								//R47����,PGABOOSTL,��ͨ��MIC���20������
			WM8978_Write_Reg(48,1<<8);								//R48����,PGABOOSTR,��ͨ��MIC���20������
			WM8978_Write_Reg(49,1<<1);								//R49,TSDEN,�������ȱ��� 
			WM8978_Write_Reg(49,1<<2);								//R49,SPEAKER BOOST,1.5x 
			WM8978_Write_Reg(10,1<<3);								//R10,SOFTMUTE�ر�,128x����,���SNR 
			WM8978_Write_Reg(14,1<<3);								//R14,ADC 128x������
}

/********************************************************************************************************
//WM8978���Ĵ���
//���Ƕ�ȡ���ؼĴ���ֵ�������ڵĶ�Ӧֵ
//reg:�Ĵ�����ַ 
//����ֵ:�Ĵ���ֵ
*********************************************************************************************************/
uint16_t WM8978_Read_Reg(uint8_t reg)
{  
			return WM8978_REGVAL_TBL[reg];	
}


/********************************************************************************************************
//WM8978 DAC/ADC����
//adcen:adcʹ��(1)/�ر�(0)
//dacen:dacʹ��(1)/�ر�(0)
*********************************************************************************************************/
void WM8978_ADDA_Cfg(uint8_t dacen,uint8_t adcen)
{
			uint16_t regval;
			regval=WM8978_Read_Reg(3);										//��ȡR3
			if(dacen)regval|=3<<0;												//R3���2��λ����Ϊ1,����DACR&DACL
			else regval&=~(3<<0);													//R3���2��λ����,�ر�DACR&DACL.
			WM8978_Write_Reg(3,regval);										//����R3
			regval=WM8978_Read_Reg(2);										//��ȡR2
			if(adcen)regval|=3<<0;												//R2���2��λ����Ϊ1,����ADCR&ADCL
			else regval&=~(3<<0);													//R2���2��λ����,�ر�ADCR&ADCL.
			WM8978_Write_Reg(2,regval);										//����R2	
}


/*************************************************************************************************
//WM8978 ����ͨ������ 
//micen:MIC����(1)/�ر�(0)
//lineinen:Line In����(1)/�ر�(0)
//auxen:aux����(1)/�ر�(0) 
**************************************************************************************************/
void WM8978_Input_Cfg(uint8_t micen,uint8_t lineinen,uint8_t auxen)
{
			uint16_t regval;  
			regval=WM8978_Read_Reg(2);										//��ȡR2
			if(micen)regval|=3<<2;												//����INPPGAENR,INPPGAENL(MIC��PGA�Ŵ�)
			else regval&=~(3<<2);													//�ر�INPPGAENR,INPPGAENL.
			WM8978_Write_Reg(2,regval);										//����R2 
			
			regval=WM8978_Read_Reg(44);										//��ȡR44
			if(micen)regval|=3<<4|3<<0;										//����LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
			else regval&=~(3<<4|3<<0);										//�ر�LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
			WM8978_Write_Reg(44,regval);									//����R44
			
			if(lineinen)WM8978_LINEIN_Gain(5);						//LINE IN 0dB����
			else WM8978_LINEIN_Gain(0);										//�ر�LINE IN
			if(auxen)WM8978_AUX_Gain(7);									//AUX 6dB����
			else WM8978_AUX_Gain(0);											//�ر�AUX����  
}



/****************************************************************************************************
//WM8978 ������� 
//dacen:DAC���(����)����(1)/�ر�(0)
//bpsen:Bypass���(¼��,����MIC,LINE IN,AUX��)����(1)/�ر�(0) 
*****************************************************************************************************/
void WM8978_Output_Cfg(uint8_t dacen,uint8_t bpsen)
{
			uint16_t regval=0;
			if(dacen)regval|=1<<0;												//DAC���ʹ��
			if(bpsen)
			{
				regval|=1<<1;																//BYPASSʹ��
				regval|=5<<2;																//0dB����
			} 
			WM8978_Write_Reg(50,regval);									//R50����
			WM8978_Write_Reg(51,regval);									//R51���� 
}


/****************************************************************************************************
//WM8978 MIC��������(������BOOST��20dB,MIC-->ADC���벿�ֵ�����)
//gain:0~63,��Ӧ-12dB~35.25dB,0.75dB/Step
*****************************************************************************************************/
void WM8978_MIC_Gain(uint8_t gain)
{
			gain&=0X3F;
			WM8978_Write_Reg(45,gain);										//R45,��ͨ��PGA���� 
			WM8978_Write_Reg(46,gain|1<<8);								//R46,��ͨ��PGA����
}



/****************************************************************************************************
//WM8978 L2/R2(Ҳ����Line In)��������(L2/R2-->ADC���벿�ֵ�����)
//gain:0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
*****************************************************************************************************/
void WM8978_LINEIN_Gain(uint8_t gain)
{
			uint16_t regval;
			gain&=0X07;
			regval=WM8978_Read_Reg(47);										//��ȡR47
			regval&=~(7<<4);															//���ԭ�������� 
			WM8978_Write_Reg(47,regval|gain<<4);					//����R47
			regval=WM8978_Read_Reg(48);										//��ȡR48
			regval&=~(7<<4);															//���ԭ�������� 
			WM8978_Write_Reg(48,regval|gain<<4);					//����R48
} 



/****************************************************************************************************
//WM8978 AUXR,AUXL(PWM��Ƶ����)��������(AUXR/L-->ADC���벿�ֵ�����)
//gain:0~7,0��ʾͨ����ֹ,1~7,��Ӧ-12dB~6dB,3dB/Step
*****************************************************************************************************/
void WM8978_AUX_Gain(uint8_t gain)
{
			uint16_t regval;
			gain&=0X07;
			regval=WM8978_Read_Reg(47);										//��ȡR47
			regval&=~(7<<0);															//���ԭ�������� 
			WM8978_Write_Reg(47,regval|gain<<0);					//����R47
			regval=WM8978_Read_Reg(48);										//��ȡR48
			regval&=~(7<<0);															//���ԭ�������� 
			WM8978_Write_Reg(48,regval|gain<<0);					//����R48
}  



/****************************************************************************************************
//����I2S����ģʽ
//fmt:0,LSB(�Ҷ���);1,MSB(�����);2,�����ֱ�׼I2S;3,PCM/DSP;
//len:0,16λ;1,20λ;2,24λ;3,32λ;  
*****************************************************************************************************/
void WM8978_I2S_Cfg(uint8_t fmt,uint8_t len)
{
			fmt&=0X03;
			len&=0X03;																		//�޶���Χ
			WM8978_Write_Reg(4,(fmt<<3)|(len<<5));				//R4,WM8978����ģʽ����	
}	



/****************************************************************************************************
//���ö���������������
//voll:����������(0~63)
//volr:����������(0~63)
*****************************************************************************************************/
void WM8978_HPvol_Set(uint8_t voll,uint8_t volr)
{
			voll&=0X3F;
			volr&=0X3F;																		//�޶���Χ
			if(voll==0)voll|=1<<6;												//����Ϊ0ʱ,ֱ��mute
			if(volr==0)volr|=1<<6;												//����Ϊ0ʱ,ֱ��mute 
			WM8978_Write_Reg(52,voll);										//R52,������������������
			WM8978_Write_Reg(53,volr|(1<<8));							//R53,������������������,ͬ������(HPVU=1)
}



/****************************************************************************************************
//������������
//voll:����������(0~63) 
*****************************************************************************************************/
void WM8978_SPKvol_Set(uint8_t volx)
{ 
			volx&=0X3F;																		//�޶���Χ
			if(volx==0)volx|=1<<6;												//����Ϊ0ʱ,ֱ��mute 
			WM8978_Write_Reg(54,volx);										//R54,������������������
			WM8978_Write_Reg(55,volx|(1<<8));							//R55,������������������,ͬ������(SPKVU=1)	
}


/****************************************************************************************************
//����3D������
//depth:0~15(3Dǿ��,0����,15��ǿ)
*****************************************************************************************************/
void WM8978_3D_Set(uint8_t depth)
{ 
			depth&=0XF;																		//�޶���Χ 
			WM8978_Write_Reg(41,depth);										//R41,3D�������� 	
}



/****************************************************************************************************
//����EQ/3D���÷���
//dir:0,��ADC������
//1,��DAC������(Ĭ��)
*****************************************************************************************************/
void WM8978_EQ_3D_Dir(uint8_t dir)
{
			uint16_t regval; 
			regval=WM8978_Read_Reg(0X12);
			if(dir)regval|=1<<8;
			else regval&=~(1<<8); 
			WM8978_Write_Reg(18,regval);									//R18,EQ1�ĵ�9λ����EQ/3D����
}



/****************************************************************************************************
//����EQ1
//cfreq:��ֹƵ��,0~3,�ֱ��Ӧ:80/105/135/175Hz
//gain:����,0~24,��Ӧ-12~+12dB
*****************************************************************************************************/
void WM8978_EQ1_Set(uint8_t cfreq,uint8_t gain)
{ 
			uint16_t regval;
			cfreq&=0X3;																		//�޶���Χ 
			if(gain>24)gain=24;
			gain=24-gain;
			regval=WM8978_Read_Reg(18);
			regval&=0X100;
			regval|=cfreq<<5;															//���ý�ֹƵ�� 
			regval|=gain;																	//��������	
			WM8978_Write_Reg(18,regval);									//R18,EQ1���� 	
}



/****************************************************************************************************
//����EQ2
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:230/300/385/500Hz
//gain:����,0~24,��Ӧ-12~+12dB
*****************************************************************************************************/
void WM8978_EQ2_Set(uint8_t cfreq,uint8_t gain)
{ 
			uint16_t regval=0;
			cfreq&=0X3;																		//�޶���Χ 
			if(gain>24)gain=24;
			gain=24-gain; 
			regval|=cfreq<<5;															//���ý�ֹƵ�� 
			regval|=gain;																	//��������	
			WM8978_Write_Reg(19,regval);									//R19,EQ2���� 	
}



/****************************************************************************************************
//����EQ3
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:650/850/1100/1400Hz
//gain:����,0~24,��Ӧ-12~+12dB
*****************************************************************************************************/
void WM8978_EQ3_Set(uint8_t cfreq,uint8_t gain)
{ 
			uint16_t regval=0;
			cfreq&=0X3;																		//�޶���Χ 
			if(gain>24)gain=24;
			gain=24-gain; 
			regval|=cfreq<<5;															//���ý�ֹƵ�� 
			regval|=gain;																	//��������	
			WM8978_Write_Reg(20,regval);									//R20,EQ3���� 	
}



/****************************************************************************************************
//����EQ4
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:1800/2400/3200/4100Hz
//gain:����,0~24,��Ӧ-12~+12dB
*****************************************************************************************************/
void WM8978_EQ4_Set(uint8_t cfreq,uint8_t gain)
{ 
			uint16_t regval=0;
			cfreq&=0X3;																		//�޶���Χ 
			if(gain>24)gain=24;
			gain=24-gain; 
			regval|=cfreq<<5;															//���ý�ֹƵ�� 
			regval|=gain;																	//��������	
			WM8978_Write_Reg(21,regval);									//R21,EQ4���� 	
}



/****************************************************************************************************
//����EQ5
//cfreq:����Ƶ��,0~3,�ֱ��Ӧ:5300/6900/9000/11700Hz
//gain:����,0~24,��Ӧ-12~+12dB
*****************************************************************************************************/
void WM8978_EQ5_Set(uint8_t cfreq,uint8_t gain)
{ 
			uint16_t regval=0;
			cfreq&=0X3;																		//�޶���Χ 
			if(gain>24)gain=24;
			gain=24-gain; 
			regval|=cfreq<<5;															//���ý�ֹƵ�� 
			regval|=gain;																	//��������	
			WM8978_Write_Reg(22,regval);									//R22,EQ5���� 	
}

/****************************************************************************************************
//��ʼ��i2s
*****************************************************************************************************/
void i2s_config(void)
{
			/* enable the GPIO clock */
			rcu_periph_clock_enable(RCU_GPIOA);
			rcu_periph_clock_enable(RCU_GPIOB);
			rcu_periph_clock_enable(RCU_GPIOC);
			/* enable I2S2 clock */
			rcu_periph_clock_enable(RCU_SPI2);

			/* I2S2_MCK(PC7), I2S2_CK(PB3), I2S2_WS(PA4), I2S2_SD(PC12), I2S2_ADD_SD(PB4) GPIO pin configuration */
			gpio_af_set(GPIOC, GPIO_AF_6, GPIO_PIN_7 | GPIO_PIN_12);
			gpio_af_set(GPIOB, GPIO_AF_7, GPIO_PIN_4);
			gpio_af_set(GPIOB, GPIO_AF_6, GPIO_PIN_3);
			gpio_af_set(GPIOA, GPIO_AF_6, GPIO_PIN_4);
		
			gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7 | GPIO_PIN_12);
			gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4);
			gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_4);
		
			gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7 | GPIO_PIN_12); 
			gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3); 
			gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4); 
		
			spi_i2s_deinit(SPI2);

			/* I2S2 peripheral configuration */
			i2s_psc_config(SPI2, 4000, I2S_FRAMEFORMAT_DT16B_CH16B, I2S_MCKOUT_ENABLE);
			//i2s_psc_config(SPI2, i2saudiofreq, I2S_FRAMEFORMAT_DT16B_CH16B, I2S_MCLKOUTPUT);
			i2s_init(SPI2, I2S_MODE_MASTERTX, I2S_STD_PHILLIPS, I2S_CKPL_LOW);
			//i2s_psc_config(SPI2, i2saudiofreq, I2S_FRAMEFORMAT_DT16B_CH16B, I2S_MCLKOUTPUT);
			//i2s_init(SPI2, I2S_MODE_MASTERTX, I2S_STANDARD, I2S_CKPL_HIGH);
			/* enable the I2S2 peripheral */
			
			i2s_full_duplex_mode_config(I2S2_ADD, I2S_MODE_SLAVERX, I2S_STD_PHILLIPS, I2S_CKPL_LOW,I2S_FRAMEFORMAT_DT16B_CH16B);
			I2S_ADD_I2SCTL(I2S2_ADD) = (uint32_t)0x0900;
			i2s_enable(SPI2); 
			i2s_enable(I2S2_ADD); 
			I2S_ADD_I2SCTL(I2S2_ADD) |= (uint32_t)0x0600;
			spi_i2s_interrupt_enable(SPI2, SPI_I2S_INT_TBE);
			spi_i2s_interrupt_enable(I2S2_ADD, SPI_I2S_INT_RBNE);
}

/*********************************************************************************************************
������:     e4_init
��ڲ���:   ��
���ڲ���:   �� 
����ֵ:     ��
����:       zzz
����:       2023/4/10
��������:   ��ʼ��i2c,��ʼ��wm8978
**********************************************************************************************************/
void e4_init(void)
{
			i2c2_gpio_config();
		  i2c2_config();
      WM8978_Init();
			WM8978_HPvol_Set(40,40);
			WM8978_SPKvol_Set(60);	
}


/*********************************************************************************************************
������:     e4_sound_recording
��ڲ���:   �� 
���ڲ���:   �� 
����ֵ:     ��
����:       zzz
����:       2023/4/10
��������:   ¼������
**********************************************************************************************************/
void e4_sound_recording_config(void)
{
      WM8978_ADDA_Cfg(0,1);		
			WM8978_Input_Cfg(1,1,0);	
			WM8978_Output_Cfg(0,0);		
			WM8978_MIC_Gain(46);		
			WM8978_I2S_Cfg(2,0);	
			
			i2s_config();  
}



/*********************************************************************************************************
������:     e4_playback
��ڲ���:   �� 
���ڲ���:   �� 
����ֵ:     ��
����:       zzz
����:       2023/4/10
��������:   ��������
**********************************************************************************************************/
void e4_playback_config(void)
{
			WM8978_SPKvol_Set(60);	
			WM8978_ADDA_Cfg(1,0);	
			WM8978_Input_Cfg(0,0,0);
			WM8978_Output_Cfg(1,0);		
}


