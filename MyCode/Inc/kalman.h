/*
 * kalman.h
 *
 *  Created on: Jul 24, 2022
 *      Author: BGD
 */

#ifndef KALMAN_KALMAN_H_
#define KALMAN_KALMAN_H_

typedef struct
{
  /*���ö�*/
  float LastP;//�ϴι���Э����
  float Now_P;//��ǰ����Э����
  float out;//�������˲������
  float Kg;//����������
  float Q;
  float R;
} Kalman_Typedef;

void Kalman_Init(Kalman_Typedef *klm, const float klm_Q, const float klm_R);
void KalmanFilter(Kalman_Typedef *klm, float input);



#endif /* KALMAN_KALMAN_H_ */
