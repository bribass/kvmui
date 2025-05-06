// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef PROVIDERS_QUICKEMU_H
#define PROVIDERS_QUICKEMU_H

#include "vmprovider.h"
#include "vmprovideraddwizard.h"

class QuickemuProvider : public VMProvider {
    Q_OBJECT

public:
    explicit QuickemuProvider() = default;
    explicit QuickemuProvider(const QString& dir);

    // Serialization
    VMProvider* fromConfigJson(const QJsonObject& obj) override;
    void toConfigJson(QJsonObject* obj) override;

    // Methods for providing UI elements for Add Provider wizard
    [[nodiscard]] QString addDescription() const override;
    void addConfigure(VMProviderAddWizardConfigPage* page, QGridLayout* layout) override;
    VMProvider* addFinalize(VMProviderAddWizard* wizard) override;

    // Methods for providing UI elements for VMInfo model
    [[nodiscard]] QString uiDescription() const override;
    [[nodiscard]] QIcon uiIcon() const override;

private:
    QString m_dir;
};

#endif // PROVIDERS_QUICKEMU_H
