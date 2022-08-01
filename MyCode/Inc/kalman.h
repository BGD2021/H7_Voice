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
  /*不用动*/
  float LastP;//上次估算协方差
  float Now_P;//当前估算协方差
  float out;//卡尔曼滤波器输出
  float Kg;//卡尔曼增益
  float Q;
  float R;
} Kalman_Typedef;

void Kalman_Init(Kalman_Typedef *klm, const float klm_Q, const float klm_R);
void KalmanFilter(Kalman_Typedef *klm, float input);



#endif /* KALMAN_KALMAN_H_ */
