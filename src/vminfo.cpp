// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vminfo.h"

#include <QIcon>

#include "vmprovider.h"

void VMInfo::addProvider(VMProvider* provider) {
    m_providers.push_back(provider);
}

QModelIndex VMInfo::index(int row, int column, const QModelIndex& parent) const {
    if(parent.isValid())
        return {};
    return createIndex(row, column);
}

QModelIndex VMInfo::parent(const QModelIndex& child) const {
    Q_UNUSED(child);

    // the VM info structure does not have a parent; return an invalid (i.e., default constructed) index.
    return {};
}

int VMInfo::rowCount(const QModelIndex& parent) const {
    if(parent.isValid())
        return 0;
    return static_cast<int>(m_providers.count());
}

int VMInfo::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

QVariant VMInfo::data(const QModelIndex& index, int role) const {
    if(index.row() < 0 || index.row() >= m_providers.count())
        return {};
    if(role == Qt::DisplayRole || role == Qt::EditRole)
        return m_providers.at(index.row())->uiDescription();
    else if(role == Qt::DecorationRole)
        return m_providers.at(index.row())->uiIcon();
    return {};
}
