/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.
    
    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADALIBRARYJOINTSEXPORTER_HPP
#define	KDLCOLLADALIBRARYJOINTSEXPORTER_HPP

#include "COLLADASWLibraryJoints.h"


class KDLColladaLibraryJointsExporter : public COLLADASW::LibraryJoints
{

public:

    KDLColladaLibraryJointsExporter(COLLADASW::StreamWriter * streamWriter);
    virtual ~KDLColladaLibraryJointsExporter();

    void doExport();

private:

  //  COLLADASW::LibraryJoints libraryJoints;
};

#endif //KDLCOLLADALIBRARYJOINTSEXPORTER_HPP

