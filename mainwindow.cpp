/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2019 by Andrew Bond                                     *
 *                                                                         *
 *   https://www.abondservices.com                                         *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, version 3.                                *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    watcher = new ABMountWatcher(this);
    connect(watcher, SIGNAL(mountState(bool)), this,SLOT(stateChange(bool)));
    watcher->setMountPoint(monitorDir);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete watcher;
}
void MainWindow::stateChange(bool mounted){
    if (mounted){
        ui->label->setText("Mounted");

    } else {
        ui->label->setText("Not Mounted");
    }

}
