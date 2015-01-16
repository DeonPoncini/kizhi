---
Title: kizhi
Description: Multiplatform Logging utility
Author: Deon Poncini

---
kizhi
===============

Developed by Deon Poncini <dex1337@gmail.com>

Description
-----------
Kizhi is a logging tool to log at different log levels. It logs for desktop
and android

Kizhi Pogost is a large wooden building in Russia, hence the pun for a log
framework.

Usage
-----
Use the log macros like so:

    KIZHI_LEVEL_TF(tag) << "Message " << 1 << " works like a stream ";

Each message prints out the file name and line number along with the message
to help debugging

Each macro comes in four varieties:

    KIZHI_TRACE_TF(tag) // prints a tag, message, file and line numbers
    KIZHI_TRACE_T(tag) // prints a tag and message
    KIZHI_TRACE_F(tag) // prints a message, file and line numbers
    KIZHI_TRACE(tag) // prints a message only

License
-------
Copyright (c) 2015 Deon Poncini.
See the LICENSE file for license rights and limitations (MIT)
