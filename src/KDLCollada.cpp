/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "KDLCollada.h"
#include "KDLColladaExporter.h"
#include "KDLColladaImporter.h"

#include "COLLADASaxFWLLoader.h"
#include "GeneratedSaxParserCoutErrorHandler.h"
#include "COLLADAFWRoot.h"

using namespace std;
using namespace KDL;

KDLCollada::KDLCollada()
{
}

KDLCollada::KDLCollada(const KDLCollada& orig)
{
}

KDLCollada::~KDLCollada()
{
}

bool KDLCollada::load(const string& filename, std::vector<Chain>& kdlChain)
{
    KDLColladaImporter importer(kdlChain);
    COLLADASaxFWL::Loader loader;

    COLLADAFW::Root root(&loader, &importer);


    return root.loadDocument(filename);
}

bool KDLCollada::save(const string& filename, std::vector<Chain>& kdlChain)
{
    KDLColladaExporter exporter(filename, kdlChain);



    return exporter.exportChain();
}
