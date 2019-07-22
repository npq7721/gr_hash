# Raptoreum Core
https://ritocoin.org/

# gr_hash
Source code for the gr hash function. You can use this with python (using the instructions below) or anywhere else you need to incorporate gr. For nomp, simply add this to your multi-hashing module and edit the bindings and rebuild.

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
  * Luke Pighetti for X16S
  * SUQA for X22i
  * Trevali for X21S
  * kryptoshi for the idea of merging the ideas of X22i with X16S.
  * barrystyle for pulling variants of cryptonight into one place.
  * Tri Nguyen (git id: npq7721) for putting GR logic together

## What is gr_hash ?
The cornerstone feature of our coin at launch is the new GR algorithm, inspired by x16R and X16S. The hashing algorithm begins with 16 algorithms shuffled and hashed in the manner prescribed by X16S, followed by 5 additional hashing algorithms: haval256, tiger, lyra2, gost512, and sha256. The inclusion of lyra2 brings numerous advantages, making parallelization of the algorithm practically impossible, with each step relying on the previous step having already been computed. It is a “friendly” algorithm that makes GPUs produce much less heat and uses less electricity during mining.


## What is Raptoreum?


 is a blockchain software development project designed to experiment with alternative and additional concepts with ideas based on those begun by the Ravencoin project.

Raptoreum launches with the spirit of community, cypherpunk culture and hacker ethics. Raptoreum is a fork of the Ravencoin codebase, which is an experimental blockchain and platform optimized for transferring assets, such as tokens, from one holder to another. The launch of Raptoreum offers several improvements to Ravencoin. First, a change in the proof-of-work mining algorithm, second, a commitment to keeping mining accessible to casual hobbyists, third, an addition for in wallet interest feature, and finally, an emphasis on the community-driven development of user friendly features and add-on utilities. The culture of Raptoreum will be of rapid software development and frequent releases of experimental features.

Raptoreum is intended to be a bazaar of ideas prioritizing security, user control, privacy, censorship resistance, and fair distribution of hashrate to all members of the cryptocurrency community.
