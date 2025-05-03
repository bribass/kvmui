// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMPROVIDER_H
#define VMPROVIDER_H

#include <QObject>
#include <QString>

class QIcon;
class QGridLayout;
class VMProviderAddWizard;
class VMProviderAddWizardConfigPage;

class VMProvider : public QObject {
    Q_OBJECT

public:
    explicit VMProvider() = default;

    // Registration of subclasses
#define REGISTER_VMPROVIDER(x) static auto dummy = VMProvider::register_provider(#x, new x);
    typedef std::map<const char*, VMProvider*> ProviderMap;
public:
    static bool register_provider(const char* name, VMProvider* provider);
    static ProviderMap& get_providers();
protected:
    static ProviderMap s_types;

    // Methods for providing UI elements for Add Provider wizard
public:
    [[nodiscard]] virtual QString addDescription() const = 0;
    virtual void addConfigure(VMProviderAddWizardConfigPage* page, QGridLayout *layout) = 0;
    virtual VMProvider* addFinalize(VMProviderAddWizard* wizard) = 0;

    // Methods for providing UI elements for VMInfo model
public:
    [[nodiscard]] virtual QString uiDescription() const = 0;
    [[nodiscard]] virtual QIcon uiIcon() const = 0;
};

#endif // VMPROVIDER_H
