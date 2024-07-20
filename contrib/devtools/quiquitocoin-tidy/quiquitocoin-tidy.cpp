// Copyright (c) 2023 Quiquitocoin Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "logprintf.h"

#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

class QuiquitocoinModule final : public clang::tidy::ClangTidyModule
{
public:
    void addCheckFactories(clang::tidy::ClangTidyCheckFactories& CheckFactories) override
    {
        CheckFactories.registerCheck<quiquitocoin::LogPrintfCheck>("quiquitocoin-unterminated-logprintf");
    }
};

static clang::tidy::ClangTidyModuleRegistry::Add<QuiquitocoinModule>
    X("quiquitocoin-module", "Adds quiquitocoin checks.");

volatile int QuiquitocoinModuleAnchorSource = 0;
