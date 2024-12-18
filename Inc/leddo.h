#ifndef LEDDO_H
#define LEDDO_H

#include "stm32f4xx_hal.h"

extern float Distance;
extern uint32_t prevalue;

// Hàm tính thời gian delay dựa trên khoảng cách
uint32_t LedDo_Update(float distance);

void Init_GPIO_TIM4(void);

// Hàm khởi tạo LED và Timer 4
void LedDo_Init(void);

// Hàm cập nhật Timer 4 với giá trị khoảng cách mới
void LedDo_UpdateTimer(float distance);

// Hàm điều khiển LED nhấp nháy
void LedDoNhapnhay(void);

#endif /* LEDDO_H */
