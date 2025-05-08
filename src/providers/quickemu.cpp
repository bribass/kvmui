// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "providers/quickemu.h"

#include <QDirIterator>
#include <QFileDialog>
#include <QGridLayout>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <KLocalizedString>

#include "vmprovideraddwizard.h"

using namespace Qt::Literals::StringLiterals;

REGISTER_VMPROVIDER(QuickemuProvider)

QuickemuProvider::QuickemuProvider(const QString& dir)
: m_dir(dir) {}

VMProvider* QuickemuProvider::fromConfigJson(const QJsonObject& obj) {
    auto provider = new QuickemuProvider();
    provider->m_dir = obj[u"dir"_s].toString();
    return provider;
}

void QuickemuProvider::toConfigJson(QJsonObject* obj) {
    obj->insert(u"dir"_s, m_dir);
}

QListWidgetItem* QuickemuProvider::getAddProviderSelectItem() const {
    auto item = new QListWidgetItem();
    item->setText(i18n("Quickemu"));
    item->setIcon(QIcon::fromTheme(u"kvmui-hv-quickemu"_s));
    return item;
}

void QuickemuProvider::addConfigure(VMProviderAddWizardConfigPage* page, QGridLayout* layout) {
    auto label = new QLabel(i18n("Directory containing VMs:"));
    layout->addWidget(label, 0, 0);

    auto field = new QLineEdit();
    page->registerField(u"dir*"_s, field);
    layout->addWidget(field, 0, 1);

    auto browse = new QPushButton();
    browse->setIcon(QIcon::fromTheme(u"folder-symbolic"_s));
    connect(browse, &QPushButton::clicked, this, [=] {
        auto dir = QFileDialog::getExistingDirectory(page, i18n("Select the directory that contains Quickemu VMs"), field->text());
        if(!dir.isNull()) {
            field->setText(dir);
        }
    });
    layout->addWidget(browse, 0, 2);
}

VMProvider* QuickemuProvider::addFinalize(VMProviderAddWizard* wizard) {
    auto retval = new QuickemuProvider();
    retval->m_dir = wizard->field(u"dir"_s).toString();
    return retval;
}

QTreeWidgetItem* QuickemuProvider::getVmTreeItem() {
    if(!m_vmTreeItem) {
        m_vmTreeItem = new QTreeWidgetItem();
        m_vmTreeItem->setText(0, i18n("Quickemu (%1)", m_dir));
        m_vmTreeItem->setIcon(0, QIcon::fromTheme(u"kvmui-hv-quickemu"_s));
    }
    return m_vmTreeItem;
}

void QuickemuProvider::refresh() {
    // Scan m_dir for *.conf files
    QDirIterator it(m_dir, QStringList() << u"*.conf"_s, QDir::Files);
    while(it.hasNext()) {
        auto filename = it.next();
        QFileInfo fileinfo(filename);
        auto filebase = fileinfo.baseName();
        if(!m_configs.contains(filebase)) {
            auto item = new QTreeWidgetItem();
            item->setText(0, filebase);
            item->setIcon(0, QIcon::fromTheme(u"kvmui-vm-stopped"_s));
            auto treeParent = getVmTreeItem();
            treeParent->addChild(item);
            treeParent->sortChildren(0, Qt::AscendingOrder);
            m_configs.append(filebase);
        }
    }
}
