// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vminfo.h"

#include <QTreeWidget>
#include <KConfigGroup>
#include <KSharedConfig>

#include "vmprovider.h"
#include "vmprovideraddwizard.h"

using namespace Qt::Literals::StringLiterals;

VMInfo* VMInfo::fromConfig(const QStringList& config) {
    auto newInfo = new VMInfo();
    for(const auto& string : config) {
        VMProvider* newProvider = VMProvider::fromConfigString(string);
        if(newProvider) {
            newProvider->setInfo(newInfo);
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

void VMInfo::refresh() {
    for(auto provider : m_providers) {
        auto vmTreeItem = provider->getVmTreeItem();
        if(m_vmViewWidget->indexOfTopLevelItem(vmTreeItem) == -1) {
            m_vmViewWidget->addTopLevelItem(vmTreeItem);
            vmTreeItem->setExpanded(true);
        }
        provider->refresh();
    }
}

void VMInfo::appendProvider(VMProvider* provider) {
    provider->setInfo(this);
    m_providers.append(provider);

    // Serialize the new provider list to configuration
    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup vmConfig(config, u"VmProviders"_s);
    vmConfig.writeEntry("Providers", toConfig());
    vmConfig.config()->sync();
}

void VMInfo::setVmViewWidget(QTreeWidget* widget) {
    m_vmViewWidget = widget;
}
