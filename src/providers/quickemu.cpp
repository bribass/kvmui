// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "providers/quickemu.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
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

QString QuickemuProvider::addDescription() const {
    return i18n("Quickemu");
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

QString QuickemuProvider::uiDescription() const {
    return i18n("Quickemu (%1)", m_dir);
}

QIcon QuickemuProvider::uiIcon() const {
    return QIcon::fromTheme(u"kvmui-hv-quickemu"_s);
}
