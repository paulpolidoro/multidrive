#ifndef FONT_CONSOLAS_H
#define FONT_CONSOLAS_H

#include <stdint.h>

// Estrutura para armazenar os dados de cada caractere
// typedef struct {
//     const uint8_t *data; // Dados do bitmap
//     uint16_t width;      // Largura do caractere
//     uint16_t height;     // Altura do caractere
//     uint8_t dataSize;    // Tamanho dos dados
// } tImage;

// // Estrutura para mapear caracteres com seus bitmaps
// typedef struct {
//     long int code;       // Código ASCII do caractere
//     const tImage *image; // Ponteiro para a imagem do caractere
//     const int image_left;
//     const int image_top;
//     const int char_width;
//     const int char_height;
// } tChar;

// // Estrutura para a fonte completa
// typedef struct {
//     int length;          // Número de caracteres na fonte
//     const tChar *chars;  // Array de caracteres
// } tFont;

// Definição dos caracteres
static const uint8_t image_data_Consolas_0x41[] = {0x0f, 0xff, 0xff, 0x80, 0x5f, 0xff, 0xff, 0x80, 0xef, 0xff, 0xff, 0x30, 0xf7, 0xff, 0xfe, 0x70, 0xfb, 0xff, 0xfc, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xf8, 0x00, 0x01, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xe7, 0xff, 0xfe, 0x70, 0x4f, 0xff, 0xff, 0x20, 0x1f, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0x00, 0xcf, 0xff, 0xfe, 0x30, 0xe7, 0xff, 0xfc, 0x70, 0xf0, 0x00, 0x00, 0xf0, 0xf8, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xfc, 0x00, 0x01, 0xf0, 0xf8, 0x00, 0x01, 0xf0, 0xf0, 0x00, 0x00, 0xf0, 0xe0, 0x00, 0x00, 0x70, 0x40, 0x00, 0x00, 0x20};
static const uint8_t image_data_Consolas_0x42[] = {};
static const uint8_t image_data_Consolas_0x43[] = { };
static const uint8_t image_data_Consolas_0x31[] = { };
static const uint8_t image_data_Consolas_0x32[] = { };
static const uint8_t image_data_Consolas_0x33[] = { /* Dados para '3' */ };
static const uint8_t image_data_Consolas_0x34[] = { /* Dados para '4' */ };
static const uint8_t image_data_Consolas_0x35[] = { /* Dados para '5' */ };
static const uint8_t image_data_Consolas_0x36[] = { /* Dados para '6' */ };
static const uint8_t image_data_Consolas_0x37[] = { /* Dados para '7' */ };
static const uint8_t image_data_Consolas_0x38[] = { /* Dados para '8' */ };
static const uint8_t image_data_Consolas_0x39[] = { /* Dados para '9' */ };
static const uint8_t image_data_Consolas_0x30[] = { /* Dados para '0' */ };
static const uint8_t image_data_Consolas_0x2d[] = { /* Dados para '-' */ };
static const uint8_t image_data_Consolas_0x3a[] = { /* Dados para ':' */ };

// Mapear os caracteres para suas imagens
static const tImage Consolas_0x41 = { image_data_Consolas_0x41, 32, 50, 8 };
static const tImage Consolas_0x42 = { image_data_Consolas_0x42, 16, 33, 8 };
static const tImage Consolas_0x43 = { image_data_Consolas_0x43, 16, 33, 8 };
static const tImage Consolas_0x31 = { image_data_Consolas_0x31, 16, 33, 8 };
static const tImage Consolas_0x32 = { image_data_Consolas_0x32, 16, 33, 8 };
static const tImage Consolas_0x33 = { image_data_Consolas_0x33, 16, 33, 8 };
static const tImage Consolas_0x34 = { image_data_Consolas_0x34, 16, 33, 8 };
static const tImage Consolas_0x35 = { image_data_Consolas_0x35, 16, 33, 8 };
static const tImage Consolas_0x36 = { image_data_Consolas_0x36, 16, 33, 8 };
static const tImage Consolas_0x37 = { image_data_Consolas_0x37, 16, 33, 8 };
static const tImage Consolas_0x38 = { image_data_Consolas_0x38, 16, 33, 8 };
static const tImage Consolas_0x39 = { image_data_Consolas_0x39, 16, 33, 8 };
static const tImage Consolas_0x30 = { image_data_Consolas_0x30, 16, 33, 8 };
static const tImage Consolas_0x2d = { image_data_Consolas_0x2d, 16, 33, 8 };
static const tImage Consolas_0x3a = { image_data_Consolas_0x3a, 16, 33, 8 };

// Array de caracteres
static const tChar Consolas_array[] = {
    {0x41, &Consolas_0x41, 0, 0, 16, 33}, // 'A'
    {0x42, &Consolas_0x42, 0, 0, 16, 33}, // 'B'
    {0x43, &Consolas_0x43, 0, 0, 16, 33}, // 'C'
    {0x31, &Consolas_0x31, 0, 0, 16, 33}, // '1'
    {0x32, &Consolas_0x32, 0, 0, 16, 33}, // '2'
    {0x33, &Consolas_0x33, 0, 0, 16, 33}, // '3'
    {0x34, &Consolas_0x34, 0, 0, 16, 33}, // '4'
    {0x35, &Consolas_0x35, 0, 0, 16, 33}, // '5'
    {0x36, &Consolas_0x36, 0, 0, 16, 33}, // '6'
    {0x37, &Consolas_0x37, 0, 0, 16, 33}, // '7'
    {0x38, &Consolas_0x38, 0, 0, 16, 33}, // '8'
    {0x39, &Consolas_0x39, 0, 0, 16, 33}, // '9'
    {0x30, &Consolas_0x30, 0, 0, 16, 33}, // '0'
    {0x2d, &Consolas_0x2d, 0, 0, 16, 33}, // '-'
    {0x3a, &Consolas_0x3a, 0, 0, 16, 33}, // ':'
};

// Fonte completa
const tFont Consolas = { sizeof(Consolas_array) / sizeof(tChar), Consolas_array };

#endif // FONT_CONSOLAS_H