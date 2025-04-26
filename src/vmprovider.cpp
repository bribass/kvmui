// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vmprovider.h"

#include <QIcon>

VMProvider::VMProvider(const QString& desc, const QString& icon)
: m_description(desc), m_iconName(icon) {}

const QString& VMProvider::uiDescription() const {
    return m_description;
}

QIcon VMProvider::uiIcon() const {
    return QIcon::fromTheme(m_iconName);
}
