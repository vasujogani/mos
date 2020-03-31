#ifndef __omap44xx_ckgen_prm_DEV_H
#define __omap44xx_ckgen_prm_DEV_H 1
/*
 * DEVICE DEFINITION: 
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
#define __DN(x) omap44xx_ckgen_prm ## _ ## x
/*
 * Constants defn: omap44xx_ckgen_prm.clksel_status ()
 *  - width 1 bits
 */
typedef uint8_t omap44xx_ckgen_prm_clksel_status_t;
#define omap44xx_ckgen_prm_CLKSEL_0 ((omap44xx_ckgen_prm_clksel_status_t)0x0)
#define omap44xx_ckgen_prm_CLKSEL_1 ((omap44xx_ckgen_prm_clksel_status_t)0x1)

static inline char *omap44xx_ckgen_prm_clksel_status_describe(omap44xx_ckgen_prm_clksel_status_t _e) __attribute__ ((always_inline));
static inline char *omap44xx_ckgen_prm_clksel_status_describe(omap44xx_ckgen_prm_clksel_status_t _e)
{
    switch (_e) {
    case omap44xx_ckgen_prm_CLKSEL_0:
        return("CLKSEL_0: Select SYS_CLK divided by 1");
    case omap44xx_ckgen_prm_CLKSEL_1:
        return("CLKSEL_1: Select SYS_CLK divided by 2 Must be used for SYS_CLK &gt; 26 MHz");
    default:
        return(NULL);
    }
}

static inline int omap44xx_ckgen_prm_clksel_status_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status_t _e) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_clksel_status_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status_t _e)
{
    char *d = omap44xx_ckgen_prm_clksel_status_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "omap44xx_ckgen_prm_clksel_status_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: omap44xx_ckgen_prm.clksel_status1 ()
 *  - width 1 bits
 */
typedef uint8_t omap44xx_ckgen_prm_clksel_status1_t;
#define omap44xx_ckgen_prm_CLKSEL_0_1 ((omap44xx_ckgen_prm_clksel_status1_t)0x0)
#define omap44xx_ckgen_prm_CLKSEL_1_1 ((omap44xx_ckgen_prm_clksel_status1_t)0x1)

static inline char *omap44xx_ckgen_prm_clksel_status1_describe(omap44xx_ckgen_prm_clksel_status1_t _e) __attribute__ ((always_inline));
static inline char *omap44xx_ckgen_prm_clksel_status1_describe(omap44xx_ckgen_prm_clksel_status1_t _e)
{
    switch (_e) {
    case omap44xx_ckgen_prm_CLKSEL_0_1:
        return("CLKSEL_0_1: Selects SYS_CLK for L4WKUP_ICLK Selects SYS_CLK for ABE_DPLL_BYPASS_CLK");
    case omap44xx_ckgen_prm_CLKSEL_1_1:
        return("CLKSEL_1_1: Selects ABE_LP_CLK for L4WKUP_ICLK Selects 32K_FCLK for ABE_DPLL_BYPASS_CLK");
    default:
        return(NULL);
    }
}

static inline int omap44xx_ckgen_prm_clksel_status1_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status1_t _e) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_clksel_status1_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status1_t _e)
{
    char *d = omap44xx_ckgen_prm_clksel_status1_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "omap44xx_ckgen_prm_clksel_status1_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: omap44xx_ckgen_prm.clksel_status2 ()
 *  - width 1 bits
 */
typedef uint8_t omap44xx_ckgen_prm_clksel_status2_t;
#define omap44xx_ckgen_prm_CLKSEL_0_2 ((omap44xx_ckgen_prm_clksel_status2_t)0x0)
#define omap44xx_ckgen_prm_CLKSEL_1_2 ((omap44xx_ckgen_prm_clksel_status2_t)0x1)

static inline char *omap44xx_ckgen_prm_clksel_status2_describe(omap44xx_ckgen_prm_clksel_status2_t _e) __attribute__ ((always_inline));
static inline char *omap44xx_ckgen_prm_clksel_status2_describe(omap44xx_ckgen_prm_clksel_status2_t _e)
{
    switch (_e) {
    case omap44xx_ckgen_prm_CLKSEL_0_2:
        return("CLKSEL_0_2: Selects SYS_CLK");
    case omap44xx_ckgen_prm_CLKSEL_1_2:
        return("CLKSEL_1_2: Selects SYS_32K");
    default:
        return(NULL);
    }
}

static inline int omap44xx_ckgen_prm_clksel_status2_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status2_t _e) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_clksel_status2_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_clksel_status2_t _e)
{
    char *d = omap44xx_ckgen_prm_clksel_status2_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "omap44xx_ckgen_prm_clksel_status2_t", (uint64_t )(_e)));
    }
}

