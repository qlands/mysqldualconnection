/*
    myDBConn
    This class stablish a direct connection to a MySQL Embedded Directory
    Copyright (C) 2014  Carlos Quiros
    Contact: Carlos Quiros cquiros(at)qlands.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef MYDBCONN_H
#define MYDBCONN_H

#include <QObject>
#include <QSqlDatabase>

#ifdef Q_OS_WIN
#include <winsock.h>
#endif

#include <mysql.h>
#include "embdriver.h"



class myDBConn : public QObject
{
    Q_OBJECT
public:
    explicit myDBConn(QObject *parent = 0);
    int connectToDB(QString path);
    int closeConnection();
    embeddedDriver *getDriver();
private:
    MYSQL *m_mysql;
    embeddedDriver *m_drv;
    bool m_connected;
    long getBufferSize();
    void log(QString message);
};

#endif // MYDBCONN_H
