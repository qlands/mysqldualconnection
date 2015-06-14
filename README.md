# MySQL Dual Connection
MySQL Dual Connection is an example of how to achieve a dual (server & embedded) connection to [MySQL/MariaDB](https://mariadb.org/) in one [Qt 5](https://www.qt.io/) application. The example creates a new Qt SQL driver (embeddedDriver) that can be used with the rest of Qt SQL classes. 

**Special requirement**
- Uses libmysqld.**a** (MySQL/MariaDB embedded library). **It does not work with  libmysqld.so** because Qt 5 would not be able to determine which library to use “mysqlclient” (server libary) or “mysqld” at run time.
- Requires a MySQL/MariaDB “share” directory that matches the library version. At this point the “share” directory inside the example database (embdbtest) matches MariaDB 10.0.19.

#### *Parameters*
  - a - Path to the embedded database.
  - d - Schema name.
  - r - Use remote connection. False by default.
  - H - MySQL/MariaDB host. Default is localhost.
  - P - MySQL/MariaDB port. Default is 3306.
  - u - MySQL/MariaDB user name.
  - p - MySQL/MariaDB user password.

### *Example of embedded connection*
  ```sh
$ ./mysqldualconnection -a /path_to_my_embedded_database -d my_embedded_database
```
### *Example of server connection*
  ```sh
$ ./mysqldualconnection -r -H my_MariaDB_server -u my_user_name -p my_password -d my_embedded_database
```

## Technology
ODK Tools was built using:

- [C++](https://isocpp.org/), a general-purpose programming language.
- [Qt 5](https://www.qt.io/), a cross-platform application framework.
- [CMake](http://www.cmake.org/), a cross-platform free and open-source software for managing the build process of software using a compiler-independent method.

## Building and testing
To build this site for local viewing or development:

    $ git clone https://github.com/qlands/mysqldualconnection.git
    $ cd mysqldualconnection
    $ mkdir build
    $ cbuild
    $ cmake ..
    $ ./mysqldualconnection -a ../embdbtest -d embtest
    >> Embedded connection
    >> Code: 2 - Description: Row 2
    >> Code: 1 - Description: Row 1

## Author
Carlos Quiros (cquiros_at_qlands.com)

## License
This repository contains the code of:

- [Qt 5](https://www.qt.io/) which is licensed under the [LGPL v2.1 and GPL v 3.0 licenses](https://www.gnu.org/licenses/licenses.html).

Otherwise, the contents of this application is [GPL V3](http://www.gnu.org/copyleft/gpl.html). 