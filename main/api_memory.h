#ifndef API_MEMORY_H
#define API_MEMORY_H

#include "esp_err.h"
#include <stddef.h> // Para size_t
#include <stdint.h> // Para int32_t

/**
 * @brief Define los tipos de datos soportados por la API de memoria.
 */
typedef enum {
    API_TYPE_BLOB = 0, ///< Tipo binario genérico. (Para GET: Asigna dinámicamente; Para SET: Requiere un parámetro de longitud, por lo que su SET no está implementado en esta versión simple).
    API_TYPE_STRING,   ///< Tipo cadena de texto (null-terminated).
    API_TYPE_INT,      ///< Tipo entero de 32 bits (i32).
    // Se pueden añadir más tipos (u64, i64, etc.) aquí
} api_memory_type_t;


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
 * Esta función recupera datos de NVS de cualquier tipo.
 *
 * @note Para STRING/BLOB, esta función asigna dinámicamente la memoria necesaria (malloc).
 * El llamador DEBE liberar la memoria usando free() después de usarla.
 *
 * @param type Especifica el tipo de dato que se espera leer (INT, STRING, BLOB).
 * @param key Cadena de texto única para identificar el dato (máx. 15 caracteres).
 * @param data_ptr Puntero a la ubicación de los datos:
 * - Si type es API_TYPE_INT: Debe ser int* (e.g., &mi_entero).
 * - Si type es API_TYPE_STRING/BLOB: Debe ser un puntero a un puntero (e.g., char **mi_cadena).
 * @return ESP_OK si la lectura fue exitosa.
 * @return ESP_ERR_NVS_NOT_FOUND si la clave no existe.
 * @return ESP_ERR_NO_MEM si falla la asignación dinámica (malloc).
 * @return Otros códigos de error de esp_err.h en caso de fallo.
 */
esp_err_t memory_get(api_memory_type_t type, const char *key, void *data_ptr);

/**
 * @brief Establece el valor asociado a una clave (key).
 *
 * Esta función escribe datos en NVS bajo la clave especificada, infiriendo la longitud.
 *
 * @note El tipo API_TYPE_BLOB NO está soportado en esta firma de API, ya que su longitud
 * no se puede inferir. Use API_TYPE_STRING para datos no enteros.
 *
 * @param type Especifica el tipo de dato que se va a escribir (INT, STRING).
 * @param key Cadena de texto única para identificar el dato (máx. 15 caracteres).
 * @param data Puntero a los datos que se van a escribir.
 * - Si type es API_TYPE_INT: Debe ser int* (e.g., &mi_entero).
 * - Si type es API_TYPE_STRING: Debe ser char* (e.g., mi_cadena).
 * @return ESP_OK si la escritura fue exitosa.
 * @return ESP_ERR_NOT_SUPPORTED si se intenta usar API_TYPE_BLOB.
 * @return Otros códigos de error de esp_err.h en caso de fallo.
 */
esp_err_t memory_set(api_memory_type_t type, const char *key, const void *data);

#endif // API_MEMORY_H
