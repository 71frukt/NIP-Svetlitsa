// #include "Lustre/lustre.hpp"

// namespace Esp32Soft
// {

// void Lustre::turnOnFluorescentEffect (uint8_t targetBrightness)
// {
//     if (targetBrightness > 100)
//         targetBrightness = 100;

//     // 1. Предварительная задержка (эмуляция нагрева катодов)
//     SetBrightness(1); // Еле заметное свечение
//     delay(random(200, 600)); 

//     // 2. Серия вспышек (3-6 попыток)
//     int attempts = random(3, 7);
//     int pauseDuration = 400; // Начальная пауза между вспышками (мс)

//     for (int i = 0; i < attempts; i++) {
//         // Вспышка:
//         // Яркость случайная, от 50% до 100%, чтобы имитировать нестабильность дуги
//         uint8_t flashBrightness = random(50, 101); 
//         SetBrightness(flashBrightness);
        
//         // Длительность вспышки очень короткая (20-80 мс)
//         delay(random(20, 80));

//         // Гашение:
//         SetBrightness(0);

//         // Пауза перед следующей попыткой.
//         // С каждым шагом пауза уменьшается на 20-30%, имитируя ионизацию газа.
//         delay(pauseDuration);
//         pauseDuration = (int)(pauseDuration * random(60, 80) / 100.0);
        
//         // Защита от слишком короткой паузы (не менее 20 мс)
//         if (pauseDuration < 20) pauseDuration = 20;
//     }

//     // 3. Финальное включение
//     // Иногда лампы включаются не сразу на 100%, а "проседают" на долю секунды
//     SetBrightness(targetBrightness);
//     delay(50);
//     SetBrightness(targetBrightness * 0.8); // Легкое проседание
//     delay(100);
//     SetBrightness(targetBrightness);       // Стабильная работа
// }

// }