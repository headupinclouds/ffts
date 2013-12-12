#include "arch_codegen.h"
#include "ffts.h"
insns_t* generate_size8_base_case(insns_t **fp, int sign ) { 
	insns_t * x_8_addr = *fp
	memcpy(*fp, vfp_x8, vfp_end - vfp_x8);
	if(sign > 0) {
		*fp[65] ^= 0x00000040; 
		*fp[66] ^= 0x00000040; 
		*fp[68] ^= 0x00000040; 
		*fp[70] ^= 0x00000040; 
		*fp[103] ^= 0x00000040; 
		*fp[104] ^= 0x00000040; 
		*fp[105] ^= 0x00000040; 
		*fp[108] ^= 0x00000040; 
		*fp[113] ^= 0x00000040; 
		*fp[114] ^= 0x00000040; 
		*fp[117] ^= 0x00000040; 
		*fp[118] ^= 0x00000040; 
	}
	*fp += (vfp_end - vfp_x8) / 4;
	return x_8_addr;
}

insns_t* generate_size4_base_case(insns_t **fp, int sign) {
	insns_t * x_4_addr = *fp;
	memcpy(*fp, vfp_x4, vfp_x8 - vfp_x4);
	if(sign > 0) {
		*fp[36] ^= 0x00000040; 
		*fp[38] ^= 0x00000040; 
		*fp[43] ^= 0x00000040; 
		*fp[44] ^= 0x00000040;
	}
	*fp += (vfp_x8 - vfp_x4) / 4;
	return x_4_addr;
}


insns_t* generate_start_init(insns_t **fp, ffts_plan_t *p  ) {
	insns_t	* start = *fp;
	**fp = PUSH_LR(); fp++;
	**fp = 0xed2d8b10; fp++;

	ADDI(fp, 3, 1, 0);
	ADDI(fp, 7, 1, N);
	ADDI(fp, 5, 1, 2*N);
	ADDI(fp, 10, 7, 2*N);
	ADDI(fp, 4, 5, 2*N);
	ADDI(fp, 8, 10, 2*N);
	ADDI(fp, 6, 4, 2*N);
	ADDI(fp, 9, 8, 2*N);
	
  **fp = LDRI(12, 0, ((uint32_t)&p->offsets) - ((uint32_t)p)); *fp++; // load offsets into r12
//  *fp++ = LDRI(1, 0, 4); // load ws into r1
	ADDI(fp, 1, 0, 0);

	ADDI(fp, 0, 2, 0), // mov out into r0
	**fp = LDRI(2, 1, ((uint32_t)&p->ee_ws) - ((uint32_t)p)); *fp++; 
	MOVI(fp, 11, p->i0);
	return start;
}

