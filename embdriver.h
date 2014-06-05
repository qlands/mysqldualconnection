/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSql module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GBTEMBDRIVER
#define GBTEMBDRIVER

#include <QSqlDriver>
#include <QSqlResult>

#if defined (Q_OS_WIN32)
#include <qt_windows.h>
#endif

#ifdef Q_OS_WIN
#include <winsock.h>
#endif

#include <mysql.h>
#include <QTextCodec>


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class embeddedDriverPrivate;
class embeddedResultPrivate;
class embeddedDriver;
class QSqlRecordInfo;

class embeddedResult : public QSqlResult
{
    friend class embeddedDriver;
    friend class embeddedResultPrivate;
public:
    explicit embeddedResult(const embeddedDriver* db);
    ~embeddedResult();

    QVariant handle() const;
protected:
    void cleanup();
    bool fetch(int i);
    bool fetchNext();
    bool fetchLast();
    bool fetchFirst();
    QVariant data(int field);
    bool isNull(int field);
    bool reset (const QString& query);
    int size();
    int numRowsAffected();
    QVariant lastInsertId() const;
    QSqlRecord record() const;
    void virtual_hook(int id, void *data);
    bool nextResult();

#if MYSQL_VERSION_ID >= 40108
    bool prepare(const QString& stmt);
    bool exec();
#endif
private:
    embeddedResultPrivate* d;
};

class embeddedDriver : public QSqlDriver
{
    Q_OBJECT
    friend class embeddedResult;
public:
    explicit embeddedDriver(QObject *parent=0);
    explicit embeddedDriver(MYSQL *con, QObject * parent=0);
    ~embeddedDriver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
               const QString & user,
               const QString & password,
               const QString & host,
               int port,
               const QString& connOpts);
    void close();
    QSqlResult *createResult() const;
    QStringList tables(QSql::TableType) const;
    QSqlIndex primaryIndex(const QString& tablename) const;
    QSqlRecord record(const QString& tablename) const;
    QString formatValue(const QSqlField &field,
                                     bool trimStrings) const;
    QVariant handle() const;
    QString escapeIdentifier(const QString &identifier, IdentifierType type) const;

protected Q_SLOTS:
    bool isIdentifierEscapedImplementation(const QString &identifier, IdentifierType type) const;

protected:
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
private:
    void init();
    embeddedDriverPrivate* d;
};

class embeddedDriverPrivate
{
public:
    embeddedDriverPrivate() : mysql(0),
#ifndef QT_NO_TEXTCODEC
        tc(QTextCodec::codecForLocale()),
#else
        tc(0),
#endif
        preparedQuerysEnabled(false) {}
    MYSQL *mysql;
    QTextCodec *tc;

    bool preparedQuerysEnabled;
};

class embeddedResultPrivate : public QObject
{
    Q_OBJECT
public:
    embeddedResultPrivate(const embeddedDriver* dp, const embeddedResult* d) : driver(dp), result(0), q(d),
        rowsAffected(0), hasBlobs(false)
#if MYSQL_VERSION_ID >= 40108
        , stmt(0), meta(0), inBinds(0), outBinds(0)
#endif
        , preparedQuery(false)
        {
            connect(dp, SIGNAL(destroyed()), this, SLOT(driverDestroyed()));
        }

    const embeddedDriver* driver;
    MYSQL_RES *result;
    MYSQL_ROW row;
    const embeddedResult* q;

    int rowsAffected;

    bool bindInValues();
    void bindBlobs();

    bool hasBlobs;
    struct QMyField
    {
        QMyField()
            : outField(0), nullIndicator(false), bufLength(0ul),
              myField(0), type(QVariant::Invalid)
        {}
        char *outField;
        my_bool nullIndicator;
        ulong bufLength;
        MYSQL_FIELD *myField;
        QVariant::Type type;
    };

    QVector<QMyField> fields;

#if MYSQL_VERSION_ID >= 40108
    MYSQL_STMT* stmt;
    MYSQL_RES* meta;

    MYSQL_BIND *inBinds;
    MYSQL_BIND *outBinds;
#endif

    bool preparedQuery;

private Q_SLOTS:
    void driverDestroyed() { driver = NULL; }
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // GBTEMBDRIVER
