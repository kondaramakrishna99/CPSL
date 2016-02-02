/**
 * Architecture related info such as OS,
 * instruction set, and optimization features
 * will be listed here.
 */

#ifndef DSLPROJECT_TARGET_H
#define DSLPROJECT_TARGET_H


class Target {
    enum OS {OSUnknown = 0, Linux, Windows, OSX, Android, IOS, NaCl} os;

    /** The architecture used by the target. Determines the
     * instruction set to use. For the PNaCl target, the "instruction
     * set" is actually llvm bitcode.
     * Corresponds to arch_name_map in Target.cpp. */
    enum Arch {ArchUnknown = 0, X86, ARM, PNaCl, MIPS} arch;
public:
    Target():os(OSUnknown), arch(ArchUnknown) {};

};


#endif //DSLPROJECT_TARGET_H
