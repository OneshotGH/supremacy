#pragma once

#include <inttypes.h>

namespace x86 {
	enum class reg : size_t {
		eax = 0,
		ecx,
		edx,
		ebx,
		esp,
		ebp,
		esi,
		edi,

		/*
		x64:
		r8,
		r9,
		r10,
		r11,
		r12,
		r13,
		r14,
		r15,*/
	};

	enum instruction : uint8_t {
		retn_imm16 = 0xc2,
		retn       = 0xc3,
		fs         = 0x64,
		call       = 0xff,
		nop        = 0x90
	};

	__forceinline static uint32_t encode_call_reg( x86::reg dreg ) {
		return ( 0xd0 + ( size_t( dreg ) ) );
	}

	__forceinline static uint32_t encode_mov_imm32( x86::reg dreg ) {
		return ( 0xb8 + ( size_t( dreg ) ) );
	}

	__forceinline static uint32_t encode_push_reg( x86::reg dreg ) {
		return ( 0x50 | ( ( size_t( dreg ) ) & 7 ) );
	}

	__forceinline static uint32_t encode_pop_reg( x86::reg dreg ) {
		return ( 0x58 | ( ( size_t( dreg ) ) & 7 ) );
	}
};