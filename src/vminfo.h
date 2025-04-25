// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMINFO_H
#define VMINFO_H

#include <QAbstractItemModel>

class VMProvider;

class VMInfo : public QAbstractItemModel {
public:
    void addProvider(VMProvider* provider);

    // QAbstractItemModel members
    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    QList<VMProvider*> m_providers;
};

#endif // VMINFO_H
