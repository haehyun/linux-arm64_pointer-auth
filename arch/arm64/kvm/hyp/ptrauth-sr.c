/*
 * Copyright (C) 2017 ARM Ltd
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

#include <linux/compiler.h>
#include <linux/kvm_host.h>

#include <asm/cpucaps.h>
#include <asm/cpufeature.h>
#include <asm/kvm_asm.h>
#include <asm/kvm_hyp.h>

static bool __hyp_text __ptrauth_is_enabled(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.hcr_el2 & (HCR_API | HCR_APK);
}

#define __ptrauth_save_key(regs, key)						\
({										\
	regs[key ## KEYLO_EL1] = read_sysreg_s(SYS_ ## key ## KEYLO_EL1);	\
	regs[key ## KEYHI_EL1] = read_sysreg_s(SYS_ ## key ## KEYHI_EL1);	\
})

static void __hyp_text __ptrauth_save_state(struct kvm_cpu_context *ctxt)
{
	if (cpus_have_const_cap(ARM64_HAS_ADDRESS_AUTH)) {
		__ptrauth_save_key(ctxt->sys_regs, APIA);
		__ptrauth_save_key(ctxt->sys_regs, APIB);
		__ptrauth_save_key(ctxt->sys_regs, APDA);
		__ptrauth_save_key(ctxt->sys_regs, APDB);
	}

	if (cpus_have_const_cap(ARM64_HAS_GENERIC_AUTH)) {
		__ptrauth_save_key(ctxt->sys_regs, APGA);
	}
}

#define __ptrauth_restore_key(regs, key) 					\
({										\
	write_sysreg_s(regs[key ## KEYLO_EL1], SYS_ ## key ## KEYLO_EL1);	\
	write_sysreg_s(regs[key ## KEYHI_EL1], SYS_ ## key ## KEYHI_EL1);	\
})

static void __hyp_text __ptrauth_restore_state(struct kvm_cpu_context *ctxt)
{

	if (cpus_have_const_cap(ARM64_HAS_ADDRESS_AUTH)) {
		__ptrauth_restore_key(ctxt->sys_regs, APIA);
		__ptrauth_restore_key(ctxt->sys_regs, APIB);
		__ptrauth_restore_key(ctxt->sys_regs, APDA);
		__ptrauth_restore_key(ctxt->sys_regs, APDB);
	}

	if (cpus_have_const_cap(ARM64_HAS_GENERIC_AUTH)) {
		__ptrauth_restore_key(ctxt->sys_regs, APGA);
	}
}

void __hyp_text __ptrauth_switch_to_guest(struct kvm_vcpu *vcpu,
					  struct kvm_cpu_context *host_ctxt,
					  struct kvm_cpu_context *guest_ctxt)
{
	if (!__ptrauth_is_enabled(vcpu))
		return;

	__ptrauth_save_state(host_ctxt);
	__ptrauth_restore_state(guest_ctxt);
}

void __hyp_text __ptrauth_switch_to_host(struct kvm_vcpu *vcpu,
					 struct kvm_cpu_context *host_ctxt,
					 struct kvm_cpu_context *guest_ctxt)
{
	if (!__ptrauth_is_enabled(vcpu))
		return;

	__ptrauth_save_state(guest_ctxt);
	__ptrauth_restore_state(host_ctxt);
}
