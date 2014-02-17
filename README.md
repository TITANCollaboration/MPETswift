swift
=====

*swift* is a program to generate stored waveform inverse Fourier transform (SWIFT) signals for cleaning unwanted contaminants from a Penning trap. It can often happen that there are multiple species delivered in the rare-isotope beam, with the likelihood increasing as we move heavier in mass. The task of identifying each contaminant is tedious, and in some cases we can't even identify all of them. SWIFT eliminates the trial and error in the contaminant guessing game because it can clean a wide range of frequencies at once.

Installing
==========

Running *make* should compile a program called 'swift'. There is an install command in the makefile, which will copy the compiled binary into a directory called '~/local/bin'.

Compiling
=========

There are several dependancies that are required to compile swift:

* boost
* fftw
* gsl

fftw and gsl libraries provide the fft algorithms. boost is required for the network communication to the afg, program options parser, and some math functions.
