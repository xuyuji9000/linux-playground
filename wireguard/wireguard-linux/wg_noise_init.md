This file is used to document the source code annotation about `wg_noise_init`.


``` C
// drivers/net/wireguard/noise.c

void __init wg_noise_init(void)
{
        struct blake2s_state blake;

        blake2s(handshake_init_chaining_key, handshake_name, NULL,
                NOISE_HASH_LEN, sizeof(handshake_name), 0); 
        blake2s_init(&blake, NOISE_HASH_LEN);
        blake2s_update(&blake, handshake_init_chaining_key, NOISE_HASH_LEN);
        blake2s_update(&blake, identifier_name, sizeof(identifier_name));
        blake2s_final(&blake, handshake_init_hash);
}
```

``` C
// include/crypto/blake2s.h
static inline void __blake2s_init(struct blake2s_state *state, size_t outlen,
                                  const void *key, size_t keylen)
{
        state->h[0] = BLAKE2S_IV0 ^ (0x01010000 | keylen << 8 | outlen);
        state->h[1] = BLAKE2S_IV1;
        state->h[2] = BLAKE2S_IV2;
        state->h[3] = BLAKE2S_IV3;
        state->h[4] = BLAKE2S_IV4;
        state->h[5] = BLAKE2S_IV5;
        state->h[6] = BLAKE2S_IV6;
        state->h[7] = BLAKE2S_IV7;
        state->t[0] = 0;
        state->t[1] = 0;
        state->f[0] = 0;
        state->f[1] = 0;
        state->buflen = 0;
        state->outlen = outlen;
        if (keylen) {
                memcpy(state->buf, key, keylen);
                memset(&state->buf[keylen], 0, BLAKE2S_BLOCK_SIZE - keylen);
                state->buflen = BLAKE2S_BLOCK_SIZE;
        }   
}

static inline void blake2s_init(struct blake2s_state *state,
                                const size_t outlen)
{
        __blake2s_init(state, outlen, NULL, 0); 
}
```

``` C
// lib/crypto/blake2s.c

void blake2s_update(struct blake2s_state *state, const u8 *in, size_t inlen)
{
        __blake2s_update(state, in, inlen, blake2s_compress);
}
EXPORT_SYMBOL(blake2s_update);
```

``` C
// include/crypto/internal/blake2s.h

/* Helper functions for BLAKE2s shared by the library and shash APIs */

static inline void __blake2s_update(struct blake2s_state *state,
                                    const u8 *in, size_t inlen,
                                    blake2s_compress_t compress)
{
        const size_t fill = BLAKE2S_BLOCK_SIZE - state->buflen;

        if (unlikely(!inlen))
                return;
        if (inlen > fill) {
                memcpy(state->buf + state->buflen, in, fill);
                (*compress)(state, state->buf, 1, BLAKE2S_BLOCK_SIZE);
                state->buflen = 0;
                in += fill;
                inlen -= fill;
        }   
        if (inlen > BLAKE2S_BLOCK_SIZE) {
                const size_t nblocks = DIV_ROUND_UP(inlen, BLAKE2S_BLOCK_SIZE);
                /* Hash one less (full) block than strictly possible */
                (*compress)(state, in, nblocks - 1, BLAKE2S_BLOCK_SIZE);
                in += BLAKE2S_BLOCK_SIZE * (nblocks - 1); 
                inlen -= BLAKE2S_BLOCK_SIZE * (nblocks - 1); 
        }   
        memcpy(state->buf + state->buflen, in, inlen);
        state->buflen += inlen;
}

```

``` C
// lib/crypto/blake2s.c

#if IS_ENABLED(CONFIG_CRYPTO_ARCH_HAVE_LIB_BLAKE2S)
#  define blake2s_compress blake2s_compress_arch
#else
#  define blake2s_compress blake2s_compress_generic
#endif
```

``` C
// lib/crypto/blake2s-generic.c

void blake2s_compress_generic(struct blake2s_state *state,const u8 *block,
                              size_t nblocks, const u32 inc)
{
    // ...
}

EXPORT_SYMBOL(blake2s_compress_generic);

```