/*
 * Constants defn: omap44xx_ckgen_prm.sys_clksel_status ()
 *  - width 3 bits
 */
typedef uint8_t omap44xx_ckgen_prm_sys_clksel_status_t;
#define omap44xx_ckgen_prm_SYS_CLKSEL_0 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x0)
#define omap44xx_ckgen_prm_SYS_CLKSEL_1 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x1)
#define omap44xx_ckgen_prm_SYS_CLKSEL_2 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x2)
#define omap44xx_ckgen_prm_SYS_CLKSEL_3 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x3)
#define omap44xx_ckgen_prm_SYS_CLKSEL_4 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x4)
#define omap44xx_ckgen_prm_SYS_CLKSEL_5 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x5)
#define omap44xx_ckgen_prm_SYS_CLKSEL_6 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x6)
#define omap44xx_ckgen_prm_SYS_CLKSEL_7 ((omap44xx_ckgen_prm_sys_clksel_status_t)0x7)

static inline char *omap44xx_ckgen_prm_sys_clksel_status_describe(omap44xx_ckgen_prm_sys_clksel_status_t _e) __attribute__ ((always_inline));
static inline char *omap44xx_ckgen_prm_sys_clksel_status_describe(omap44xx_ckgen_prm_sys_clksel_status_t _e)
{
    switch (_e) {
    case omap44xx_ckgen_prm_SYS_CLKSEL_0:
        return("SYS_CLKSEL_0: Uninitialized");
    case omap44xx_ckgen_prm_SYS_CLKSEL_1:
        return("SYS_CLKSEL_1: Input clock is 12 MHz");
    case omap44xx_ckgen_prm_SYS_CLKSEL_2:
        return("SYS_CLKSEL_2: Reserved");
    case omap44xx_ckgen_prm_SYS_CLKSEL_3:
        return("SYS_CLKSEL_3: Input clock is 16.8 MHz");
    case omap44xx_ckgen_prm_SYS_CLKSEL_4:
        return("SYS_CLKSEL_4: Input clock is 19.2 MHz");
    case omap44xx_ckgen_prm_SYS_CLKSEL_5:
        return("SYS_CLKSEL_5: Input clock is 26 MHz");
    case omap44xx_ckgen_prm_SYS_CLKSEL_6:
        return("SYS_CLKSEL_6: Reserved");
    case omap44xx_ckgen_prm_SYS_CLKSEL_7:
        return("SYS_CLKSEL_7: Input clock is 38.4 MHz");
    default:
        return(NULL);
    }
}

static inline int omap44xx_ckgen_prm_sys_clksel_status_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_sys_clksel_status_t _e) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_sys_clksel_status_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_sys_clksel_status_t _e)
{
    char *d = omap44xx_ckgen_prm_sys_clksel_status_describe(_e);
    if (d) {
        return(snprintf(_s, _size, "%s", d));
    } else {
        return(snprintf(_s, _size, "Unknown constant %s value 0x%" PRIx64, "omap44xx_ckgen_prm_sys_clksel_status_t", (uint64_t )(_e)));
    }
}

