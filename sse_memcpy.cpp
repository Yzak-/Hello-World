__declspec(naked) static void sse_memcpy ( void *dest, 
	                                       const void *src, 
										   size_t n) {

	// static unsigned int address_;

	__asm {

		
		mov edi, dword ptr [ esp + 0x04 ]
		mov esi, dword ptr [ esp + 0x08 ] 
		mov ecx, dword ptr [ esp + 0x0C ] // loop 

		mov ebx, ecx
		shr ecx, 7

		je  byte_low_128_enable_test 

sse_loop:
		// prefetchnta [ esi ]
		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]
		movdqa xmm2, [ esi + 0x20 ]
		movdqa xmm3, [ esi + 0x30 ]
		
		movdqa [ edi + 0x00 ] , xmm0
		movdqa [ edi + 0x10 ] , xmm1
		movdqa [ edi + 0x20 ] , xmm2
		movdqa [ edi + 0x30 ] , xmm3

		movdqa xmm4, [ esi + 0x40 ]
		movdqa xmm5, [ esi + 0x50 ]
		movdqa xmm6, [ esi + 0x60 ]
		movdqa xmm7, [ esi + 0x70 ]

		movdqa [ edi + 0x40 ] , xmm4
		movdqa [ edi + 0x50 ] , xmm5
		movdqa [ edi + 0x60 ] , xmm6
		movdqa [ edi + 0x70 ] , xmm7

		lea esi, [ esi + 0x80 ]
		lea edi, [ edi + 0x80 ]

		dec ecx 
		jne sse_loop
		
byte_low_128_enable_test:

		mov ecx, ebx
		and ecx, 0x70
		lea ecx, [_large_swicth_table + ecx ]
		jmp ecx

_large_swicth_table:

		    and ebx, 0xF
			lea ebx, [ ebx * 8 + _little_switch_table ]
		    jmp ebx

			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC */
		jmp low_32_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
		jmp low_48_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /* 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
		jmp low_64_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
		jmp low_80_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
		jmp low_96_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
		jmp low_112_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]
		movdqa xmm2, [ esi + 0x20 ]
		movdqa xmm3, [ esi + 0x30 ]

		movdqa [ edi + 0x00 ] , xmm0
		movdqa [ edi + 0x10 ] , xmm1
		movdqa [ edi + 0x20 ] , xmm2
		movdqa [ edi + 0x30 ] , xmm3

		movdqa xmm4, [ esi + 0x40 ]
		movdqa xmm5, [ esi + 0x50 ]
		movdqa xmm6, [ esi + 0x60 ]

		movdqa [ edi + 0x40 ] , xmm4
		movdqa [ edi + 0x50 ] , xmm5
		movdqa [ edi + 0x60 ] , xmm6

		lea esi, [ esi + 0x70 ]
		lea edi, [ edi + 0x70 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_32_bytes : // 1 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]

		movdqa [ edi + 0x00 ] , xmm0

		lea esi, [ esi + 0x10 ]
		lea edi, [ edi + 0x10 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_48_bytes : // 2 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]

		movdqa [ edi + 0x00 ] , xmm0
	    movdqa [ edi + 0x10 ] , xmm1
	
		lea esi, [ esi + 0x20 ]
		lea edi, [ edi + 0x20 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_64_bytes : // 3 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]

		movdqa [ edi + 0x00 ] , xmm0
	    movdqa [ edi + 0x10 ] , xmm1
			
	    movdqa xmm2, [ esi + 0x20 ]

		movdqa [ edi + 0x20 ] , xmm2
			
		lea esi, [ esi + 0x30 ]
		lea edi, [ edi + 0x30 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_80_bytes : // 4 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]

		movdqa [ edi + 0x00 ] , xmm0
		movdqa [ edi + 0x10 ] , xmm1
		
		movdqa xmm2, [ esi + 0x20 ]
		movdqa xmm3, [ esi + 0x30 ]

		movdqa [ edi + 0x20 ] , xmm2
		movdqa [ edi + 0x30 ] , xmm3

		lea esi, [ esi + 0x40 ]
		lea edi, [ edi + 0x40 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_96_bytes :  // 5 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]
		movdqa xmm2, [ esi + 0x20 ]
		

		movdqa [ edi + 0x00 ] , xmm0
		movdqa [ edi + 0x10 ] , xmm1
		movdqa [ edi + 0x20 ] , xmm2
			
		movdqa xmm3, [ esi + 0x30 ]
		movdqa xmm4, [ esi + 0x40 ]

		movdqa [ edi + 0x30 ] , xmm3
		movdqa [ edi + 0x40 ] , xmm4

		lea esi, [ esi + 0x50 ]
		lea edi, [ edi + 0x50 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

low_112_bytes :  // 6 * 16 ^  ~ $ n

		movdqa xmm0, [ esi + 0x00 ]
		movdqa xmm1, [ esi + 0x10 ]
		movdqa xmm2, [ esi + 0x20 ]

		movdqa [ edi + 0x00 ] , xmm0
		movdqa [ edi + 0x10 ] , xmm1
		movdqa [ edi + 0x20 ] , xmm2

		movdqa xmm3, [ esi + 0x30 ]
		movdqa xmm4, [ esi + 0x40 ]
		movdqa xmm5, [ esi + 0x50 ]

		movdqa [ edi + 0x30 ] , xmm3
		movdqa [ edi + 0x40 ] , xmm4
		movdqa [ edi + 0x50 ] , xmm5

		lea esi, [ esi + 0x60 ]
		lea edi, [ edi + 0x60 ]

		and ebx, 0xF
		lea ebx, [ ebx * 8 + _little_switch_table ]
		jmp ebx

_little_switch_table:

			ret // 0
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC

			mov al, byte ptr [ esi ] // 1
			mov byte ptr [ edi ], al
			ret

			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 

		mov ax, word ptr [ esi ] // 2
		mov word ptr [ edi ], ax
		ret
			_emit 0xCC 

		jmp low_3_bytes // 3
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 

		mov eax, dword ptr [ esi ] // 4
		mov dword ptr [ edi ], eax
		ret
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
		jmp low_5_bytes // 5
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
        jmp low_6_bytes // 6
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
		jmp low_7_bytes // 7
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC 
        
		movq mm0, mmword ptr [ esi ] // 8
		movq dword ptr [ edi ], mm0
		ret
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
        jmp low_9_bytes // 9
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC 
        jmp low_10_bytes // 10
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
        jmp low_11_bytes // 11
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC 
        jmp low_12_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
        jmp low_13_bytes
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */
        jmp low_14_bytes 
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC /*
			_emit 0xCC
			_emit 0xCC
			_emit 0xCC */

		mov al, byte ptr [ esi + 0xF ]
		movdqa xmm0, xmmword ptr [ esi + 0x00]
		movdqa xmmword ptr [ edi + 0x00 ], xmm0
		mov byte ptr [ edi + 0xF ], al

		ret

low_3_bytes :

		mov ax, word ptr [ esi ]
		mov word ptr [ edi ], ax

		mov al, byte ptr [ esi + 2]
		mov byte ptr [ edi + 2 ], al
		
		ret

low_5_bytes :

		mov eax, dword ptr [ esi ]
		mov dword ptr [ edi ], eax
		mov al, byte ptr [ esi + 4 ]
		mov byte ptr [ edi + 4 ], al
		ret

low_6_bytes:

		mov eax, dword ptr [ esi ]
		mov dword ptr [ edi ], eax
		mov ax, word ptr [ esi + 4 ]
		mov word ptr [ edi + 4 ], ax
		ret

low_7_bytes :

		mov al, byte ptr [ esi + 0x07 ]
		movq mm0, dword ptr [ esi + 0x00 ]
		movq dword ptr [ edi + 0x00  ], mm0
		mov byte ptr [ edi + 0x07 ], al
		ret

low_9_bytes :

		movq mm0, mmword ptr [ esi ]
		movq dword ptr [ edi ], mm0
		mov al, byte ptr [ esi + 8 ]
		mov byte ptr [ edi + 8 ], al
		ret

low_10_bytes :

		movq mm0, mmword ptr [ esi ]
		movq dword ptr [ edi ], mm0
		mov ax, word ptr [ esi + 8 ]
		mov word ptr [ edi + 8 ], ax
		ret

low_11_bytes :

		movq mm0, mmword ptr [ esi ]
		movq dword ptr [ edi ], mm0
		mov ax, word ptr [ esi + 8 ]
		mov word ptr [ edi + 8 ], ax
		mov al, byte ptr [ esi + 10 ]
		mov byte ptr [ edi + 10 ], al
		ret

low_12_bytes :

		mov eax, dword ptr [ esi + 0x0C ]
		movdqa xmm0, xmmword ptr [ esi + 0x00]
		movdqa xmmword ptr [ edi + 0x00 ], xmm0
		mov dword ptr [ edi + 0x0C ], eax

		ret

low_13_bytes :

		movq mm0, mmword ptr [ esi ]
		movq dword ptr [ edi ], mm0
		mov eax, dword ptr [ esi + 8 ]
		mov dword ptr [ edi + 8 ], eax
		mov al, byte ptr [ esi + 12 ]
		mov byte ptr [ edi + 12 ], al
		ret

low_14_bytes :

        mov ax, word ptr [ esi + 0x0E ]

		movdqa xmm0, xmmword ptr [ esi + 0x00]
		movdqa xmmword ptr [ edi + 0x00 ], xmm0
		
		mov word ptr [ edi + 0x0E ], ax

		ret
		
	}
}

