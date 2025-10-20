#include "unity.h"
#include "api_memory.h"
#include "mock_nvs_flash.h"
#include "mock_nvs.h"
#include <string.h>

// Variables simuladas
static int dummy_int;
static char *dummy_str;

// ---------------------------------------------------------------------------
// SETUP / TEARDOWN
// ---------------------------------------------------------------------------
void setUp(void)
{
    dummy_int = 0;
    dummy_str = NULL;
}

void tearDown(void)
{
    if (dummy_str) {
        free(dummy_str);
        dummy_str = NULL;
    }
}

// ---------------------------------------------------------------------------
// TESTS
// ---------------------------------------------------------------------------

// Test: inicialización correcta
void test_memory_init_ok(void)
{
    nvs_flash_init_ExpectAndReturn(ESP_OK);
    nvs_open_ExpectAndReturn("app_mem", NVS_READWRITE, NULL, ESP_OK);

    esp_err_t res = memory_init();
    TEST_ASSERT_EQUAL(ESP_OK, res);
}

// Test: escritura de un entero
void test_memory_set_int(void)
{
    int valor = 42;

    nvs_set_i32_ExpectAndReturn(0, "clave_int", valor, ESP_OK);
    nvs_commit_ExpectAndReturn(0, ESP_OK);

    esp_err_t res = memory_set(API_TYPE_INT, "clave_int", &valor);
    TEST_ASSERT_EQUAL(ESP_OK, res);
}

// Test: escritura de una cadena
void test_memory_set_string(void)
{
    const char *texto = "Hola";

    nvs_set_str_ExpectAndReturn(0, "clave_str", texto, ESP_OK);
    nvs_commit_ExpectAndReturn(0, ESP_OK);

    esp_err_t res = memory_set(API_TYPE_STRING, "clave_str", texto);
    TEST_ASSERT_EQUAL(ESP_OK, res);
}

// Test: intento de guardar BLOB → no soportado
void test_memory_set_blob_not_supported(void)
{
    uint8_t blob[3] = {1, 2, 3};

    esp_err_t res = memory_set(API_TYPE_BLOB, "clave_blob", blob);
    TEST_ASSERT_EQUAL(ESP_ERR_NOT_SUPPORTED, res);
}

// Test: lectura de entero
void test_memory_get_int(void)
{
    int out_val = 0;
    nvs_get_i32_ExpectAndReturn(0, "clave_int", &out_val, ESP_OK);

    esp_err_t res = memory_get(API_TYPE_INT, "clave_int", &out_val);
    TEST_ASSERT_EQUAL(ESP_OK, res);
}

// Test: lectura de string
void test_memory_get_string(void)
{
    char *out_str = NULL;
    nvs_get_str_ExpectAnyArgsAndReturn(ESP_OK);

    esp_err_t res = memory_get(API_TYPE_STRING, "clave_str", &out_str);
    TEST_ASSERT_EQUAL(ESP_OK, res);
}