/*
 * Register type: omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t
 * Description: Implicit type of Select the SYS CLK for ABE and DSS subsystems. [warm reset insensitive] register
 * Fields:
 *   clksel	(size 1, offset 0, init 0):	RW	Selects the divider value
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
typedef uint32_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t;
#define omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_default 0x0
static inline omap44xx_ckgen_prm_clksel_status_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_extract(omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_extract(omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval)
{
    return((omap44xx_ckgen_prm_clksel_status_t )((_regval & 0x1) >> 0));
}

static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_insert(omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval, omap44xx_ckgen_prm_clksel_status_t _fieldval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_insert(omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval, omap44xx_ckgen_prm_clksel_status_t _fieldval)
{
    return((_regval & 0xfffffffe) | (0x1 & (((omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t )(_fieldval)) << 0)));
}

static inline int omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Selects the divider value)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Register type: omap44xx_ckgen_prm_cm_l4_wkup_clksel_t
 * Description: Implicit type of Control the functional clock source of L4_WKUP, PRM and Smart Reflex functional clock. register
 * Fields:
 *   clksel	(size 1, offset 0, init 0):	RW	Select the clock source for L4WKUP_ICLK and for ABE_DPLL_BYPASS_CLK clocks.
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
typedef uint32_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_t;
#define omap44xx_ckgen_prm_cm_l4_wkup_clksel_default 0x0
static inline omap44xx_ckgen_prm_clksel_status1_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_extract(omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status1_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_extract(omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval)
{
    return((omap44xx_ckgen_prm_clksel_status1_t )((_regval & 0x1) >> 0));
}

static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_insert(omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval, omap44xx_ckgen_prm_clksel_status1_t _fieldval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_insert(omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval, omap44xx_ckgen_prm_clksel_status1_t _fieldval)
{
    return((_regval & 0xfffffffe) | (0x1 & (((omap44xx_ckgen_prm_cm_l4_wkup_clksel_t )(_fieldval)) << 0)));
}

static inline int omap44xx_ckgen_prm_cm_l4_wkup_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_l4_wkup_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status1_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Select the clock source for L4WKUP_ICLK and for ABE_DPLL_BYPASS_CLK clocks.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Register type: omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t
 * Description: Implicit type of Control the source of the reference clock for DPLL_ABE register
 * Fields:
 *   clksel	(size 1, offset 0, init 0):	RW	Select the source for the DPLL_ABE reference clock.
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
typedef uint32_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t;
#define omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_default 0x0
static inline omap44xx_ckgen_prm_clksel_status2_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_extract(omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status2_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_extract(omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval)
{
    return((omap44xx_ckgen_prm_clksel_status2_t )((_regval & 0x1) >> 0));
}

static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_insert(omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval, omap44xx_ckgen_prm_clksel_status2_t _fieldval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_insert(omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval, omap44xx_ckgen_prm_clksel_status2_t _fieldval)
{
    return((_regval & 0xfffffffe) | (0x1 & (((omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t )(_fieldval)) << 0)));
}

static inline int omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status2_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Select the source for the DPLL_ABE reference clock.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Register type: omap44xx_ckgen_prm_cm_sys_clksel_t
 * Description: Implicit type of Software sets the SYS_CLK configuration corresponding to the frequency of SYS_CLK. [warm reset insensitive] register
 * Fields:
 *   sys_clksel	(size 3, offset 0, init 0):	RW	System clock input selection.
 *   _anon3	(size 29, offset 3, init 0):	MBZ	_
 */
