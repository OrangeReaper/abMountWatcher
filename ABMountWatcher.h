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
#ifndef ABMOUNTWATCHER_H
#define ABMOUNTWATCHER_H

#include <QObject>
#include <QTimer>
#include <QDir>

class ABMountWatcher : public QObject
{
    Q_OBJECT
public:
    explicit ABMountWatcher(QObject *parent = nullptr, QString mountPoint=nullptr, bool enabled=true, int pollPeriod=500);
    ~ABMountWatcher();

    int     pollPeriod()                        {return m_pollPeriod;}
    void    setPollPeriod(int pollPeriod)       {m_pollPeriod=pollPeriod;}

    bool    isEnabled()                         {return m_enabled;}
    void    setEnabled(bool enabled);

    QString mountPoint()                        {return m_mountPoint->absolutePath();}
    void    setMountPoint(QString mountPoint);

    bool    isMounted()                         {return (m_status == mounted);}

    enum    status  {unknown, mounted, notMounted};

signals:
    void    mountState(bool mounted);
public slots:
    void    pollMountPoint();
private:
    status  m_status        = unknown;
    QDir    * m_mountPoint  = nullptr;
    QTimer  * m_timer       = nullptr;
    int     m_pollPeriod    = 500;
    bool    m_enabled       = true;
};

#endif // ABMOUNTWATCHER_H
