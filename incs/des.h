#ifndef DES
# define DES

#include "./base.h"

# define ENCRYPTION 5
# define DECRYPTION 6

typedef struct  s_keys
{
    char origin_key[16];
    char round_keys[16][48];
}               t_keys;

typedef struct  s_block
{
    char    raw[64];
    char    permuted[64];
    char    left[32];
    char    right[32];
    char    expanded[48];
    char    xored[48];
    char    s_boxed[32];
    char    p_boxed[32];
    char    processed[64];
}               t_block;

/*
**  CONST.c
*/
extern const u_int8_t expansion_permutation[48];
extern const u_int8_t s_boxes[8][64];
extern const u_int8_t p_box[32];
extern const u_int8_t initial_permutation[64];
extern const u_int8_t final_permutation[64];
extern const u_int8_t key_compression[48];
extern const u_int8_t key_permutation[56];

/*
**  KEY.c
*/
void create_all_round_keys(t_keys *keys, u_int8_t type);

/*
**  OPERATION.c
*/
void permute(char *input, char *output, const u_int8_t *array, int size);
void xor_bits_string(char *first, char *second, char *output, u_int64_t size);

/*
**  ROUND.c
*/
void prepare_rounds(t_message_des *msg, t_block *block, char *input);
void execute_round(t_block *block, t_keys *keys, u_int8_t round);





void print_binary_str(char *str, char *type, int size);

#endif