typedef uint32_t omap44xx_ckgen_prm_cm_sys_clksel_t;
#define omap44xx_ckgen_prm_cm_sys_clksel_default 0x0
static inline omap44xx_ckgen_prm_sys_clksel_status_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_extract(omap44xx_ckgen_prm_cm_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_sys_clksel_status_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_extract(omap44xx_ckgen_prm_cm_sys_clksel_t _regval)
{
    return((omap44xx_ckgen_prm_sys_clksel_status_t )((_regval & 0x7) >> 0));
}

static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_insert(omap44xx_ckgen_prm_cm_sys_clksel_t _regval, omap44xx_ckgen_prm_sys_clksel_status_t _fieldval) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_insert(omap44xx_ckgen_prm_cm_sys_clksel_t _regval, omap44xx_ckgen_prm_sys_clksel_status_t _fieldval)
{
    return((_regval & 0xfffffff8) | (0x7 & (((omap44xx_ckgen_prm_cm_sys_clksel_t )(_fieldval)) << 0)));
}

static inline int omap44xx_ckgen_prm_cm_sys_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_sys_clksel_prtval(char *_s, size_t _size, omap44xx_ckgen_prm_cm_sys_clksel_t _regval)
{
    int _r = 0;
    int _avail;
    int _rc;
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " sys_clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_sys_clksel_status_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(System clock input selection.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    return(_r);
}

/*
 * Device representation structure
 */
struct __DN(t) {
    mackerel_addr_t base;
};
typedef struct __DN(t) __DN(t);

/*
 * Initial register values (currently 0)
 */
enum omap44xx_ckgen_prm_initials {
    omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_initial = 0x0,
    omap44xx_ckgen_prm_cm_l4_wkup_clksel_initial = 0x0,
    omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_initial = 0x0,
    omap44xx_ckgen_prm_cm_sys_clksel_initial = 0x0
};

/*
 * Device Initialization function
 */
static inline void omap44xx_ckgen_prm_initialize(__DN(t) *_dev, mackerel_addr_t base) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_initialize(__DN(t) *_dev, mackerel_addr_t base)
{
    _dev->base = base;
}

/*
 * Register cm_abe_dss_sys_clksel: Select the SYS CLK for ABE and DSS subsystems. [warm reset insensitive]
 * Type: omap44xx_ckgen_prm.cm_abe_dss_sys_clksel (Implicit type of Select the SYS CLK for ABE and DSS subsystems. [warm reset insensitive] register)
 *   clksel	(size 1, offset 0, init 0):	RW	Selects the divider value
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rawrd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rawrd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x0));
}

static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x0));
}

static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval)
{
    mackerel_write_addr_32(_dev->base, 0x0, _regval);
}

static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval)
{
    _regval = (_regval & 0x1);
    // No MB1 fields present
    // No pre-read of register required
    mackerel_write_addr_32(_dev->base, 0x0, _regval);
}

static inline int omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_pr(char *_s, size_t _size, __DN(t) *_dev)
{
    int _r = 0;
    int _avail;
    int _rc;
    omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x0);
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "Register cm_abe_dss_sys_clksel (Select the SYS CLK for ABE and DSS subsystems. [warm reset insensitive]): ");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Selects the divider value)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    // _anon1 is anonymous
    return(_r);
}

static inline omap44xx_ckgen_prm_clksel_status_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_rdf(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status_t omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_rdf(__DN(t) *_dev)
{
    omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x0);
    return(omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_extract(_regval));
}

static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status_t _fieldval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status_t _fieldval)
{
    omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t _regval = 0x1 & (((omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_t )(_fieldval)) << 0);
    // No pre-read of register required
    // No read of register shadow required
    _regval = (_regval & 0x1);
    // No MB1 fields present
    mackerel_write_addr_32(_dev->base, 0x0, _regval);
    // No shadow register to write to
}

/*
 * Register cm_l4_wkup_clksel: Control the functional clock source of L4_WKUP, PRM and Smart Reflex functional clock.
 * Type: omap44xx_ckgen_prm.cm_l4_wkup_clksel (Implicit type of Control the functional clock source of L4_WKUP, PRM and Smart Reflex functional clock. register)
 *   clksel	(size 1, offset 0, init 0):	RW	Select the clock source for L4WKUP_ICLK and for ABE_DPLL_BYPASS_CLK clocks.
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_rawrd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_rawrd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x8));
}

static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_rd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_l4_wkup_clksel_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_rd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x8));
}

static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval)
{
    mackerel_write_addr_32(_dev->base, 0x8, _regval);
}

static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval)
{
    _regval = (_regval & 0x1);
    // No MB1 fields present
    // No pre-read of register required
    mackerel_write_addr_32(_dev->base, 0x8, _regval);
}

static inline int omap44xx_ckgen_prm_cm_l4_wkup_clksel_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_l4_wkup_clksel_pr(char *_s, size_t _size, __DN(t) *_dev)
{
    int _r = 0;
    int _avail;
    int _rc;
    omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x8);
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "Register cm_l4_wkup_clksel (Control the functional clock source of L4_WKUP, PRM and Smart Reflex functional clock.): ");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status1_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Select the clock source for L4WKUP_ICLK and for ABE_DPLL_BYPASS_CLK clocks.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    // _anon1 is anonymous
    return(_r);
}

static inline omap44xx_ckgen_prm_clksel_status1_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_rdf(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status1_t omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_rdf(__DN(t) *_dev)
{
    omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x8);
    return(omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_extract(_regval));
}

static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status1_t _fieldval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_l4_wkup_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status1_t _fieldval)
{
    omap44xx_ckgen_prm_cm_l4_wkup_clksel_t _regval = 0x1 & (((omap44xx_ckgen_prm_cm_l4_wkup_clksel_t )(_fieldval)) << 0);
    // No pre-read of register required
    // No read of register shadow required
    _regval = (_regval & 0x1);
    // No MB1 fields present
    mackerel_write_addr_32(_dev->base, 0x8, _regval);
    // No shadow register to write to
}

/*
 * Register cm_abe_pll_ref_clksel: Control the source of the reference clock for DPLL_ABE
 * Type: omap44xx_ckgen_prm.cm_abe_pll_ref_clksel (Implicit type of Control the source of the reference clock for DPLL_ABE register)
 *   clksel	(size 1, offset 0, init 0):	RW	Select the source for the DPLL_ABE reference clock.
 *   _anon1	(size 31, offset 1, init 0):	MBZ	_
 */
static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rawrd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rawrd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0xc));
}

