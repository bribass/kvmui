// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vmprovider.h"

#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;

QMap<QString, VMProvider*> VMProvider::s_types = {};

bool VMProvider::register_provider(const char* name, VMProvider* provider) {
    s_types[QString::fromUtf8(name)] = provider;
    return true;
}

VMProvider::ProviderMap& VMProvider::get_providers() {
    return s_types;
}

VMProvider* VMProvider::fromConfigString(const QString& config) {
    QJsonParseError docError;
    const auto doc = QJsonDocument::fromJson(config.toUtf8(), &docError);
    if(docError.error != QJsonParseError::NoError) {
        return nullptr;
    }
    const auto docClassJson = doc[u"class"_s];
    if(docClassJson.isUndefined()) {
        return nullptr;
    }
    const auto docClass = docClassJson.toString();
    if(!s_types.contains(docClass)) {
        return nullptr;
    }
    return s_types[docClass]->fromConfigJson(doc.object());
}

QString VMProvider::toConfigString() {
    QJsonObject obj;
    obj[u"class"_s] = QString::fromUtf8(metaObject()->className());
    toConfigJson(&obj);
    QJsonDocument doc(obj);
    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
}
