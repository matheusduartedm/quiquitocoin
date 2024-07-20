// Copyright (c) 2011-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef QUIQUITOCOIN_QT_QUIQUITOCOINADDRESSVALIDATOR_H
#define QUIQUITOCOIN_QT_QUIQUITOCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class QuiquitocoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit QuiquitocoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** Quiquitocoin address widget validator, checks for a valid quiquitocoin address.
 */
class QuiquitocoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit QuiquitocoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // QUIQUITOCOIN_QT_QUIQUITOCOINADDRESSVALIDATOR_H
