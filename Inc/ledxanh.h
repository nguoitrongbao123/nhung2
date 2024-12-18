#define __LEDXANH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"  // Đảm bảo rằng bạn sử dụng đúng thư viện STM32 cho vi xử lý của mình

// Khai báo các hàm trong thư viện LedXanh
void LedXanh_Init(void);       // Khởi tạo LED xanh và Timer
void LedXanh_Toggle(void);     // Hàm Toggle để thay đổi trạng thái LED

#ifdef __cplusplus
}
#endif

