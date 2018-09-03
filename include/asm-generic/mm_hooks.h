/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Define generic no-op hooks for arch_dup_mmap, arch_exit_mmap
 * and arch_unmap to be included in asm-FOO/mmu_context.h for any
 * arch FOO which doesn't need to hook these.
 */
#ifndef _ASM_GENERIC_MM_HOOKS_H
#define _ASM_GENERIC_MM_HOOKS_H

#ifndef arch_dup_mmap
static inline int arch_dup_mmap(struct mm_struct *oldmm,
				struct mm_struct *mm)
{
	return 0;
}
#endif

#ifndef arch_exit_mmap
static inline void arch_exit_mmap(struct mm_struct *mm)
{
}
#endif

#ifndef arch_unmap
static inline void arch_unmap(struct mm_struct *mm,
			struct vm_area_struct *vma,
			unsigned long start, unsigned long end)
{
}
#endif

#ifndef arch_bprm_mm_init
static inline void arch_bprm_mm_init(struct mm_struct *mm,
				     struct vm_area_struct *vma)
{
}
#endif

#ifndef arch_vma_access_permitted
static inline bool arch_vma_access_permitted(struct vm_area_struct *vma,
		bool write, bool execute, bool foreign)
{
	/* by default, allow everything */
	return true;
}
#endif

#endif	/* _ASM_GENERIC_MM_HOOKS_H */