static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0xc));
}

static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval)
{
    mackerel_write_addr_32(_dev->base, 0xc, _regval);
}

static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval)
{
    _regval = (_regval & 0x1);
    // No MB1 fields present
    // No pre-read of register required
    mackerel_write_addr_32(_dev->base, 0xc, _regval);
}

static inline int omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_pr(char *_s, size_t _size, __DN(t) *_dev)
{
    int _r = 0;
    int _avail;
    int _rc;
    omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0xc);
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "Register cm_abe_pll_ref_clksel (Control the source of the reference clock for DPLL_ABE): ");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_clksel_status2_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(Select the source for the DPLL_ABE reference clock.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    // _anon1 is anonymous
    return(_r);
}

static inline omap44xx_ckgen_prm_clksel_status2_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_rdf(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_clksel_status2_t omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_rdf(__DN(t) *_dev)
{
    omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0xc);
    return(omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_extract(_regval));
}

static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status2_t _fieldval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_clksel_status2_t _fieldval)
{
    omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t _regval = 0x1 & (((omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_t )(_fieldval)) << 0);
    // No pre-read of register required
    // No read of register shadow required
    _regval = (_regval & 0x1);
    // No MB1 fields present
    mackerel_write_addr_32(_dev->base, 0xc, _regval);
    // No shadow register to write to
}

/*
 * Register cm_sys_clksel: Software sets the SYS_CLK configuration corresponding to the frequency of SYS_CLK. [warm reset insensitive]
 * Type: omap44xx_ckgen_prm.cm_sys_clksel (Implicit type of Software sets the SYS_CLK configuration corresponding to the frequency of SYS_CLK. [warm reset insensitive] register)
 *   sys_clksel	(size 3, offset 0, init 0):	RW	System clock input selection.
 *   _anon3	(size 29, offset 3, init 0):	MBZ	_
 */
