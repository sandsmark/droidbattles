/***************************************************************************
                          docbrowser.cpp  -  description
                             -------------------
    begin                : Sat Jan 6 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@linux.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "docbrowser.h"
//Added by qt3to4:
#include <QCloseEvent>

DocBrowser::DocBrowser (QString src)
{
    setSource (src);
    resize (800,600);
    show();
}

DocBrowser::~DocBrowser()
{
}

void DocBrowser::closeEvent (QCloseEvent*)
{
    delete this;
}

void DocBrowser::lookUp(const QString &keyword)
{
    const QHash<QString, QString> mapping = {
        {"mov", "index-10.html#ss10.1"},
        {"nop", "index-10.html#ss10.2"},
        {"movsb", "index-10.html#ss10.3"},
        {"movsw", "index-10.html#ss10.3"},
        {"stosb", "index-10.html#ss10.4"},
        {"stosw", "index-10.html#ss10.4"},
        {"lodsb", "index-10.html#ss10.5"},
        {"lodsw", "index-10.html#ss10.5"},
        {"push", "index-10.html#ss10.6"},
        {"pop", "index-10.html#ss10.7"},
        {"xchg", "index-10.html#ss10.8"},
        {"test", "index-10.html#ss10.9"},
        {"cmp", "index-10.html#ss10.10"},
        {"icmp", "index-10.html#ss10.10"},
        {"cmpsb", "index-10.html#ss10.11"},
        {"jmp", "index-10.html#ss10.12"},

        {"jz", "index-10.html#ss10.13"},
        {"jnz", "index-10.html#ss10.13"},
        {"jae", "index-10.html#ss10.13"},
        {"jbe", "index-10.html#ss10.13"},
        {"ja", "index-10.html#ss10.13"},
        {"jb", "index-10.html#ss10.13"},
        {"cj", "index-10.html#ss10.13"},
        {"cjn", "index-10.html#ss10.13"},

        {"lz", "index-10.html#ss10.14"},
        {"lnz", "index-10.html#ss10.14"},
        {"la", "index-10.html#ss10.14"},
        {"lb", "index-10.html#ss10.14"},
        {"lae", "index-10.html#ss10.14"},
        {"lbe", "index-10.html#ss10.14"},

        {"loop", "index-10.html#ss10.15"},
        {"call", "index-10.html#ss10.16"},
        {"ret", "index-10.html#ss10.17"},
        {"iret", "index-10.html#ss10.18"},

        {"cli", "index-10.html#ss10.19"},
        {"sti", "index-10.html#ss10.19"},

        {"out", "index-10.html#ss10.20"},
        {"in", "index-10.html#ss10.21"},

        {"inc", "index-10.html#ss10.22"},
        {"dec", "index-10.html#ss10.22"},

        {"add", "index-10.html#ss10.23"},
        {"sub", "index-10.html#ss10.23"},

        {"and", "index-10.html#ss10.24"},
        {"or", "index-10.html#ss10.24"},
        {"xor", "index-10.html#ss10.24"},

        {"shr", "index-10.html#ss10.25"},
        {"shl", "index-10.html#ss10.25"},

        {"ishr", "index-10.html#ss10.26"},
        {"ishl", "index-10.html#ss10.26"},

        {"ror", "index-10.html#ss10.27"},
        {"rol", "index-10.html#ss10.27"},

        {"int", "index-10.html#ss10.28"},

        {"mul", "index-10.html#ss10.29"},
        {"imul", "index-10.html#ss10.29"},

        {"div", "index-10.html#ss10.30"},
        {"idiv", "index-10.html#ss10.30"},

        {"sin", "index-10.html#ss10.31"},
        {"cos", "index-10.html#ss10.32"},
        {"sinfunc", "index-10.html#ss10.33"},
        {"cosfunc", "index-10.html#ss10.34"},
        {"atanfunc", "index-10.html#ss10.35"},
        {"rnd", "index-10.html#ss10.36"},
        {"hwait", "index-10.html#ss10.37"},
        {"sqr", "index-10.html#ss10.38"},
        {"msg", "index-10.html#ss10.39"},
        {"err", "index-10.html#ss10.40"},
        {"readfile", "index-10.html#ss10.41"},
        {"writefile", "index-10.html#ss10.41"},

        {"ax", "index-6.html#ss6.1"},
        {"ah", "index-6.html#ss6.1"},
        {"al", "index-6.html#ss6.1"},
        {"bx", "index-6.html#ss6.1"},
        {"bh", "index-6.html#ss6.1"},
        {"bl", "index-6.html#ss6.1"},
        {"cx", "index-6.html#ss6.1"},
        {"ch", "index-6.html#ss6.1"},
        {"cl", "index-6.html#ss6.1"},
        {"dx", "index-6.html#ss6.1"},
        {"dh", "index-6.html#ss6.1"},
        {"dl", "index-6.html#ss6.1"},
        {"eip", "index-6.html#ss6.1"},
        {"bp", "index-6.html#ss6.1"},
        {"si", "index-6.html#ss6.1"},
        {"di", "index-6.html#ss6.1"},
        {"flags", "index-6.html#ss6.1"},

        {"org", "index-6.html#ss6.3"},
        {"CPUboot", "index-6.html#ss6.3"},
        {"interrupt", "index-6.html#ss6.3"},
        {"db", "index-6.html#ss6.3"},
        {"dw", "index-6.html#ss6.3"},

    };


    if (keyword.startsWith(":") || keyword.startsWith("#") || keyword.startsWith("$") || keyword.startsWith("@")) {
        setSource(QString("index-6.html#ss6.2"));
        return;
    }

    if (mapping.contains(keyword)) {
        setSource(mapping[keyword]);
        return;
    }
}
