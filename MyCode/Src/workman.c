#include "workman.h"
#include "main.h"
#include "arm_math.h"
#include "tft.h"
uint8_t mode=0;
extern float adjust;
extern uint8_t R_onedata,R_alldata[256];
uint8_t readyToFFT=0;

uint16_t ad_values[10];
float voice_input[10][32];
float voice_FFT[32];
//float voice_FFT_A[32];

float_t Servo=90.0;

float phase[8][220];
float Am[8][221];

int countDida = 0;
int FFT_time;
//上10次距离
float sita_last10[10];
//上15次的距离
float dis_last15[8][15];
float distance[8];
//取几次距离取平均
int howTimes=9;
float sortDis[15];
Kalman_Typedef KAL[8];
arm_rfft_fast_instance_f32 FFT_S;
float sita1,sita2,l1,l2;
float sita,l,l_last15[15];
float l_sort[15];
float adjustDis=0,adjustSita=0;
uint8_t isAdjust=0,wantAdjust=0;

void Servo_con(float_t angel)
{
	if(angel<=180&&angel>=0)
	{
		TIM4->CCR1=500+angel/180.0*2000.0;
	}

}

//初始化自己外设及while循环前的函数
void init_start()
{
	arm_rfft_fast_init_f32(&FFT_S,32);
	Kalman_Init(&KAL[0], 0.2, 0.4);
	Kalman_Init(&KAL[1], 0.2, 0.4);
	Kalman_Init(&KAL[2], 0.2, 0.4);
	Kalman_Init(&KAL[3], 0.05, 0.4);
	Kalman_Init(&KAL[4], 0.05, 0.4);
	Kalman_Init(&KAL[5], 0.2, 0.4);
	Kalman_Init(&KAL[6], 0.2, 0.4);
	Kalman_Init(&KAL[7], 0.01, 0.4);
	HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, SET);
	//开启ADC轮询采样十路信号
	HAL_UART_Receive_IT(&huart6, &R_onedata, 1);
