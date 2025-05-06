// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>

#include "mainwindow.h"
#include "vminfo.h"
#include "vmprovider.h"

int main(int argc, char** argv) {
    using namespace Qt::Literals::StringLiterals;

    // Initialize the application
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("kvmui");

    // Configure the aboutdata for the application
    KAboutData aboutData(u"kvmui"_s,
                         i18n("KDE Virtual Machine UI"),
                         u"0.1.0"_s,
                         i18n("An interface for working with virtual machines."),
                         KAboutLicense::GPL_V3,
                         i18n("Copyright (c) 2025 Brian Bassett"),
                         u""_s,
                         u"https://github.com/bribass/kvmui"_s,
                         u"https://github.com/bribass/kvmui/issues"_s);
    aboutData.addAuthor(u"Brian Bassett"_s, i18n("Developer"), u"bbassett1276@gmail.com"_s);
    KAboutData::setApplicationData(aboutData);

    // Parse the command line
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    // Load the VMInfo with configuration
    KSharedConfigPtr config = KSharedConfig::openConfig();
    KConfigGroup vmConfig(config, u"VmProviders"_s);
    QStringList vmProviderList = vmConfig.readEntry("Providers", QStringList());
    auto vmInfo = VMInfo::fromConfig(vmProviderList);

    // Create the main window
    auto main_window = new MainWindow(vmInfo);
    main_window->show();
    return QApplication::exec();
}
