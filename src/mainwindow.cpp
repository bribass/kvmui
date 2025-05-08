// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QLabel>
#include <QSplitter>
#include <QTreeWidget>
#include <KActionCollection>
#include <KLocalizedString>
#include <KStandardAction>

#include "vminfo.h"

using namespace Qt::Literals::StringLiterals;

MainWindow::MainWindow(VMInfo* vmInfo, QWidget* parent)
: KXmlGuiWindow(parent), m_vmInfo(vmInfo) {
    // horizontal separation between VM tree (on left) and VM display (on right)
    m_splitter = new QSplitter();
    setCentralWidget(m_splitter);

    // the VM tree
    m_vmView = new QTreeWidget(m_splitter);
    m_vmView->setHeaderHidden(true);
    m_vmInfo->setVmViewWidget(m_vmView);
    m_vmInfo->refresh();

    // the VM display
    auto m_vmDisplay = new QLabel(m_splitter);
    m_vmDisplay->setText(i18n("PLACEHOLDER"));
    m_vmDisplay->setMinimumWidth(200);
    m_vmDisplay->setMinimumHeight(200);
    m_vmDisplay->setAlignment(Qt::AlignCenter);

    // done!
    setupActions();
}

MainWindow::~MainWindow() {
    delete m_vmView;
    delete m_splitter;
}

void MainWindow::setupActions() {
    // Add VM Provider
    auto providerAddAction = new QAction(this);
    providerAddAction->setText(i18n("&Add VM Provider"));
    providerAddAction->setIcon(QIcon::fromTheme(u"list-add-symbolic"_s));
    actionCollection()->addAction(u"provider_add"_s, providerAddAction);
    actionCollection()->setDefaultShortcut(providerAddAction, Qt::CTRL | Qt::Key_A); // NOLINT(*-static-accessed-through-instance)
    connect(providerAddAction, &QAction::triggered, m_vmInfo, [=] { m_vmInfo->addProvider(this); });

    // Refresh
    auto refreshAction = new QAction(this);
    refreshAction->setText(i18n("Refresh"));
    refreshAction->setIcon(QIcon::fromTheme(u"view-refresh"_s));
    actionCollection()->addAction(u"refresh"_s, refreshAction);
    actionCollection()->setDefaultShortcut(refreshAction, Qt::Key_F5);
    connect(refreshAction, &QAction::triggered, m_vmInfo, [=] { m_vmInfo->refresh(); });

    // Quit
    KStandardAction::quit(qApp, &QCoreApplication::quit, actionCollection());

    setupGUI(Default, u"kvmuiui.rc"_s);
}
