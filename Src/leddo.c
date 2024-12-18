
#include "leddo.h"

// Biến khoảng cách (giả lập ở đây, có thể thay đổi từ cảm biến)


// Hàm tính thời gian delay dựa trên khoảng cách
uint32_t LedDo_Update(float distance)
{
    uint32_t delay_time;

    if (distance <= 2)
    {
        delay_time = 400; // 400Hz
    }
    else if (distance > 2 && distance <= 4)
    {
        delay_time = 800; // 800kHz
    }
    else if (distance > 4 && distance <= 6)
    {
        delay_time = 1200; // 1200kHz
    }
    else if (distance > 6 && distance <= 8)
    {
        delay_time = 1600; // 1600Hz
    }
    else if (distance > 8 && distance <= 10)
    {
        delay_time = 2000; // 2000Hz
    }
    else if (distance > 10 && distance <= 12)
    {
        delay_time = 2400; // 2400Hz
    }
    else if (distance > 12 && distance <= 14)
    {
        delay_time = 2800; // 2800Hz
    }
    else if (distance > 14 && distance <= 16)
    {
        delay_time = 3200; // 3200Hz
    }
    else if (distance > 16 && distance <= 18)
    {
        delay_time = 3600; // 3600Hz
    }
    else if (distance > 18 && distance <= 25)
    {
        delay_time = 5000; // 4Khz
    }
    else
    {
        delay_time = 0; // LED tắt nếu khoảng cách > 25cm
    }
    return delay_time;
}

/* Init GPIO of Timer */
void Init_GPIO_TIM4(void)
{
    RCC->AHB1ENR |= (1 << 1);
    GPIOB->MODER |= (1 << 14);
}

// Hàm khởi tạo LED và Timer
void LedDo_Init(void)
{
    RCC->APB1ENR |= (1 << 2); // Kích hoạt clock Timer 4

    // Cấu hình Timer 4
    TIM4->PSC = (1600 - 1);           // Chia tần số từ 16 MHz xuống 10kHz
    TIM4->ARR = (10000- 1);           // Set 5Khz
    TIM4->CR1 |= (1 << 0); // Bật Timer 4
}

// Hàm cập nhật Timer với giá trị khoảng cách mới
void LedDo_UpdateTimer(float distance)
{
	uint32_t value = LedDo_Update(distance);
	if(value != prevalue)
	{
		TIM4->ARR = value;				// Cập nhật ARR mới
		prevalue = value;
		TIM4->CR1 |= (1 << 7);
		TIM4->EGR |= (1 << 0);          // Re-initialize Timer
	}

}

// Hàm điều khiển LED nhấp nháy
void LedDoNhapnhay(void)
{
    if ((TIM4->SR & 0x1) && (prevalue != 0))
    {                           // Kiểm tra cờ Update Event của Timer 4
        TIM4->SR &= ~(0x1);     // Xóa cờ
        GPIOB->ODR ^= (1 << 7); // Đảo trạng thái LED
    }else
    {
    	GPIOB->ODR &= ~(1 << 7);
    }
}

