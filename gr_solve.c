#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "gr.h"

// baz

int main()
{
        uint8_t genesisdata[80] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0xcc,0xa6,0x6a,
                                    0x44,0xf8,0xbd,0x55,0x45,0xc3,0x16,0x4a,0x3a,0x76,0xda,0x50,0x39,0x53,0x28,0xc9,0x07,0x56,0x33,0x77,
                                    0x5b,0xc4,0xc8,0x79,0x8f,0xd6,0x77,0x2b,0x70,0x0d,0x21,0x5c,0xf0,0xff,0x0f,0x1e,0x00,0x00,0x00,0x00 };
        char inputdata[80];
        char outputhash[32];
        int i;
        uint32_t nonce = 0;
        uint32_t ncount = nonce;

        unsigned int starttimer = (int)time(NULL);

        while (true) {

           ++nonce;

           if(nonce % 4 == 0)
              printf("\r%08x",nonce);

           memcpy(inputdata,genesisdata,76);
           memcpy(inputdata+76,&nonce,4); 
           gr_hash((void*)inputdata,(void*)outputhash);
           uint32_t *target = *(uint32_t*)&outputhash[28];

           if (target < 0xfffff) {
              printf("\n");
              for (i=0; i<32; i++)
                 printf("%02hhx",outputhash[31-i]);
              printf("\n");
           }

           if ((time(NULL)-starttimer) > 1) {
              uint32_t hashes = nonce - ncount;
              printf("\n\n\n%u hashes/sec\n", hashes);
              ncount = nonce;
              starttimer = time(NULL);
           }
       }
}
