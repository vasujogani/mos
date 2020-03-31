#ifndef CAPBITS_H
#define CAPBITS_H
#include <barrelfish_kpi/capabilities.h>
#pragma pack(1)
struct DevFrame;
struct DevFrame_Mapping;
struct Dispatcher;
struct EndPoint;
struct FCNode;
struct Frame;
struct Frame_Mapping;
struct ID;
struct IO;
struct IPI;
struct IRQDest;
struct IRQSrc;
struct IRQTable;
struct Kernel;
struct KernelControlBlock;
struct L1CNode;
struct L2CNode;
struct Notify_IPI;
struct Notify_RCK;
struct Null;
struct PerfMon;
struct PhysAddr;
struct RAM;
struct VNode_AARCH64_l0;
struct VNode_AARCH64_l0_Mapping;
struct VNode_AARCH64_l1;
struct VNode_AARCH64_l1_Mapping;
struct VNode_AARCH64_l2;
struct VNode_AARCH64_l2_Mapping;
struct VNode_AARCH64_l3;
struct VNode_AARCH64_l3_Mapping;
struct VNode_ARM_l1;
struct VNode_ARM_l1_Mapping;
struct VNode_ARM_l2;
struct VNode_ARM_l2_Mapping;
struct VNode_x86_32_pdir;
struct VNode_x86_32_pdir_Mapping;
struct VNode_x86_32_pdpt;
struct VNode_x86_32_pdpt_Mapping;
struct VNode_x86_32_ptable;
struct VNode_x86_32_ptable_Mapping;
struct VNode_x86_64_pdir;
struct VNode_x86_64_pdir_Mapping;
struct VNode_x86_64_pdpt;
struct VNode_x86_64_pdpt_Mapping;
struct VNode_x86_64_pml4;
struct VNode_x86_64_pml4_Mapping;
struct VNode_x86_64_ptable;
struct VNode_x86_64_ptable_Mapping;
struct capability;
union capability_u;
enum __attribute__((__packed__)) objtype {
    ObjType_Num = 49,
    ObjType_IPI = 48,
    ObjType_KernelControlBlock = 47,
    ObjType_PerfMon = 46,
    ObjType_ID = 45,
    ObjType_Notify_IPI = 44,
    ObjType_Notify_RCK = 43,
    ObjType_IO = 42,
    ObjType_IRQSrc = 41,
    ObjType_IRQDest = 40,
    ObjType_IRQTable = 39,
    ObjType_VNode_AARCH64_l3_Mapping = 38,
    ObjType_VNode_AARCH64_l3 = 37,
    ObjType_VNode_AARCH64_l2_Mapping = 36,
    ObjType_VNode_AARCH64_l2 = 35,
    ObjType_VNode_AARCH64_l1_Mapping = 34,
    ObjType_VNode_AARCH64_l1 = 33,
    ObjType_VNode_AARCH64_l0_Mapping = 32,
    ObjType_VNode_AARCH64_l0 = 31,
    ObjType_VNode_ARM_l2_Mapping = 30,
    ObjType_VNode_ARM_l2 = 29,
    ObjType_VNode_ARM_l1_Mapping = 28,
    ObjType_VNode_ARM_l1 = 27,
    ObjType_VNode_x86_32_ptable_Mapping = 26,
    ObjType_VNode_x86_32_ptable = 25,
    ObjType_VNode_x86_32_pdir_Mapping = 24,
    ObjType_VNode_x86_32_pdir = 23,
    ObjType_VNode_x86_32_pdpt_Mapping = 22,
    ObjType_VNode_x86_32_pdpt = 21,
    ObjType_VNode_x86_64_ptable_Mapping = 20,
    ObjType_VNode_x86_64_ptable = 19,
    ObjType_VNode_x86_64_pdir_Mapping = 18,
    ObjType_VNode_x86_64_pdir = 17,
    ObjType_VNode_x86_64_pdpt_Mapping = 16,
    ObjType_VNode_x86_64_pdpt = 15,
    ObjType_VNode_x86_64_pml4_Mapping = 14,
    ObjType_VNode_x86_64_pml4 = 13,
    ObjType_Kernel = 12,
    ObjType_DevFrame_Mapping = 11,
    ObjType_DevFrame = 10,
    ObjType_Frame_Mapping = 9,
    ObjType_Frame = 8,
    ObjType_EndPoint = 7,
    ObjType_Dispatcher = 6,
    ObjType_FCNode = 5,
    ObjType_L2CNode = 4,
    ObjType_L1CNode = 3,
    ObjType_RAM = 2,
    ObjType_PhysAddr = 1,
    ObjType_Null = 0
};
struct Null {};
struct PhysAddr {genpaddr_t base;
                 pasid_t pasid;
                 gensize_t bytes;};
