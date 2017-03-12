// JNI code by leorblx, base decryption code by ArmsOfSorrow.
// https://github.com/ArmsOfSorrow/nfsw-decrypt
#include "me_leorblx_webtools_NativeBridge.h"

#include <map>
#include <string>
#include <cstddef>
#include <iterator>
#include <vector>

#include <assert.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>

using std::vector;

// Constants
const char *binMode = "rb";

// Macros

// http://stackoverflow.com/questions/1546789/clean-code-to-printf-size-t-in-c-or-nearest-equivalent-of-c99s-z-in-c
#if defined(_MSC_VER) || defined(__MINGW32__) //__MINGW32__ should goes before __GNUC__
  #define JL_SIZE_T_SPECIFIER    "%Iu"
  #define JL_SSIZE_T_SPECIFIER   "%Id"
  #define JL_PTRDIFF_T_SPECIFIER "%Id"
#elif defined(__GNUC__)
  #define JL_SIZE_T_SPECIFIER    "%zu"
  #define JL_SSIZE_T_SPECIFIER   "%zd"
  #define JL_PTRDIFF_T_SPECIFIER "%zd"
#else
  // TODO figure out which to use.
  #if NUMBITS == 32
    #define JL_SIZE_T_SPECIFIER    something_unsigned
    #define JL_SSIZE_T_SPECIFIER   something_signed
    #define JL_PTRDIFF_T_SPECIFIER something_signed
  #else
    #define JL_SIZE_T_SPECIFIER    something_bigger_unsigned
    #define JL_SSIZE_T_SPECIFIER   something_bigger_signed
    #define JL_PTRDIFF_T_SPECIFIER something-bigger_signed
  #endif
#endif

// Functions

// File decryption
#ifndef strlcpy
    size_t strlcpy(char *d, char const *s, size_t n) {
        return snprintf(d, n, "%s", s);
    }
#endif

#ifndef strlcat
    size_t strlcat(char *d, char const *s, size_t n) {
        return snprintf(d, n, "%s%s", d, s);
    }
#endif

#ifndef fopen_s
    int fopen_s(FILE **f, const char *name, const char *mode) {
        int ret = 0;
        assert(f);
        *f = fopen(name, mode);
        /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
        if (!*f)
            ret = errno;
        return ret;
    }
#endif

#ifndef file_getlength
    long file_getlength(FILE *pFile) {
        fseek(pFile, 0, SEEK_END);
        long len = ftell(pFile);
        rewind(pFile);

        return len;
    }
#endif

void apply_cipher(char *pBuf, unsigned int len) {
    unsigned int eax, ecx = 0;
    unsigned int edi = 0x00519753;

    for (int i = 0; i < len; ++i) {
        eax = edi;
        eax ^= 0x1D872B41;
        ecx = eax >> 0x5;
        ecx ^= eax;
        edi = ecx << 0x1B;
        edi ^= ecx;
        ecx = 0x00B0ED68;
        edi ^= eax;
        eax = edi >> 0x17;
        *pBuf ^= (char) eax;
        ++pBuf;
    }
}

// Others

// http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
std::vector<std::string> extract_keys(std::map<std::string, long> map) {
   std::vector<std::string> retval;
   
   for (auto const& element : map) {
       retval.push_back(element.first);
   }
   
   return retval;
}

