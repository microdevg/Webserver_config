#include "api_memory.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include <stdlib.h>
#include <string.h>

static const char *TAG = "api_memory";
static nvs_handle_t s_nvs_handle = 0;

#define NAMESPACE_NAME "app_memory"  // Espacio de nombres reservado

// ============================================================
// Inicialización / Desinicialización
// ============================================================

esp_err_t memory_init(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error inicializando NVS: %s", esp_err_to_name(err));
        return err;
    }

    err = nvs_open(NAMESPACE_NAME, NVS_READWRITE, &s_nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error abriendo namespace NVS: %s", esp_err_to_name(err));
    }
    return err;
}

esp_err_t memory_deinit(void)
{
    if (s_nvs_handle) {
        nvs_close(s_nvs_handle);
        s_nvs_handle = 0;
    }
    return ESP_OK;
}

// ============================================================
// Lectura (GET)
// ============================================================

esp_err_t memory_get(api_memory_type_t type, const char *key, void *data_ptr)
{
    if (!s_nvs_handle) return ESP_ERR_INVALID_STATE;
    if (!key || !data_ptr) return ESP_ERR_INVALID_ARG;

    esp_err_t err;

    switch (type) {
    case API_TYPE_INT: {
        int32_t value = 0;
        err = nvs_get_i32(s_nvs_handle, key, &value);
        if (err == ESP_OK) {
            *(int32_t *)data_ptr = value;
        }
        break;
    }

    case API_TYPE_STRING: {
        size_t required_size = 0;
        err = nvs_get_str(s_nvs_handle, key, NULL, &required_size);
        if (err == ESP_OK) {
            char *buf = malloc(required_size);
            if (!buf) return ESP_ERR_NO_MEM;
            err = nvs_get_str(s_nvs_handle, key, buf, &required_size);
            if (err == ESP_OK) {
                *(char **)data_ptr = buf; // asigna al puntero del usuario
            } else {
                free(buf);
            }
        }
        break;
    }

    case API_TYPE_BLOB: {
        size_t required_size = 0;
        err = nvs_get_blob(s_nvs_handle, key, NULL, &required_size);
        if (err == ESP_OK) {
            void *buf = malloc(required_size);
            if (!buf) return ESP_ERR_NO_MEM;
            err = nvs_get_blob(s_nvs_handle, key, buf, &required_size);
            if (err == ESP_OK) {
                *(void **)data_ptr = buf; // asigna al puntero del usuario
            } else {
                free(buf);
            }
        }
        break;
    }

    default:
        err = ESP_ERR_NOT_SUPPORTED;
        break;
    }

    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Error al leer clave '%s': %s", key, esp_err_to_name(err));
    }

    return err;
}

// ============================================================
// Escritura (SET)
// ============================================================

esp_err_t memory_set(api_memory_type_t type, const char *key, const void *data)
{
    if (!s_nvs_handle) return ESP_ERR_INVALID_STATE;
    if (!key || !data) return ESP_ERR_INVALID_ARG;

    esp_err_t err;

    switch (type) {
    case API_TYPE_INT:
        err = nvs_set_i32(s_nvs_handle, key, *(int32_t *)data);
        break;

    case API_TYPE_STRING:
        err = nvs_set_str(s_nvs_handle, key, (const char *)data);
        break;

    case API_TYPE_BLOB:
        err = ESP_ERR_NOT_SUPPORTED;  // SET de blob requiere longitud
        break;

    default:
        err = ESP_ERR_INVALID_ARG;
        break;
    }

    if (err == ESP_OK) {
        err = nvs_commit(s_nvs_handle);
    }

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error al escribir clave '%s': %s", key, esp_err_to_name(err));
    }

    return err;
}
