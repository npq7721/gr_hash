# Raptoreum Core
https://raptoreum.com/

# gr_hash
Source code for the gr hash function. You use this with python (using the instructions below) or anywhere else you need to incorporate gr. For nomp, simply add this to your multi-hashing module and edit the bindings and rebuild.

## Prerequisites for python:

```
sudo apt-get install python-dev
```

## Installation for python:

To install this module, clone this repository and run:

```
python setup.py install
```

You can verify the installation by running:

```
python test.py
```

## Credits

  * Ravencoin for X16R
  * barrystyle for pulling variants of cryptonight into one place.
  * Tri Nguyen (git id: npq7721) for putting GR logic together

## What is gr_hash ?
GhostRider is a combination of known mining technologies and methodologies from x16r (Raven) and CryptoNight (Monero). X16r provides a randomness to an existing hash chaining methodology for mining, it lacks a memory requirement which means asics can potentially gain significant advantages over gpus. CryptoNight, on other hand has features that require cpu/gpu memory which makes it harder for asics to gain a significant advantage over cpu/gpu, but it lacks the randomness that x16r has.
Over the recent year, the Monero team committed to combat asics by forking CryptoNight to add more variables to its memory requirements, as well as hashing methodology. However, each fork’s hashing method remains static.
## GhostRider methodology:
With the realization of the value that the x16r randomness provides in battling the curve of asic efficiency combined with the impact of a high memory requirement. The concept of GhostRider was born by combining both methodologies together by randomly selecting 15 different core base algorithms and mixing them with 3 different random variants of Cryptonight hashing. These algorithms are divided into 3 groups of 5 random order core algorithms followed by 1 random order CN variant. All 15 order core algorithms are random but not no single algorithm being repeated in the same chain. The same goes for the order of CN derivatives.

## What is Raptoreum?


It is a blockchain software development project designed to experiment with alternative and additional concepts with ideas based on those begun by the Ravencoin project.

Raptoreum launches with the spirit of community, cypherpunk culture and hacker ethics. Raptoreum is a fork of the Ravencoin codebase, which is an experimental blockchain and platform optimized for transferring assets, such as tokens, from one holder to another. The launch of Raptoreum offers several improvements to Ravencoin. First, a change in the proof-of-work mining algorithm, second, a commitment to keeping mining accessible to casual hobbyists, third, an addition for in wallet interest feature, and finally, an emphasis on the community-driven development of user friendly features and add-on utilities. The culture of Raptoreum will be of rapid software development and frequent releases of experimental features.

Raptoreum is intended to be a full blown crypto ecosystem prioritizing transparency, security, user control, privacy, censorship resistance, and a fair distribution of hashrate to all members of the cryptocurrency community.