struct RAM {genpaddr_t base;
            pasid_t pasid;
            gensize_t bytes;};
struct L1CNode {lpaddr_t cnode;
                gensize_t allocated_bytes;
                CapRights rightsmask;};
struct L2CNode {lpaddr_t cnode;
                CapRights rightsmask;};
struct FCNode {genpaddr_t cnode;
               uint8_t bits;
               CapRights rightsmask;
               coreid_t core_id;
               uint8_t guard_size;
               capaddr_t guard;};
struct Dispatcher {struct dcb* dcb;};
struct EndPoint {struct dcb* listener;
                 lvaddr_t epoffset;
                 uint32_t epbuflen;};
struct Frame {genpaddr_t base;
              pasid_t pasid;
              gensize_t bytes;};
struct Frame_Mapping {struct capability* frame;
                      lvaddr_t pte;
                      uint16_t pte_count;};
struct DevFrame {genpaddr_t base;
                 pasid_t pasid;
                 gensize_t bytes;};
struct DevFrame_Mapping {struct capability* frame;
                         lvaddr_t pte;
                         uint16_t pte_count;};
struct Kernel {};
struct VNode_x86_64_pml4 {genpaddr_t base;};
struct VNode_x86_64_pml4_Mapping {struct capability* frame;
                                  lvaddr_t pte;
                                  uint16_t pte_count;};
struct VNode_x86_64_pdpt {genpaddr_t base;};
struct VNode_x86_64_pdpt_Mapping {struct capability* frame;
                                  lvaddr_t pte;
                                  uint16_t pte_count;};
struct VNode_x86_64_pdir {genpaddr_t base;};
struct VNode_x86_64_pdir_Mapping {struct capability* frame;
                                  lvaddr_t pte;
                                  uint16_t pte_count;};
struct VNode_x86_64_ptable {genpaddr_t base;};
struct VNode_x86_64_ptable_Mapping {struct capability* frame;
                                    lvaddr_t pte;
                                    uint16_t pte_count;};
struct VNode_x86_32_pdpt {genpaddr_t base;};
struct VNode_x86_32_pdpt_Mapping {struct capability* frame;
                                  lvaddr_t pte;
                                  uint16_t pte_count;};
struct VNode_x86_32_pdir {genpaddr_t base;};
struct VNode_x86_32_pdir_Mapping {struct capability* frame;
                                  lvaddr_t pte;
                                  uint16_t pte_count;};
struct VNode_x86_32_ptable {genpaddr_t base;};
struct VNode_x86_32_ptable_Mapping {struct capability* frame;
                                    lvaddr_t pte;
                                    uint16_t pte_count;};
struct VNode_ARM_l1 {genpaddr_t base;};
struct VNode_ARM_l1_Mapping {struct capability* frame;
                             lvaddr_t pte;
                             uint16_t pte_count;};
struct VNode_ARM_l2 {genpaddr_t base;};
struct VNode_ARM_l2_Mapping {struct capability* frame;
                             lvaddr_t pte;
                             uint16_t pte_count;};
struct VNode_AARCH64_l0 {genpaddr_t base;};
struct VNode_AARCH64_l0_Mapping {struct capability* frame;
                                 lvaddr_t pte;
                                 uint16_t pte_count;};
struct VNode_AARCH64_l1 {genpaddr_t base;};
struct VNode_AARCH64_l1_Mapping {struct capability* frame;
                                 lvaddr_t pte;
                                 uint16_t pte_count;};
struct VNode_AARCH64_l2 {genpaddr_t base;};
struct VNode_AARCH64_l2_Mapping {struct capability* frame;
                                 lvaddr_t pte;
                                 uint16_t pte_count;};
