/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Logger.h"
#ifdef WIN32
#include "windows.h"
#endif

using namespace std;

Logger::Loglevel Logger::minLoglevel = Logger::WARNING;
bool Logger::useFilename = false;
bool Logger::useLogfile = false;
std::string Logger::logfilename;
Logger::Listener* Logger::listener = 0;
std::ofstream Logger::logfile;

Logger::Logger(Loglevel level)
{
    needNewline = false;
    this->level = level;
    isAboveLoglevel = (level >= minLoglevel);
}

Logger::~Logger()
{
    if (isAboveLoglevel)
        flush();
}

void Logger::setMinLoglevel(Loglevel minLoglevel)
{
    Logger::minLoglevel = minLoglevel;
}

Logger::Loglevel Logger::getMinLoglevel()
{
    return Logger::minLoglevel;
}

void Logger::setUseFilename(bool useFilenames)
{
    Logger::useFilename = useFilenames;
}

void Logger::setLogfile(std::string filename, bool append)
{
    if (useLogfile)
        logfile.close();

    useLogfile = true;
    ios_base::openmode mode = ios::out;
    if (!append)
        mode |= ios::trunc;
    else
        mode |= ios::app;
    logfile.open(filename.c_str(), mode);
}

void Logger::setListener(Listener* listener)
{
    Logger::listener = listener;
}

std::string& Logger::levelToString(Loglevel loglevel)
{
    static std::string names[] = {"DEBUG", "INFO", "WARNING", "ERROR", "FATAL"};
    return names[loglevel];
}

std::ostream& Logger::write(std::string filename, int line)
{
    if (!isAboveLoglevel)
        return stream; //todo: should return stream which does not do anything

    stream << "[" << levelToString(level);
    if (useFilename)
        stream << " " << filename << "(" << line << ")";
    stream << "] ";
    needNewline = true;

    return stream;
}

void Logger::flush()
{
    if (needNewline)
        stream << endl;

    if (useLogfile)
    {
        logfile << stream.str();
        logfile.flush();
    }

    if (listener)
        listener->write(level, stream.str());

    switch (level)
    {
    case FATAL:
#ifdef WIN32
        MessageBox(0, stream.str().c_str(), "BRICS_MM Fatal Error", MB_OK|MB_ICONERROR);
#else
        cerr << stream.str();
#endif
        exit(0);
    case LOGERROR:
        cerr << stream.str();
        break;
    default:
        cout << stream.str();
    }

}

