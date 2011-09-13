/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADASCENEEXPORTER_HPP
#define	KDLCOLLADASCENEEXPORTER_HPP

#include "COLLADASWScene.h"
#include <vector>
#include <string>

namespace KDL
{
    class Chain;
    class Joint;
}

class KDLColladaSceneExporter : public COLLADASW::Scene
{

public:

    KDLColladaSceneExporter(COLLADASW::StreamWriter * streamWriter);
    virtual ~KDLColladaSceneExporter();

    bool doExport(std::vector<KDL::Chain>& kdlChains);

    void makeColladaSWInstanceKinematicsScene(COLLADASW::StreamWriter* streamWriter,
                                              KDL::Chain& kdlChain,
                                              std::string kinSceneId,
                                              std::string url,
                                              std::string sid);

private:

};

#endif //KDLCOLLADALIBRARYJOINTSEXPORTER_HPP