//  LH_Mouse_Ex' s memcpy
__declspec(naked) void *__cdecl my_memcpy_sse2_aligned(void *, const void *, unsigned int){
	__asm {
		// esp ->          [old edi]
		//  +4            [old esi]
		//  +8            [ret addr]
		//  +0C    void *      dst
		//  +10    const void *  src
		//  +14    unsigned int  cnt

		push esi
			push edi

			mov ecx, [esp + 14h]
		mov esi, [esp + 10h]
		mov edi, [esp + 0Ch]
		shr ecx, 4
			jz _remainder
			mov eax, 8
			cmp ecx, eax
			jbe _copy_remainder_segs
_copy_loop_by_seg:
		movdqu xmm7, [esi + 70h]
		movdqu xmm6, [esi + 60h]
		movdqa [edi + 70h], xmm7
			movdqa [edi + 60h], xmm6
			movdqu xmm5, [esi + 50h]
		movdqu xmm4, [esi + 40h]
		movdqa [edi + 50h], xmm5
			movdqa [edi + 40h], xmm4
			movdqu xmm3, [esi + 30h]
		movdqu xmm2, [esi + 20h]
		movdqa [edi + 30h], xmm3
			movdqa [edi + 20h], xmm2
			movdqu xmm1, [esi + 10h]
		movdqu xmm0, [esi]
		movdqa [edi + 10h], xmm1
			movdqa [edi], xmm0

			lea esi, [esi + 80h]
		lea edi, [edi + 80h]

		sub ecx, eax
			cmp ecx, eax
			ja _copy_loop_by_seg
_copy_remainder_segs:
		// 执行到这里 ecx 只可能为 0-8 中的一个。
		jz _copy_80h
			cmp ecx, 4
			jz _copy_40h
			ja _switch_gt4
			cmp ecx, 2
			jz _copy_20h
			ja _copy_30h
			jmp _copy_10h
_switch_gt4:
		cmp ecx, 6
			jz _copy_60h
			ja _copy_70h
			jmp _copy_50h
_copy_80h:
		movdqu xmm7, [esi + 70h]
		movdqa [edi + 70h], xmm7
_copy_70h:
		movdqu xmm6, [esi + 60h]
		movdqa [edi + 60h], xmm6
_copy_60h:
		movdqu xmm5, [esi + 50h]
		movdqa [edi + 50h], xmm5
_copy_50h:
		movdqu xmm4, [esi + 40h]
		movdqa [edi + 40h], xmm4
_copy_40h:
		movdqu xmm3, [esi + 30h]
		movdqa [edi + 30h], xmm3
_copy_30h:
		movdqu xmm2, [esi + 20h]
		movdqa [edi + 20h], xmm2
_copy_20h:
		movdqu xmm1, [esi + 10h]
		movdqa [edi + 10h], xmm1
_copy_10h:
		movdqu xmm0, [esi]
		movdqa [edi], xmm0
_remainder:
		lea eax, [ecx * 8]
		lea esi, [esi + eax * 2]
		lea edi, [edi + eax * 2]

		mov ecx, [esp + 14h]
		and ecx, 0Fh
			rep movsb

			mov eax, [esp + 0Ch]
		pop edi
			pop esi
			ret              // __cdecl
	}
}

