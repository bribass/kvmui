// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMINFO_H
#define VMINFO_H

#include <QObject>

class QTreeWidget;
class VMProvider;

class VMInfo : public QObject {
    Q_OBJECT

public:
    // Serialization
    static VMInfo* fromConfig(const QStringList& config);
    QStringList toConfig();

public Q_SLOTS:
    void addProvider(QWidget* parent);
    void refresh();

public:
    void appendProvider(VMProvider* provider);
    void setVmViewWidget(QTreeWidget* widget);

private:
    QList<VMProvider*> m_providers;
    QTreeWidget* m_vmViewWidget = nullptr;
};

#endif // VMINFO_H
