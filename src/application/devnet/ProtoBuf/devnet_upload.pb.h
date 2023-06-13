/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.7 */

#ifndef PB_DEVNET_UPLOAD_PB_H_INCLUDED
#define PB_DEVNET_UPLOAD_PB_H_INCLUDED
#include "pb.h"
#include "header.pb.h"
#include "Payload.pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _Upload {
    bool has_header;
    Header header;
    bool has_payload;
    Payload payload;
} Upload;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define Upload_init_default                      {false, Header_init_default, false, Payload_init_default}
#define Upload_init_zero                         {false, Header_init_zero, false, Payload_init_zero}

/* Field tags (for use in manual encoding/decoding) */
#define Upload_header_tag                        1
#define Upload_payload_tag                       2

/* Struct field encoding specification for nanopb */
#define Upload_FIELDLIST(X, a) \
X(a, STATIC,   OPTIONAL, MESSAGE,  header,            1) \
X(a, STATIC,   OPTIONAL, MESSAGE,  payload,           2)
#define Upload_CALLBACK NULL
#define Upload_DEFAULT NULL
#define Upload_header_MSGTYPE Header
#define Upload_payload_MSGTYPE Payload

extern const pb_msgdesc_t Upload_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Upload_fields &Upload_msg

/* Maximum encoded size of messages (where known) */
#define Upload_size                              597

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
