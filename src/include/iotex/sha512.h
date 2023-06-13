#ifndef IOTEX_SHA512_H
#define IOTEX_SHA512_H

#include "build_info.h"

#include <stddef.h>
#include <stdint.h>

/** SHA-512 input data was malformed. */
#define IOTEX_ERR_SHA512_BAD_INPUT_DATA                 -0x0075

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(IOTEX_SHA512_ALT)
// Regular implementation
//

/**
 * \brief          The SHA-512 context structure.
 *
 *                 The structure is used both for SHA-384 and for SHA-512
 *                 checksum calculations. The choice between these two is
 *                 made in the call to iotex_sha512_starts().
 */
typedef struct iotex_sha512_context
{
    uint64_t total[2];          /*!< The number of Bytes processed. */
    uint64_t state[8];          /*!< The intermediate digest state. */
    unsigned char buffer[128];  /*!< The data block being processed. */
#if defined(IOTEX_SHA384_C)
    int is384;                  /*!< Determines which function to use:
                                                      0: Use SHA-512, or 1: Use SHA-384. */
#endif
}
iotex_sha512_context;

#else  /* IOTEX_SHA512_ALT */
#include "sha512_alt.h"
#endif /* IOTEX_SHA512_ALT */

/**
 * \brief          This function initializes a SHA-512 context.
 *
 * \param ctx      The SHA-512 context to initialize. This must
 *                 not be \c NULL.
 */
void iotex_sha512_init( iotex_sha512_context *ctx );

/**
 * \brief          This function clears a SHA-512 context.
 *
 * \param ctx      The SHA-512 context to clear. This may be \c NULL,
 *                 in which case this function does nothing. If it
 *                 is not \c NULL, it must point to an initialized
 *                 SHA-512 context.
 */
void iotex_sha512_free( iotex_sha512_context *ctx );

/**
 * \brief          This function clones the state of a SHA-512 context.
 *
 * \param dst      The destination context. This must be initialized.
 * \param src      The context to clone. This must be initialized.
 */
void iotex_sha512_clone( iotex_sha512_context *dst,
                           const iotex_sha512_context *src );

/**
 * \brief          This function starts a SHA-384 or SHA-512 checksum
 *                 calculation.
 *
 * \param ctx      The SHA-512 context to use. This must be initialized.
 * \param is384    Determines which function to use. This must be
 *                 either \c 0 for SHA-512, or \c 1 for SHA-384.
 *
 * \note           When \c IOTEX_SHA384_C is not defined,
 *                 \p is384 must be \c 0, or the function will return
 *                 #IOTEX_ERR_SHA512_BAD_INPUT_DATA.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int iotex_sha512_starts( iotex_sha512_context *ctx, int is384 );

/**
 * \brief          This function feeds an input buffer into an ongoing
 *                 SHA-512 checksum calculation.
 *
 * \param ctx      The SHA-512 context. This must be initialized
 *                 and have a hash operation started.
 * \param input    The buffer holding the input data. This must
 *                 be a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data in Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int iotex_sha512_update( iotex_sha512_context *ctx,
                           const unsigned char *input,
                           size_t ilen );

/**
 * \brief          This function finishes the SHA-512 operation, and writes
 *                 the result to the output buffer.
 *
 * \param ctx      The SHA-512 context. This must be initialized
 *                 and have a hash operation started.
 * \param output   The SHA-384 or SHA-512 checksum result.
 *                 This must be a writable buffer of length \c 64 bytes
 *                 for SHA-512, \c 48 bytes for SHA-384.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int iotex_sha512_finish( iotex_sha512_context *ctx,
                           unsigned char *output );

/**
 * \brief          This function processes a single data block within
 *                 the ongoing SHA-512 computation.
 *                 This function is for internal use only.
 *
 * \param ctx      The SHA-512 context. This must be initialized.
 * \param data     The buffer holding one block of data. This
 *                 must be a readable buffer of length \c 128 Bytes.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int iotex_internal_sha512_process( iotex_sha512_context *ctx,
                                     const unsigned char data[128] );

/**
 * \brief          This function calculates the SHA-512 or SHA-384
 *                 checksum of a buffer.
 *
 *                 The function allocates the context, performs the
 *                 calculation, and frees the context.
 *
 *                 The SHA-512 result is calculated as
 *                 output = SHA-512(input buffer).
 *
 * \param input    The buffer holding the input data. This must be
 *                 a readable buffer of length \p ilen Bytes.
 * \param ilen     The length of the input data in Bytes.
 * \param output   The SHA-384 or SHA-512 checksum result.
 *                 This must be a writable buffer of length \c 64 bytes
 *                 for SHA-512, \c 48 bytes for SHA-384.
 * \param is384    Determines which function to use. This must be either
 *                 \c 0 for SHA-512, or \c 1 for SHA-384.
 *
 * \note           When \c IOTEX_SHA384_C is not defined, \p is384 must
 *                 be \c 0, or the function will return
 *                 #IOTEX_ERR_SHA512_BAD_INPUT_DATA.
 *
 * \return         \c 0 on success.
 * \return         A negative error code on failure.
 */
int iotex_sha512( const unsigned char *input,
                    size_t ilen,
                    unsigned char *output,
                    int is384 );

#if defined(IOTEX_SELF_TEST)

 /**
 * \brief          The SHA-384 or SHA-512 checkup routine.
 *
 * \return         \c 0 on success.
 * \return         \c 1 on failure.
 */
int iotex_sha512_self_test( int verbose );
#endif /* IOTEX_SELF_TEST */

#ifdef __cplusplus
}
#endif

#endif /* iotex_sha512.h */