//	TFT_Init();
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	Servo_con(90);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ad_values, 8);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);

}
//while循环里做的函数
void while_do()
{
	if(readyToFFT==1)
	{
		TIM2->CNT = 0;
		for(int i=0;i<8;i++)
		{
			arm_rfft_fast_f32(&FFT_S, voice_input[i], voice_FFT, 0);

			phase[i][countDida] = atan2(voice_FFT[2],voice_FFT[3])*180.0/3.1415926;
			if(i==0||i==1||i==2)
			arm_cmplx_mag_f32(&voice_FFT[2], &Am[i][countDida],2);
		}
		//arm_cmplx_mag_f32(&voice_FFT[2], &Am[1][countDida],2);

//
//		phase[3][countDida] = phase[1][countDida]-phase[3][countDida];
//		if(phase[3][countDida]>180)
//		{
//			phase[3][countDida]-=360;
//		}
//		else if(phase[3][countDida]<-180)phase[3][countDida]+=360;
//		phase[4][countDida] = phase[2][countDida]-phase[4][countDida];
//		if(phase[4][countDida]<-180)phase[3][countDida]+=360;
//		else if(phase[4][countDida]>180)phase[4][countDida]-=360;
		phase[3][countDida] -= phase[1][countDida];
		if(phase[3][countDida]<0)phase[3][countDida]+=360;
		phase[4][countDida] -= phase[2][countDida];
		if(phase[4][countDida]<0)phase[4][countDida]+=360;
		for(int i=1;i<3;i++)
		{
			phase[i][countDida] -= phase[0][countDida];
			if(phase[i][countDida]>180)phase[i][countDida]-=360;
			else if(phase[i][countDida]<-180)phase[i][countDida]+=360;
			//if(phase[i][countDida]<0)phase[i][countDida]+=360;
		}


		phase[0][countDida]-=phase[0][countDida];

		FFT_time = TIM2->CNT;

		if(++countDida>=220)
		{

			float max=0;
			int maxPlace=5;
			float dis;
			for(int i=5;i<215;i++)
			{
				if(Am[0][i]-Am[0][i-2]>max)
				{
					max = Am[0][i]-Am[0][i-2];
					maxPlace = i;
				}
			}

			for(int i=14;i>=1;i--)
			{
				for(int j=1;j<3;j++)
				{
					dis_last15[j][i] = dis_last15[j][i-1];
				}
			}
			for(int index=1;index<3;index++)
			{
				dis = phase[index][maxPlace]/360.0*34;
				dis_last15[index][0] = dis;
				for(int i=0;i<15;i++)
				{
					sortDis[i] = dis_last15[index][i];
				}
				sort(sortDis, 15);
				dis = (sortDis[5]+sortDis[6]+sortDis[7]+sortDis[8]+sortDis[9])/5;
				KalmanFilter(&KAL[index], dis);
				distance[index]=KAL[index].out;
//				if(index==1||index==2)
//				distance[index] = dis;
			}
			//再找一次1的maxplace
			max=0;
			for(int i=5;i<215;i++)
			{
				if(Am[1][i]-Am[1][i-2]>max)
				{
					max = Am[1][i]-Am[1][i-2];
					maxPlace = i;
				}
			}

			for(int i=14;i>=1;i--)
			{
				for(int j=3;j<4;j++)
				{
					dis_last15[j][i] = dis_last15[j][i-1];
				}
			}
			for(int index=3;index<4;index++)
			{
				dis = phase[index][maxPlace]/360.0*34;
				dis_last15[index][0] = dis;
				for(int i=0;i<15;i++)
				{
					sortDis[i] = dis_last15[index][i];
				}
				sort(sortDis, 15);
				dis = (sortDis[5]+sortDis[6]+sortDis[7]+sortDis[8]+sortDis[9])/5;
				KalmanFilter(&KAL[index], dis);
				distance[index]=KAL[index].out;
//				if(index==1||index==2)
//				distance[index] = dis;
			}
			//再找一次2的maxplace
			max=0;
			for(int i=5;i<215;i++)
			{
				if(Am[2][i]-Am[2][i-2]>max)
				{
					max = Am[2][i]-Am[2][i-2];
					maxPlace = i;
				}
			}

			for(int i=14;i>=1;i--)
			{
				for(int j=4;j<5;j++)
				{
					dis_last15[j][i] = dis_last15[j][i-1];
				}
			}
			for(int index=4;index<5;index++)
			{
				dis = phase[index][maxPlace]/360.0*34;
				dis_last15[index][0] = dis;
				for(int i=0;i<15;i++)
				{
					sortDis[i] = dis_last15[index][i];
				}
				sort(sortDis, 15);
				dis = (sortDis[5]+sortDis[6]+sortDis[7]+sortDis[8]+sortDis[9])/5;
				KalmanFilter(&KAL[index], dis);
				distance[index]=KAL[index].out;
//				if(index==1||index==2)
//				distance[index] = dis;
			}


			//if(distance[1]<-7.5)distance[1]+=34;
			l1 = (6400-distance[3]*distance[3])/2/distance[3];
			l2 = (6400-distance[4]*distance[4])/2/distance[4];
			l2-=adjustDis;
			if(wantAdjust==1)
			{
				adjustDis = l2-l1;
			}

			if(distance[1]<-5)
			{
				if(l2-l1<0)distance[1]+=34;
			}
			if(distance[2]<-5)
			{
				if(l2-l1>0)distance[2]+=34;
			}

			sita1 = atan(sqrt(  1325-distance[1]*distance[1])/distance[1]  )*180.0/3.1415926;
			if(sita1<0)sita1+=90;
			else sita1-=90;

			sita2 = -atan(sqrt(  1325-distance[2]*distance[2])/distance[2]  )*180.0/3.1415926;
			if(sita2<0)sita2+=90;
			else sita2-=90;

			sita= (sita1/2+sita2/2-adjustSita)*1.085;
			if(wantAdjust==1)
			{
				adjustSita = sita1/2+sita2/2;
				wantAdjust=0;
				isAdjust = 1;
			}

//			for(int i=14;i>=1;i--)
//			{
//				l_last15[i] = l_last15[i-1];
//			}
//			l_last15[0] = sqrt( 2*l1*l1 + 2*l2*l2 - 4900 )/2;
//
//			for(int i=0;i<15;i++)
//			{
//				l_sort[i] = l_last15[i];
//			}
//			sort(l_sort, 15);
//
//			l = (l_sort[5]+l_sort[6]+l_sort[7]+l_sort[8]+l_sort[9])/5;
//
//			KalmanFilter(&KAL[7], l);
//			l = KAL[7].out;
			l = 250/cosf(sita/180*3.1415926);
			//printf("%.3f,%.3f,%.3f,%.3f,%.3f\n",l1,l2,sita1,sita2,(sita1+sita2)/2);
			//printf("%.3f,%.3f,%.3f,%.3f\n",distance[3]-1.7,distance[3]-distance[4]-1.7,distance[3],distance[4]);
			//printf("%.3f,%.3f,%.3f,%.3f\n",l1,l2,l2-l1,sita2);
			//printf("%.3f,%.3f,%.3f,%.3f\n",sita1,sita2,sita,distance[2]);
			tft_text_float_3(0, 4, l);
			tft_text_float_3(0, 5, sita);

			uint16_t slit;
			if( (250*tan(sita/180*3.1415926)/3+50)<=100&& (250*tan(sita/180*3.1415926)/3+50)>=0)
			{
				slit = (uint16_t)(250*tan(sita/180*3.1415926)/3+50);

			}
			tft_slideblock(0, 6, slit);
			//printf("%.3f,%.3f,%.3f\n",l1,l2,l);

			float resultMax,resultMin;
			uint32_t place;
			for(int i=9;i>=1;i--)
			{
				sita_last10[i]= sita_last10[i-1];
			}
			sita_last10[0] = sita;

			if(mode == 0)
			{
				HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, SET);
			}
			else
			{
				arm_max_f32(sita_last10, 10, &resultMax, &place);
				arm_min_f32(sita_last10, 10, &resultMin, &place);
				if(resultMax-resultMin>1.5)
					HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, RESET);
				else
					HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, SET);
//				if(sita_last10[0]-sita_last10[1]>1.5||sita_last10[0]-sita_last10[1]<-1.5)
//				{
//					HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, RESET);
//				}
//				else
//				{
//					HAL_GPIO_WritePin(RED_GPIO_Port, RED_Pin, SET);
//				}
			}

			if(isAdjust)
				Servo_con(90-sita);
			else
				Servo_con(90);



			countDida=0;
		}

		readyToFFT=0;

	}

}

