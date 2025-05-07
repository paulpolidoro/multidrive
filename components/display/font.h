#ifndef FONT_H
#define FONT_H

#include <stdint.h>

// Estrutura para armazenar os dados de cada caractere
typedef struct {
    const uint8_t *data; // Dados do bitmap
    uint16_t width;      // Largura do caractere
    uint16_t height;     // Altura do caractere
    uint8_t dataSize;    // Tamanho dos dados
} tImage;

// Estrutura para mapear caracteres com seus bitmaps
typedef struct {
    long int code;       // Código ASCII do caractere
    const tImage *image; // Ponteiro para a imagem do caractere
    const int image_left;
    const int image_top;
    const int char_width;
    const int char_height;
} tChar;

// Estrutura para a fonte completa
typedef struct {
    int length;          // Número de caracteres na fonte
    const tChar *chars;  // Array de caracteres
} tFont;

#endif // FONT_H