struct VNode_AARCH64_l3 {genpaddr_t base;};
struct VNode_AARCH64_l3_Mapping {struct capability* frame;
                                 lvaddr_t pte;
                                 uint16_t pte_count;};
struct IRQTable {};
struct IRQDest {uint64_t cpu;
                uint64_t vector;};
struct IRQSrc {uint64_t vector;
               uint64_t controller;};
struct IO {uint16_t start;
           uint16_t end;};
struct Notify_RCK {coreid_t coreid;
                   uint16_t chanid;};
struct Notify_IPI {coreid_t coreid;
                   uint16_t chanid;};
struct ID {coreid_t coreid;
           uint32_t core_local_id;};
struct PerfMon {};
struct KernelControlBlock {struct kcb* kcb;};
struct IPI {};
union capability_u {struct  Null null;
                    struct  PhysAddr physaddr;
                    struct  RAM ram;
                    struct  L1CNode l1cnode;
                    struct  L2CNode l2cnode;
                    struct  FCNode fcnode;
                    struct  Dispatcher dispatcher;
                    struct  EndPoint endpoint;
                    struct  Frame frame;
                    struct  Frame_Mapping frame_mapping;
                    struct  DevFrame devframe;
                    struct  DevFrame_Mapping devframe_mapping;
                    struct  Kernel kernel;
                    struct  VNode_x86_64_pml4 vnode_x86_64_pml4;
                    struct  VNode_x86_64_pml4_Mapping vnode_x86_64_pml4_mapping;
                    struct  VNode_x86_64_pdpt vnode_x86_64_pdpt;
                    struct  VNode_x86_64_pdpt_Mapping vnode_x86_64_pdpt_mapping;
                    struct  VNode_x86_64_pdir vnode_x86_64_pdir;
                    struct  VNode_x86_64_pdir_Mapping vnode_x86_64_pdir_mapping;
                    struct  VNode_x86_64_ptable vnode_x86_64_ptable;
                    struct  VNode_x86_64_ptable_Mapping vnode_x86_64_ptable_mapping;
                    struct  VNode_x86_32_pdpt vnode_x86_32_pdpt;
                    struct  VNode_x86_32_pdpt_Mapping vnode_x86_32_pdpt_mapping;
                    struct  VNode_x86_32_pdir vnode_x86_32_pdir;
                    struct  VNode_x86_32_pdir_Mapping vnode_x86_32_pdir_mapping;
                    struct  VNode_x86_32_ptable vnode_x86_32_ptable;
                    struct  VNode_x86_32_ptable_Mapping vnode_x86_32_ptable_mapping;
                    struct  VNode_ARM_l1 vnode_arm_l1;
                    struct  VNode_ARM_l1_Mapping vnode_arm_l1_mapping;
                    struct  VNode_ARM_l2 vnode_arm_l2;
                    struct  VNode_ARM_l2_Mapping vnode_arm_l2_mapping;
                    struct  VNode_AARCH64_l0 vnode_aarch64_l0;
                    struct  VNode_AARCH64_l0_Mapping vnode_aarch64_l0_mapping;
                    struct  VNode_AARCH64_l1 vnode_aarch64_l1;
                    struct  VNode_AARCH64_l1_Mapping vnode_aarch64_l1_mapping;
                    struct  VNode_AARCH64_l2 vnode_aarch64_l2;
                    struct  VNode_AARCH64_l2_Mapping vnode_aarch64_l2_mapping;
                    struct  VNode_AARCH64_l3 vnode_aarch64_l3;
                    struct  VNode_AARCH64_l3_Mapping vnode_aarch64_l3_mapping;
                    struct  IRQTable irqtable;
                    struct  IRQDest irqdest;
                    struct  IRQSrc irqsrc;
                    struct  IO io;
                    struct  Notify_RCK notify_rck;
                    struct  Notify_IPI notify_ipi;
                    struct  ID id;
                    struct  PerfMon perfmon;
                    struct  KernelControlBlock kernelcontrolblock;
                    struct  IPI ipi;};
struct capability {union  capability_u u;
                   enum objtype type;
                   CapRights rights;};
#pragma pack(0)
#endif // CAPBITS_H
