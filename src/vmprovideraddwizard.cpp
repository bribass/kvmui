// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vmprovideraddwizard.h"

#include <QGridLayout>
#include <QListWidget>
#include <KLocalizedString>

#include "vminfo.h"
#include "vmprovider.h"

using namespace Qt::Literals::StringLiterals;

VMProviderAddWizard::VMProviderAddWizard(VMInfo* info, QWidget* parent)
: QWizard(parent), m_info(info), m_provider(nullptr) {
    setWizardStyle(QWizard::ModernStyle);
    setWindowTitle(i18n("Add Virtual Machine Provider"));
    setOption(QWizard::NoBackButtonOnStartPage, true);

    setPage(PageIntro, new VMProviderAddWizardIntroPage());
    setPage(PageSelect, new VMProviderAddWizardSelectPage(&m_provider));
    setPage(PageConfig, new VMProviderAddWizardConfigPage(&m_provider));
    setPage(PageComplete, new VMProviderAddWizardCompletePage());
    setStartId(PageIntro);
}

VMProviderAddWizard::~VMProviderAddWizard() = default;

void VMProviderAddWizard::setStaticProvider(VMProvider* provider) {
    m_provider = provider;
}

void VMProviderAddWizard::accept() {
    auto newProvider = m_provider->addFinalize(this);
    m_info->appendProvider(newProvider);
    m_info->refresh();
    QWizard::accept();
}

VMProviderAddWizardIntroPage::VMProviderAddWizardIntroPage(QWidget* parent)
: QWizardPage(parent) {
    setTitle(i18n("Introduction"));
}

VMProviderAddWizardSelectPage::VMProviderAddWizardSelectPage(VMProvider** pProvider, QWidget* parent)
: QWizardPage(parent), m_pProvider(pProvider) {
    setTitle(i18n("Select Virtual Machine Provider"));
    setSubTitle(i18n("Please select the provider you wish to add."));

    m_list = new QListWidget();
    for(auto it : VMProvider::get_providers()) {
        auto item = it->getAddProviderSelectItem();
        item->setData(Qt::UserRole, QVariant::fromValue(static_cast<void*>(it)));
        m_list->addItem(item);
    }
    m_list->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(m_list, &QListWidget::itemSelectionChanged, this, &VMProviderAddWizardSelectPage::listChanged);
    registerField(u"provider*"_s, m_list, "selectedItems", SIGNAL(itemSelectionChanged()));

    auto layout = new QGridLayout();
    layout->addWidget(m_list, 0, 0);
    setLayout(layout);
}

bool VMProviderAddWizardSelectPage::isComplete() const {
    return m_list->selectedItems().count() != 0;
}

void VMProviderAddWizardSelectPage::listChanged() const {
    if(m_list->selectedItems().count() == 0) {
        *m_pProvider = nullptr;
    } else {
        auto var = m_list->selectedItems().at(0)->data(Qt::UserRole);
        if(auto var_void = qvariant_cast<void*>(var)) {
            auto provider = static_cast<VMProvider*>(var_void);
            *m_pProvider = provider;
        }
    }
}

VMProviderAddWizardConfigPage::VMProviderAddWizardConfigPage(VMProvider** pProvider, QWidget* parent)
: QWizardPage(parent), m_pProvider(pProvider), m_initialized(false) {
    setTitle(i18n("Configure Virtual Machine Provider"));
    setSubTitle(i18n("Please configure the provider."));
}

void VMProviderAddWizardConfigPage::initializePage() {
    if(!m_initialized) {
        auto layout = new QGridLayout();
        (*m_pProvider)->addConfigure(this, layout);
        setLayout(layout);
        m_initialized = true;
    }
}

VMProviderAddWizardCompletePage::VMProviderAddWizardCompletePage(QWidget* parent)
: QWizardPage(parent) {
    setTitle(i18n("Provider Complete"));
}
