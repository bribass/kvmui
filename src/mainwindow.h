// This file is part of kvmui
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>

class QSplitter;
class QTreeView;

class VMInfo;

class MainWindow : public KXmlGuiWindow {
public:
    explicit MainWindow(VMInfo* vmInfo, QWidget* parent = nullptr);

private:
    QSplitter* m_splitter;
    QTreeView* m_vmView;
    VMInfo* m_vmInfo;
};

#endif // MAINWINDOW_H
