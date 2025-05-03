// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "vmprovider.h"

std::map<const char*, VMProvider*> VMProvider::s_types = {};

bool VMProvider::register_provider(const char* name, VMProvider* provider) {
    s_types[name] = provider;
    return true;
}

VMProvider::ProviderMap& VMProvider::get_providers() {
    return s_types;
}
