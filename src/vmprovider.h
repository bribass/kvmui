// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMPROVIDER_H
#define VMPROVIDER_H

#include <QObject>
#include <QString>

class QIcon;
class QGridLayout;
class QListWidgetItem;
class QTreeWidgetItem;
class VMInfo;
class VMProviderAddWizard;
class VMProviderAddWizardConfigPage;

class VMProvider : public QObject {
    Q_OBJECT

public:
    explicit VMProvider() = default;

    void setInfo(VMInfo* info);
protected:
    VMInfo* m_info;

    // Registration of subclasses
#define REGISTER_VMPROVIDER(x) static auto dummy = VMProvider::register_provider(#x, new (x));
    typedef QMap<QString, VMProvider*> ProviderMap;
public:
    static bool register_provider(const char* name, VMProvider* provider);
    static ProviderMap& get_providers();
protected:
    static ProviderMap s_types;

public:
    // Serialization
    static VMProvider* fromConfigString(const QString& config);
    virtual VMProvider* fromConfigJson(const QJsonObject& obj) = 0;
    QString toConfigString();
    virtual void toConfigJson(QJsonObject* obj) = 0;

    // Methods for providing UI elements for Add Provider wizard
public:
    [[nodiscard]] virtual QListWidgetItem* getAddProviderSelectItem() const = 0;
    virtual void addConfigure(VMProviderAddWizardConfigPage* page, QGridLayout *layout) = 0;
    virtual VMProvider* addFinalize(VMProviderAddWizard* wizard) = 0;

    // Methods for providing UI elements for VMInfo model
public:
    [[nodiscard]] virtual QTreeWidgetItem* getVmTreeItem() = 0;

protected:
    QTreeWidgetItem* m_vmTreeItem;

    // Manage individual VMs
public:
    virtual void refresh() = 0;
};

#endif // VMPROVIDER_H
