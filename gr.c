#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sph/extra.h"
#include "sph/sph_blake.h"
#include "sph/sph_bmw.h"
#include "sph/sph_groestl.h"
#include "sph/sph_jh.h"
#include "sph/sph_keccak.h"
#include "sph/sph_skein.h"
#include "sph/sph_luffa.h"
#include "sph/sph_cubehash.h"
#include "sph/sph_shavite.h"
#include "sph/sph_simd.h"
#include "sph/sph_echo.h"
#include "sph/sph_hamsi.h"
#include "sph/sph_fugue.h"
#include "sph/sph_shabal.h"
#include "sph/sph_whirlpool.h"
#include "sph/sph_sha2.h"
#include "sph/sph_haval.h"
#include "sph/sph_tiger.h"
#include "sph/lyra2.h"
#include "sph/gost_streebog.h"
#include "cryptonote/cryptonight_dark.h"
#include "cryptonote/cryptonight_dark_lite.h"
#include "cryptonote/cryptonight_fast.h"
#include "cryptonote/cryptonight.h"
#include "cryptonote/cryptonight_lite.h"
#include "cryptonote/cryptonight_soft_shell.h"
#include "cryptonote/cryptonight_turtle.h"
#include "cryptonote/cryptonight_turtle_lite.h"

enum Algo {
        BLAKE = 0,
        BMW,
        GROESTL,
        JH,
        KECCAK,
        SKEIN,
        LUFFA,
        CUBEHASH,
        SHAVITE,
        SIMD,
        ECHO,
        HAMSI,
        FUGUE,
        SHABAL,
        WHIRLPOOL,
        HASH_FUNC_COUNT
};

enum CNAlgo {
	CNDark = 0,
	CNDarklite,
	CNFast,
	CNLite,
	CNTurtle,
	CNTurtlelite,
	CN_HASH_FUNC_COUNT
};

static void getAlgoString(const uint8_t* prevblock, char *output, int algoCount)
{
	char *sptr = output;
	int j;
	bool selectedAlgo[algoCount];
	for(int z=0; z < algoCount; z++) {
	   selectedAlgo[z] = false;
	}
	int selectedCount = 0;
	for (j = 0; j < 64; j++) {
		char b = (63 - j) >> 1; // 64 ascii hex chars, reversed
		uint8_t algoDigit = ((j & 1) ? prevblock[b] & 0xF : prevblock[b] >> 4) % algoCount;
		if(!selectedAlgo[algoDigit]) {
			selectedAlgo[algoDigit] = true;
			selectedCount++;
		} else {
			continue;
		}
		if(selectedCount == algoCount) {
			break;
		}
		if (algoDigit >= 10)
			sprintf(sptr, "%c", 'A' + (algoDigit - 10));
		else
			sprintf(sptr, "%u", (uint32_t) algoDigit);
		sptr++;
	}
	if(selectedCount < algoCount) {
		for(uint8_t i = 0; i < algoCount; i++) {
			if(!selectedAlgo[i]) {
				if (i >= 10)
					sprintf(sptr, "%c", 'A' + (i - 10));
				else
					sprintf(sptr, "%u", (uint32_t) i);
				sptr++;
			}
		}
	}
	*sptr = '\0';
}

