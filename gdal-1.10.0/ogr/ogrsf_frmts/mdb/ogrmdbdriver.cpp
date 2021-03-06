/******************************************************************************
 * $Id: ogrmdbdriver.cpp 21560 2011-01-23 12:11:33Z rouault $
 *
 * Project:  OpenGIS Simple Features Reference Implementation
 * Purpose:  Implements Personal Geodatabase driver.
 * Author:   Even Rouault, <even dot rouault at mines dash paris dot org>
 *
 ******************************************************************************
 * Copyright (c) 2011, Even Rouault, <even dot rouault at mines dash paris dot org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "ogr_mdb.h"
#include "cpl_conv.h"

CPL_CVSID("$Id: ogrmdbdriver.cpp 21560 2011-01-23 12:11:33Z rouault $");

// g++ -fPIC -g -Wall ogr/ogrsf_frmts/mdb/*.cpp -shared -o ogr_MDB.so -Iport -Igcore -Iogr -Iogr/ogrsf_frmts -Iogr/ogrsf_frmts/mdb -L. -lgdal -I/usr/lib/jvm/java-6-openjdk/include -I/usr/lib/jvm/java-6-openjdk/include/linux  -L/usr/lib/jvm/java-6-openjdk/jre/lib/amd64/server -ljvm

extern "C" void RegisterOGRMDB();

/************************************************************************/
/*                            ~OGRODBCDriver()                            */
/************************************************************************/

OGRMDBDriver::~OGRMDBDriver()

{
}

/************************************************************************/
/*                              GetName()                               */
/************************************************************************/

const char *OGRMDBDriver::GetName()

{
    return "MDB";
}

/************************************************************************/
/*                                Open()                                */
/************************************************************************/

OGRDataSource *OGRMDBDriver::Open( const char * pszFilename,
                                    int bUpdate )

{
    OGRMDBDataSource     *poDS;

    if( !EQUAL(CPLGetExtension(pszFilename),"mdb") )
        return NULL;

    VSIStatBuf sStat;
    if (VSIStat(pszFilename, &sStat) != 0)
        return NULL;

    // Open data source
    poDS = new OGRMDBDataSource();

    if( !poDS->Open( pszFilename, bUpdate, TRUE ) )
    {
        delete poDS;
        return NULL;
    }
    else
        return poDS;
}

/************************************************************************/
/*                           TestCapability()                           */
/************************************************************************/

int OGRMDBDriver::TestCapability( const char * pszCap )

{
    return FALSE;
}


/************************************************************************/
/*                           RegisterOGRMDB()                           */
/************************************************************************/

void RegisterOGRMDB()

{
    OGRSFDriverRegistrar::GetRegistrar()->RegisterDriver( new OGRMDBDriver );
}

