#include <aos/aos.h>
#include <barrelfish_kpi/capbits.h>
#include <aos/cap_predicates.h>
/* Includes: */
 
#include <stdint.h>
#include <assert.h>
 
/* Function Definitions: */
 
int8_t compare_caps(struct  capability* left,struct  capability* right,bool tiebreak) {
    uint8_t _fof_x242;
    uint8_t _fof_x243;
    genpaddr_t _fof_x244;
    genpaddr_t _fof_x245;
    gensize_t _fof_x246;
    gensize_t _fof_x247;
    struct  capability* left__236;
    struct  capability left__236__237;
    enum objtype left__236__237__240;
    union  capability_u left__236__237__248;
    struct  FCNode left__236__237__248__250;
    genpaddr_t left__236__237__248__250__252;
    uint8_t left__236__237__248__250__254;
    coreid_t left__236__237__248__250__256;
    union  capability_u left__236__237__258;
    struct  Frame_Mapping left__236__237__258__260;
    lvaddr_t left__236__237__258__260__262;
    union  capability_u left__236__237__264;
    struct  DevFrame_Mapping left__236__237__264__266;
    lvaddr_t left__236__237__264__266__268;
    union  capability_u left__236__237__270;
    struct  VNode_x86_64_pml4_Mapping left__236__237__270__272;
    lvaddr_t left__236__237__270__272__274;
    union  capability_u left__236__237__276;
    struct  VNode_x86_64_pdpt_Mapping left__236__237__276__278;
    lvaddr_t left__236__237__276__278__280;
    union  capability_u left__236__237__282;
    struct  VNode_x86_64_pdir_Mapping left__236__237__282__284;
    lvaddr_t left__236__237__282__284__286;
    union  capability_u left__236__237__288;
    struct  VNode_x86_64_ptable_Mapping left__236__237__288__290;
    lvaddr_t left__236__237__288__290__292;
    union  capability_u left__236__237__294;
    struct  VNode_x86_32_pdpt_Mapping left__236__237__294__296;
    lvaddr_t left__236__237__294__296__298;
    union  capability_u left__236__237__300;
    struct  VNode_x86_32_pdir_Mapping left__236__237__300__302;
    lvaddr_t left__236__237__300__302__304;
    union  capability_u left__236__237__306;
    struct  VNode_x86_32_ptable_Mapping left__236__237__306__308;
    lvaddr_t left__236__237__306__308__310;
    union  capability_u left__236__237__312;
    struct  VNode_ARM_l1_Mapping left__236__237__312__314;
    lvaddr_t left__236__237__312__314__316;
    union  capability_u left__236__237__318;
    struct  VNode_ARM_l2_Mapping left__236__237__318__320;
    lvaddr_t left__236__237__318__320__322;
    union  capability_u left__236__237__324;
    struct  VNode_AARCH64_l0_Mapping left__236__237__324__326;
    lvaddr_t left__236__237__324__326__328;
    union  capability_u left__236__237__330;
    struct  VNode_AARCH64_l1_Mapping left__236__237__330__332;
    lvaddr_t left__236__237__330__332__334;
    union  capability_u left__236__237__336;
    struct  VNode_AARCH64_l2_Mapping left__236__237__336__338;
    lvaddr_t left__236__237__336__338__340;
    union  capability_u left__236__237__342;
    struct  VNode_AARCH64_l3_Mapping left__236__237__342__344;
    lvaddr_t left__236__237__342__344__346;
    union  capability_u left__236__237__348;
    struct  IRQDest left__236__237__348__350;
    uint64_t left__236__237__348__350__352;
    uint64_t left__236__237__348__350__354;
    union  capability_u left__236__237__356;
    struct  IRQSrc left__236__237__356__358;
    uint64_t left__236__237__356__358__360;
    uint64_t left__236__237__356__358__362;
    union  capability_u left__236__237__364;
    struct  IO left__236__237__364__366;
    uint16_t left__236__237__364__366__368;
    uint16_t left__236__237__364__366__370;
    union  capability_u left__236__237__372;
    struct  Notify_RCK left__236__237__372__374;
    coreid_t left__236__237__372__374__376;
    uint16_t left__236__237__372__374__378;
    union  capability_u left__236__237__380;
    struct  Notify_IPI left__236__237__380__382;
    coreid_t left__236__237__380__382__384;
    uint16_t left__236__237__380__382__386;
    union  capability_u left__236__237__388;
    struct  ID left__236__237__388__390;
    coreid_t left__236__237__388__390__392;
    uint32_t left__236__237__388__390__394;
    struct  capability* right__238;
    struct  capability right__238__239;
    enum objtype right__238__239__241;
    union  capability_u right__238__239__249;
    struct  FCNode right__238__239__249__251;
    genpaddr_t right__238__239__249__251__253;
    uint8_t right__238__239__249__251__255;
    coreid_t right__238__239__249__251__257;
    union  capability_u right__238__239__259;
    struct  Frame_Mapping right__238__239__259__261;
    lvaddr_t right__238__239__259__261__263;
    union  capability_u right__238__239__265;
    struct  DevFrame_Mapping right__238__239__265__267;
    lvaddr_t right__238__239__265__267__269;
    union  capability_u right__238__239__271;
    struct  VNode_x86_64_pml4_Mapping right__238__239__271__273;
    lvaddr_t right__238__239__271__273__275;
    union  capability_u right__238__239__277;
    struct  VNode_x86_64_pdpt_Mapping right__238__239__277__279;
    lvaddr_t right__238__239__277__279__281;
    union  capability_u right__238__239__283;
    struct  VNode_x86_64_pdir_Mapping right__238__239__283__285;
    lvaddr_t right__238__239__283__285__287;
    union  capability_u right__238__239__289;
    struct  VNode_x86_64_ptable_Mapping right__238__239__289__291;
    lvaddr_t right__238__239__289__291__293;
    union  capability_u right__238__239__295;
    struct  VNode_x86_32_pdpt_Mapping right__238__239__295__297;
    lvaddr_t right__238__239__295__297__299;
    union  capability_u right__238__239__301;
    struct  VNode_x86_32_pdir_Mapping right__238__239__301__303;
    lvaddr_t right__238__239__301__303__305;
    union  capability_u right__238__239__307;
    struct  VNode_x86_32_ptable_Mapping right__238__239__307__309;
    lvaddr_t right__238__239__307__309__311;
    union  capability_u right__238__239__313;
    struct  VNode_ARM_l1_Mapping right__238__239__313__315;
    lvaddr_t right__238__239__313__315__317;
    union  capability_u right__238__239__319;
    struct  VNode_ARM_l2_Mapping right__238__239__319__321;
    lvaddr_t right__238__239__319__321__323;
    union  capability_u right__238__239__325;
    struct  VNode_AARCH64_l0_Mapping right__238__239__325__327;
    lvaddr_t right__238__239__325__327__329;
    union  capability_u right__238__239__331;
    struct  VNode_AARCH64_l1_Mapping right__238__239__331__333;
    lvaddr_t right__238__239__331__333__335;
    union  capability_u right__238__239__337;
    struct  VNode_AARCH64_l2_Mapping right__238__239__337__339;
    lvaddr_t right__238__239__337__339__341;
    union  capability_u right__238__239__343;
    struct  VNode_AARCH64_l3_Mapping right__238__239__343__345;
    lvaddr_t right__238__239__343__345__347;
    union  capability_u right__238__239__349;
    struct  IRQDest right__238__239__349__351;
    uint64_t right__238__239__349__351__353;
    uint64_t right__238__239__349__351__355;
    union  capability_u right__238__239__357;
    struct  IRQSrc right__238__239__357__359;
    uint64_t right__238__239__357__359__361;
    uint64_t right__238__239__357__359__363;
    union  capability_u right__238__239__365;
    struct  IO right__238__239__365__367;
    uint16_t right__238__239__365__367__369;
    uint16_t right__238__239__365__367__371;
    union  capability_u right__238__239__373;
    struct  Notify_RCK right__238__239__373__375;
    coreid_t right__238__239__373__375__377;
    uint16_t right__238__239__373__375__379;
    union  capability_u right__238__239__381;
    struct  Notify_IPI right__238__239__381__383;
    coreid_t right__238__239__381__383__385;
    uint16_t right__238__239__381__383__387;
    union  capability_u right__238__239__389;
    struct  ID right__238__239__389__391;
    coreid_t right__238__239__389__391__393;
    uint32_t right__238__239__389__391__395;
 
    left__236 = left;
    left__236__237 = *left__236;
    right__238 = right;
    right__238__239 = *right__238;
    left__236__237__240 = left__236__237.type;
    right__238__239__241 = right__238__239.type;
    _fof_x242 = get_type_root(left__236__237__240);
    _fof_x243 = get_type_root(right__238__239__241);
    if ((_fof_x242 != _fof_x243)){
        return ((((_fof_x242 < _fof_x243)) ? (-1) : (1)));
    } else {
    }
    _fof_x244 = get_address(left);
    _fof_x245 = get_address(right);
    if ((_fof_x244 != _fof_x245)){
        return ((((_fof_x244 < _fof_x245)) ? (-1) : (1)));
    } else {
    }
    _fof_x246 = get_size(left);
    _fof_x247 = get_size(right);
    if ((_fof_x246 != _fof_x247)){
        return ((((_fof_x246 > _fof_x247)) ? (-1) : (1)));
    } else {
    }
    if ((left__236__237__240 != right__238__239__241)){
        return ((((left__236__237__240 < right__238__239__241)) ? (-1) : (1)));
    } else {
    }
    switch (left__236__237__240) {
        case ObjType_ID: {
            left__236__237__388 = left__236__237.u;
            right__238__239__389 = right__238__239.u;
            left__236__237__388__390 = left__236__237__388.id;
            right__238__239__389__391 = right__238__239__389.id;
            left__236__237__388__390__392 = left__236__237__388__390.coreid;
            right__238__239__389__391__393 = right__238__239__389__391.coreid;
            if ((left__236__237__388__390__392 != right__238__239__389__391__393)){
                return ((((left__236__237__388__390__392 < right__238__239__389__391__393)) ? (-1) : (1)));
            } else {
            }
            left__236__237__388__390__394 = left__236__237__388__390.core_local_id;
            right__238__239__389__391__395 = right__238__239__389__391.core_local_id;
            if ((left__236__237__388__390__394 != right__238__239__389__391__395)){
                return ((((left__236__237__388__390__394 < right__238__239__389__391__395)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_Notify_IPI: {
            left__236__237__380 = left__236__237.u;
            right__238__239__381 = right__238__239.u;
            left__236__237__380__382 = left__236__237__380.notify_ipi;
            right__238__239__381__383 = right__238__239__381.notify_ipi;
            left__236__237__380__382__384 = left__236__237__380__382.coreid;
            right__238__239__381__383__385 = right__238__239__381__383.coreid;
            if ((left__236__237__380__382__384 != right__238__239__381__383__385)){
                return ((((left__236__237__380__382__384 < right__238__239__381__383__385)) ? (-1) : (1)));
            } else {
            }
            left__236__237__380__382__386 = left__236__237__380__382.chanid;
            right__238__239__381__383__387 = right__238__239__381__383.chanid;
            if ((left__236__237__380__382__386 != right__238__239__381__383__387)){
                return ((((left__236__237__380__382__386 < right__238__239__381__383__387)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_Notify_RCK: {
            left__236__237__372 = left__236__237.u;
            right__238__239__373 = right__238__239.u;
            left__236__237__372__374 = left__236__237__372.notify_rck;
            right__238__239__373__375 = right__238__239__373.notify_rck;
            left__236__237__372__374__376 = left__236__237__372__374.coreid;
            right__238__239__373__375__377 = right__238__239__373__375.coreid;
            if ((left__236__237__372__374__376 != right__238__239__373__375__377)){
                return ((((left__236__237__372__374__376 < right__238__239__373__375__377)) ? (-1) : (1)));
            } else {
            }
            left__236__237__372__374__378 = left__236__237__372__374.chanid;
            right__238__239__373__375__379 = right__238__239__373__375.chanid;
            if ((left__236__237__372__374__378 != right__238__239__373__375__379)){
                return ((((left__236__237__372__374__378 < right__238__239__373__375__379)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_IO: {
            left__236__237__364 = left__236__237.u;
            right__238__239__365 = right__238__239.u;
            left__236__237__364__366 = left__236__237__364.io;
            right__238__239__365__367 = right__238__239__365.io;
            left__236__237__364__366__368 = left__236__237__364__366.start;
            right__238__239__365__367__369 = right__238__239__365__367.start;
            if ((left__236__237__364__366__368 != right__238__239__365__367__369)){
                return ((((left__236__237__364__366__368 < right__238__239__365__367__369)) ? (-1) : (1)));
            } else {
            }
            left__236__237__364__366__370 = left__236__237__364__366.end;
            right__238__239__365__367__371 = right__238__239__365__367.end;
            if ((left__236__237__364__366__370 != right__238__239__365__367__371)){
                return ((((left__236__237__364__366__370 < right__238__239__365__367__371)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_IRQSrc: {
            left__236__237__356 = left__236__237.u;
            right__238__239__357 = right__238__239.u;
            left__236__237__356__358 = left__236__237__356.irqsrc;
            right__238__239__357__359 = right__238__239__357.irqsrc;
            left__236__237__356__358__360 = left__236__237__356__358.vector;
            right__238__239__357__359__361 = right__238__239__357__359.vector;
            if ((left__236__237__356__358__360 != right__238__239__357__359__361)){
                return ((((left__236__237__356__358__360 < right__238__239__357__359__361)) ? (-1) : (1)));
            } else {
            }
            left__236__237__356__358__362 = left__236__237__356__358.controller;
            right__238__239__357__359__363 = right__238__239__357__359.controller;
            if ((left__236__237__356__358__362 != right__238__239__357__359__363)){
                return ((((left__236__237__356__358__362 < right__238__239__357__359__363)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_IRQDest: {
            left__236__237__348 = left__236__237.u;
            right__238__239__349 = right__238__239.u;
            left__236__237__348__350 = left__236__237__348.irqdest;
            right__238__239__349__351 = right__238__239__349.irqdest;
            left__236__237__348__350__352 = left__236__237__348__350.cpu;
            right__238__239__349__351__353 = right__238__239__349__351.cpu;
            if ((left__236__237__348__350__352 != right__238__239__349__351__353)){
                return ((((left__236__237__348__350__352 < right__238__239__349__351__353)) ? (-1) : (1)));
            } else {
            }
            left__236__237__348__350__354 = left__236__237__348__350.vector;
            right__238__239__349__351__355 = right__238__239__349__351.vector;
            if ((left__236__237__348__350__354 != right__238__239__349__351__355)){
                return ((((left__236__237__348__350__354 < right__238__239__349__351__355)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_AARCH64_l3_Mapping: {
            left__236__237__342 = left__236__237.u;
            right__238__239__343 = right__238__239.u;
            left__236__237__342__344 = left__236__237__342.vnode_aarch64_l3_mapping;
            right__238__239__343__345 = right__238__239__343.vnode_aarch64_l3_mapping;
            left__236__237__342__344__346 = left__236__237__342__344.pte;
            right__238__239__343__345__347 = right__238__239__343__345.pte;
            if ((left__236__237__342__344__346 != right__238__239__343__345__347)){
                return ((((left__236__237__342__344__346 < right__238__239__343__345__347)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_AARCH64_l2_Mapping: {
            left__236__237__336 = left__236__237.u;
            right__238__239__337 = right__238__239.u;
            left__236__237__336__338 = left__236__237__336.vnode_aarch64_l2_mapping;
            right__238__239__337__339 = right__238__239__337.vnode_aarch64_l2_mapping;
            left__236__237__336__338__340 = left__236__237__336__338.pte;
            right__238__239__337__339__341 = right__238__239__337__339.pte;
            if ((left__236__237__336__338__340 != right__238__239__337__339__341)){
                return ((((left__236__237__336__338__340 < right__238__239__337__339__341)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_AARCH64_l1_Mapping: {
            left__236__237__330 = left__236__237.u;
            right__238__239__331 = right__238__239.u;
            left__236__237__330__332 = left__236__237__330.vnode_aarch64_l1_mapping;
            right__238__239__331__333 = right__238__239__331.vnode_aarch64_l1_mapping;
            left__236__237__330__332__334 = left__236__237__330__332.pte;
            right__238__239__331__333__335 = right__238__239__331__333.pte;
            if ((left__236__237__330__332__334 != right__238__239__331__333__335)){
                return ((((left__236__237__330__332__334 < right__238__239__331__333__335)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_AARCH64_l0_Mapping: {
            left__236__237__324 = left__236__237.u;
            right__238__239__325 = right__238__239.u;
            left__236__237__324__326 = left__236__237__324.vnode_aarch64_l0_mapping;
            right__238__239__325__327 = right__238__239__325.vnode_aarch64_l0_mapping;
            left__236__237__324__326__328 = left__236__237__324__326.pte;
            right__238__239__325__327__329 = right__238__239__325__327.pte;
            if ((left__236__237__324__326__328 != right__238__239__325__327__329)){
                return ((((left__236__237__324__326__328 < right__238__239__325__327__329)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_ARM_l2_Mapping: {
            left__236__237__318 = left__236__237.u;
            right__238__239__319 = right__238__239.u;
            left__236__237__318__320 = left__236__237__318.vnode_arm_l2_mapping;
            right__238__239__319__321 = right__238__239__319.vnode_arm_l2_mapping;
            left__236__237__318__320__322 = left__236__237__318__320.pte;
            right__238__239__319__321__323 = right__238__239__319__321.pte;
            if ((left__236__237__318__320__322 != right__238__239__319__321__323)){
                return ((((left__236__237__318__320__322 < right__238__239__319__321__323)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_ARM_l1_Mapping: {
            left__236__237__312 = left__236__237.u;
            right__238__239__313 = right__238__239.u;
            left__236__237__312__314 = left__236__237__312.vnode_arm_l1_mapping;
            right__238__239__313__315 = right__238__239__313.vnode_arm_l1_mapping;
            left__236__237__312__314__316 = left__236__237__312__314.pte;
            right__238__239__313__315__317 = right__238__239__313__315.pte;
            if ((left__236__237__312__314__316 != right__238__239__313__315__317)){
                return ((((left__236__237__312__314__316 < right__238__239__313__315__317)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_32_ptable_Mapping: {
            left__236__237__306 = left__236__237.u;
            right__238__239__307 = right__238__239.u;
            left__236__237__306__308 = left__236__237__306.vnode_x86_32_ptable_mapping;
            right__238__239__307__309 = right__238__239__307.vnode_x86_32_ptable_mapping;
            left__236__237__306__308__310 = left__236__237__306__308.pte;
            right__238__239__307__309__311 = right__238__239__307__309.pte;
            if ((left__236__237__306__308__310 != right__238__239__307__309__311)){
                return ((((left__236__237__306__308__310 < right__238__239__307__309__311)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_32_pdir_Mapping: {
            left__236__237__300 = left__236__237.u;
            right__238__239__301 = right__238__239.u;
            left__236__237__300__302 = left__236__237__300.vnode_x86_32_pdir_mapping;
            right__238__239__301__303 = right__238__239__301.vnode_x86_32_pdir_mapping;
            left__236__237__300__302__304 = left__236__237__300__302.pte;
            right__238__239__301__303__305 = right__238__239__301__303.pte;
            if ((left__236__237__300__302__304 != right__238__239__301__303__305)){
                return ((((left__236__237__300__302__304 < right__238__239__301__303__305)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_32_pdpt_Mapping: {
            left__236__237__294 = left__236__237.u;
            right__238__239__295 = right__238__239.u;
            left__236__237__294__296 = left__236__237__294.vnode_x86_32_pdpt_mapping;
            right__238__239__295__297 = right__238__239__295.vnode_x86_32_pdpt_mapping;
            left__236__237__294__296__298 = left__236__237__294__296.pte;
            right__238__239__295__297__299 = right__238__239__295__297.pte;
            if ((left__236__237__294__296__298 != right__238__239__295__297__299)){
                return ((((left__236__237__294__296__298 < right__238__239__295__297__299)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_64_ptable_Mapping: {
            left__236__237__288 = left__236__237.u;
            right__238__239__289 = right__238__239.u;
            left__236__237__288__290 = left__236__237__288.vnode_x86_64_ptable_mapping;
            right__238__239__289__291 = right__238__239__289.vnode_x86_64_ptable_mapping;
            left__236__237__288__290__292 = left__236__237__288__290.pte;
            right__238__239__289__291__293 = right__238__239__289__291.pte;
            if ((left__236__237__288__290__292 != right__238__239__289__291__293)){
                return ((((left__236__237__288__290__292 < right__238__239__289__291__293)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_64_pdir_Mapping: {
            left__236__237__282 = left__236__237.u;
            right__238__239__283 = right__238__239.u;
            left__236__237__282__284 = left__236__237__282.vnode_x86_64_pdir_mapping;
            right__238__239__283__285 = right__238__239__283.vnode_x86_64_pdir_mapping;
            left__236__237__282__284__286 = left__236__237__282__284.pte;
            right__238__239__283__285__287 = right__238__239__283__285.pte;
            if ((left__236__237__282__284__286 != right__238__239__283__285__287)){
                return ((((left__236__237__282__284__286 < right__238__239__283__285__287)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_64_pdpt_Mapping: {
            left__236__237__276 = left__236__237.u;
            right__238__239__277 = right__238__239.u;
            left__236__237__276__278 = left__236__237__276.vnode_x86_64_pdpt_mapping;
            right__238__239__277__279 = right__238__239__277.vnode_x86_64_pdpt_mapping;
            left__236__237__276__278__280 = left__236__237__276__278.pte;
            right__238__239__277__279__281 = right__238__239__277__279.pte;
            if ((left__236__237__276__278__280 != right__238__239__277__279__281)){
                return ((((left__236__237__276__278__280 < right__238__239__277__279__281)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_VNode_x86_64_pml4_Mapping: {
            left__236__237__270 = left__236__237.u;
            right__238__239__271 = right__238__239.u;
            left__236__237__270__272 = left__236__237__270.vnode_x86_64_pml4_mapping;
            right__238__239__271__273 = right__238__239__271.vnode_x86_64_pml4_mapping;
            left__236__237__270__272__274 = left__236__237__270__272.pte;
            right__238__239__271__273__275 = right__238__239__271__273.pte;
            if ((left__236__237__270__272__274 != right__238__239__271__273__275)){
                return ((((left__236__237__270__272__274 < right__238__239__271__273__275)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_DevFrame_Mapping: {
            left__236__237__264 = left__236__237.u;
            right__238__239__265 = right__238__239.u;
            left__236__237__264__266 = left__236__237__264.devframe_mapping;
            right__238__239__265__267 = right__238__239__265.devframe_mapping;
            left__236__237__264__266__268 = left__236__237__264__266.pte;
            right__238__239__265__267__269 = right__238__239__265__267.pte;
            if ((left__236__237__264__266__268 != right__238__239__265__267__269)){
                return ((((left__236__237__264__266__268 < right__238__239__265__267__269)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_Frame_Mapping: {
            left__236__237__258 = left__236__237.u;
            right__238__239__259 = right__238__239.u;
            left__236__237__258__260 = left__236__237__258.frame_mapping;
            right__238__239__259__261 = right__238__239__259.frame_mapping;
            left__236__237__258__260__262 = left__236__237__258__260.pte;
            right__238__239__259__261__263 = right__238__239__259__261.pte;
            if ((left__236__237__258__260__262 != right__238__239__259__261__263)){
                return ((((left__236__237__258__260__262 < right__238__239__259__261__263)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        case ObjType_FCNode: {
            left__236__237__248 = left__236__237.u;
            right__238__239__249 = right__238__239.u;
            left__236__237__248__250 = left__236__237__248.fcnode;
            right__238__239__249__251 = right__238__239__249.fcnode;
            left__236__237__248__250__252 = left__236__237__248__250.cnode;
            right__238__239__249__251__253 = right__238__239__249__251.cnode;
            if ((left__236__237__248__250__252 != right__238__239__249__251__253)){
                return ((((left__236__237__248__250__252 < right__238__239__249__251__253)) ? (-1) : (1)));
            } else {
            }
            left__236__237__248__250__254 = left__236__237__248__250.bits;
            right__238__239__249__251__255 = right__238__239__249__251.bits;
            if ((left__236__237__248__250__254 != right__238__239__249__251__255)){
                return ((((left__236__237__248__250__254 < right__238__239__249__251__255)) ? (-1) : (1)));
            } else {
            }
            left__236__237__248__250__256 = left__236__237__248__250.core_id;
            right__238__239__249__251__257 = right__238__239__249__251.core_id;
            if ((left__236__237__248__250__256 != right__238__239__249__251__257)){
                return ((((left__236__237__248__250__256 < right__238__239__249__251__257)) ? (-1) : (1)));
            } else {
            }
            break;
        }
        default: {
        }
    }
    if (tiebreak){
        if ((left != right)){
            return ((((left < right)) ? (-1) : (1)));
        } else {
        }
    } else {
    }
    return (0);
}
 
genpaddr_t get_address(struct  capability* cap) {
    uint64_t _fof_x102;
    uint64_t _fof_x113;
    uint64_t _fof_x124;
    uint64_t _fof_x135;
    uint64_t _fof_x146;
    uint64_t _fof_x157;
    uint64_t _fof_x168;
    uint64_t _fof_x179;
    uint64_t _fof_x190;
    uint64_t _fof_x201;
    uint64_t _fof_x207;
    uint64_t _fof_x30;
    uint64_t _fof_x36;
    uint64_t _fof_x47;
    uint64_t _fof_x58;
    uint64_t _fof_x69;
    uint64_t _fof_x80;
    uint64_t _fof_x91;
    struct  capability* cap__10;
    struct  capability* cap__103;
    struct  capability cap__103__104;
    union  capability_u cap__103__104__105;
    struct  VNode_x86_32_pdpt cap__103__104__105__106;
    genpaddr_t cap__103__104__105__106__107;
    struct  capability* cap__108;
    struct  capability cap__108__109;
    union  capability_u cap__108__109__110;
    struct  VNode_x86_32_pdpt_Mapping cap__108__109__110__111;
    struct capability* cap__108__109__110__111__112;
    struct  capability cap__10__11;
    union  capability_u cap__10__11__12;
    struct  RAM cap__10__11__12__13;
    genpaddr_t cap__10__11__12__13__14;
    struct  capability* cap__114;
    struct  capability cap__114__115;
    union  capability_u cap__114__115__116;
    struct  VNode_x86_32_pdir cap__114__115__116__117;
    genpaddr_t cap__114__115__116__117__118;
    struct  capability* cap__119;
    struct  capability cap__119__120;
    union  capability_u cap__119__120__121;
    struct  VNode_x86_32_pdir_Mapping cap__119__120__121__122;
    struct capability* cap__119__120__121__122__123;
    struct  capability* cap__125;
    struct  capability cap__125__126;
    union  capability_u cap__125__126__127;
    struct  VNode_x86_32_ptable cap__125__126__127__128;
    genpaddr_t cap__125__126__127__128__129;
    struct  capability* cap__130;
    struct  capability cap__130__131;
    union  capability_u cap__130__131__132;
    struct  VNode_x86_32_ptable_Mapping cap__130__131__132__133;
    struct capability* cap__130__131__132__133__134;
    struct  capability* cap__136;
    struct  capability cap__136__137;
    union  capability_u cap__136__137__138;
    struct  VNode_ARM_l1 cap__136__137__138__139;
    genpaddr_t cap__136__137__138__139__140;
    struct  capability* cap__141;
    struct  capability cap__141__142;
    union  capability_u cap__141__142__143;
    struct  VNode_ARM_l1_Mapping cap__141__142__143__144;
    struct capability* cap__141__142__143__144__145;
    struct  capability* cap__147;
    struct  capability cap__147__148;
    union  capability_u cap__147__148__149;
    struct  VNode_ARM_l2 cap__147__148__149__150;
    genpaddr_t cap__147__148__149__150__151;
    struct  capability* cap__15;
    struct  capability* cap__152;
    struct  capability cap__152__153;
    union  capability_u cap__152__153__154;
    struct  VNode_ARM_l2_Mapping cap__152__153__154__155;
    struct capability* cap__152__153__154__155__156;
    struct  capability* cap__158;
    struct  capability cap__158__159;
    union  capability_u cap__158__159__160;
    struct  VNode_AARCH64_l0 cap__158__159__160__161;
    genpaddr_t cap__158__159__160__161__162;
    struct  capability cap__15__16;
    union  capability_u cap__15__16__17;
    struct  L1CNode cap__15__16__17__18;
    lpaddr_t cap__15__16__17__18__19;
    struct  capability* cap__163;
    struct  capability cap__163__164;
    union  capability_u cap__163__164__165;
    struct  VNode_AARCH64_l0_Mapping cap__163__164__165__166;
    struct capability* cap__163__164__165__166__167;
    struct  capability* cap__169;
    struct  capability cap__169__170;
    union  capability_u cap__169__170__171;
    struct  VNode_AARCH64_l1 cap__169__170__171__172;
    genpaddr_t cap__169__170__171__172__173;
    struct  capability* cap__174;
    struct  capability cap__174__175;
    union  capability_u cap__174__175__176;
    struct  VNode_AARCH64_l1_Mapping cap__174__175__176__177;
    struct capability* cap__174__175__176__177__178;
    struct  capability* cap__180;
    struct  capability cap__180__181;
    union  capability_u cap__180__181__182;
    struct  VNode_AARCH64_l2 cap__180__181__182__183;
    genpaddr_t cap__180__181__182__183__184;
    struct  capability* cap__185;
    struct  capability cap__185__186;
    union  capability_u cap__185__186__187;
    struct  VNode_AARCH64_l2_Mapping cap__185__186__187__188;
    struct capability* cap__185__186__187__188__189;
    struct  capability* cap__191;
    struct  capability cap__191__192;
    union  capability_u cap__191__192__193;
    struct  VNode_AARCH64_l3 cap__191__192__193__194;
    genpaddr_t cap__191__192__193__194__195;
    struct  capability* cap__196;
    struct  capability cap__196__197;
    union  capability_u cap__196__197__198;
    struct  VNode_AARCH64_l3_Mapping cap__196__197__198__199;
    struct capability* cap__196__197__198__199__200;
    struct  capability* cap__2;
    struct  capability* cap__20;
    struct  capability* cap__202;
    struct  capability cap__202__203;
    union  capability_u cap__202__203__204;
    struct  KernelControlBlock cap__202__203__204__205;
    struct kcb* cap__202__203__204__205__206;
    struct  capability cap__20__21;
    union  capability_u cap__20__21__22;
    struct  L2CNode cap__20__21__22__23;
    lpaddr_t cap__20__21__22__23__24;
    struct  capability* cap__25;
    struct  capability cap__25__26;
    union  capability_u cap__25__26__27;
    struct  Dispatcher cap__25__26__27__28;
    struct dcb* cap__25__26__27__28__29;
    struct  capability cap__2__3;
    enum objtype cap__2__3__4;
    struct  capability* cap__31;
    struct  capability cap__31__32;
    union  capability_u cap__31__32__33;
    struct  EndPoint cap__31__32__33__34;
    struct dcb* cap__31__32__33__34__35;
    struct  capability* cap__37;
    struct  capability cap__37__38;
    union  capability_u cap__37__38__39;
    struct  Frame cap__37__38__39__40;
    genpaddr_t cap__37__38__39__40__41;
    struct  capability* cap__42;
    struct  capability cap__42__43;
    union  capability_u cap__42__43__44;
    struct  Frame_Mapping cap__42__43__44__45;
    struct capability* cap__42__43__44__45__46;
    struct  capability* cap__48;
    struct  capability cap__48__49;
    union  capability_u cap__48__49__50;
    struct  DevFrame cap__48__49__50__51;
    genpaddr_t cap__48__49__50__51__52;
    struct  capability* cap__5;
    struct  capability* cap__53;
    struct  capability cap__53__54;
    union  capability_u cap__53__54__55;
    struct  DevFrame_Mapping cap__53__54__55__56;
    struct capability* cap__53__54__55__56__57;
    struct  capability* cap__59;
    struct  capability cap__59__60;
    union  capability_u cap__59__60__61;
    struct  VNode_x86_64_pml4 cap__59__60__61__62;
    genpaddr_t cap__59__60__61__62__63;
    struct  capability cap__5__6;
    union  capability_u cap__5__6__7;
    struct  PhysAddr cap__5__6__7__8;
    genpaddr_t cap__5__6__7__8__9;
    struct  capability* cap__64;
    struct  capability cap__64__65;
    union  capability_u cap__64__65__66;
    struct  VNode_x86_64_pml4_Mapping cap__64__65__66__67;
    struct capability* cap__64__65__66__67__68;
    struct  capability* cap__70;
    struct  capability cap__70__71;
    union  capability_u cap__70__71__72;
    struct  VNode_x86_64_pdpt cap__70__71__72__73;
    genpaddr_t cap__70__71__72__73__74;
    struct  capability* cap__75;
    struct  capability cap__75__76;
    union  capability_u cap__75__76__77;
    struct  VNode_x86_64_pdpt_Mapping cap__75__76__77__78;
    struct capability* cap__75__76__77__78__79;
    struct  capability* cap__81;
    struct  capability cap__81__82;
    union  capability_u cap__81__82__83;
    struct  VNode_x86_64_pdir cap__81__82__83__84;
    genpaddr_t cap__81__82__83__84__85;
    struct  capability* cap__86;
    struct  capability cap__86__87;
    union  capability_u cap__86__87__88;
    struct  VNode_x86_64_pdir_Mapping cap__86__87__88__89;
    struct capability* cap__86__87__88__89__90;
    struct  capability* cap__92;
    struct  capability cap__92__93;
    union  capability_u cap__92__93__94;
    struct  VNode_x86_64_ptable cap__92__93__94__95;
    genpaddr_t cap__92__93__94__95__96;
    struct  capability* cap__97;
    struct  capability cap__97__98;
    union  capability_u cap__97__98__99;
    struct  VNode_x86_64_ptable_Mapping cap__97__98__99__100;
    struct capability* cap__97__98__99__100__101;
 
    cap__2 = cap;
    cap__2__3 = *cap__2;
    cap__2__3__4 = cap__2__3.type;
    switch (cap__2__3__4) {
        case ObjType_IPI: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_KernelControlBlock: {
            cap__202 = cap;
            cap__202__203 = *cap__202;
            cap__202__203__204 = cap__202__203.u;
            cap__202__203__204__205 = cap__202__203__204.kernelcontrolblock;
            cap__202__203__204__205__206 = cap__202__203__204__205.kcb;
            _fof_x207 = mem_to_local_phys(((lvaddr_t) cap__202__203__204__205__206));
            return (_fof_x207);
            break;
        }
        case ObjType_PerfMon: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_ID: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_Notify_IPI: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_Notify_RCK: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_IO: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_IRQSrc: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_IRQDest: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_IRQTable: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_VNode_AARCH64_l3_Mapping: {
            cap__196 = cap;
            cap__196__197 = *cap__196;
            cap__196__197__198 = cap__196__197.u;
            cap__196__197__198__199 = cap__196__197__198.vnode_aarch64_l3_mapping;
            cap__196__197__198__199__200 = cap__196__197__198__199.frame;
            _fof_x201 = get_address(cap__196__197__198__199__200);
            return (_fof_x201);
            break;
        }
        case ObjType_VNode_AARCH64_l3: {
            cap__191 = cap;
            cap__191__192 = *cap__191;
            cap__191__192__193 = cap__191__192.u;
            cap__191__192__193__194 = cap__191__192__193.vnode_aarch64_l3;
            cap__191__192__193__194__195 = cap__191__192__193__194.base;
            return (cap__191__192__193__194__195);
            break;
        }
        case ObjType_VNode_AARCH64_l2_Mapping: {
            cap__185 = cap;
            cap__185__186 = *cap__185;
            cap__185__186__187 = cap__185__186.u;
            cap__185__186__187__188 = cap__185__186__187.vnode_aarch64_l2_mapping;
            cap__185__186__187__188__189 = cap__185__186__187__188.frame;
            _fof_x190 = get_address(cap__185__186__187__188__189);
            return (_fof_x190);
            break;
        }
        case ObjType_VNode_AARCH64_l2: {
            cap__180 = cap;
            cap__180__181 = *cap__180;
            cap__180__181__182 = cap__180__181.u;
            cap__180__181__182__183 = cap__180__181__182.vnode_aarch64_l2;
            cap__180__181__182__183__184 = cap__180__181__182__183.base;
            return (cap__180__181__182__183__184);
            break;
        }
        case ObjType_VNode_AARCH64_l1_Mapping: {
            cap__174 = cap;
            cap__174__175 = *cap__174;
            cap__174__175__176 = cap__174__175.u;
            cap__174__175__176__177 = cap__174__175__176.vnode_aarch64_l1_mapping;
            cap__174__175__176__177__178 = cap__174__175__176__177.frame;
            _fof_x179 = get_address(cap__174__175__176__177__178);
            return (_fof_x179);
            break;
        }
        case ObjType_VNode_AARCH64_l1: {
            cap__169 = cap;
            cap__169__170 = *cap__169;
            cap__169__170__171 = cap__169__170.u;
            cap__169__170__171__172 = cap__169__170__171.vnode_aarch64_l1;
            cap__169__170__171__172__173 = cap__169__170__171__172.base;
            return (cap__169__170__171__172__173);
            break;
        }
        case ObjType_VNode_AARCH64_l0_Mapping: {
            cap__163 = cap;
            cap__163__164 = *cap__163;
            cap__163__164__165 = cap__163__164.u;
            cap__163__164__165__166 = cap__163__164__165.vnode_aarch64_l0_mapping;
            cap__163__164__165__166__167 = cap__163__164__165__166.frame;
            _fof_x168 = get_address(cap__163__164__165__166__167);
            return (_fof_x168);
            break;
        }
        case ObjType_VNode_AARCH64_l0: {
            cap__158 = cap;
            cap__158__159 = *cap__158;
            cap__158__159__160 = cap__158__159.u;
            cap__158__159__160__161 = cap__158__159__160.vnode_aarch64_l0;
            cap__158__159__160__161__162 = cap__158__159__160__161.base;
            return (cap__158__159__160__161__162);
            break;
        }
        case ObjType_VNode_ARM_l2_Mapping: {
            cap__152 = cap;
            cap__152__153 = *cap__152;
            cap__152__153__154 = cap__152__153.u;
            cap__152__153__154__155 = cap__152__153__154.vnode_arm_l2_mapping;
            cap__152__153__154__155__156 = cap__152__153__154__155.frame;
            _fof_x157 = get_address(cap__152__153__154__155__156);
            return (_fof_x157);
            break;
        }
        case ObjType_VNode_ARM_l2: {
            cap__147 = cap;
            cap__147__148 = *cap__147;
            cap__147__148__149 = cap__147__148.u;
            cap__147__148__149__150 = cap__147__148__149.vnode_arm_l2;
            cap__147__148__149__150__151 = cap__147__148__149__150.base;
            return (cap__147__148__149__150__151);
            break;
        }
        case ObjType_VNode_ARM_l1_Mapping: {
            cap__141 = cap;
            cap__141__142 = *cap__141;
            cap__141__142__143 = cap__141__142.u;
            cap__141__142__143__144 = cap__141__142__143.vnode_arm_l1_mapping;
            cap__141__142__143__144__145 = cap__141__142__143__144.frame;
            _fof_x146 = get_address(cap__141__142__143__144__145);
            return (_fof_x146);
            break;
        }
        case ObjType_VNode_ARM_l1: {
            cap__136 = cap;
            cap__136__137 = *cap__136;
            cap__136__137__138 = cap__136__137.u;
            cap__136__137__138__139 = cap__136__137__138.vnode_arm_l1;
            cap__136__137__138__139__140 = cap__136__137__138__139.base;
            return (cap__136__137__138__139__140);
            break;
        }
        case ObjType_VNode_x86_32_ptable_Mapping: {
            cap__130 = cap;
            cap__130__131 = *cap__130;
            cap__130__131__132 = cap__130__131.u;
            cap__130__131__132__133 = cap__130__131__132.vnode_x86_32_ptable_mapping;
            cap__130__131__132__133__134 = cap__130__131__132__133.frame;
            _fof_x135 = get_address(cap__130__131__132__133__134);
            return (_fof_x135);
            break;
        }
        case ObjType_VNode_x86_32_ptable: {
            cap__125 = cap;
            cap__125__126 = *cap__125;
            cap__125__126__127 = cap__125__126.u;
            cap__125__126__127__128 = cap__125__126__127.vnode_x86_32_ptable;
            cap__125__126__127__128__129 = cap__125__126__127__128.base;
            return (cap__125__126__127__128__129);
            break;
        }
        case ObjType_VNode_x86_32_pdir_Mapping: {
            cap__119 = cap;
            cap__119__120 = *cap__119;
            cap__119__120__121 = cap__119__120.u;
            cap__119__120__121__122 = cap__119__120__121.vnode_x86_32_pdir_mapping;
            cap__119__120__121__122__123 = cap__119__120__121__122.frame;
            _fof_x124 = get_address(cap__119__120__121__122__123);
            return (_fof_x124);
            break;
        }
        case ObjType_VNode_x86_32_pdir: {
            cap__114 = cap;
            cap__114__115 = *cap__114;
            cap__114__115__116 = cap__114__115.u;
            cap__114__115__116__117 = cap__114__115__116.vnode_x86_32_pdir;
            cap__114__115__116__117__118 = cap__114__115__116__117.base;
            return (cap__114__115__116__117__118);
            break;
        }
        case ObjType_VNode_x86_32_pdpt_Mapping: {
            cap__108 = cap;
            cap__108__109 = *cap__108;
            cap__108__109__110 = cap__108__109.u;
            cap__108__109__110__111 = cap__108__109__110.vnode_x86_32_pdpt_mapping;
            cap__108__109__110__111__112 = cap__108__109__110__111.frame;
            _fof_x113 = get_address(cap__108__109__110__111__112);
            return (_fof_x113);
            break;
        }
        case ObjType_VNode_x86_32_pdpt: {
            cap__103 = cap;
            cap__103__104 = *cap__103;
            cap__103__104__105 = cap__103__104.u;
            cap__103__104__105__106 = cap__103__104__105.vnode_x86_32_pdpt;
            cap__103__104__105__106__107 = cap__103__104__105__106.base;
            return (cap__103__104__105__106__107);
            break;
        }
        case ObjType_VNode_x86_64_ptable_Mapping: {
            cap__97 = cap;
            cap__97__98 = *cap__97;
            cap__97__98__99 = cap__97__98.u;
            cap__97__98__99__100 = cap__97__98__99.vnode_x86_64_ptable_mapping;
            cap__97__98__99__100__101 = cap__97__98__99__100.frame;
            _fof_x102 = get_address(cap__97__98__99__100__101);
            return (_fof_x102);
            break;
        }
        case ObjType_VNode_x86_64_ptable: {
            cap__92 = cap;
            cap__92__93 = *cap__92;
            cap__92__93__94 = cap__92__93.u;
            cap__92__93__94__95 = cap__92__93__94.vnode_x86_64_ptable;
            cap__92__93__94__95__96 = cap__92__93__94__95.base;
            return (cap__92__93__94__95__96);
            break;
        }
        case ObjType_VNode_x86_64_pdir_Mapping: {
            cap__86 = cap;
            cap__86__87 = *cap__86;
            cap__86__87__88 = cap__86__87.u;
            cap__86__87__88__89 = cap__86__87__88.vnode_x86_64_pdir_mapping;
            cap__86__87__88__89__90 = cap__86__87__88__89.frame;
            _fof_x91 = get_address(cap__86__87__88__89__90);
            return (_fof_x91);
            break;
        }
        case ObjType_VNode_x86_64_pdir: {
            cap__81 = cap;
            cap__81__82 = *cap__81;
            cap__81__82__83 = cap__81__82.u;
            cap__81__82__83__84 = cap__81__82__83.vnode_x86_64_pdir;
            cap__81__82__83__84__85 = cap__81__82__83__84.base;
            return (cap__81__82__83__84__85);
            break;
        }
        case ObjType_VNode_x86_64_pdpt_Mapping: {
            cap__75 = cap;
            cap__75__76 = *cap__75;
            cap__75__76__77 = cap__75__76.u;
            cap__75__76__77__78 = cap__75__76__77.vnode_x86_64_pdpt_mapping;
            cap__75__76__77__78__79 = cap__75__76__77__78.frame;
            _fof_x80 = get_address(cap__75__76__77__78__79);
            return (_fof_x80);
            break;
        }
        case ObjType_VNode_x86_64_pdpt: {
            cap__70 = cap;
            cap__70__71 = *cap__70;
            cap__70__71__72 = cap__70__71.u;
            cap__70__71__72__73 = cap__70__71__72.vnode_x86_64_pdpt;
            cap__70__71__72__73__74 = cap__70__71__72__73.base;
            return (cap__70__71__72__73__74);
            break;
        }
        case ObjType_VNode_x86_64_pml4_Mapping: {
            cap__64 = cap;
            cap__64__65 = *cap__64;
            cap__64__65__66 = cap__64__65.u;
            cap__64__65__66__67 = cap__64__65__66.vnode_x86_64_pml4_mapping;
            cap__64__65__66__67__68 = cap__64__65__66__67.frame;
            _fof_x69 = get_address(cap__64__65__66__67__68);
            return (_fof_x69);
            break;
        }
        case ObjType_VNode_x86_64_pml4: {
            cap__59 = cap;
            cap__59__60 = *cap__59;
            cap__59__60__61 = cap__59__60.u;
            cap__59__60__61__62 = cap__59__60__61.vnode_x86_64_pml4;
            cap__59__60__61__62__63 = cap__59__60__61__62.base;
            return (cap__59__60__61__62__63);
            break;
        }
        case ObjType_Kernel: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_DevFrame_Mapping: {
            cap__53 = cap;
            cap__53__54 = *cap__53;
            cap__53__54__55 = cap__53__54.u;
            cap__53__54__55__56 = cap__53__54__55.devframe_mapping;
            cap__53__54__55__56__57 = cap__53__54__55__56.frame;
            _fof_x58 = get_address(cap__53__54__55__56__57);
            return (_fof_x58);
            break;
        }
        case ObjType_DevFrame: {
            cap__48 = cap;
            cap__48__49 = *cap__48;
            cap__48__49__50 = cap__48__49.u;
            cap__48__49__50__51 = cap__48__49__50.devframe;
            cap__48__49__50__51__52 = cap__48__49__50__51.base;
            return (cap__48__49__50__51__52);
            break;
        }
        case ObjType_Frame_Mapping: {
            cap__42 = cap;
            cap__42__43 = *cap__42;
            cap__42__43__44 = cap__42__43.u;
            cap__42__43__44__45 = cap__42__43__44.frame_mapping;
            cap__42__43__44__45__46 = cap__42__43__44__45.frame;
            _fof_x47 = get_address(cap__42__43__44__45__46);
            return (_fof_x47);
            break;
        }
        case ObjType_Frame: {
            cap__37 = cap;
            cap__37__38 = *cap__37;
            cap__37__38__39 = cap__37__38.u;
            cap__37__38__39__40 = cap__37__38__39.frame;
            cap__37__38__39__40__41 = cap__37__38__39__40.base;
            return (cap__37__38__39__40__41);
            break;
        }
        case ObjType_EndPoint: {
            cap__31 = cap;
            cap__31__32 = *cap__31;
            cap__31__32__33 = cap__31__32.u;
            cap__31__32__33__34 = cap__31__32__33.endpoint;
            cap__31__32__33__34__35 = cap__31__32__33__34.listener;
            _fof_x36 = mem_to_local_phys(((lvaddr_t) cap__31__32__33__34__35));
            return (_fof_x36);
            break;
        }
        case ObjType_Dispatcher: {
            cap__25 = cap;
            cap__25__26 = *cap__25;
            cap__25__26__27 = cap__25__26.u;
            cap__25__26__27__28 = cap__25__26__27.dispatcher;
            cap__25__26__27__28__29 = cap__25__26__27__28.dcb;
            _fof_x30 = mem_to_local_phys(((lvaddr_t) cap__25__26__27__28__29));
            return (_fof_x30);
            break;
        }
        case ObjType_FCNode: {
            return (((genpaddr_t) 0));
            break;
        }
        case ObjType_L2CNode: {
            cap__20 = cap;
            cap__20__21 = *cap__20;
            cap__20__21__22 = cap__20__21.u;
            cap__20__21__22__23 = cap__20__21__22.l2cnode;
            cap__20__21__22__23__24 = cap__20__21__22__23.cnode;
            return (cap__20__21__22__23__24);
            break;
        }
        case ObjType_L1CNode: {
            cap__15 = cap;
            cap__15__16 = *cap__15;
            cap__15__16__17 = cap__15__16.u;
            cap__15__16__17__18 = cap__15__16__17.l1cnode;
            cap__15__16__17__18__19 = cap__15__16__17__18.cnode;
            return (cap__15__16__17__18__19);
            break;
        }
        case ObjType_RAM: {
            cap__10 = cap;
            cap__10__11 = *cap__10;
            cap__10__11__12 = cap__10__11.u;
            cap__10__11__12__13 = cap__10__11__12.ram;
            cap__10__11__12__13__14 = cap__10__11__12__13.base;
            return (cap__10__11__12__13__14);
            break;
        }
        case ObjType_PhysAddr: {
            cap__5 = cap;
            cap__5__6 = *cap__5;
            cap__5__6__7 = cap__5__6.u;
            cap__5__6__7__8 = cap__5__6__7.physaddr;
            cap__5__6__7__8__9 = cap__5__6__7__8.base;
            return (cap__5__6__7__8__9);
            break;
        }
        case ObjType_Null: {
            return (((genpaddr_t) 0));
            break;
        }
        default: {
            assert(0);
            return (0);
        }
    }
}
 
gensize_t get_size(struct  capability* cap) {
    struct  capability* cap__208;
    struct  capability cap__208__209;
    enum objtype cap__208__209__210;
    struct  capability* cap__211;
    struct  capability cap__211__212;
    union  capability_u cap__211__212__213;
    struct  PhysAddr cap__211__212__213__214;
    gensize_t cap__211__212__213__214__215;
    struct  capability* cap__216;
    struct  capability cap__216__217;
    union  capability_u cap__216__217__218;
    struct  RAM cap__216__217__218__219;
    gensize_t cap__216__217__218__219__220;
    struct  capability* cap__221;
    struct  capability cap__221__222;
    union  capability_u cap__221__222__223;
    struct  L1CNode cap__221__222__223__224;
    gensize_t cap__221__222__223__224__225;
    struct  capability* cap__226;
    struct  capability cap__226__227;
    union  capability_u cap__226__227__228;
    struct  Frame cap__226__227__228__229;
    gensize_t cap__226__227__228__229__230;
    struct  capability* cap__231;
    struct  capability cap__231__232;
    union  capability_u cap__231__232__233;
    struct  DevFrame cap__231__232__233__234;
    gensize_t cap__231__232__233__234__235;
 
    cap__208 = cap;
    cap__208__209 = *cap__208;
    cap__208__209__210 = cap__208__209.type;
    switch (cap__208__209__210) {
        case ObjType_IPI: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_KernelControlBlock: {
            return ((((gensize_t) 1) << 16));
            break;
        }
        case ObjType_PerfMon: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_ID: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_Notify_IPI: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_Notify_RCK: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_IO: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_IRQSrc: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_IRQDest: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_IRQTable: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_VNode_AARCH64_l3_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_AARCH64_l3: {
            return (4096);
            break;
        }
        case ObjType_VNode_AARCH64_l2_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_AARCH64_l2: {
            return (4096);
            break;
        }
        case ObjType_VNode_AARCH64_l1_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_AARCH64_l1: {
            return (4096);
            break;
        }
        case ObjType_VNode_AARCH64_l0_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_AARCH64_l0: {
            return (4096);
            break;
        }
        case ObjType_VNode_ARM_l2_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_ARM_l2: {
            return (1024);
            break;
        }
        case ObjType_VNode_ARM_l1_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_ARM_l1: {
            return (16384);
            break;
        }
        case ObjType_VNode_x86_32_ptable_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_32_ptable: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_32_pdir_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_32_pdir: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_32_pdpt_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_32_pdpt: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_64_ptable_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_64_ptable: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_64_pdir_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_64_pdir: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_64_pdpt_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_64_pdpt: {
            return (4096);
            break;
        }
        case ObjType_VNode_x86_64_pml4_Mapping: {
            return (0);
            break;
        }
        case ObjType_VNode_x86_64_pml4: {
            return (4096);
            break;
        }
        case ObjType_Kernel: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_DevFrame_Mapping: {
            return (0);
            break;
        }
        case ObjType_DevFrame: {
            cap__231 = cap;
            cap__231__232 = *cap__231;
            cap__231__232__233 = cap__231__232.u;
            cap__231__232__233__234 = cap__231__232__233.devframe;
            cap__231__232__233__234__235 = cap__231__232__233__234.bytes;
            return (cap__231__232__233__234__235);
            break;
        }
        case ObjType_Frame_Mapping: {
            return (0);
            break;
        }
        case ObjType_Frame: {
            cap__226 = cap;
            cap__226__227 = *cap__226;
            cap__226__227__228 = cap__226__227.u;
            cap__226__227__228__229 = cap__226__227__228.frame;
            cap__226__227__228__229__230 = cap__226__227__228__229.bytes;
            return (cap__226__227__228__229__230);
            break;
        }
        case ObjType_EndPoint: {
            return (0);
            break;
        }
        case ObjType_Dispatcher: {
            return ((((gensize_t) 1) << 10));
            break;
        }
        case ObjType_FCNode: {
            return (((gensize_t) 0));
            break;
        }
        case ObjType_L2CNode: {
            return (16384);
            break;
        }
        case ObjType_L1CNode: {
            cap__221 = cap;
            cap__221__222 = *cap__221;
            cap__221__222__223 = cap__221__222.u;
            cap__221__222__223__224 = cap__221__222__223.l1cnode;
            cap__221__222__223__224__225 = cap__221__222__223__224.allocated_bytes;
            return (cap__221__222__223__224__225);
            break;
        }
        case ObjType_RAM: {
            cap__216 = cap;
            cap__216__217 = *cap__216;
            cap__216__217__218 = cap__216__217.u;
            cap__216__217__218__219 = cap__216__217__218.ram;
            cap__216__217__218__219__220 = cap__216__217__218__219.bytes;
            return (cap__216__217__218__219__220);
            break;
        }
        case ObjType_PhysAddr: {
            cap__211 = cap;
            cap__211__212 = *cap__211;
            cap__211__212__213 = cap__211__212.u;
            cap__211__212__213__214 = cap__211__212__213.physaddr;
            cap__211__212__213__214__215 = cap__211__212__213__214.bytes;
            return (cap__211__212__213__214__215);
            break;
        }
        case ObjType_Null: {
            return (((gensize_t) 0));
            break;
        }
        default: {
            assert(0);
            return (0);
        }
    }
}
 
uint8_t get_type_root(enum objtype type) {
 
    switch (type) {
        case ObjType_IPI: {
            return (12);
            break;
        }
        case ObjType_KernelControlBlock: {
            return (1);
            break;
        }
        case ObjType_PerfMon: {
            return (11);
            break;
        }
        case ObjType_ID: {
            return (10);
            break;
        }
        case ObjType_Notify_IPI: {
            return (9);
            break;
        }
        case ObjType_Notify_RCK: {
            return (8);
            break;
        }
        case ObjType_IO: {
            return (7);
            break;
        }
        case ObjType_IRQSrc: {
            return (6);
            break;
        }
        case ObjType_IRQDest: {
            return (5);
            break;
        }
        case ObjType_IRQTable: {
            return (4);
            break;
        }
        case ObjType_VNode_AARCH64_l3_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l3: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l2_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l2: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l1_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l1: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l0_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_AARCH64_l0: {
            return (1);
            break;
        }
        case ObjType_VNode_ARM_l2_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_ARM_l2: {
            return (1);
            break;
        }
        case ObjType_VNode_ARM_l1_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_ARM_l1: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_ptable_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_ptable: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_pdir_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_pdir: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_pdpt_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_32_pdpt: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_ptable_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_ptable: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pdir_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pdir: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pdpt_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pdpt: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pml4_Mapping: {
            return (1);
            break;
        }
        case ObjType_VNode_x86_64_pml4: {
            return (1);
            break;
        }
        case ObjType_Kernel: {
            return (3);
            break;
        }
        case ObjType_DevFrame_Mapping: {
            return (1);
            break;
        }
        case ObjType_DevFrame: {
            return (1);
            break;
        }
        case ObjType_Frame_Mapping: {
            return (1);
            break;
        }
        case ObjType_Frame: {
            return (1);
            break;
        }
        case ObjType_EndPoint: {
            return (1);
            break;
        }
        case ObjType_Dispatcher: {
            return (1);
            break;
        }
        case ObjType_FCNode: {
            return (2);
            break;
        }
        case ObjType_L2CNode: {
            return (1);
            break;
        }
        case ObjType_L1CNode: {
            return (1);
            break;
        }
        case ObjType_RAM: {
            return (1);
            break;
        }
        case ObjType_PhysAddr: {
            return (1);
            break;
        }
        case ObjType_Null: {
            return (0);
            break;
        }
        default: {
            assert(0);
            return (0);
        }
    }
}
 
bool is_ancestor(struct  capability* child,struct  capability* parent) {
    bool _fof_x409;
    genpaddr_t _fof_x410;
    genpaddr_t _fof_x411;
    gensize_t _fof_x412;
    gensize_t _fof_x413;
    struct  capability* child__403;
    struct  capability child__403__404;
    enum objtype child__403__404__407;
    struct  capability* parent__405;
    struct  capability parent__405__406;
    enum objtype parent__405__406__408;
 
    child__403 = child;
    child__403__404 = *child__403;
    parent__405 = parent;
    parent__405__406 = *parent__405;
    child__403__404__407 = child__403__404.type;
    parent__405__406__408 = parent__405__406.type;
    _fof_x409 = is_well_founded(parent__405__406__408,child__403__404__407);
    if ((! _fof_x409)){
        return (0);
    } else {
    }
    _fof_x410 = get_address(parent);
    _fof_x411 = get_address(child);
    _fof_x412 = get_size(parent);
    _fof_x413 = get_size(child);
    if ((child__403__404__407 == parent__405__406__408)){
        return ((((_fof_x410 < _fof_x411) & ((_fof_x410 + _fof_x412) >= (_fof_x411 + _fof_x413))) | ((_fof_x410 <= _fof_x411) & ((_fof_x410 + _fof_x412) > (_fof_x411 + _fof_x413)))));
    } else {
        return (((_fof_x410 <= _fof_x411) & ((_fof_x410 + _fof_x412) >= (_fof_x411 + _fof_x413))));
    }
}
 
bool is_copy(struct  capability* left,struct  capability* right) {
    int8_t _fof_x402;
    struct  capability* left__396;
    struct  capability left__396__397;
    enum objtype left__396__397__400;
    struct  capability* right__398;
    struct  capability right__398__399;
    enum objtype right__398__399__401;
 
    left__396 = left;
    left__396__397 = *left__396;
    right__398 = right;
    right__398__399 = *right__398;
    left__396__397__400 = left__396__397.type;
    right__398__399__401 = right__398__399.type;
    if ((left__396__397__400 != right__398__399__401)){
        return (0);
    } else {
    }
    switch (left__396__397__400) {
        case ObjType_IPI: {
            return (1);
            break;
        }
        case ObjType_PerfMon: {
            return (1);
            break;
        }
        case ObjType_IRQTable: {
            return (1);
            break;
        }
        case ObjType_Kernel: {
            return (1);
            break;
        }
        case ObjType_Null: {
            return (0);
            break;
        }
        default: {
        }
    }
    _fof_x402 = compare_caps(left,right,0);
    return ((_fof_x402 == 0));
}
 
bool is_equal_type(enum objtype left_type,enum objtype right_type) {
 
    return ((left_type == right_type));
}
 
bool is_well_founded(enum objtype src_type,enum objtype dest_type) {
 
    switch (dest_type) {
        case ObjType_KernelControlBlock: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l3_Mapping: {
            return (((src_type == ObjType_VNode_AARCH64_l3) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l3: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l2_Mapping: {
            return (((src_type == ObjType_VNode_AARCH64_l2) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l2: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l1_Mapping: {
            return (((src_type == ObjType_VNode_AARCH64_l1) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l1: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l0_Mapping: {
            return (((src_type == ObjType_VNode_AARCH64_l0) | 0));
            break;
        }
        case ObjType_VNode_AARCH64_l0: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_ARM_l2_Mapping: {
            return (((src_type == ObjType_VNode_ARM_l2) | 0));
            break;
        }
        case ObjType_VNode_ARM_l2: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_ARM_l1_Mapping: {
            return (((src_type == ObjType_VNode_ARM_l1) | 0));
            break;
        }
        case ObjType_VNode_ARM_l1: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_32_ptable_Mapping: {
            return (((src_type == ObjType_VNode_x86_32_ptable) | 0));
            break;
        }
        case ObjType_VNode_x86_32_ptable: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_32_pdir_Mapping: {
            return (((src_type == ObjType_VNode_x86_32_pdir) | 0));
            break;
        }
        case ObjType_VNode_x86_32_pdir: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_32_pdpt_Mapping: {
            return (((src_type == ObjType_VNode_x86_32_pdpt) | 0));
            break;
        }
        case ObjType_VNode_x86_32_pdpt: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_64_ptable_Mapping: {
            return (((src_type == ObjType_VNode_x86_64_ptable) | 0));
            break;
        }
        case ObjType_VNode_x86_64_ptable: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pdir_Mapping: {
            return (((src_type == ObjType_VNode_x86_64_pdir) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pdir: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pdpt_Mapping: {
            return (((src_type == ObjType_VNode_x86_64_pdpt) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pdpt: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pml4_Mapping: {
            return (((src_type == ObjType_VNode_x86_64_pml4) | 0));
            break;
        }
        case ObjType_VNode_x86_64_pml4: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_DevFrame_Mapping: {
            return (((src_type == ObjType_DevFrame) | 0));
            break;
        }
        case ObjType_DevFrame: {
            return (((src_type == ObjType_PhysAddr) | (src_type == ObjType_DevFrame)));
            break;
        }
        case ObjType_Frame_Mapping: {
            return (((src_type == ObjType_Frame) | 0));
            break;
        }
        case ObjType_Frame: {
            return (((src_type == ObjType_RAM) | (src_type == ObjType_Frame)));
            break;
        }
        case ObjType_EndPoint: {
            return (((src_type == ObjType_Dispatcher) | 0));
            break;
        }
        case ObjType_Dispatcher: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_L2CNode: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_L1CNode: {
            return (((src_type == ObjType_RAM) | 0));
            break;
        }
        case ObjType_RAM: {
            return (((src_type == ObjType_PhysAddr) | (src_type == ObjType_RAM)));
            break;
        }
        case ObjType_PhysAddr: {
            return ((0 | (src_type == ObjType_PhysAddr)));
            break;
        }
        default: {
            return (0);
        }
    }
}
 
 
 
