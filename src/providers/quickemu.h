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
    [[nodiscard]] QListWidgetItem* getAddProviderSelectItem() const override;
    void addConfigure(VMProviderAddWizardConfigPage* page, QGridLayout* layout) override;
    VMProvider* addFinalize(VMProviderAddWizard* wizard) override;

    // Methods for providing UI elements for VMInfo model
    [[nodiscard]] QTreeWidgetItem* getVmTreeItem() override;

    // Manage individual VMs
public:
    void refresh() override;

private:
    QString m_dir;
    QStringList m_configs;
};

#endif // PROVIDERS_QUICKEMU_H
