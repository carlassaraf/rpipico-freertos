#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Tarea de blinky
 * @param params puntero a parametros de tarea
*/
void task_blink(void *params) {
    // Inicializacion de GPIO 25 como salida
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while(1) {
        // Leo el GPIO 25 y escribo su estado contrario
        gpio_put(PICO_DEFAULT_LED_PIN, !gpio_get(PICO_DEFAULT_LED_PIN));
        // Bloqueo la tarea por medio segundo
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Programa principal
*/
int main(void) {
    // Creo tarea
    xTaskCreate(
        task_blink,                 // Puntero a funcion para llamar
        "Task Blink",               // Nombre para debuggear
        configMINIMAL_STACK_SIZE,   // Espacio en stack reservado 
        NULL,                       // Parametros
        tskIDLE_PRIORITY + 1UL,     // Prioridad mayor que la Idle
        NULL                        // Sin handle
    );

    // Arranco el scheduler
    vTaskStartScheduler();
}