void gr_hash(const char* input, char* output) {
	uint32_t hash[64/4];
	char hashOrder[16] = { 0};
	char cnHashOrder[7] = { 0};

	sph_blake512_context ctx_blake;
	sph_bmw512_context ctx_bmw;
	sph_groestl512_context ctx_groestl;
	sph_jh512_context ctx_jh;
	sph_keccak512_context ctx_keccak;
	sph_skein512_context ctx_skein;
	sph_luffa512_context ctx_luffa;
	sph_cubehash512_context ctx_cubehash;
	sph_shavite512_context ctx_shavite;
	sph_simd512_context ctx_simd;
	sph_echo512_context ctx_echo;
	sph_hamsi512_context ctx_hamsi;
	sph_fugue512_context ctx_fugue;
	sph_shabal512_context ctx_shabal;
	sph_whirlpool_context ctx_whirlpool;
	sph_haval256_5_context ctx_haval;
	sph_tiger_context ctx_tiger;
	sph_gost512_context ctx_gost;
	sph_sha256_context ctx_sha;

	void *in = (void*) input;
	int size = 80;

	getAlgoString(&input[4], hashOrder, 15);
	getAlgoString(&input[4], cnHashOrder, 6);
	int i;
	for (i = 0; i < 18; i++)
	{
		uint8_t algo;
		uint8_t cnAlgo;
		int coreSelection;
		int cnSelection = -1;
		if(i < 5) {
			coreSelection = i;
		} else if(i < 11) {
			coreSelection = i-1;
		} else {
			coreSelection = i-2;
		}
		if(i==5) {
			coreSelection = -1;
			cnSelection = 0;
		}
		if(i==11) {
			coreSelection = -1;
			cnSelection = 1;
		}
		if(i==17) {
			coreSelection = -1;
			cnSelection = 2;
		}
		if(coreSelection >= 0) {
			const char elem = hashOrder[coreSelection];
			algo = elem >= 'A' ? elem - 'A' + 10 : elem - '0';
		} else {
			algo = 16; // skip core hashing for this loop iteration
		}
		if(cnSelection >=0) {
			const char cnElem = cnHashOrder[cnSelection];
			cnAlgo = cnElem >= 'A' ? cnElem - 'A' + 10 : cnElem - '0';
		} else {
			cnAlgo = 14; // skip cn hashing for this loop iteration
		}
		//selection cnAlgo. if a CN algo is selected then core algo will not be selected
		switch(cnAlgo)
		{
		 case CNDark:
			cryptonightdark_hash(in, hash, size, 1);
			break;
		 case CNDarklite:
			cryptonightdarklite_hash(in, hash, size, 1);
			break;
		 case CNFast:
			cryptonightfast_hash(in, hash, size, 1);
			break;
		 case CNLite:
			cryptonightlite_hash(in, hash, size, 1);
			break;
		 case CNTurtle:
			cryptonightturtle_hash(in, hash, size, 1);
			break;
		 case CNTurtlelite:
			cryptonightturtlelite_hash(in, hash, size, 1);
			break;
		}
		//selection core algo
		switch (algo) {
		case BLAKE:
				sph_blake512_init(&ctx_blake);
				sph_blake512(&ctx_blake, in, size);
				sph_blake512_close(&ctx_blake, hash);
				break;
		case BMW:
				sph_bmw512_init(&ctx_bmw);
				sph_bmw512(&ctx_bmw, in, size);
				sph_bmw512_close(&ctx_bmw, hash);
				break;
		case GROESTL:
				sph_groestl512_init(&ctx_groestl);
				sph_groestl512(&ctx_groestl, in, size);
				sph_groestl512_close(&ctx_groestl, hash);
				break;
		case SKEIN:
				sph_skein512_init(&ctx_skein);
				sph_skein512(&ctx_skein, in, size);
				sph_skein512_close(&ctx_skein, hash);
				break;
		case JH:
				sph_jh512_init(&ctx_jh);
				sph_jh512(&ctx_jh, in, size);
				sph_jh512_close(&ctx_jh, hash);
				break;
		case KECCAK:
				sph_keccak512_init(&ctx_keccak);
				sph_keccak512(&ctx_keccak, in, size);
				sph_keccak512_close(&ctx_keccak, hash);
				break;
		case LUFFA:
				sph_luffa512_init(&ctx_luffa);
				sph_luffa512(&ctx_luffa, in, size);
				sph_luffa512_close(&ctx_luffa, hash);
				break;
		case CUBEHASH:
				sph_cubehash512_init(&ctx_cubehash);
				sph_cubehash512(&ctx_cubehash, in, size);
				sph_cubehash512_close(&ctx_cubehash, hash);
				break;
		case SHAVITE:
				sph_shavite512_init(&ctx_shavite);
				sph_shavite512(&ctx_shavite, in, size);
				sph_shavite512_close(&ctx_shavite, hash);
				break;
		case SIMD:
				sph_simd512_init(&ctx_simd);
				sph_simd512(&ctx_simd, in, size);
				sph_simd512_close(&ctx_simd, hash);
				break;
		case ECHO:
				sph_echo512_init(&ctx_echo);
				sph_echo512(&ctx_echo, in, size);
				sph_echo512_close(&ctx_echo, hash);
				break;
		case HAMSI:
				sph_hamsi512_init(&ctx_hamsi);
				sph_hamsi512(&ctx_hamsi, in, size);
				sph_hamsi512_close(&ctx_hamsi, hash);
				break;
		case FUGUE:
				sph_fugue512_init(&ctx_fugue);
				sph_fugue512(&ctx_fugue, in, size);
				sph_fugue512_close(&ctx_fugue, hash);
				break;
		case SHABAL:
				sph_shabal512_init(&ctx_shabal);
				sph_shabal512(&ctx_shabal, in, size);
				sph_shabal512_close(&ctx_shabal, hash);
				break;
		case WHIRLPOOL:
				sph_whirlpool_init(&ctx_whirlpool);
				sph_whirlpool(&ctx_whirlpool, in, size);
				sph_whirlpool_close(&ctx_whirlpool, hash);
				break;
		}
		in = (void*) hash;
		size = 64;
	}
	memcpy(output, hash, 32);
}