std::map<std::string, long> createPhysicsMap() {
    std::map<std::string, long> map;
    
    map.insert(std::make_pair("ALFA ROMEO 8C COMPETIZIONE", 226126488));
    map.insert(std::make_pair("ASTON MARTIN DBS", 738983158));
    map.insert(std::make_pair("ASTON MARTIN DBS VOLANTE", 1606403377));
    map.insert(std::make_pair("ASTON MARTIN VANTAGE V12", 3020568755));
    map.insert(std::make_pair("AUDI A1 CLUBSPORT QUATTRO CONCEPT", 2483550265));
    map.insert(std::make_pair("AUDI A3 3.2 QUATTRO", 1447950598));
    map.insert(std::make_pair("AUDI QUATTRO 20V", 2215218184));
    map.insert(std::make_pair("AUDI R8 4.2 FSI QUATTRO", 96940328));
    map.insert(std::make_pair("AUDI R8 COUPE 5.2 FSI QUATTRO", 1692883589));
    map.insert(std::make_pair("AUDI R8 LMS ULTRA", 3838204992));
    map.insert(std::make_pair("AUDI RS4", 1198628936));
    map.insert(std::make_pair("AUDI S5", 616754006));
    map.insert(std::make_pair("AUDI TT RS COUPE", 3760350532));
    map.insert(std::make_pair("BENTLEY CONTINENTAL SUPERSPORTS CONVERTIBLE", 1747671174));
    map.insert(std::make_pair("BENTLEY CONTINENTAL SUPERSPORTS COUPE", 3048674933));
    map.insert(std::make_pair("BMW 1 SERIES M COUPE", 1362045085));
    map.insert(std::make_pair("BMW 135i COUPE", 4048551937));
    map.insert(std::make_pair("BMW 3.0 CSL GR.5", 2830421725));
    map.insert(std::make_pair("BMW M1 PROCAR", 2122419239));
    map.insert(std::make_pair("BMW M3 (E92)", 700802152));
    map.insert(std::make_pair("BMW M3 GTR (E46)", 3448244287));
    map.insert(std::make_pair("BMW M3 GTS (E92)", 3771450869));
    map.insert(std::make_pair("BMW M3 SPORT EVOLUTION (E30)", 2208974420));
    map.insert(std::make_pair("BMW M6 CABRIOLET", 3106200836));
    map.insert(std::make_pair("BMW M6 COUPE", 3424833218));
    map.insert(std::make_pair("BMW Z4 GT3", 391691160));
    map.insert(std::make_pair("BMW Z4 M COUPE", 4232410043));
    map.insert(std::make_pair("BUGATTI VEYRON 16.4", 3729224832));
    map.insert(std::make_pair("CADILLAC CTS-V", 2651207871));
    map.insert(std::make_pair("CATERHAM SUPERLIGHT R500", 2064453805));
    map.insert(std::make_pair("CHEVROLET CAMARO SS", 2425636121));
    map.insert(std::make_pair("CHEVROLET CAMARO ZL1", 4097872176));
    map.insert(std::make_pair("CHEVROLET CAMARO ZL1 ELITE EDITION", 3492999886));
    map.insert(std::make_pair("CHEVROLET CHEVELLE SS", 65044046));
    map.insert(std::make_pair("CHEVROLET COBALT SS", 1841343282));
    map.insert(std::make_pair("CHEVROLET CORVETTE STING RAY (C2)", 3045084254));
    map.insert(std::make_pair("CHEVROLET CORVETTE Z06", 1853505843));
    map.insert(std::make_pair("CHEVROLET CORVETTE Z06 CARBON LIMITED EDITION", 1683048341));
    map.insert(std::make_pair("CHEVROLET CORVETTE ZR1", 2072093248));
    map.insert(std::make_pair("CHEVROLET EL CAMINO SS", 2015802169));
    map.insert(std::make_pair("CHRYSLER 300C HEMI V8", 1746378961));
    map.insert(std::make_pair("DODGE CHALLENGER R/T", 2744149874));
    map.insert(std::make_pair("DODGE CHALLENGER R/T CONCEPT", 3111694136));
    map.insert(std::make_pair("DODGE CHARGER R/T", 2257416053));
    map.insert(std::make_pair("DODGE CHARGER SRT-8 SUPER BEE", 2210168336));
    map.insert(std::make_pair("DODGE CHARGER SRT-8 (2012)", 2434282173));
    map.insert(std::make_pair("DODGE VIPER ELITE SRT-10 ACR", 2222864237));
    map.insert(std::make_pair("DODGE VIPER SRT-10", 3660768406));
    map.insert(std::make_pair("FORD CAPRI RS 3100", 1528001747));
    map.insert(std::make_pair("FORD CROWN VICTORIA POLICE INTERCEPTOR", 1849927410));
    map.insert(std::make_pair("FORD ESCORT MK1 RS1600 FIA GROUP 2", 558351072));
    map.insert(std::make_pair("FORD ESCORT RS COSWORTH", 3780028278));
    map.insert(std::make_pair("FORD F-150 RAPTOR SVT", 2848084960));
    map.insert(std::make_pair("FORD FOCUS RS", 3593046329));
    map.insert(std::make_pair("FORD GT", 1119921642));
    map.insert(std::make_pair("FORD GT40", 2743845698));
    map.insert(std::make_pair("FORD LOTUS CORTINA", 3174564404));
    map.insert(std::make_pair("FORD POLICE INTERCEPTOR", 1213953721));
    map.insert(std::make_pair("FORD MUSTANG BOSS 302", 4239617268));
    map.insert(std::make_pair("FORD MUSTANG BOSS 302 '69", 1379198987));
    map.insert(std::make_pair("FORD MUSTANG RTR-X", 2180899715));
    map.insert(std::make_pair("FORD SHELBY GT500 SUPER SNAKE", 2812191053));
    map.insert(std::make_pair("FORD SHELBY TERLINGUA MUSTANG", 3299184535));
    map.insert(std::make_pair("HUMMER H1", 3743758759));
    map.insert(std::make_pair("HUMMER H1 SNOWFLAKE", 1101501558));
    map.insert(std::make_pair("INFINITI G35", 3879636592));
    map.insert(std::make_pair("JAGUAR E-TYPE LIGHTWEIGHT", 2929107554));
    map.insert(std::make_pair("JAGUAR XKR", 3256903572));
    map.insert(std::make_pair("JEEP GRAND CHEROKEE SRT", 49262384));
    map.insert(std::make_pair("KOENIGSEGG AGERA", 2885108237));
    map.insert(std::make_pair("KOENIGSEGG CCX", 851565734));
    map.insert(std::make_pair("KOENIGSEGG CCX ELITE EDITION", 2849243667));
    map.insert(std::make_pair("KOENIGSEGG CCXR EDITION", 3791206397));
    map.insert(std::make_pair("LAMBORGHINI AVENTADOR LP 700-4", 782340389));
    map.insert(std::make_pair("LAMBORGHINI COUNTACH 5000 QUATTROVALVOLE", 753694961));
    map.insert(std::make_pair("LAMBORGHINI DIABLO SV", 1501719908));
    map.insert(std::make_pair("LAMBORGHINI ESTOQUE", 305284749));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP 550-2 VALENTINO BALBONI", 2295513436));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP 560-4", 3652740394));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP 560-4 SPYDER", 1946692043));
    map.insert(std::make_pair("LAMBORGHINI MIURA SV", 2881853762));
    map.insert(std::make_pair("LAMBORGHINI MIURA CONCEPT", 1715410532));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 640", 3839584179));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 650-4 ROADSTER", 116888911));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 670-4 SUPERVELOCE", 3424950933));
    map.insert(std::make_pair("LAMBORGHINI REVENTON", 2502510567));
    map.insert(std::make_pair("LAMBORGHINI SESTO ELEMENTO", 1914316466));
    map.insert(std::make_pair("LANCIA DELTA HF", 4140664939));
    map.insert(std::make_pair("LEXUS IS 300", 1543450544));
    map.insert(std::make_pair("LEXUS IS 350", 3967172679));
    map.insert(std::make_pair("LEXUS IS F", 608899747));
    map.insert(std::make_pair("LEXUS LFA", 3404495997));
    map.insert(std::make_pair("LOTUS ELISE 111R", 826100022));
    map.insert(std::make_pair("LOTUS EUROPA S", 2443315892));
    map.insert(std::make_pair("LOTUS EVORA", 3652242210));
    map.insert(std::make_pair("LOTUS EXIGE CUP 260", 2400736834));
    map.insert(std::make_pair("MARUSSIA B2", 3598578092));
    map.insert(std::make_pair("MAZDA MX-5 MIATA", 2278634376));
    map.insert(std::make_pair("MAZDA RX-7", 4243400612));
    map.insert(std::make_pair("MAZDA RX-7 FC3S", 2233053554));
    map.insert(std::make_pair("MAZDA RX-7 RZ", 1106440273));
    map.insert(std::make_pair("MAZDA RX-8", 3593684023));
    map.insert(std::make_pair("MAZDA RX-8 '09", 913728625));
    map.insert(std::make_pair("MAZDA MAZDASPEED 3 '08", 1886825490));
    map.insert(std::make_pair("MCLAREN F1 ELITE", 2752968912));
    map.insert(std::make_pair("MCLAREN MP4-12C", 170263900));
    map.insert(std::make_pair("MCLAREN MP4-12C 'BRAAAIIIINS' EDITION", 396212969));
    map.insert(std::make_pair("MERCEDES-BENZ SLR MCLAREN 722 EDITION", 3523829773));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GS-T", 1524705036));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GS-T ELITE EDITION", 1861278489));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GT", 166450190));
    map.insert(std::make_pair("MITSUBISHI LANCER EVOLUTION VIII", 3438214070));
    map.insert(std::make_pair("MITSUBISHI LANCER EVOLUTION IX MR-EDITION", 2101449805));
    map.insert(std::make_pair("MITSUBISHI LANCER EVOLUTION X", 1804573216));
    map.insert(std::make_pair("NFS WORLD BATTLEFIELD SUV #1", 3038909480));
    map.insert(std::make_pair("NFS WORLD BATTLEFIELD SUV #2", 342953166));
    map.insert(std::make_pair("NFS WORLD RABBIT SUV", 813924329));
    map.insert(std::make_pair("NISSAN 200SX (S14)", 3593096112));
    map.insert(std::make_pair("NISSAN 240SX (S13)", 2825858044));
    map.insert(std::make_pair("NISSAN 350Z (Z33)", 890471737));
    map.insert(std::make_pair("NISSAN 370Z (Z34)", 1965030943));
    map.insert(std::make_pair("NISSAN 370Z ROADSTER (Z34)", 3519223149));
    map.insert(std::make_pair("NISSAN FAIRLADY 240ZG", 1684160862));
    map.insert(std::make_pair("NISSAN GT-R (R35)", 4217318880));
    map.insert(std::make_pair("NISSAN GT-R SPECV (R35)", 3981355351));
    map.insert(std::make_pair("NISSAN R34 GT-R NISMO Z-TUNE", 2903547464));
    map.insert(std::make_pair("NISSAN SILVIA S15", 3703742235));
    map.insert(std::make_pair("NISSAN SKYLINE 2000GT-R (C10)", 2559752336));
    map.insert(std::make_pair("NISSAN SKYLINE GT-R (R32)", 1454444272));
    map.insert(std::make_pair("NISSAN SKYLINE GT-R V-SPEC (R34)", 3685220761));
    map.insert(std::make_pair("PAGANI ZONDA CINQUE", 2521436549));
    map.insert(std::make_pair("PAGANI ZONDA F", 2908026505));
    map.insert(std::make_pair("PAGANI ZONDA F ROADSTER", 3313383302));
    map.insert(std::make_pair("PLYMOUTH HEMI CUDA", 1601041606));
    map.insert(std::make_pair("PLYMOUTH ROAD RUNNER", 459783596));
    map.insert(std::make_pair("PONTIAC FIREBIRD FORMULA", 335414303));
    map.insert(std::make_pair("PONTIAC GTO '65", 3873582052));
    map.insert(std::make_pair("PONTIAC SOLSTICE GXP", 926809415));
    map.insert(std::make_pair("PORSCHE 911 CARRERA RSR 3.0", 1170411476));
    map.insert(std::make_pair("PORSCHE 911 CARRERA S", 1433115429));
    map.insert(std::make_pair("PORSCHE 911 GT2", 2604594287));
    map.insert(std::make_pair("PORSCHE 911 GT2 (997)", 3566516144));
    map.insert(std::make_pair("PORSCHE 911 GT3 RS", 1092157913));
    map.insert(std::make_pair("PORSCHE 911 GT3 RS 4.0", 554050898));
    map.insert(std::make_pair("PORSCHE 911 TURBO", 1518310457));
    map.insert(std::make_pair("PORSCHE 914-6 GT", 2357465487));
    map.insert(std::make_pair("PORSCHE 959", 579778535));
    map.insert(std::make_pair("PORSCHE BOXSTER SPYDER", 2975052995));
    map.insert(std::make_pair("PORSCHE CARRERA GT", 1728462292));
    map.insert(std::make_pair("PORSCHE CAYMAN S", 1096113131));
    map.insert(std::make_pair("PORSCHE CONCEPT 918 RSR", 1712914169));
    map.insert(std::make_pair("PORSCHE PANAMERA TURBO", 1851620885));
    map.insert(std::make_pair("RENAULT SPORT CLIO V6", 3000637927));
    map.insert(std::make_pair("RENAULT SPORT MEGANE RS", 4285991974));
    map.insert(std::make_pair("SCION TC", 2753606463));
    map.insert(std::make_pair("SHELBY AC COBRA 427", 3967174710));
    map.insert(std::make_pair("SHELBY COBRA DAYTONA COUPE", 1386210131));
    map.insert(std::make_pair("MERCEDES-BENZ SLR MCLAREN STIRLING MOSS", 117677212));
    map.insert(std::make_pair("SUBARU IMPREZA WRX STI", 3098117036));
    map.insert(std::make_pair("SUBARU IMPREZA WRX STI (HATCHBACK)", 1306578585));
    map.insert(std::make_pair("TOYOTA COROLLA GT-S (AE86)", 890389270));
    map.insert(std::make_pair("TOYOTA MR2", 814288006));
    map.insert(std::make_pair("TOYOTA SUPRA", 1727083572));
    map.insert(std::make_pair("VAUXHALL MONARO VXR", 2734558288));
    map.insert(std::make_pair("VOLKSWAGEN GOLF GTI", 3794739586));
    map.insert(std::make_pair("VOLKSWAGEN R32", 2485894945));
    map.insert(std::make_pair("VOLKSWAGEN SCIROCCO", 2329071357));
    map.insert(std::make_pair("Dumptruck (player_dumptruck)", 1998148470));
    map.insert(std::make_pair("Firetruck (player_firetruck)", 2899963559));
    map.insert(std::make_pair("Semi truck (cs_semi)", 880729926));
    map.insert(std::make_pair("Police Cruiser (copmidsize_nis)", 2503453879));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #1 (copmidsize)", 3147508024));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #2 (copmidsize_ce)", 2893222352));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #3 (copmidsize_nis_ld)", 1567506004));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #4 (copmidsize_weak)", 2758051216));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #5 (copmidsize_escape)", 670270267));
    map.insert(std::make_pair("Police Dodge Charger SRT-8 #6 (player_cop)", 4118654313));
    map.insert(std::make_pair("Undercover Police Dodge Charger SRT-8 (copghost)", 2745291138));
    map.insert(std::make_pair("Police Pontiac GTO #1 (copgto)", 3432534870));
    map.insert(std::make_pair("Police Pontiac GTO #2 (copgto_escape)", 415375992));
    map.insert(std::make_pair("Undercover Police Pontiac GTO (copgtoghost)", 3924565494));
    map.insert(std::make_pair("Police Muscle Car #1 (copcarmus08)", 3446082958));
    map.insert(std::make_pair("Police Muscle Car #2 (copcarmus08_escape)", 567053233));
    map.insert(std::make_pair("Undercover Police Muscle Car #1 (copcarmus08gh)", 4167086461));
    map.insert(std::make_pair("Undercover Police Muscle Car #2 (copcarmus08gh_escape)", 2263868110));
    map.insert(std::make_pair("Police Corvette #1 (copsporthench)", 3002281954));
    map.insert(std::make_pair("Police Corvette #2 (copsport_escape)", 3560312949));
    map.insert(std::make_pair("Police Corvette #3 (player_cop_corvette)", 3006666286));
    map.insert(std::make_pair("Police Corvette #4 (player_cop_gto)", 2500824978));
    map.insert(std::make_pair("Undercover Police Corvette (copsportghost)", 2766890632));
    map.insert(std::make_pair("Police Cross Corvette #1 (copsport)", 2051656907));
    map.insert(std::make_pair("Police Cross Corvette #1 (copcross)", 3548151917));
    map.insert(std::make_pair("Police Light Rhino SUV (copsuvl)", 1420889656));
    map.insert(std::make_pair("Police Heavy Rhino SUV #1 (copsuv)", 951288358));
    map.insert(std::make_pair("Police Heavy Rhino SUV #2 (copsuvpatrol)", 773103276));
    map.insert(std::make_pair("Police Heavy Rhino SUV #3 (copsuv_escape)", 1615846148));
    map.insert(std::make_pair("Police Heavy Rhino SUV #4 (player_cop_suv)", 3500317914));
    map.insert(std::make_pair("Police Heavy Rhino SUV #5 (cop_copsuv)", 2705562036));
    map.insert(std::make_pair("Police Helicopter #1 (copheli)", 105275058));
    map.insert(std::make_pair("Police Helicopter #2 (copter)", 2485624493));
    map.insert(std::make_pair("TRAFHA (Hatchback)", 2697444185));
    map.insert(std::make_pair("TRAF4DSEDA (Sedan #1/\"Civillian\" Taxi)", 3751483097));
    map.insert(std::make_pair("TRAFTAXI (Taxi)", 3590420638));
    map.insert(std::make_pair("TRAF4DSEDB (Sedan #2/\"Civillian\" Courtesy Car)", 1714104611));
    map.insert(std::make_pair("TRAFCOURT (Courtesy Car)", 3866921014));
    map.insert(std::make_pair("TRAFFICCOUP (Coupe)", 1394226312));
    map.insert(std::make_pair("TRAF4DSEDC (Sedan #3/Classic Sedan)", 1590265686));
    map.insert(std::make_pair("TRAFSTWAG (Station Wagon)", 1137593283));
    map.insert(std::make_pair("TRAFPICKUPA (Pickup)", 2109639133));
    map.insert(std::make_pair("TRAFMINIVAN (Minivan)", 3872702185));
    map.insert(std::make_pair("TRAFSUVA (SUV)", 1049534608));
    map.insert(std::make_pair("TRAFVANB (Van)", 1407692666));
    map.insert(std::make_pair("TRAFNEWS (News Van)", 3686349938));
    map.insert(std::make_pair("TRAFAMB (Ambulance)", 1869084661));
    map.insert(std::make_pair("TRAFDMPTR (Dumptruck)", 3312194361));
    map.insert(std::make_pair("TRAFGARB (Garbage Truck)", 3426097812));
    map.insert(std::make_pair("TRAFCMTR (Cement Truck)", 1177767274));
    map.insert(std::make_pair("TRAFFIRE (Firetruck)", 147320032));
    map.insert(std::make_pair("TRAFCAMPER (Camper)", 1749358113));
    map.insert(std::make_pair("SEMI (Truck with no trailer)", 3574286522));
    map.insert(std::make_pair("SEMIA (Truck with Tanker)", 3712834604));
    map.insert(std::make_pair("TRAILERA (Tank Trailer)", 14167946));
    map.insert(std::make_pair("SEMIB (Truck with Cars)", 2847214020));
    map.insert(std::make_pair("TRAILERB (Trailer with Cars)", 480926608));
    map.insert(std::make_pair("SEMIBOX (Truck with Autozone Trailer)", 2792933787));
    map.insert(std::make_pair("TRAILERBOX (Autozone Trailer)", 2782182566));
    map.insert(std::make_pair("SEMICMT (Truck with Pipes)", 3223840706));
    map.insert(std::make_pair("TRAILERCMT (Trailer with Pipes)", 923662918));
    map.insert(std::make_pair("SEMICON (Truck with Containers)", 621673210));
    map.insert(std::make_pair("TRAILERCON (Trailer Containers)", 1170647601));
    map.insert(std::make_pair("SEMICRATE (Truck with Boxes)", 3908647713));
    map.insert(std::make_pair("TRAILERCRATE (Trailer with Boxes)", 2699977158));
    map.insert(std::make_pair("SEMILOG (Trailer with Logs)", 177392743));
    map.insert(std::make_pair("TRAILERLOG (Trailer with Logs)", 3707500446));
    map.insert(std::make_pair("AAA (Test Car)", 4123572107));
    map.insert(std::make_pair("BMW M3 E46", 3718574377));
    map.insert(std::make_pair("BMW M3 GTR E46 RACE", 1309171635));
    map.insert(std::make_pair("PORSCHE 911 TURBO S (996)", 3531430797));
    map.insert(std::make_pair("LOTUS EXIGE (2008)", 3239158528));
    map.insert(std::make_pair("RENAULT MÉGANE COUPÉ", 1340781260));
    
    return map;
}

