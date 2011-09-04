/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.
    
    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADAEXPORTER_H
#define	KDLCOLLADAEXPORTER_H

#include <string>
#include <vector>
#include "COLLADASWStreamWriter.h"

namespace COLLADABU {
    class NativeString;
}

namespace KDL {
    class Chain;
}

class KDLColladaExporter {
public:
    KDLColladaExporter(const std::string& filename, std::vector<KDL::Chain>& kdlChain);
    bool exportAsset();
    KDLColladaExporter(const KDLColladaExporter& orig);
    virtual ~KDLColladaExporter();
    bool exportScene();
    bool exportJoints();
    bool exportLibraryJoints();

     enum SystemUnitType
    {
        UNITS_INCHES,
        UNITS_FEET,
        UNITS_MILES,
        UNITS_MILLIMETERS,
        UNITS_CENTIMETERS,
        UNITS_METERS,
        UNITS_KILOMETERS
    };


private:


    /** The stream writer used to write the COLLADASW file.*/
    COLLADASW::StreamWriter mStreamWriter;


};

#endif	/* KDLCOLLADAEXPORTER_H */

