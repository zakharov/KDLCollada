/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.
    
    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef KDLCOLLADA_H
#define	KDLCOLLADA_H

#include <kdl/chain.hpp>
#include <string>

class KDLCollada {
public:
    KDLCollada();
    KDLCollada(const KDLCollada& orig);
    virtual ~KDLCollada();

    bool load(const std::string& filename, std::vector<KDL::Chain>& kdlChain);
    bool save(const std::string& filename, std::vector<KDL::Chain>& kdlChain);

private:

};

#endif	/* KDLCOLLADA_H */

