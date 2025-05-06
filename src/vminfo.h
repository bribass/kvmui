// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMINFO_H
#define VMINFO_H

#include <QAbstractItemModel>

class VMProvider;

class VMInfo : public QAbstractItemModel {
    Q_OBJECT

public Q_SLOTS:
    void addProvider(QWidget* parent);

public:
    void appendProvider(VMProvider* provider);

    // QAbstractItemModel members
    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex& child) const override;
    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    [[nodiscard]] int columnCount(const QModelIndex& parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

private:
    QList<VMProvider*> m_providers;
};

#endif // VMINFO_H
