// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#include "mainwindow.h"

#include <QLabel>
#include <QSplitter>
#include <QTreeView>
#include <KLocalizedString>

#include "vminfo.h"

MainWindow::MainWindow(VMInfo *vmInfo, QWidget *parent) : KXmlGuiWindow(parent), m_vmInfo(vmInfo)
{
    // horizontal separation between VM tree (on left) and VM display (on right)
    m_splitter = new QSplitter();
    setCentralWidget(m_splitter);

    // the VM tree
    m_vmView = new QTreeView();
    m_vmView->setHeaderHidden(true);
    m_vmView->setModel(m_vmInfo);
    m_splitter->addWidget(m_vmView);

    // the VM display
    auto m_vmDisplay = new QLabel();
    m_vmDisplay->setText(i18n("PLACEHOLDER"));
    m_vmDisplay->setMinimumWidth(200);
    m_vmDisplay->setMinimumHeight(200);
    m_vmDisplay->setAlignment(Qt::AlignCenter);
    m_splitter->addWidget(m_vmDisplay);

    // done!
    setupGUI();
}
