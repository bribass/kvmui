// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMPROVIDERADDWIZARD_H
#define VMPROVIDERADDWIZARD_H

#include <QListWidget>
#include <QWizard>

class VMInfo;
class VMProvider;

class VMProviderAddWizard : public QWizard {
    Q_OBJECT

public:
    explicit VMProviderAddWizard(VMInfo* info, QWidget* parent = nullptr);
    ~VMProviderAddWizard() override;

    enum {
        PageIntro,
        PageSelect,
        PageConfig,
        PageComplete
    };

    void setStaticProvider(VMProvider *provider);

public:
    void accept() override;

private:
    VMInfo* m_info;
    VMProvider* m_provider;
};

class VMProviderAddWizardIntroPage : public QWizardPage {
    Q_OBJECT

public:
    explicit VMProviderAddWizardIntroPage(QWidget* parent = nullptr);
};

class VMProviderAddWizardSelectPage : public QWizardPage {
    Q_OBJECT

public:
    explicit VMProviderAddWizardSelectPage(VMProvider** pProvider, QWidget* parent = nullptr);
    [[nodiscard]] bool isComplete() const override;

private Q_SLOTS:
    void listChanged() const;

private:
    VMProvider** m_pProvider;
    QListWidget* m_list;
};

class VMProviderAddWizardConfigPage : public QWizardPage {
    Q_OBJECT

public:
    explicit VMProviderAddWizardConfigPage(VMProvider** pProvider, QWidget* parent = nullptr);
    void initializePage() override;

    using QWizardPage::registerField;   // expose this method to the VMProvider's addConfigure method

private:
    VMProvider** m_pProvider;
    bool m_initialized;
};

class VMProviderAddWizardCompletePage : public QWizardPage {
    Q_OBJECT

public:
    explicit VMProviderAddWizardCompletePage(QWidget* parent = nullptr);
};

#endif // VMPROVIDERADDWIZARD_H
