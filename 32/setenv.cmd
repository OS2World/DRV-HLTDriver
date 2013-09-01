/***************************************************************************
 *      Created 2005  eCo Software                                         *
 *                                                                         *
 *      DISCLAIMER OF WARRANTIES.  The following [enclosed] code is        *
 *      sample code created by eCo Software. This sample code is not part  *
 *      of any standard or eCo Software product and is provided to you     *
 *      solely for the purpose of assisting you in the development of your *
 *      applications.  The code is provided "AS IS", without               *
 *      warranty of any kind. eCo Software shall not be liable for any     *
 *      damages arising out of your use of the sample code, even if they   *
 *      have been advised of the possibility of such damages.              *
 *                                                                         *
 *       Author: Pavel Shtemenko <pasha@paco.odessa.ua>                    *
 *-------------------------------------------------------------------------*/

    /*
     * Toolkit (4.5) main directory.
     */
     sTKMain    = 'e:\os2tk45';

    /*
     * Device Driver Kit (DDK) (v4.0+) base (important not main) directory.
     */
    sDDKBase    = 'e:\os2tk45\ddk\base';

    /*
     * IBM C/C++ Compiler and Tools Version 3.6.5 main directory.
     */
    sCxxMain    = 'e:\compilers\ibmcxxo';

    /*
     * Microsoft C v6.0a main directory.
     */
    sMSCMain    = 'e:\os2tk45\ddk\ddktools\toolkits\msc60';


    /**
     * Set environment - don't change locally!
     *
     * Note: This is done in this inefficient was to allow this file to be
     *       invoked serveral times and still have the exactly same environment.
     **/
    call EnvVar_Set      'tkmain',  sTkMain;
    call EnvVar_Set      'ddkbase', sDDKBase;
    call EnvVar_Set      'cxxmain', sCxxMain;
    call EnvVar_Set      'mscmain', sMSCMain;


    call EnvVar_AddFront 'path',        sMSCMain'\binp;'
    call EnvVar_AddFront 'path',        sDDKBase'\tools;'
    call EnvVar_AddFront 'path',        sCxxMain'\bin;'
    call EnvVar_AddFront 'path',        sTkMain'\bin;'
    call EnvVar_AddFront 'path',        'e:\os2tk45\ddk\base32\tools\os2.386\bin;'

    call EnvVar_AddFront 'dpath',       sCxxMain'\help;'
    call EnvVar_AddFront 'dpath',       sCxxMain'\local;'
    call EnvVar_AddFront 'dpath',       sTkMain'\book;'
    call EnvVar_AddFront 'dpath',       sTkMain'\msg;'

    call EnvVar_AddFront 'beginlibpath', sCxxMain'\runtime;'
    call EnvVar_AddFront 'beginlibpath', sCxxMain'\dll;'
    call EnvVar_AddFront 'beginlibpath', sTkMain'\dll;'

    call EnvVar_AddFront 'help',        sTkMain'\help;'
    call EnvVar_AddFront 'bookshelf',   sTkMain'\archived;'
    call EnvVar_AddFront 'bookshelf',   sTkMain'\book;'

    call EnvVar_AddFront 'nlspath',     sCxxMain'\msg\%N;'
    call EnvVar_AddFront 'nlspath',     sTkMain'\msg\%N;'
    call EnvVar_AddEnd   'ulspath',     sTkMain'\language;'

    call EnvVar_AddFront 'include',     sDDKBase'\h;'
    call EnvVar_AddFront 'include',     sCxxMain'\include;'
    call EnvVar_AddFront 'include',     sTkMain'\H;'
    call EnvVar_AddFront 'include',     sTkMain'\H\GL;'
    call EnvVar_AddFront 'include',     sTkMain'\SPEECH\H;'
    call EnvVar_AddFront 'include',     sTkMain'\H\RPC;'
    call EnvVar_AddFront 'include',     sTkMain'\H\NETNB;'
    call EnvVar_AddFront 'include',     sTkMain'\H\NETINET;'
    call EnvVar_AddFront 'include',     sTkMain'\H\NET;'
    call EnvVar_AddFront 'include',     sTkMain'\H\ARPA;'

    call EnvVar_AddEnd   'lib',         sTkMain'\SAMPLES\MM\LIB;'
    call EnvVar_AddEnd   'lib',         sTkMain'\SPEECH\LIB;'
    call EnvVar_AddFront 'lib',         sCxxMain'\lib;'
    call EnvVar_AddFront 'lib',         sDDKBase'\lib;'
    call EnvVar_AddFront 'lib',         sTkMain'\lib;'
    call EnvVar_AddFront 'lib',         sMSCMain'\lib;'

    call EnvVar_AddFront 'helpndx',     'EPMKWHLP.NDX;'

    call EnvVar_AddFront 'ipfc',        sCxxMain'\ipfc;'
    call EnvVar_AddFront 'ipfc',        sTkMain'\ipfc;'

    call EnvVar_Set      'LANG',        'en_us'
    call EnvVar_Set      'CPP_DBG_LANG', 'CPP'

    call EnvVar_Set      'CPREF',       'CP1.INF+CP2.INF+CP3.INF'
    call EnvVar_Set      'GPIREF',      'GPI1.INF+GPI2.INF+GPI3.INF+GPI4.INF'
    call EnvVar_Set      'MMREF',       'MMREF1.INF+MMREF2.INF+MMREF3.INF'
    call EnvVar_Set      'PMREF',       'PM1.INF+PM2.INF+PM3.INF+PM4.INF+PM5.INF'
    call EnvVar_Set      'WPSREF',      'WPS1.INF+WPS2.INF+WPS3.INF'

    exit(0);

