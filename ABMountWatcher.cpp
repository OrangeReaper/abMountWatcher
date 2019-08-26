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
#include "ABMountWatcher.h"

ABMountWatcher::ABMountWatcher(QObject *parent, QString mountPoint, bool enabled, int pollPeriod ) : QObject(parent)
{
    m_pollPeriod    = pollPeriod;
    m_timer         = new QTimer(this);
    m_enabled       = enabled;

    setMountPoint(mountPoint);
}
ABMountWatcher::~ABMountWatcher(){
    if (m_timer         != nullptr) delete m_timer;
    if (m_mountPoint    != nullptr) delete m_mountPoint;
}
void ABMountWatcher::setEnabled(bool enabled){
    m_enabled=enabled;
    if (enabled){
        connect(m_timer, SIGNAL(timeout()), this, SLOT(pollMountPoint()));
        m_timer->start(m_pollPeriod);
    } else {
        connect(m_timer, SIGNAL(timeout()), 0, 0);
        m_timer->stop();
    }
}
void ABMountWatcher::pollMountPoint(){
    status currentStatus=mounted;
    bool _mounted = true;
    m_mountPoint->refresh();
    if (m_mountPoint->count() < 3){
        currentStatus = notMounted;
        _mounted = false;
    }
    if (currentStatus != m_status){
        emit mountState(_mounted);
        m_status = currentStatus;
    }
}
void ABMountWatcher::setMountPoint(QString mountPoint){
    bool enabled=m_enabled;
    if (mountPoint != nullptr){
        setEnabled(false);
        if (m_mountPoint != nullptr) delete m_mountPoint;
        m_mountPoint = new QDir(mountPoint);
        setEnabled(enabled);
    }
}