static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_rawrd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_rawrd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x10));
}

static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_rd(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_cm_sys_clksel_t omap44xx_ckgen_prm_cm_sys_clksel_rd(__DN(t) *_dev)
{
    return(mackerel_read_addr_32(_dev->base, 0x10));
}

static inline void omap44xx_ckgen_prm_cm_sys_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_sys_clksel_rawwr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_sys_clksel_t _regval)
{
    mackerel_write_addr_32(_dev->base, 0x10, _regval);
}

static inline void omap44xx_ckgen_prm_cm_sys_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_sys_clksel_t _regval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_sys_clksel_wr(__DN(t) *_dev, omap44xx_ckgen_prm_cm_sys_clksel_t _regval)
{
    _regval = (_regval & 0x7);
    // No MB1 fields present
    // No pre-read of register required
    mackerel_write_addr_32(_dev->base, 0x10, _regval);
}

static inline int omap44xx_ckgen_prm_cm_sys_clksel_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_cm_sys_clksel_pr(char *_s, size_t _size, __DN(t) *_dev)
{
    int _r = 0;
    int _avail;
    int _rc;
    omap44xx_ckgen_prm_cm_sys_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x10);
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "Register cm_sys_clksel (Software sets the SYS_CLK configuration corresponding to the frequency of SYS_CLK. [warm reset insensitive]): ");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, " sys_clksel =\t");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_sys_clksel_status_prtval(_s + _r, _avail, omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_extract(_regval));
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "\t(System clock input selection.)\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    // _anon3 is anonymous
    return(_r);
}

static inline omap44xx_ckgen_prm_sys_clksel_status_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_rdf(__DN(t) *_dev) __attribute__ ((always_inline));
static inline omap44xx_ckgen_prm_sys_clksel_status_t omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_rdf(__DN(t) *_dev)
{
    omap44xx_ckgen_prm_cm_sys_clksel_t _regval = mackerel_read_addr_32(_dev->base, 0x10);
    return(omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_extract(_regval));
}

static inline void omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_sys_clksel_status_t _fieldval) __attribute__ ((always_inline));
static inline void omap44xx_ckgen_prm_cm_sys_clksel_sys_clksel_wrf(__DN(t) *_dev, omap44xx_ckgen_prm_sys_clksel_status_t _fieldval)
{
    omap44xx_ckgen_prm_cm_sys_clksel_t _regval = 0x7 & (((omap44xx_ckgen_prm_cm_sys_clksel_t )(_fieldval)) << 0);
    // No pre-read of register required
    // No read of register shadow required
    _regval = (_regval & 0x7);
    // No MB1 fields present
    mackerel_write_addr_32(_dev->base, 0x10, _regval);
    // No shadow register to write to
}

static inline int omap44xx_ckgen_prm_pr(char *_s, size_t _size, __DN(t) *_dev) __attribute__ ((always_inline));
static inline int omap44xx_ckgen_prm_pr(char *_s, size_t _size, __DN(t) *_dev)
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
    _rc = snprintf(_s + _r, _avail, "Dump of device omap44xx_ckgen_prm ():\n");
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_cm_abe_dss_sys_clksel_pr(_s + _r, _avail, _dev);
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_cm_l4_wkup_clksel_pr(_s + _r, _avail, _dev);
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_cm_abe_pll_ref_clksel_pr(_s + _r, _avail, _dev);
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = omap44xx_ckgen_prm_cm_sys_clksel_pr(_s + _r, _avail, _dev);
    if ((_rc > 0) && (_rc < _avail)) {
        _r = (_r + _rc);
    }
    _avail = ((_r > _size) ? 0 : (_size - _r));
    _rc = snprintf(_s + _r, _avail, "End of dump of device omap44xx_ckgen_prm\n");
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
#endif // __omap44xx_ckgen_prm_DEV_H