std::map<std::string, long> createBaseCarMap() {
    std::map<std::string, long> map;
    
    map.insert(std::make_pair("ALFA ROMEO 8C COMPETIZIONE", 461323600));
    map.insert(std::make_pair("ASTON MARTIN DBS", 40376));
    map.insert(std::make_pair("ASTON MARTIN DBS VOLANTE", 927255791));
    map.insert(std::make_pair("ASTON MARTIN VANTAGE V12", 1153363998));
    map.insert(std::make_pair("AUDI A1 CLUBSPORT QUATTRO CONCEPT", 56149));
    map.insert(std::make_pair("AUDI A3 3.2 QUATTRO", 691868261));
    map.insert(std::make_pair("AUDI QUATTRO 20V", 2090374038));
    map.insert(std::make_pair("AUDI R8 4.2 FSI QUATTRO", 1673));
    map.insert(std::make_pair("AUDI R8 COUPE 5.2 FSI QUATTRO", 60217920));
    map.insert(std::make_pair("AUDI R8 LMS ULTRA", 691868389));
    map.insert(std::make_pair("AUDI RS4", 56152));
    map.insert(std::make_pair("AUDI S5", 1703));
    map.insert(std::make_pair("AUDI TT RS COUPE", 2098561293));
    map.insert(std::make_pair("BENTLEY CONTINENTAL SUPERSPORTS CONVERTIBLE", 334671939));
    map.insert(std::make_pair("BENTLEY CONTINENTAL SUPERSPORTS COUPE", 147456602));
    map.insert(std::make_pair("BMW 135i COUPE", 1293405201));
    map.insert(std::make_pair("BMW 1 SERIES M COUPE", 41998979));
    map.insert(std::make_pair("BMW 3.0 CSL GR.5", 1507688326));
    map.insert(std::make_pair("BMW M1 PROCAR", 1967974518));
    map.insert(std::make_pair("BMW M3 (E92)", 1816135925));
    map.insert(std::make_pair("BMW M3 GTR (E46)", 1816139026));
    map.insert(std::make_pair("BMW M3 GTS (E92)", 1816139027));
    map.insert(std::make_pair("BMW M3 SPORT EVOLUTION (E30)", 1816135725));
    map.insert(std::make_pair("BMW M6 CABRIOLET", 193545762));
    map.insert(std::make_pair("BMW M6 COUPE", 41999880));
    map.insert(std::make_pair("BMW Z4 GT3", 1831591905));
    map.insert(std::make_pair("BMW Z4 M COUPE", 1933));
    map.insert(std::make_pair("BUGATTI VEYRON 16.4", 691868228));
    map.insert(std::make_pair("CADILLAC CTS-V", 1316159));
    map.insert(std::make_pair("CAR_MANU_GENERIC CAR_MDL_TRAFVANB", 1443310131));
    map.insert(std::make_pair("CATERHAM SUPERLIGHT R500", 691868226));
    map.insert(std::make_pair("CHEVROLET CAMARO SS", 1410528946));
    map.insert(std::make_pair("CHEVROLET CAMARO ZL1", 974805577));
    map.insert(std::make_pair("CHEVROLET CAMARO ZL1 ELITE EDITION", 16618735));
    map.insert(std::make_pair("CHEVROLET CHEVELLE SS", 1370575257));
    map.insert(std::make_pair("CHEVROLET COBALT SS", 691868325));
    map.insert(std::make_pair("CHEVROLET CORVETTE STINGRAY (C2)", 1408763688));
    map.insert(std::make_pair("CHEVROLET CORVETTE Z06", 755477579));
    map.insert(std::make_pair("CHEVROLET CORVETTE Z06 CARBON LIMITED EDITION", 434493780));
    map.insert(std::make_pair("CHEVROLET CORVETTE ZR1", 755478696));
    map.insert(std::make_pair("CHEVROLET EL CAMINO SS", 1265021465));
    map.insert(std::make_pair("CHRYSLER 300C HEMI V8", 700789));
    map.insert(std::make_pair("DODGE CHALLENGER R/T CONCEPT", 290872130));
    map.insert(std::make_pair("DODGE CHALLENGER R/T", 1008844988));
    map.insert(std::make_pair("DODGE CHARGER R/T", 990337002));
    map.insert(std::make_pair("DODGE CHARGER SRT-8 SUPER BEE", 1634713038));
    map.insert(std::make_pair("DODGE VIPER SRT-10", 1666705986));
    map.insert(std::make_pair("DODGE VIPER ELUTE SRT-10 ACR", 1711519800));
    map.insert(std::make_pair("FORD CAPRI RS 3100", 691868288));
    map.insert(std::make_pair("FORD CROWN VICTORIA POLICE INTERCEPTOR", 947943862));
    map.insert(std::make_pair("FORD ESCORT RS COSWORTH", 370786472));
    map.insert(std::make_pair("FORD Escort MK1 RS1600 FIA Group 2", 691868358));
    map.insert(std::make_pair("FORD F-150 RAPTOR SVT", 691868360));
    map.insert(std::make_pair("FORD FOCUS RS", 1340228859));
    map.insert(std::make_pair("FORD GT", 1544720613));
    map.insert(std::make_pair("FORD GT40", 1426430711));
    map.insert(std::make_pair("FORD POLICE INTERCEPTOR", 691868290));
    map.insert(std::make_pair("FORD LOTUS CORTINA", 691868255));
    map.insert(std::make_pair("FORD MUSTANG BOSS 302", 26123784));
    map.insert(std::make_pair("FORD MUSTANG BOSS 302 '69", 26123612));
    map.insert(std::make_pair("FORD MUSTANG RTR-X", 2020296126));
    map.insert(std::make_pair("FORD SHELBY GT500 SUPER SNAKE", 529336918));
    map.insert(std::make_pair("FORD SHELBY TERLINGUA MUSTANG", 1095591178));
    map.insert(std::make_pair("HUMMER H1", 691868352));
    map.insert(std::make_pair("HUMMER H1 SNOWFLAKE", 691868257));
    map.insert(std::make_pair("INFINITI G35", 43118));
    map.insert(std::make_pair("JAGUAR E-TYPE LIGHTWEIGHT", 1925678880));
    map.insert(std::make_pair("JAGUAR XKR", 921096850));
    map.insert(std::make_pair("JEEP GRAND CHEROKEE SRT", 691868222));
    map.insert(std::make_pair("KOENIGSEGG AGERA", 691868319));
    map.insert(std::make_pair("KOENIGSEGG CCX", 39325));
    map.insert(std::make_pair("KOENIGSEGG CCX ELITE EDITION", 1606457066));
    map.insert(std::make_pair("KOENIGSEGG CCXR EDITION", 691868327));
    map.insert(std::make_pair("LAMBORGHINI AVENTADOR LP 700-4", 691868323));
    map.insert(std::make_pair("LAMBORGHINI COUNTACH 5000 QUATTROVALVOLE", 303028364));
    map.insert(std::make_pair("LAMBORGHINI DIABLO SV", 1458721354));
    map.insert(std::make_pair("LAMBORGHINI ESTOQUE", 691868259));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP 550-2 VALENTINO BALBONI", 837621662));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP 560-4 SPYDER", 1913185783));
    map.insert(std::make_pair("LAMBORGHINI GALLARDO LP560-4", 930004306));
    map.insert(std::make_pair("LAMBORGHINI MIURA CONCEPT", 691868220));
    map.insert(std::make_pair("LAMBORGHINI MIURA SV", 344244090));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 640", 133082177));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 650-4 ROADSTER", 133082210));
    map.insert(std::make_pair("LAMBORGHINI MURCIELAGO LP 670-4 SUPERVELOCE", 1305539024));
    map.insert(std::make_pair("LAMBORGHINI REVENTON", 691868420));
    map.insert(std::make_pair("LAMBORGHINI SESTO ELEMENTO", 402882280));
    map.insert(std::make_pair("LANCIA DELTA HF", 44072489));
    map.insert(std::make_pair("LEXUS IS F", 46369));
    map.insert(std::make_pair("LEXUS IS 300", 50476782));
    map.insert(std::make_pair("LEXUS IS 350", 50476947));
    map.insert(std::make_pair("LEXUS LFA", 1106775043));
    map.insert(std::make_pair("LOTUS ELISE 111R", 45506673));
    map.insert(std::make_pair("LOTUS EUROPA S", 1512713003));
    map.insert(std::make_pair("LOTUS EVORA", 45872540));
    map.insert(std::make_pair("LOTUS EXIGE CUP 260", 1146389329));
    map.insert(std::make_pair("MARUSSIA B2", 691868387));
    map.insert(std::make_pair("MAZDA MAZDASPEED 3 '08", 87126832));
    map.insert(std::make_pair("MAZDA MX-5 MIATA", 55402337));
    map.insert(std::make_pair("MAZDA RX-7", 56320));
    map.insert(std::make_pair("MAZDA RX-7 FC3S", 691868354));
    map.insert(std::make_pair("MAZDA RX-7 RZ", 61335276));
    map.insert(std::make_pair("MAZDA RX-8", 56321));
    map.insert(std::make_pair("MAZDA RX-8 '09", 1925369332));
    map.insert(std::make_pair("MCLAREN F1 ELITE", 691868418));
    map.insert(std::make_pair("MCLAREN MP4-12C", 1580541262));
    map.insert(std::make_pair("MCLAREN MP4-12C 'BRAAAIIIINS' EDITION", 691868385));
    map.insert(std::make_pair("MERCEDES-BENZ SLR MCLAREN STIRLING MOSS", 691868224));
    map.insert(std::make_pair("MERCEDES-BENZ SLR MCLAREN 722 EDITION", 2049908075));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GS-T", 691868391));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GS-T ELITE EDITION", 1546676681));
    map.insert(std::make_pair("MITSUBISHI ECLIPSE GT", 1054632705));
    map.insert(std::make_pair("MITSUBISHI LANCER EVO VIII", 164818934));
    map.insert(std::make_pair("MITSUBISHI LANCER EVOLUTION IX MR-EDITION", 164818935));
    map.insert(std::make_pair("MITSUBISHI LANCER EVOLUTION X", 164818966));
    map.insert(std::make_pair("NFS WORLD BATTLEFIELD SUV #1", 1137479728));
    map.insert(std::make_pair("NFS WORLD BATTLEFIELD SUV #2", 1137479729));
    map.insert(std::make_pair("NISSAN SKYLINE 2000GT-R (C10)", 323834537));
    map.insert(std::make_pair("NISSAN 200SX (S14)", 21940732));
    map.insert(std::make_pair("NISSAN 240SX (S13)", 22084480));
    map.insert(std::make_pair("NISSAN 350Z (Z33)", 706257));
    map.insert(std::make_pair("NISSAN 370Z (Z34)", 708435));
    map.insert(std::make_pair("NISSAN 370Z ROADSTER (Z34)", 659675369));
    map.insert(std::make_pair("NISSAN FAIRLADY 240ZG", 1719570146));
    map.insert(std::make_pair("NISSAN GT-R (R35)", 1750743496));
    map.insert(std::make_pair("NISSAN GT-R SPECV (R35)", 1939960434));
    map.insert(std::make_pair("NISSAN R34 GT-R NISMO Z-TUNE", 691868393));
    map.insert(std::make_pair("NISSAN SILVIA S15", 951615808));
    map.insert(std::make_pair("NISSAN SKYLINE GT-R (R32)", 1750743499));
    map.insert(std::make_pair("NISSAN SKYLINE GT-R V-SPEC (R34)", 1102563490));
    map.insert(std::make_pair("PAGANI ZONDA CINQUE", 691868422));
    map.insert(std::make_pair("PAGANI ZONDA F", 70523771));
    map.insert(std::make_pair("PAGANI ZONDA F ROADSTER", 450173759));
    map.insert(std::make_pair("PLYMOUTH HEMI CUDA", 1316732));
    map.insert(std::make_pair("PLYMOUTH ROAD RUNNER", 317646849));
    map.insert(std::make_pair("PONTIAC FIREBIRD FORMULA", 656975595));
    map.insert(std::make_pair("PONTIAC GTO '65", 48171572));
    map.insert(std::make_pair("PONTIAC SOLSTICE GXP", 1794097140));
    map.insert(std::make_pair("PORSCHE 911 CARRERA RSR 3.0", 1515789756));
    map.insert(std::make_pair("PORSCHE 911 CARRERA S", 926261));
    map.insert(std::make_pair("PORSCHE 911 GT2", 999200615));
    map.insert(std::make_pair("PORSCHE 911 GT3 RS", 1502747725));
    map.insert(std::make_pair("PORSCHE 911 GT3 RS 4.0", 691868424));
    map.insert(std::make_pair("PORSCHE 911 TURBO", 30573264));
    map.insert(std::make_pair("PORSCHE 914-6 GT", 691868294));
    map.insert(std::make_pair("PORSCHE 959", 27942));
    map.insert(std::make_pair("PORSCHE BOXSTER SPYDER", 740942307));
    map.insert(std::make_pair("PORSCHE CARRERA GT", 507824006));
    map.insert(std::make_pair("PORSCHE CAYMAN S", 682541205));
    map.insert(std::make_pair("PORSCHE 911 GT2 (997)", 1008903605));
    map.insert(std::make_pair("PORSCHE PANAMERA TURBO", 1848802011));
    map.insert(std::make_pair("RENAULT SPORT MEGANE RS", 467126062));
    map.insert(std::make_pair("RENAULT SPORT CLIO V6", 1423445682));
    map.insert(std::make_pair("SCION TC", 1434507918));
    map.insert(std::make_pair("SHELBY COBRA DAYTONA COUPE", 661194635));
    map.insert(std::make_pair("SHELBY AC COBRA 427", 691868286));
    map.insert(std::make_pair("SUBARU IMPREZA WRX STI", 376520152));
    map.insert(std::make_pair("SUBARU IMPREZA WRX STI (HATCHBACK)", 1317604272));
    map.insert(std::make_pair("TOYOTA COROLLA GT-S (AE86)", 142863381));
    map.insert(std::make_pair("TOYOTA MR2", 50672));
    map.insert(std::make_pair("TOYOTA SUPRA", 62440586));
    map.insert(std::make_pair("VOLKSWAGEN GOLF GTI", 1589472076));
    map.insert(std::make_pair("VOLKSWAGEN R32", 55094));
    map.insert(std::make_pair("VOLKSWAGEN SCIROCCO", 90545772));
    
    return map;
}

