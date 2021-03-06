#ifndef __cpuid_arm_DEV_H
#define __cpuid_arm_DEV_H 1
/*
 * DEVICE DEFINITION: ARMv7+ CPUID fields
 * 
 * Copyright (c) 2010, ETH Zurich.
 * All rights reserved.
 * 
 * This file is distributed under the terms in the attached LICENSE
 * file. If you do not find this file, copies can be found by
 * writing to:
 * ETH Zurich D-INFK, Universitaetstr. 6, CH-8092 Zurich.
 * Attn: Systems Group.
 * 
 * THIS FILE IS AUTOMATICALLY GENERATED BY MACKEREL: DO NOT EDIT!
 */
#include <mackerel/mackerel.h>
#include <inttypes.h>
#undef __DN
#define __DN(x) cpuid_arm ## _ ## x
/*
 * Constants defn: cpuid_arm.ftr_supp (Feature support)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_ftr_supp_t;
#define cpuid_arm_ftr_ni ((cpuid_arm_ftr_supp_t)0x0)
#define cpuid_arm_ftr_i ((cpuid_arm_ftr_supp_t)0x1)

static inline char *cpuid_arm_ftr_supp_describe(cpuid_arm_ftr_supp_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_ftr_supp_describe(cpuid_arm_ftr_supp_t _e)
{
    switch (_e) {
    case cpuid_arm_ftr_ni:
        return("ftr_ni: Not implemented");
    case cpuid_arm_ftr_i:
        return("ftr_i: Implemented");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_ftr_supp_prtval(char *_s, size_t _size, cpuid_arm_ftr_supp_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_ftr_supp_prtval(char *_s, size_t _size, cpuid_arm_ftr_supp_t _e)
{
    char *d = cpuid_arm_ftr_supp_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_ftr_supp_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.jaz_supp (Jazelle extension support)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_jaz_supp_t;
#define cpuid_arm_jaz_ni ((cpuid_arm_jaz_supp_t)0x0)
#define cpuid_arm_jaz_it ((cpuid_arm_jaz_supp_t)0x1)
#define cpuid_arm_jaz_i ((cpuid_arm_jaz_supp_t)0x2)

static inline char *cpuid_arm_jaz_supp_describe(cpuid_arm_jaz_supp_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_jaz_supp_describe(cpuid_arm_jaz_supp_t _e)
{
    switch (_e) {
    case cpuid_arm_jaz_ni:
        return("jaz_ni: Not implemented");
    case cpuid_arm_jaz_it:
        return("jaz_it: Implemented, trivial");
    case cpuid_arm_jaz_i:
        return("jaz_i: Implemented, full");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_jaz_supp_prtval(char *_s, size_t _size, cpuid_arm_jaz_supp_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_jaz_supp_prtval(char *_s, size_t _size, cpuid_arm_jaz_supp_t _e)
{
    char *d = cpuid_arm_jaz_supp_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_jaz_supp_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.thm_supp (ThumbEE instruction set support)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_thm_supp_t;
#define cpuid_arm_thm_ni ((cpuid_arm_thm_supp_t)0x0)
#define cpuid_arm_thm_i1 ((cpuid_arm_thm_supp_t)0x1)
#define cpuid_arm_thm_i2 ((cpuid_arm_thm_supp_t)0x3)

static inline char *cpuid_arm_thm_supp_describe(cpuid_arm_thm_supp_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_thm_supp_describe(cpuid_arm_thm_supp_t _e)
{
    switch (_e) {
    case cpuid_arm_thm_ni:
        return("thm_ni: Not implemented");
    case cpuid_arm_thm_i1:
        return("thm_i1: Thumb 1");
    case cpuid_arm_thm_i2:
        return("thm_i2: Thumb 2");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_thm_supp_prtval(char *_s, size_t _size, cpuid_arm_thm_supp_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_thm_supp_prtval(char *_s, size_t _size, cpuid_arm_thm_supp_t _e)
{
    char *d = cpuid_arm_thm_supp_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_thm_supp_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.mpr_supp (M profile)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_mpr_supp_t;
#define cpuid_arm_mpr_ni ((cpuid_arm_mpr_supp_t)0x0)
#define cpuid_arm_mpr_i ((cpuid_arm_mpr_supp_t)0x2)

static inline char *cpuid_arm_mpr_supp_describe(cpuid_arm_mpr_supp_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_mpr_supp_describe(cpuid_arm_mpr_supp_t _e)
{
    switch (_e) {
    case cpuid_arm_mpr_ni:
        return("mpr_ni: Not supported");
    case cpuid_arm_mpr_i:
        return("mpr_i: Supported");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_mpr_supp_prtval(char *_s, size_t _size, cpuid_arm_mpr_supp_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_mpr_supp_prtval(char *_s, size_t _size, cpuid_arm_mpr_supp_t _e)
{
    char *d = cpuid_arm_mpr_supp_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_mpr_supp_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.sec_supp (M profile)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_sec_supp_t;
#define cpuid_arm_sec_ni ((cpuid_arm_sec_supp_t)0x0)
#define cpuid_arm_sec_i ((cpuid_arm_sec_supp_t)0x1)
#define cpuid_arm_sec_ir ((cpuid_arm_sec_supp_t)0x2)

static inline char *cpuid_arm_sec_supp_describe(cpuid_arm_sec_supp_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_sec_supp_describe(cpuid_arm_sec_supp_t _e)
{
    switch (_e) {
    case cpuid_arm_sec_ni:
        return("sec_ni: Not implemented");
    case cpuid_arm_sec_i:
        return("sec_i: Implemented");
    case cpuid_arm_sec_ir:
        return("sec_ir: Implemented, with NSACR.RFR");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_sec_supp_prtval(char *_s, size_t _size, cpuid_arm_sec_supp_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_sec_supp_prtval(char *_s, size_t _size, cpuid_arm_sec_supp_t _e)
{
    char *d = cpuid_arm_sec_supp_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_sec_supp_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.midr_impl (Implementer code)
 *  - no width specified
 */
