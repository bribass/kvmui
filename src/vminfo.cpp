// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vminfo.h"

#include "vmprovider.h"
#include "vmprovideraddwizard.h"

using namespace Qt::Literals::StringLiterals;

VMInfo* VMInfo::fromConfig(const QStringList& config) {
    auto newInfo = new VMInfo();
    for(const auto& string : config) {
        VMProvider* newProvider = VMProvider::fromConfigString(string);
        if(newProvider) {
            newInfo->m_providers.append(newProvider);
        }
    }
    return newInfo;
}

QStringList VMInfo::toConfig() {
    QStringList list;
    for(auto provider : m_providers) {
        list.append(provider->toConfigString());
    }
    return list;
}

void VMInfo::addProvider(QWidget* parent) {
    auto wiz = new VMProviderAddWizard(this, parent);
    wiz->show();
}

void VMInfo::appendProvider(VMProvider* provider) {
    const int oldSize = static_cast<int>(m_providers.count());
    beginInsertRows({}, oldSize, oldSize);
    m_providers.append(provider);
    endInsertRows();
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
    if(role == Qt::DecorationRole)
        return m_providers.at(index.row())->uiIcon();
    return {};
}
