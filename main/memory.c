/**
 * @file api_memory.c
 * @brief Implementación del módulo de mapa de memoria persistente utilizando ESP-IDF NVS.
 *
 * NOTA: Esta versión contiene funciones stub que devuelven ESP_OK.
 * La implementación real de NVS debe agregarse para la funcionalidad completa.
 */

#include "memory.h"
#include "nvs_flash.h" // Necesario para inicializar la partición NVS
#include "nvs.h"       // Necesario para manejar los espacios de nombres NVS
#include "esp_log.h"   // Para logging/depuración

// Definición de la etiqueta para el log
static const char *TAG = "API_MEMORY";

// Handle global para la instancia NVS
// Usado por todas las funciones memory_get/set
static nvs_handle_t memory_nvs_handle;

// Nombre del namespace que usará esta API en NVS
#define NVS_NAMESPACE "app_memory"


/**
 * @brief Inicializa el módulo de memoria.
 */
esp_err_t memory_init(void)
{
    // --- STUB: La implementación real debería inicializar NVS y abrir el namespace ---
    ESP_LOGI(TAG, "memory_init: Inicialización STUB (Devuelve ESP_OK)");
    return ESP_OK;
}

/**
 * @brief Desinicializa el módulo de memoria.
 */
esp_err_t memory_deinit(void)
{
    // --- STUB: La implementación real debería cerrar el handle NVS ---
    ESP_LOGI(TAG, "memory_deinit: Desinicialización STUB (Devuelve ESP_OK)");
    // if (memory_nvs_handle != 0) { nvs_close(memory_nvs_handle); }
    return ESP_OK;
}

/**
 * @brief Obtiene el valor asociado a una clave (key).
 */
esp_err_t memory_get(const char *key, void *buffer, size_t *len)
{
    // --- STUB: La implementación real debería usar nvs_get_blob/get_str/get_i32 etc. ---
    ESP_LOGI(TAG, "memory_get: Intentando leer clave '%s' (STUB)", key);

    // Lógica STUB para simular una lectura exitosa:
    if (buffer && len) {
        // En un caso real, len sería el tamaño del dato leído.
        // Aquí solo simulamos que el buffer es lo suficientemente grande.
    }

    return ESP_OK;
}

/**
 * @brief Establece el valor asociado a una clave (key).
 */
esp_err_t memory_set(const char *key, const void *buffer, size_t len)
{
    // --- STUB: La implementación real debería usar nvs_set_blob/set_str/set_i32 etc. y nvs_commit ---
    ESP_LOGI(TAG, "memory_set: Intentando escribir clave '%s' de tamaño %zu bytes (STUB)", key, len);
    return ESP_OK;
}