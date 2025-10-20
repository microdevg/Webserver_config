/**
 * @file api_memory.h
 * @brief Proporciona una interfaz para un mapa de memoria de aplicación persistente
 * utilizando el servicio de Almacenamiento No Volátil (NVS) de ESP-IDF.
 *
 * Este módulo actúa como una capa de abstracción para que la aplicación
 * pueda leer y escribir datos clave-valor de forma persistente.
 * Está diseñado para ser de uso general, facilitando la gestión de
 * configuraciones y estados.
 */

#ifndef API_MEMORY_H
#define API_MEMORY_H

#include "esp_err.h"
#include <stddef.h> // Para size_t

/**
 * @brief Inicializa el módulo de memoria.
 *
 * Abre el espacio de nombres NVS dedicado para la memoria de la aplicación.
 * Debe llamarse una vez antes de cualquier otra función de 'memory_'.
 *
 * @return ESP_OK si la inicialización fue exitosa.
 * @return Otros códigos de error de esp_err.h si falla la inicialización de NVS.
 */
esp_err_t memory_init(void);

/**
 * @brief Desinicializa el módulo de memoria.
 *
 * Libera los recursos asociados al módulo de memoria (cierra el handle NVS).
 *
 * @return Siempre devuelve ESP_OK.
 */
esp_err_t memory_deinit(void);

/**
 * @brief Obtiene el valor asociado a una clave (key) y lo almacena en un buffer.
 *
 * Esta función recupera datos de NVS de cualquier tipo (entero, cadena, binario)
 * de hasta 'len' bytes y lo copia en el 'buffer' proporcionado.
 *
 * @param key Cadena de texto única para identificar el dato (máx. 15 caracteres).
 * @param buffer Puntero al buffer donde se almacenarán los datos leídos.
 * @param len Puntero al tamaño del buffer de entrada. Al salir, contiene el
 * tamaño real de los datos leídos.
 * @return ESP_OK si la lectura fue exitosa.
 * @return ESP_ERR_NVS_NOT_FOUND si la clave no existe.
 * @return ESP_ERR_NVS_INVALID_LENGTH si el buffer es demasiado pequeño.
 * @return Otros códigos de error de esp_err.h en caso de fallo.
 */
esp_err_t memory_get(const char *key, void *buffer, size_t *len);

/**
 * @brief Establece el valor asociado a una clave (key).
 *
 * Esta función escribe datos binarios (o cualquier tipo de dato) en NVS
 * bajo la clave especificada.
 *
 * @param key Cadena de texto única para identificar el dato (máx. 15 caracteres).
 * @param buffer Puntero a los datos que se van a escribir.
 * @param len El tamaño de los datos en bytes a escribir.
 * @return ESP_OK si la escritura fue exitosa.
 * @return ESP_ERR_NVS_KEY_TOO_LONG si la clave excede el límite.
 * @return ESP_ERR_NVS_VALUE_TOO_LONG si los datos exceden el límite de tamaño.
 * @return Otros códigos de error de esp_err.h en caso de fallo.
 */
esp_err_t memory_set(const char *key, const void *buffer, size_t len);

#endif // API_MEMORY_H
