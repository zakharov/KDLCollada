/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADALIBRARYKINEMATICSMODELSEXPORTER_HPP
#define	KDLCOLLADALIBRARYKINEMATICSMODELSEXPORTER_HPP

#include "COLLADASWLibraryKinematicsModels.h"
#include "COLLADASWInstanceJoint.h"

#include <vector>
#include <string>

namespace KDL
{
    class Chain;
    class Joint;
}

namespace COLLADASW
{
    class KinematicsModel;
}

class KDLColladaLibraryKinematicsModelsExporter : public COLLADASW::LibraryKinematicsModels
{

public:

    KDLColladaLibraryKinematicsModelsExporter(COLLADASW::StreamWriter * streamWriter);
    virtual ~KDLColladaLibraryKinematicsModelsExporter();

    bool doExport(std::vector <KDL::Chain>& kdlChain);

    COLLADASW::KinematicsModel makeColladaSWKinematicsModel(COLLADASW::StreamWriter * streamWriter, KDL::Chain& kdlChain, std::string id);
    COLLADASW::InstanceJoint makeColladaSWInstanceJoint(COLLADASW::StreamWriter* streamWriter, KDL::Joint& kdlJoint, std::string url, std::string sid);
    unsigned int makeColladaSWSerialKinematicsChain(COLLADASW::StreamWriter* streamWriter, KDL::Chain& kdlChain, std::string kinModelName, unsigned int jointCounter = 0);

private:


};

#endif //KDLCOLLADALIBRARYJOINTSEXPORTER_HPP

