/*
 * Copyright (C) 2016 ARM Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_POINTER_AUTH_H
#define __ASM_POINTER_AUTH_H

#include <linux/bitops.h>
#include <linux/random.h>

#include <asm/cpufeature.h>
#include <asm/memory.h>
#include <asm/sysreg.h>

#ifdef CONFIG_ARM64_POINTER_AUTHENTICATION
/*
 * Each key is a 128-bit quantity which is split accross a pair of 64-bit
 * registers (Lo and Hi).
 */
struct ptrauth_key {
	unsigned long lo, hi;
};

/*
 * We give each process its own instruction A key (APIAKey), which is shared by
 * all threads. This is inherited upon fork(), and reinitialised upon exec*().
 * All other keys are currently unused, with APIBKey, APDAKey, and APBAKey
 * instructions behaving as NOPs.
 */
struct ptrauth_keys {
	struct ptrauth_key apia;
};

static inline void ptrauth_keys_init(struct ptrauth_keys *keys)
{
	if (!cpus_have_const_cap(ARM64_HAS_ADDRESS_AUTH))
		return;

	get_random_bytes(keys, sizeof(*keys));
}

#define __ptrauth_key_install(k, v)			\
do {							\
	write_sysreg_s(v.lo, SYS_ ## k ## KEYLO_EL1);	\
	write_sysreg_s(v.hi, SYS_ ## k ## KEYHI_EL1);	\
} while (0)

static inline void ptrauth_keys_switch(struct ptrauth_keys *keys)
{
	if (!cpus_have_const_cap(ARM64_HAS_ADDRESS_AUTH))
		return;

	__ptrauth_key_install(APIA, keys->apia);
}

static inline void ptrauth_keys_dup(struct ptrauth_keys *old,
				    struct ptrauth_keys *new)
{
	if (!cpus_have_const_cap(ARM64_HAS_ADDRESS_AUTH))
		return;

	*new = *old;
}

/*
 * The EL0 pointer bits used by a pointer authentication code.
 * This is dependent on TBI0 being enabled, or bits 63:56 would also apply.
 */
#define ptrauth_pac_mask() 	GENMASK(54, VA_BITS)

/* Only valid for EL0 TTBR0 instruction pointers */
static inline unsigned long ptrauth_strip_insn_pac(unsigned long ptr)
{
	return ptr & ~ptrauth_pac_mask();
}

#define mm_ctx_ptrauth_init(ctx) \
	ptrauth_keys_init(&(ctx)->ptrauth_keys)

#define mm_ctx_ptrauth_switch(ctx) \
	ptrauth_keys_switch(&(ctx)->ptrauth_keys)

#define mm_ctx_ptrauth_dup(oldctx, newctx) \
	ptrauth_keys_dup(&(oldctx)->ptrauth_keys, &(newctx)->ptrauth_keys)

#else
#define ptrauth_strip_insn_pac(lr)	(lr)
#define mm_ctx_ptrauth_init(ctx)
#define mm_ctx_ptrauth_switch(ctx)
#define mm_ctx_ptrauth_dup(oldctx, newctx)
#endif

#endif /* __ASM_POINTER_AUTH_H */
