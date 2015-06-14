/****************************************************************************
**
** Copyright (C) 2015 QLands Technology Consultants.
** All rights reserved.
** Contact: QLands (cquiros@qlands.com)
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 3.0 as published by the Free Software Foundation and
** appearing in the file LICENSE included in the packaging of this
** application. Please review the following information to ensure the GNU Lesser
** General Public License version 3.0 requirements will be met:
** https://www.gnu.org/copyleft/lesser.html.
**
****************************************************************************/

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "mydbconn.h"
#include <stdio.h>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


//This logs messages to the terminal.
void log(QString message)
{
    QString temp;
    temp = message + "\n";
    printf(temp.toLocal8Bit().data());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setApplicationName("mysqldualconn");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("MySQL Dual (Embedded/Server) Connection Example");
    parser.addHelpOption();
    parser.addVersionOption();

    //Common options
    QCommandLineOption dbOption(QStringList() << "d" << "database","Database name","DBName","");
    parser.addOption(dbOption);
    QCommandLineOption remoteOption(QStringList() << "r" << "remote", "Connect to a remote server");
    parser.addOption(remoteOption);

    //Remote options
    QCommandLineOption hostOption(QStringList() << "H" << "host","Host server. Default localhost","host","localhost");
    parser.addOption(hostOption);
    QCommandLineOption portOption(QStringList() << "P" << "port","Host server port. Default localhost","Numeric Port","3306");
    parser.addOption(portOption);
    QCommandLineOption userOption(QStringList() << "u" << "user","User name","userName","");
    parser.addOption(userOption);
    QCommandLineOption passOption(QStringList() << "p" << "password","Password","password","");
    parser.addOption(passOption);

    //Embedded options
    QCommandLineOption pathOption(QStringList() << "a" << "path","Path to embedded database","Directory");
    parser.addOption(pathOption);

    //Process the command line
    parser.process(a);

    //Gather the general options
    bool remote = parser.isSet(remoteOption);
    QString database = parser.value(dbOption);

    //Gather the remote options
    QString host = parser.value(hostOption);
    int port = parser.value(portOption).toInt();
    QString userName = parser.value(userOption);
    QString password = parser.value(passOption);

    //Gather the embedded options
    QString path = parser.value(pathOption);


    myDBConn con; //Creates the embedded driver
    QSqlDatabase mydb; //Creates a normal QT SQL Database class
    if (!remote) //If embedded
    {
        log("Embedded connection");
        QDir dir;
        dir.setPath(path);                
        if (con.connectToDB(dir.absolutePath()) == 1) //Stablish a embedded connection using the path
        {            
            if (!dir.cd(database)) //If the database name does not exists as directory
            {                
                con.closeConnection();
                return 1;
            }            
            mydb = QSqlDatabase::addDatabase(con.getDriver(),"connection1"); //Used the embedded driver to construct the QT Database class
        }
    }
    else
    {
        log("Remote connection");
               //If its remote then use the normal connection procedure
        mydb = QSqlDatabase::addDatabase("QMYSQL","connection1");
        mydb.setHostName(host);
        mydb.setPort(port);
        if (!userName.isEmpty())
            mydb.setUserName(userName);
        if (!password.isEmpty())
            mydb.setPassword(password);
    }

    //Set the database name
    mydb.setDatabaseName(database);

    //Try to connect    
    if (!mydb.open()) //If cannot connect then log
    {
        log("Cannot open database: " + mydb.lastError().databaseText());
        con.closeConnection();
        return 1;
    }
    else
    {
        QSqlQuery query(mydb);
        if (!query.exec("SELECT * FROM embtable"))
        {
            log("Cannot execute query: " + query.lastError().databaseText());
            return 1;
        }
        else
        {
            while (query.next())
            {
                log("Code: " + query.value(0).toString() + " - Description: " + query.value(1).toString());
            }
        }
    }

    con.closeConnection();
    return 0;
}
