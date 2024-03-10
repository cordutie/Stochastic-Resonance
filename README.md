<div align="center">
  
# Stochastic Resonance

[**Rodrigo Cádiz**](https://rodrigocadiz.com/music/)<sup>1,2</sup> and [**Esteban Gutiérrez**](https://github.com/cordutie)<sup>3</sup>

<sup>1</sup> *Music Institute, Pontificia Universidad Católica de Chile* <br>
<sup>2</sup> *Department of Electrical Enginering, Pontificia Universidad Católica de Chile* <br>
<sup>3</sup> *Department of Information and Communications Technologies, Universitat Pompeu Fabra* <br>

<div align="left">

## Introduction

The phenomenon of Stochastic Resonance was first introduced by Benzi, Parisi, Sutera and Vulpiani [[1]](#1) in the context of a particular stochastic dynamical system, and was later formulated in many different contexts (see for example [[2]](#2)). As it is, this phenomenon shouldn't be understood as one model, but else as a technique to create models that allows to study different stochastic dynamical systems.

Stochastic resonance is not just a theoretical phenomenon, as it has been observed in various fields, including theoretical physics [[2]](#2), signal processing [[3]](#3), metrology [[5]](#5) and sensory biology [[6]](#6). Despite this, and its clear potential as a signal processing model, there are very few documented uses of this ideas in both sound synthesis and processing.

In this repository we present "Stochastic Resonance", a package for Max that implements real-time algorithms based on Stochastic Resonance techniques that we have found can be used in sound and music applications. This package was written using the [min-devkit](https://github.com/Cycling74/min-devkit), a software development kit to develop Max externals using modern C++ code. Due to this, we were able to take advantage of the raw power of C++ and ensured that the externals in the package run as efficiently and fast as possible.

## Contents

The repo consists on two folders containing the implementation
in MAX and some example patches recorded in video.

### 1. MAX external

In this folder everything related to the MAX external can be found.

- The subfolder **Builds** contains current builds for the external
for the Windows and MAC operative systems. A little tutorial on how
to run the external can also be found in this subfolder.

- The subfolder **Code** contains the necessary code to build the MAX
external in case that the current builds stopped working. A little
tutorial on how to build the MAX external can also be found in this
subfolder.

- The subfolder **Patches** contains several MAX files that can be used 
to easily manipulate the MAX external. 

### 2. Demos

In this folder, several video demos of the MAX external. Each demo 
contains a brief readme file containing a description of it and a series 
of patches to recreate the video demo locally.

## References

<a id="1">[1]</a> R. Benzi, A. Sutera, and A. Vulpiani, “The mechanism of stochastic resonance,” Journal of Physics A: Mathematical and General, vol. 14, no. 11, p. L453, Jan. 1981. DOI: 10.1088/0305-4470/14/11/006

<a id="2">[2]</a> L. Gammaitoni, P. Hänggi, P. Jung, and F. Marchesoni, “Stochastic resonance,” Rev. Mod. Phys., vol. 70, no. 1, pp. 223–287, Jan. 1998. DOI: 10.1103/RevModPhys.70.223

<a id="3">[3]</a> M. Ueda, “Improvement of signal-to-noise ratio by stochastic resonance in sigmoid function threshold systems, demonstrated using a CMOS inverter,” Physica A: Statistical Mechanics and its Applications, vol. 389, no. 10, pp. 1978–1985, 2010. DOI: 10.1016/j.physa.2010.01.035

<a id="4">[4]</a> A. Palonpon, J. Amistoso, J. Holdsworth, W. Garcia, and C. Saloma, “Measurement of weak transmittances by stochastic resonance,” Opt. Lett., vol. 23, no. 18, pp. 1480–1482, Sep. 1998. DOI: 10.1364/OL.23.001480

<a id="5">[5]</a> A. Palonpon, J. Amistoso, J. Holdsworth, W. Garcia, and C. Saloma, “Measurement of weak transmittances by stochastic resonance,” Opt. Lett., vol. 23, no. 18, pp. 1480–1482, Sep. 1998. DOI: 10.1364/OL.23.001480

<a id="6">[6]</a> J. J. Collins, C. C. Chow, and T. T. Imhoff, “Stochastic resonance without tuning,” Nature, vol. 376, no. 6537, pp. 236–238, Jul. 1995.