/**
 * Procedure section
 **/

/*
 * Add sToAdd in front of sEnvVar.
 *
 * Known features: Don't remove sToAdd from original value if sToAdd
 *                 is at the end and don't end with a ';'.
 */
EnvVar_AddFront: procedure
    parse arg sEnvVar, sToAdd

    /* checks that sToAdd ends with an ';'. Adds one if not. */
    if (substr(sToAdd, length(sToAdd), 1) <> ';') then
        sToAdd = sToAdd || ';';

    /* check and evt. remove ';' at start of sToAdd */
    if (substr(sToAdd, 1, 1) = ';') then
        sToAdd = substr(sToAdd, 2);

    /* Get original variable value */
    sOrgEnvVar = EnvVar_Get(sEnvVar);

    /* Remove previously sToAdd if exists. (Changing sOrgEnvVar). */
    i = pos(translate(sToAdd), translate(sOrgEnvVar));
    if (i > 0) then
        sOrgEnvVar = substr(sOrgEnvVar, 1, i-1) || substr(sOrgEnvVar, i + length(sToAdd));

    /* set environment */
    return EnvVar_Set(sEnvVar, sToAdd||sOrgEnvVar);


/*
 * Add sToAdd as the end of sEnvVar.
 *
 * Known features: Don't remove sToAdd from original value if sToAdd
 *                 is at the end and don't end with a ';'.
 */
EnvVar_AddEnd: procedure
    parse arg sEnvVar, sToAdd

    /* checks that sToAdd ends with an ';'. Adds one if not. */
    if (substr(sToAdd, length(sToAdd), 1) <> ';') then
        sToAdd = sToAdd || ';';

    /* check and evt. remove ';' at start of sToAdd */
    if (substr(sToAdd, 1, 1) = ';') then
        sToAdd = substr(sToAdd, 2);

    /* Get original variable value */
    sOrgEnvVar = EnvVar_Get(sEnvVar);

    /* Remove previously sToAdd if exists. (Changing sOrgEnvVar). */
    i = pos(translate(sToAdd), translate(sOrgEnvVar));
    if (i > 0) then
        sOrgEnvVar = substr(sOrgEnvVar, 1, i-1) || substr(sOrgEnvVar, i + length(sToAdd));

    /* checks that sOrgEnvVar ends with an ';'. Adds one if not. */
    if (substr(sOrgEnvVar, length(sOrgEnvVar), 1) <> ';') then
        sOrgEnvVar = sOrgEnvVar || ';';

    /* set environment */
    return EnvVar_Set(sEnvVar, sOrgEnvVar||sToAdd);


/*
 * Sets sEnvVar to sValue.
 */
EnvVar_Set: procedure
    parse arg sEnvVar, sValue

    /*
     * Begin/EndLibpath fix:
     *      We'll have to set internal these using both commandline 'SET'
     *      and internal VALUE in order to export it and to be able to
     *      get it (with EnvVar_Get) again.
     */
    if translate(sEnvVar) = 'BEGINLIBPATH' | translate(sEnvVar) = 'ENDLIBPATH' then
        'set' sEnvVar'='sValue;
    sRc = VALUE(sEnvVar, sValue, 'OS2ENVIRONMENT');
    return 0;

/*
 * Gets the value of sEnvVar.
 */
EnvVar_Get: procedure
    parse arg sEnvVar
    return value(sEnvVar,, 'OS2ENVIRONMENT');

