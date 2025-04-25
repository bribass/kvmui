// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef VMPROVIDER_H
#define VMPROVIDER_H

#include <QString>

class QIcon;

class VMProvider {
public:
    explicit VMProvider(const QString& desc, const QString& icon);
    const QString& uiDescription() const;
    QIcon uiIcon() const;

private:
    QString m_description;
    QString m_iconName;
};

#endif // VMPROVIDER_H
