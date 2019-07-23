from distutils.core import setup, Extension

gr_hash_module = Extension('gr_hash',
                               sources = ['gr_module.c',
                                          'gr.c',
                                          'sph/extra.c',
                                          'sph/blake.c',
                                          'sph/echo.c', 
                                          'sph/groestl.c',  
                                          'sph/haval.c',    
                                          'sph/keccak.c',  
                                          'sph/shavite.c',  
                                          'sph/bmw.c',  
                                          'sph/fugue.c',
                                          'sph/hamsi.c',    
                                          'sph/luffa.c',   
                                          'sph/simd.c',
                                          'sph/sha2.c',
                                          'sph/sph_sha2.c',
                                          'sph/sph_sha2big.c',
                                          'sph/whirlpool.c',
                                          'sph/cubehash.c',  
                                          'sph/gost_streebog.c',  
                                          'sph/jh.c',  
                                          'sph/sponge.c',
                                          'sph/lyra2.c',   
                                          'sph/shabal.c',  
                                          'sph/skein.c', 
                                          'sph/tiger.c',
                                          'cryptonote/cryptonight_dark_lite.c',
                                          'cryptonote/cryptonight_dark.c',
                                          'cryptonote/cryptonight_fast.c',
                                          'cryptonote/cryptonight_lite.c',
                                          'cryptonote/cryptonight_soft_shell.c',
                                          'cryptonote/cryptonight_turtle_lite.c',
                                          'cryptonote/cryptonight_turtle.c',
                                          'cryptonote/cryptonight.c',
                                          'cryptonote/crypto/aesb.c',
                                          'cryptonote/crypto/c_blake256.c',
                                          'cryptonote/crypto/c_groestl.c',
                                          'cryptonote/crypto/c_jh.c',
                                          'cryptonote/crypto/c_keccak.c',
                                          'cryptonote/crypto/c_skein.c',
                                          'cryptonote/crypto/hash.c',
                                          'cryptonote/crypto/oaes_lib.c',
                                          'cryptonote/crypto/wild_keccak.cpp'],
                            include_dirs=['.', './sph', './cryptonote', 
                                          './cryptonote/crypto'])

setup (name = 'gr_hash',
       version = '1.0',
       ext_modules = [gr_hash_module])
