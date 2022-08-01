/*
 * kalman.c
 *
 *  Created on: Jul 24, 2022
 *      Author: BGD
 */

#include "kalman.h"

void KalmanFilter(Kalman_Typedef *klm, float input)
{
    //Ԥ��Э����̣�kʱ��ϵͳ����Э���� = k-1ʱ�̵�ϵͳЭ���� + ��������Э����
    klm->Now_P = klm->LastP + klm->Q;
    //���������淽�̣����������� = kʱ��ϵͳ����Э���� / ��kʱ��ϵͳ����Э���� + �۲�����Э���
    klm->Kg = klm->Now_P / (klm->Now_P + klm->R);
    //��������ֵ���̣�kʱ��״̬����������ֵ = ״̬������Ԥ��ֵ + ���������� * ������ֵ - ״̬������Ԥ��ֵ��
    klm->out = klm->out + klm->Kg * (input -klm->out);//��Ϊ��һ�ε�Ԥ��ֵ������һ�ε����ֵ
    //����Э�����: ���ε�ϵͳЭ����� kfp->LastP ����һ������׼����
    klm->LastP = (1-klm->Kg) * klm->Now_P;
}

void Kalman_Init(Kalman_Typedef *klm, const float klm_Q, const float klm_R)//�¶�klm_Q=0.01 klm_R=0.25
{
	klm->LastP=0.02;	//�ϴι���Э����
	klm->Now_P=0;			//��ǰ����Э����
	klm->out=0;				//�������˲������
	klm->Kg=0;				//����������
	klm->Q=klm_Q;			//Q:��������Э���� Q�������˲��������ƽ���̶ȣ�QԽСԽƽ��;
	klm->R=klm_R;			//R:�۲�����Э���� R���������˲����������ʵ�����ߵ�����̶ȣ�RԽСԽ�ӽ�(����Խ��)
}
