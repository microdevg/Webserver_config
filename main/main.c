#include "api_memory.h"
#include "esp_log.h"

static const char *TAG = "main";

void app_main(void)
{
    ESP_ERROR_CHECK(memory_init());

    // Guardar entero
    int valor = 1234;
    //memory_set(API_TYPE_INT, "mi_entero", &valor);

    // Guardar cadena
    //memory_set(API_TYPE_STRING, "mi_texto", "Hola ESP32");

    // Leer entero
    int valor_leido;
    if (memory_get(API_TYPE_INT, "mi_entero", &valor_leido) == ESP_OK)
        ESP_LOGI(TAG, "Entero leído: %d", valor_leido);

    // Leer cadena
    char *cadena = NULL;
    if (memory_get(API_TYPE_STRING, "mi_texto", &cadena) == ESP_OK) {
        ESP_LOGI(TAG, "Cadena leída: %s", cadena);
        free(cadena); // ¡Liberar memoria dinámica!
    }

    memory_deinit();
}