// Dictionaries
const std::map<std::string, long> physicsMap = createPhysicsMap();
const std::map<std::string, long> baseCarMap = createBaseCarMap();

JNIEXPORT jlong JNICALL Java_me_leorblx_webtools_NativeBridge_nativePhysicsCalc
  (JNIEnv *env, jobject obj, jstring car) {
    const char *carId = env->GetStringUTFChars(car, NULL);
    std::map<std::string, long>::const_iterator pos = physicsMap.find(carId);
    
    env->ReleaseStringUTFChars(car, carId);
    
    if (pos == physicsMap.end()) {
        return (jlong) -1;
    } else {
        return (jlong) pos->second;
    }
}

JNIEXPORT jlong JNICALL Java_me_leorblx_webtools_NativeBridge_nativeBaseCarLookup
  (JNIEnv *env, jobject obj, jstring car) {
    const char *carId = env->GetStringUTFChars(car, NULL);
    std::map<std::string, long>::const_iterator pos = baseCarMap.find(carId);
    
    env->ReleaseStringUTFChars(car, carId);
    
    if (pos == baseCarMap.end()) {
        return (jlong) -1;
    } else {
        return (jlong) pos->second;
    } 
}

JNIEXPORT jstring JNICALL Java_me_leorblx_webtools_NativeBridge_nativeDecrypt
  (JNIEnv *env, jobject obj, jstring path) {
    const char *filePath = env->GetStringUTFChars(path, NULL);
    jstring result;

    FILE *pSrcFile = nullptr;
    int err = fopen_s(&pSrcFile, filePath, binMode);

    if (!err) {
        long len = file_getlength(pSrcFile);

        if (len > 0) {
            char *buf = (char *) malloc(len);
            fread(buf, sizeof(char), len, pSrcFile);

            std::string str = std::string(buf, len);
            size_t special = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz");

            if (special != std::string::npos) {
                if (special != 2) {
                      char* msgBuf = (char*) calloc(256, sizeof(char *));

                      sprintf(msgBuf, "First special character in wrong position: " JL_SIZE_T_SPECIFIER " (expected at pos 2)", special);

                      buf = msgBuf;
                } else {
                    apply_cipher(buf, len);
                }
            } else {
                buf = (char *) "First special character not found.";
            }

            env->ReleaseStringUTFChars(path, filePath);

            result = env->NewStringUTF(buf);
        }
    } else {
        result = env->NewStringUTF((const char *) "Decryption failed. Could not open file.");
    }
    
    return result;
 }

 JNIEXPORT jobjectArray JNICALL Java_me_leorblx_webtools_NativeBridge_nativeGetBaseCarNames
   (JNIEnv *env, jobject obj) {
    jobjectArray ret;
    
    std::vector<std::string> names = extract_keys(baseCarMap);
    
    ret = (jobjectArray) env->NewObjectArray(
        baseCarMap.size(),
        env->FindClass("java/lang/String"),
        NULL
    );
    
    for (int i = 0; i < names.size(); i++) {
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(names.at(i).c_str()));
    }
    
    return ret;
 }

 JNIEXPORT jobjectArray JNICALL Java_me_leorblx_webtools_NativeBridge_nativeGetAllCarNames
   (JNIEnv *env, jobject obj) {
    jobjectArray ret;

    std::vector<std::string> names = extract_keys(physicsMap);

    ret = (jobjectArray) env->NewObjectArray(
        physicsMap.size(),
        env->FindClass("java/lang/String"),
        NULL
    );

    for (int i = 0; i < names.size(); i++) {
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(names.at(i).c_str()));
    }

    return ret;
 }
