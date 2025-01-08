## Typing practice app

This is a versatile typing practice app developed as part of an Advanced programming techniques class project. The app showcases some of the more advanced programming concepts in C++ Builder and VCL library.

![App screenshot](keytype.png)


**User-oriented features:**
- test your typing skills with customizable practice text and options (virtual keyboard shows pressed keys)
- learn touch typing through courses and lessons
- challenge yourself with the in-app game "Flying Words" (type the flying words before they disappear)
- view detailed lesson stats and overall performance
- track your typing achievements
- configure settings
- diagnose app behavior with logging messages

**Core technical features:**
- multi-language user interface with dynamic selection
- app settings stored in INI file and Windows registry
- data management with XML, JSON and custom file format
- CRUD operations on database records with MySQL
- lookup and calculated fields, including BLOB fields
- automatic report generation with FastReports (PDF + RTF)
- multi-threading support in the "Flying Words" game
- thread synchronization using mutexes and critical sections
- safe UI updates from the main thread
- separate log archiving and compression process
- TCP client/server
- UDP client/server
- SOAP client/server
- REST client/server
- symmetric and asymmetric cryptography
- hashing with variable salt and pepper
- digital signature support
- custom static and dynamic libraries
- DLL-based forms
- unit testing with DUnit

**Build instructions:**
- the app can be built using C++ Builder. Free community edition is available
- before using the app, start TCP and UDP server inside src/server folder (separate executable)