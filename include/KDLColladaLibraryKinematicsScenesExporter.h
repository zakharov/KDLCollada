/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADALIBRARYKINEMATICSSCENESEXPORTER_HPP
#define	KDLCOLLADALIBRARYKINEMATICSSCENESEXPORTER_HPP

#include "COLLADASWLibraryKinematicsScenes.h"
#include "COLLADASWInstanceKinematicsModel.h"

#include <vector>
#include <string>


namespace KDL
{
    class Chain;
    class Joint;
}

class KDLColladaLibraryKinematicsScenesExporter : public COLLADASW::LibraryKinematicsScenes
{

public:

    KDLColladaLibraryKinematicsScenesExporter(COLLADASW::StreamWriter * streamWriter);
    virtual ~KDLColladaLibraryKinematicsScenesExporter();
    COLLADASW::InstanceKinematicsModel makeColladaSWInstanceKinematicsModel(COLLADASW::StreamWriter* streamWriter, KDL::Chain& chain, std::string kinSceneId, std::string url, std::string sid);
    bool doExport(std::vector<KDL::Chain>& kdlChains);


private:


};

#endif //KDLCOLLADALIBRARYKINEMATICSSCENESEXPORTER_HPP