//
//float data1[6400];
//float data2[6400];
//TIM3中断响应函数
void resTIM3()
{
	static int count = 0;
	static float voice[10][32];
	//将十个通道采样值保存
	for(int i=0;i<8;i++)
	{
		voice[i][count] = (float)ad_values[i]/65535.0*3.3;
	}

	if(++count>=32)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<32;j++)
			{
				voice_input[i][j] = voice[i][j];
			}
		}
		if(countDida<220)readyToFFT = 1;
		count=0;
	}

//	data1[count] = (float)ad_values[0]/65535.0*3.3;
//	data2[count] = (float)ad_values[1]/65535.0*3.3;
//	if(++count>=6400)
//	{
//		HAL_TIM_Base_Stop_IT(&htim3);
//		for(int i =0;i<6400;i++)
//		{
//			printf("%.5f,%.5f\r\n",data1[i],data2[i]);
//		}
//		//HAL_TIM_Base_Start_IT(&htim3);
//		//count=0;
//	}

}


void sort(float *p,int len)
{
	for(int i=0;i<len-1;i++)
	{
		for(int j=i+1;j<len;j++)
		{
			if(p[i]>p[j])
			{
				float temp;
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}




/*
 * 重写printf
 */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart6, (uint8_t*)&ch,1,HAL_MAX_DELAY);
	//HAL_UART_Transmit(&huart3, (uint8_t*)&ch,1,HAL_MAX_DELAY);
    return ch;
}
/*
 * 重写printf
 */