typedef uint8_t cpuid_arm_midr_impl_t;
#define cpuid_arm_impl_arm ((cpuid_arm_midr_impl_t)0x41)
#define cpuid_arm_impl_dec ((cpuid_arm_midr_impl_t)0x44)
#define cpuid_arm_impl_motorola ((cpuid_arm_midr_impl_t)0x4d)
#define cpuid_arm_impl_qualcomm ((cpuid_arm_midr_impl_t)0x51)
#define cpuid_arm_impl_marvell ((cpuid_arm_midr_impl_t)0x56)
#define cpuid_arm_impl_intel ((cpuid_arm_midr_impl_t)0x69)

static inline char *cpuid_arm_midr_impl_describe(cpuid_arm_midr_impl_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_midr_impl_describe(cpuid_arm_midr_impl_t _e)
{
    switch (_e) {
    case cpuid_arm_impl_arm:
        return("impl_arm: ARM");
    case cpuid_arm_impl_dec:
        return("impl_dec: DEC");
    case cpuid_arm_impl_motorola:
        return("impl_motorola: Motorola/Freescale");
    case cpuid_arm_impl_qualcomm:
        return("impl_qualcomm: Qualcomm");
    case cpuid_arm_impl_marvell:
        return("impl_marvell: Marvell");
    case cpuid_arm_impl_intel:
        return("impl_intel: Intel");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_midr_impl_prtval(char *_s, size_t _size, cpuid_arm_midr_impl_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_midr_impl_prtval(char *_s, size_t _size, cpuid_arm_midr_impl_t _e)
{
    char *d = cpuid_arm_midr_impl_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_midr_impl_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: cpuid_arm.arm_part (ARM part number)
 *  - no width specified
 */
typedef uint16_t cpuid_arm_arm_part_t;
#define cpuid_arm_part_a5 ((cpuid_arm_arm_part_t)0xc05)
#define cpuid_arm_part_a7 ((cpuid_arm_arm_part_t)0xc07)
#define cpuid_arm_part_a8 ((cpuid_arm_arm_part_t)0xc08)
#define cpuid_arm_part_a9 ((cpuid_arm_arm_part_t)0xc09)
#define cpuid_arm_part_a15 ((cpuid_arm_arm_part_t)0xc0f)
#define cpuid_arm_part_a17 ((cpuid_arm_arm_part_t)0xc0e)
#define cpuid_arm_part_a53 ((cpuid_arm_arm_part_t)0xd03)
#define cpuid_arm_part_a57 ((cpuid_arm_arm_part_t)0xd07)
#define cpuid_arm_part_a72 ((cpuid_arm_arm_part_t)0xd08)
#define cpuid_arm_part_a73 ((cpuid_arm_arm_part_t)0xd09)

static inline char *cpuid_arm_arm_part_describe(cpuid_arm_arm_part_t _e) __attribute__ ((always_inline));
static inline char *cpuid_arm_arm_part_describe(cpuid_arm_arm_part_t _e)
{
    switch (_e) {
    case cpuid_arm_part_a5:
        return("part_a5: Cortex-A5");
    case cpuid_arm_part_a7:
        return("part_a7: Cortex-A7");
    case cpuid_arm_part_a8:
        return("part_a8: Cortex-A8");
    case cpuid_arm_part_a9:
        return("part_a9: Cortex-A9");
    case cpuid_arm_part_a15:
        return("part_a15: Cortex-A15");
    case cpuid_arm_part_a17:
        return("part_a17: Cortex-A17");
    case cpuid_arm_part_a53:
        return("part_a53: Cortex-A53");
    case cpuid_arm_part_a57:
        return("part_a57: Cortex-A57");
    case cpuid_arm_part_a72:
        return("part_a72: Cortex-A72");
    case cpuid_arm_part_a73:
        return("part_a73: Cortex-A73");
    default:
        return(NULL);
    }
}

static inline int cpuid_arm_arm_part_prtval(char *_s, size_t _size, cpuid_arm_arm_part_t _e) __attribute__ ((always_inline));
static inline int cpuid_arm_arm_part_prtval(char *_s, size_t _size, cpuid_arm_arm_part_t _e)
{
    char *d = cpuid_arm_arm_part_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "cpuid_arm_arm_part_t", (uint64_t )(_e)));
    }
}

/*
 * Data type: cpuid_arm_id_pfr0_t
 * Description: Processor Feature Register 0
 * Fields:
 *   state0	(size 4, offset 0, init 0):	RW	ARM instruction set support
 *   state1	(size 4, offset 4, init 0):	RW	Thumb instruction set support
 *   state2	(size 4, offset 8, init 0):	RW	Jazelle extension support
 *   state3	(size 4, offset 12, init 0):	RW	ThumbEE instruction set support
 *   _anon16	(size 16, offset 16, init 0):	RSVD	_
 */
typedef uint8_t *cpuid_arm_id_pfr0_t;
typedef uint8_t cpuid_arm_id_pfr0_array_t[4];
static const size_t cpuid_arm_id_pfr0_size = sizeof(cpuid_arm_id_pfr0_array_t );
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr0_state0_extract(cpuid_arm_id_pfr0_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr0_state0_extract(cpuid_arm_id_pfr0_t _dtptr)
{
    return(((*((uint8_t *)(0 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_id_pfr0_state0_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_ftr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr0_state0_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_ftr_supp_t _fieldval)
{
    *((uint8_t *)(0 + _dtptr)) = (((*((uint8_t *)(0 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline cpuid_arm_thm_supp_t cpuid_arm_id_pfr0_state1_extract(cpuid_arm_id_pfr0_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_thm_supp_t cpuid_arm_id_pfr0_state1_extract(cpuid_arm_id_pfr0_t _dtptr)
{
    return(((*((uint8_t *)(0 + _dtptr))) & 0xf0) >> 4);
}

static inline void cpuid_arm_id_pfr0_state1_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_thm_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr0_state1_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_thm_supp_t _fieldval)
{
    *((uint8_t *)(0 + _dtptr)) = (((*((uint8_t *)(0 + _dtptr))) & 0xf) | (0xf0 & (_fieldval << 4)));
}

static inline cpuid_arm_jaz_supp_t cpuid_arm_id_pfr0_state2_extract(cpuid_arm_id_pfr0_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_jaz_supp_t cpuid_arm_id_pfr0_state2_extract(cpuid_arm_id_pfr0_t _dtptr)
{
    return(((*((uint8_t *)(1 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_id_pfr0_state2_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_jaz_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr0_state2_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_jaz_supp_t _fieldval)
{
    *((uint8_t *)(1 + _dtptr)) = (((*((uint8_t *)(1 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr0_state3_extract(cpuid_arm_id_pfr0_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr0_state3_extract(cpuid_arm_id_pfr0_t _dtptr)
{
    return(((*((uint8_t *)(1 + _dtptr))) & 0xf0) >> 4);
}

static inline void cpuid_arm_id_pfr0_state3_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_ftr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr0_state3_insert(cpuid_arm_id_pfr0_t _dtptr, cpuid_arm_ftr_supp_t _fieldval)
{
    *((uint8_t *)(1 + _dtptr)) = (((*((uint8_t *)(1 + _dtptr))) & 0xf) | (0xf0 & (_fieldval << 4)));
}

static inline int cpuid_arm_id_pfr0_prtval(char *_s, size_t _size, cpuid_arm_id_pfr0_t _regval) __attribute__ ((always_inline));
static inline int cpuid_arm_id_pfr0_prtval(char *_s, size_t _size, cpuid_arm_id_pfr0_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " state0 =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_ftr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr0_state0_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(ARM instruction set support)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " state1 =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_thm_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr0_state1_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Thumb instruction set support)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " state2 =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_jaz_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr0_state2_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Jazelle extension support)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " state3 =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_ftr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr0_state3_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(ThumbEE instruction set support)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Data type: cpuid_arm_id_pfr1_t
 * Description: Processor Feature Register 1
 * Fields:
 *   prog_model	(size 4, offset 0, init 0):	RW	Programmers' model
 *   security	(size 4, offset 4, init 0):	RW	Security extensions
 *   m_profile	(size 4, offset 8, init 0):	RW	M profile
 *   virtualisation	(size 4, offset 12, init 0):	RW	Virtualisation extensions
 *   generic_timer	(size 4, offset 16, init 0):	RW	Generic timer extension
 *   _anon20	(size 12, offset 20, init 0):	RSVD	_
 */
typedef uint8_t *cpuid_arm_id_pfr1_t;
typedef uint8_t cpuid_arm_id_pfr1_array_t[4];
static const size_t cpuid_arm_id_pfr1_size = sizeof(cpuid_arm_id_pfr1_array_t );
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_prog_model_extract(cpuid_arm_id_pfr1_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_prog_model_extract(cpuid_arm_id_pfr1_t _dtptr)
{
    return(((*((uint8_t *)(0 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_id_pfr1_prog_model_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr1_prog_model_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval)
{
    *((uint8_t *)(0 + _dtptr)) = (((*((uint8_t *)(0 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline cpuid_arm_sec_supp_t cpuid_arm_id_pfr1_security_extract(cpuid_arm_id_pfr1_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_sec_supp_t cpuid_arm_id_pfr1_security_extract(cpuid_arm_id_pfr1_t _dtptr)
{
    return(((*((uint8_t *)(0 + _dtptr))) & 0xf0) >> 4);
}

static inline void cpuid_arm_id_pfr1_security_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_sec_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr1_security_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_sec_supp_t _fieldval)
{
    *((uint8_t *)(0 + _dtptr)) = (((*((uint8_t *)(0 + _dtptr))) & 0xf) | (0xf0 & (_fieldval << 4)));
}

static inline cpuid_arm_mpr_supp_t cpuid_arm_id_pfr1_m_profile_extract(cpuid_arm_id_pfr1_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_mpr_supp_t cpuid_arm_id_pfr1_m_profile_extract(cpuid_arm_id_pfr1_t _dtptr)
{
    return(((*((uint8_t *)(1 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_id_pfr1_m_profile_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_mpr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr1_m_profile_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_mpr_supp_t _fieldval)
{
    *((uint8_t *)(1 + _dtptr)) = (((*((uint8_t *)(1 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_virtualisation_extract(cpuid_arm_id_pfr1_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_virtualisation_extract(cpuid_arm_id_pfr1_t _dtptr)
{
    return(((*((uint8_t *)(1 + _dtptr))) & 0xf0) >> 4);
}

static inline void cpuid_arm_id_pfr1_virtualisation_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr1_virtualisation_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval)
{
    *((uint8_t *)(1 + _dtptr)) = (((*((uint8_t *)(1 + _dtptr))) & 0xf) | (0xf0 & (_fieldval << 4)));
}

static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_generic_timer_extract(cpuid_arm_id_pfr1_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_ftr_supp_t cpuid_arm_id_pfr1_generic_timer_extract(cpuid_arm_id_pfr1_t _dtptr)
{
    return(((*((uint8_t *)(2 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_id_pfr1_generic_timer_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_id_pfr1_generic_timer_insert(cpuid_arm_id_pfr1_t _dtptr, cpuid_arm_ftr_supp_t _fieldval)
{
    *((uint8_t *)(2 + _dtptr)) = (((*((uint8_t *)(2 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline int cpuid_arm_id_pfr1_prtval(char *_s, size_t _size, cpuid_arm_id_pfr1_t _regval) __attribute__ ((always_inline));
static inline int cpuid_arm_id_pfr1_prtval(char *_s, size_t _size, cpuid_arm_id_pfr1_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " prog_model =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_ftr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr1_prog_model_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Programmers' model)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " security =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_sec_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr1_security_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Security extensions)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " m_profile =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_mpr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr1_m_profile_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(M profile)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " virtualisation =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_ftr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr1_virtualisation_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Virtualisation extensions)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " generic_timer =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_ftr_supp_prtval(_s + _r, _avail, cpuid_arm_id_pfr1_generic_timer_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Generic timer extension)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Data type: cpuid_arm_midr_t
 * Description: Main ID Register
 * Fields:
 *   revision	(size 4, offset 0, init 0):	RW	Revision
 *   part	(size 12, offset 4, init 0):	RW	Primary part number
 *   architecture	(size 4, offset 16, init 0):	RW	Architecture
 *   variant	(size 4, offset 20, init 0):	RW	Variant
 *   implementer	(size 8, offset 24, init 0):	RW	Implementer
 */
typedef uint8_t *cpuid_arm_midr_t;
typedef uint8_t cpuid_arm_midr_array_t[4];
static const size_t cpuid_arm_midr_size = sizeof(cpuid_arm_midr_array_t );
static inline uint8_t cpuid_arm_midr_revision_extract(cpuid_arm_midr_t _dtptr) __attribute__ ((always_inline));
static inline uint8_t cpuid_arm_midr_revision_extract(cpuid_arm_midr_t _dtptr)
{
    return(((*((uint8_t *)(0 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_midr_revision_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_midr_revision_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval)
{
    *((uint8_t *)(0 + _dtptr)) = (((*((uint8_t *)(0 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline uint16_t cpuid_arm_midr_part_extract(cpuid_arm_midr_t _dtptr) __attribute__ ((always_inline));
static inline uint16_t cpuid_arm_midr_part_extract(cpuid_arm_midr_t _dtptr)
{
    return(((*((uint16_t *)(0 + _dtptr))) & 0xfff0) >> 4);
}

static inline void cpuid_arm_midr_part_insert(cpuid_arm_midr_t _dtptr, uint16_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_midr_part_insert(cpuid_arm_midr_t _dtptr, uint16_t _fieldval)
{
    *((uint16_t *)(0 + _dtptr)) = (((*((uint16_t *)(0 + _dtptr))) & 0xf) | (0xfff0 & (_fieldval << 4)));
}

static inline uint8_t cpuid_arm_midr_architecture_extract(cpuid_arm_midr_t _dtptr) __attribute__ ((always_inline));
static inline uint8_t cpuid_arm_midr_architecture_extract(cpuid_arm_midr_t _dtptr)
{
    return(((*((uint8_t *)(2 + _dtptr))) & 0xf) >> 0);
}

static inline void cpuid_arm_midr_architecture_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_midr_architecture_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval)
{
    *((uint8_t *)(2 + _dtptr)) = (((*((uint8_t *)(2 + _dtptr))) & 0xf0) | (0xf & (_fieldval << 0)));
}

static inline uint8_t cpuid_arm_midr_variant_extract(cpuid_arm_midr_t _dtptr) __attribute__ ((always_inline));
static inline uint8_t cpuid_arm_midr_variant_extract(cpuid_arm_midr_t _dtptr)
{
    return(((*((uint8_t *)(2 + _dtptr))) & 0xf0) >> 4);
}

static inline void cpuid_arm_midr_variant_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_midr_variant_insert(cpuid_arm_midr_t _dtptr, uint8_t _fieldval)
{
    *((uint8_t *)(2 + _dtptr)) = (((*((uint8_t *)(2 + _dtptr))) & 0xf) | (0xf0 & (_fieldval << 4)));
}

static inline cpuid_arm_midr_impl_t cpuid_arm_midr_implementer_extract(cpuid_arm_midr_t _dtptr) __attribute__ ((always_inline));
static inline cpuid_arm_midr_impl_t cpuid_arm_midr_implementer_extract(cpuid_arm_midr_t _dtptr)
{
    return(((*((uint8_t *)(3 + _dtptr))) & 0xff) >> 0);
}

static inline void cpuid_arm_midr_implementer_insert(cpuid_arm_midr_t _dtptr, cpuid_arm_midr_impl_t _fieldval) __attribute__ ((always_inline));
static inline void cpuid_arm_midr_implementer_insert(cpuid_arm_midr_t _dtptr, cpuid_arm_midr_impl_t _fieldval)
{
    *((uint8_t *)(3 + _dtptr)) = (((*((uint8_t *)(3 + _dtptr))) & 0x0) | (0xff & (_fieldval << 0)));
}

static inline int cpuid_arm_midr_prtval(char *_s, size_t _size, cpuid_arm_midr_t _regval) __attribute__ ((always_inline));
static inline int cpuid_arm_midr_prtval(char *_s, size_t _size, cpuid_arm_midr_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " revision =\t%" PRIx8 "\t(Revision)\n", cpuid_arm_midr_revision_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " part =\t%" PRIx16 "\t(Primary part number)\n", cpuid_arm_midr_part_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " architecture =\t%" PRIx8 "\t(Architecture)\n", cpuid_arm_midr_architecture_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " variant =\t%" PRIx8 "\t(Variant)\n", cpuid_arm_midr_variant_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " implementer =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = cpuid_arm_midr_impl_prtval(_s + _r, _avail, cpuid_arm_midr_implementer_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Implementer)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Device representation structure
 */
struct __DN(t) {
};
typedef struct __DN(t) __DN(t);

// No registers in this device

/*
 * Device Initialization function
 */
static inline void cpuid_arm_initialize(__DN(t) *_dev) __attribute__ ((always_inline));
static inline void cpuid_arm_initialize(__DN(t) *_dev)
{
}

static inline int cpuid_arm_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int cpuid_arm_pr(char *_s, size_t _size, __DN(t) *_dev)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "-------------------------\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "Dump of device cpuid_arm (ARMv7+ CPUID fields):\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "End of dump of device cpuid_arm\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "-------------------------\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

#undef __DN
#endif // __cpuid_arm_DEV_H
