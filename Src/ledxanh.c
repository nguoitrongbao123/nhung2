#include "stm32f4xx.h"

void LedXanh_Init(void) {
    // Bước 1: Kích hoạt đồng hồ cho GPIOA và Timer 5
    RCC->AHB1ENR |= (1 << 0);    // Kích hoạt Clock cho GPIOA (bit 0)
    RCC->APB1ENR |= (1 << 3);    // Kích hoạt Clock cho Timer 5 (bit 3)

    // Bước 2: Cấu hình PA0 (Chân 0 của GPIOA) làm Output
    GPIOA->MODER &= ~(0x3 << (0 * 2)); // Xóa chế độ cũ của PA0
    GPIOA->MODER |= (0x1 << (0 * 2));  // Set PA0 làm Output

    // Bước 3: Cấu hình Timer 5
    // Prescaler: Chia từ 16 MHz xuống 1 MHz (Prescaler = 15)
    TIM5->PSC = 16-1;  

    // ARR: Tạo chu kỳ 1 giây (1 Hz)
    TIM5->ARR = 1000000/2-1;  // Tạo chu kỳ 1 giây (Prescaler 1 MHz và ARR = 1000000 ticks)

    // Bước 4: Cho phép Timer và tạo tín hiệu Update
    TIM5->CR1 |= (1 << 0);  // Kích hoạt Timer 5
}

void LedXanh_Toggle(void) {
    // Chức năng Toggle LED bằng cách sử dụng Timer
    if (TIM5->SR & (1 << 0)) {  // Kiểm tra xem tín hiệu update có xảy ra hay không
        TIM5->SR &= ~(1 << 0);   // Xóa cờ tín hiệu Update
        GPIOA->ODR ^= (1 << 0);  // Toggle LED (Chuyển đổi trạng thái của PA0)
    }
}
