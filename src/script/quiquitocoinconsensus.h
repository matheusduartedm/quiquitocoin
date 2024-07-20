// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2021 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef QUIQUITOCOIN_SCRIPT_QUIQUITOCOINCONSENSUS_H
#define QUIQUITOCOIN_SCRIPT_QUIQUITOCOINCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_QUIQUITOCOIN_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/quiquitocoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBQUIQUITOCOINCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define QUIQUITOCOINCONSENSUS_API_VER 2

typedef enum quiquitocoinconsensus_error_t
{
    quiquitocoinconsensus_ERR_OK = 0,
    quiquitocoinconsensus_ERR_TX_INDEX,
    quiquitocoinconsensus_ERR_TX_SIZE_MISMATCH,
    quiquitocoinconsensus_ERR_TX_DESERIALIZE,
    quiquitocoinconsensus_ERR_AMOUNT_REQUIRED,
    quiquitocoinconsensus_ERR_INVALID_FLAGS,
    quiquitocoinconsensus_ERR_SPENT_OUTPUTS_REQUIRED,
    quiquitocoinconsensus_ERR_SPENT_OUTPUTS_MISMATCH
} quiquitocoinconsensus_error;

/** Script verification flags */
enum
{
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT             = (1U << 17), // enable TAPROOT (BIPs 341 & 342)
    quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS |
                                                               quiquitocoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT
};

typedef struct {
    const unsigned char *scriptPubKey;
    unsigned int scriptPubKeySize;
    int64_t value;
} UTXO;

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int quiquitocoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, quiquitocoinconsensus_error* err);

EXPORT_SYMBOL int quiquitocoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, quiquitocoinconsensus_error* err);

EXPORT_SYMBOL int quiquitocoinconsensus_verify_script_with_spent_outputs(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    const UTXO *spentOutputs, unsigned int spentOutputsLen,
                                    unsigned int nIn, unsigned int flags, quiquitocoinconsensus_error* err);

EXPORT_SYMBOL unsigned int quiquitocoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // QUIQUITOCOIN_SCRIPT_QUIQUITOCOINCONSENSUS_H
