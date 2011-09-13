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
#include "COLLADASWJoint.h"

#include <vector>
#include <string>

namespace KDL
{
    class Chain;
    class Joint;
}

class KDLColladaLibraryJointsExporter : public COLLADASW::LibraryJoints
{

public:

    KDLColladaLibraryJointsExporter(COLLADASW::StreamWriter * streamWriter);
    virtual ~KDLColladaLibraryJointsExporter();

    bool doExport(std::vector <KDL::Chain>& kdlChain);
    COLLADASW::Joint makeColladaSWJoint(COLLADASW::StreamWriter * streamWriter, KDL::Joint& kdlJoint, std::string uniqueId);
    const std::vector<COLLADASW::Joint>& getJoints();

private:
    std::vector<COLLADASW::Joint> joints;
  //  COLLADASW::LibraryJoints libraryJoints;
};

#endif //KDLCOLLADALIBRARYJOINTSEXPORTER_HPP

