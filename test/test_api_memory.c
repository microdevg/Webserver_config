#include "unity.h"
#include "api_memory.h"
#include "mock_nvs_flash.h"
#include "mock_nvs.h"
#include <string.h>



static nvs_handle_t s_nvs_handle = 0;

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
    s_nvs_handle = 123;

  
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
    nvs_open_ExpectAnyArgsAndReturn(ESP_OK);
    //nvs_open_ExpectAndReturn("app_memory", NVS_READWRITE, 0, ESP_OK);

    esp_err_t res = memory_init();

    TEST_ASSERT_EQUAL(ESP_OK, res);
}
void test_memory_set_int(void)
{
    int valor = 42;
    char* key = "clave_int";


    nvs_set_i32_ExpectAndReturn(
        s_nvs_handle,            
        key, 
        (int32_t)valor,          // 👈 CORRECCIÓN 1: Pasa el VALOR (42), no la dirección.
        ESP_OK
    );

    // 2. MOCK: nvs_commit
    // nvs_commit solo necesita el handle.
    nvs_commit_ExpectAndReturn(
        s_nvs_handle,            // 👈 CORRECCIÓN 2: Pasa el handle (123), no el 0.
        ESP_OK
    );

    // 3. Llamada a la función bajo prueba
    esp_err_t res = memory_set(API_TYPE_INT, key, &valor);
    
    // 4. Verificación
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