#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <windows.h>
#include <MMSystem.h>

void vc_memcpy ( void *dest, const void *src, size_t n, size_t cnt ) {

	size_t _start = timeGetTime ();

	for ( size_t index = 0; index < cnt; ++ index ) {

		memcpy ( dest, src, n );
	}

	std::cout << " vc_memcpy :" << timeGetTime() -_start << "ms ";
	
}

void my_memcpy ( void *dest, const void *src, size_t n, size_t cnt ) {

	size_t _start = timeGetTime ();

	for ( size_t index = 0; index < cnt; ++ index ) {

		sse_memcpy ( dest, src, n );
	}

	std::cout << " my_memcpy :" << timeGetTime() -_start << "ms ";
}

void ms_memcpy ( void *dest, const void *src, size_t n, size_t cnt ) {

	size_t _start = timeGetTime ();

	for ( size_t index = 0; index < cnt; ++ index ) {

		my_memcpy_sse2_aligned ( dest, src, n );
	}

	std::cout << " ms_memcpy :" << timeGetTime() -_start << "ms " ;
}

void te_memcpy ( void *dest, const void *src, size_t n, size_t cnt ) {

	size_t _start = timeGetTime ();

	for ( size_t index = 0; index < cnt; ++ index ) {

		my_memcpy_sse2_aligned ( dest, src, n );
	}

	std::cout << " temp_memcpy :" << timeGetTime() -_start << "ms " ;
}

