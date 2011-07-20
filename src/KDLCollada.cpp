/*
 * File:   KDLCollada.cpp
 * Author: alexey
 *
 * Created on July 20, 2011, 8:19 AM
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
    KDLColladaImporter importer;
 	COLLADASaxFWL::Loader loader;
	COLLADAFW::Root root(&loader, &importer);


    return root.loadDocument(filename);
}

bool KDLCollada::save(const string& filename, std::vector<Chain>& kdlChain)
{
    KDLColladaExporter exporter;
    return false;
}