insns_t * generate_start(insns_t **fp, ffts_plan_t * p, insns_t * x_4_addr, insns_t* x_8_addr, size_t leafN ,size_t N, size_t *pps) {
			memcpy(fp, vfp_e, vfp_o - vfp_e);
			if(sign > 0) {
				*fp[64] ^= 0x00000040; *fp[65] ^= 0x00000040; *fp[68] ^= 0x00000040; *fp[75] ^= 0x00000040;
				*fp[76] ^= 0x00000040; *fp[79] ^= 0x00000040; *fp[80] ^= 0x00000040; *fp[83] ^= 0x00000040;
				*fp[84] ^= 0x00000040; *fp[87] ^= 0x00000040; *fp[91] ^= 0x00000040; *fp[93] ^= 0x00000040;
			}
			*fp += (vfp_o - vfp_e) / 4;
		ADDI(fp, 2, 7, 0);
		ADDI(fp, 7, 9, 0);
		ADDI(fp, 9, 2, 0);

		ADDI(fp, 2, 8, 0);
		ADDI(fp, 8, 10, 0);
		ADDI(fp, 10, 2, 0);
	
		MOVI(fp, 11, (p->i1>0) ? p->i1 : 1);
		memcpy(*fp, vfp_o, vfp_x4 - vfp_o);
		if(sign > 0) {
			*fp[22] ^= 0x00000040; *fp[24] ^= 0x00000040; *fp[25] ^= 0x00000040; *fp[26] ^= 0x00000040;
			*fp[62] ^= 0x00000040; *fp[64] ^= 0x00000040; *fp[65] ^= 0x00000040; *fp[66] ^= 0x00000040;
		}
  		*fp += (vfp_x4 - vfp_o) / 4;
		
		ADDI(fp, 2, 3, 0);
		ADDI(fp, 3, 7, 0);
		ADDI(fp, 7, 2, 0);

		ADDI(fp, 2, 4, 0);
		ADDI(fp, 4, 8, 0);
		ADDI(fp, 8, 2, 0);
		
		ADDI(fp, 2, 5, 0);
		ADDI(fp, 5, 9, 0);
		ADDI(fp, 9, 2, 0);

		ADDI(fp, 2, 6, 0);
		ADDI(fp, 6, 10, 0);
		ADDI(fp, 10, 2, 0);

		ADDI(fp, 2, 9, 0);
		ADDI(fp, 9, 10, 0);
		ADDI(fp, 10, 2, 0);

		*fp = LDRI(2, 1, ((uint32_t)&p->ee_ws) - ((uint32_t)p)); fp++; 
	  MOVI(fp, 11, (p->i2>0) ? p->i2 : 1);
  	memcpy(*fp, vfp_e, vfp_o - vfp_e);
		if(sign > 0) {
			*fp[64] ^= 0x00000040; *fp[65] ^= 0x00000040; *fp[68] ^= 0x00000040; *fp[75] ^= 0x00000040;
			*fp[76] ^= 0x00000040; *fp[79] ^= 0x00000040; *fp[80] ^= 0x00000040; *fp[83] ^= 0x00000040;
			*fp[84] ^= 0x00000040; *fp[87] ^= 0x00000040; *fp[91] ^= 0x00000040; *fp[93] ^= 0x00000040;
		}
  	*fp += (vfp_o - vfp_e) / 4;
  **fp = LDRI(2, 1, ((uint32_t)&p->ws) - ((uint32_t)p)); *fp++; // load offsets into r12
	//ADDI(&fp, 2, 1, 0);
	MOVI(fp, 1, 0);
	
	// args: r0 - out
	//       r1 - N
	//       r2 - ws
//	ADDI(&fp, 3, 1, 0); // put N into r3 for counter

	int32_t pAddr = 0;
	int32_t pN = 0;
	int32_t pLUT = 0;
	count = 2;
	while(pps[0]) {
	
//	fprintf(stderr, "size %zu at %zu - diff %zu\n", pps[0], pps[1]*4, (pps[1]*4) - pAddr);
		if(!pN) {
			MOVI(fp, 1, pps[0]);
		}else{
  		if((pps[1]*4)-pAddr) ADDI(fp, 0, 0, (pps[1] * 4)- pAddr);
			if(pps[0] - pN) ADDI(fp, 1, 1, pps[0] - pN);
		}
		
		if(p->ws_is[__builtin_ctzl(pps[0]/leafN)-1]*8 - pLUT)
			ADDI(fp, 2, 2, p->ws_is[__builtin_ctzl(pps[0]/leafN)-1]*8 - pLUT); 


  	if(pps[0] == 2*leafN) {
        **fp = BL(*fp+2, x_4_addr); *fp++;
  	}else if(!pps[2]){
  	  //uint32_t *x_8_t_addr = fp;
    		**fp = BL(*fp+2, x_8_addr); *fp++;
  	}else{
    		**fp = BL(*fp+2, x_8_addr); *fp++;
  	}

		pAddr = pps[1] * 4;
		pN = pps[0];
		pLUT = p->ws_is[__builtin_ctzl(pps[0]/leafN)-1]*8;//LUT_offset(pps[0], leafN);
//	fprintf(stderr, "LUT offset for %d is %d\n", pN, pLUT); 
		count += 4;
		pps += 2;
	}
	
	/* This may need to be looked at to make sure it is correct */
	**fp++ = 0xecbd8b10;
	**fp++ = POP_LR(); count++;
}