int main (void) {

	static __declspec ( align (16) ) char _vc_src [0x2FFFFFFF];
	/*static __declspec ( align (16) ) char _vc_des [0x2FFFFFFF];/*
	static __declspec ( align (16) ) char _my_src [0x2FFFFFFF];
	static __declspec ( align (16) ) char _my_des [0x2FFFFFFF];
    static __declspec ( align (16) ) char _ms_src [0x2FFFFFFF];
	static __declspec ( align (16) ) char _ms_des [0x2FFFFFFF];*/

#define _loops 100

	for ( size_t index = 0; index < _loops; index ++ ) {

	    // boost::thread vc_memcpy_thread ( vc_memcpy, _vc_des, _vc_src, 0xFFFFFF, 0x40 );
		// boost::thread my_memcpy_thread ( my_memcpy, _my_des, _my_src, 0xFFFFFF, 0x40 );
        // boost::thread ms_memcpy_thread ( ms_memcpy, _ms_des, _ms_src, 0xFFFFFF, 0x40 );

		// vc_memcpy_thread.join ();
		// my_memcpy_thread.join ();
		// ms_memcpy_thread.join ();
		
#define _num 0x2FFFFFFF
#define _cnt 50

		te_memcpy ( _vc_src, _vc_src, _num, _cnt );
		vc_memcpy ( _vc_src, _vc_src, _num, _cnt );
		my_memcpy ( _vc_src, _vc_src, _num, _cnt );
		ms_memcpy ( _vc_src, _vc_src, _num, _cnt );

		std::cout << index + 1 << std::endl;
	}

	std::cout << "test end" << std::endl;

	system ( "pause" );

	return 0;
}
