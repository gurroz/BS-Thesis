#ifndef SEGMENTTRIANGLEINTERSECTION_H
#define SEGMENTTRIANGLEINTERSECTION_H

/*
This code is described in "Computational Geometry in C" (Second Edition),
Chapter 7.  It is not written to be comprehensible without the
explanation in that book.

Compile:    gcc -o inhedron inhedron.c -lm
Run (e.g.): inhedron < i.8

Written by Joseph O'Rourke, with contributions by Min Xu.
Last modified: April 1998
Questions to orourke@cs.smith.edu.
--------------------------------------------------------------------
This code is Copyright 1998 by Joseph O'Rourke.  It may be freely
redistributed in its entirety provided that this copyright notice is
not removed.
--------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define EXIT_FAILURE 1
#define X 0
#define Y 1
#define Z 2
#define MAX_INT   2147483647 
#define FALSE	0
#define TRUE	1

#define DIM 3                  /* Dimension of points */
typedef int    tPointi[DIM];   /* Type integer point */
typedef double tPointd[DIM];   /* Type double point */
#define PMAX 10000             /* Max # of pts */

class SegmentTriangleIntersection{
public:
tPointd Vertices[PMAX];        /* All the points */


/*---------------------------------------------------------------------
Function prototypes.
---------------------------------------------------------------------*/
char    SegPlaneInt( tPointi Triangle, tPointd q, tPointd r, tPointd p, int *m );
int     PlaneCoeff( tPointi T, tPointd N, double *D );
void    NormalVec( tPointd q, tPointd b, tPointd c, tPointd N );
double  Dot( tPointd q, tPointd d );
void    SubVec( tPointd q, tPointd b, tPointd c );
char    InTri3D( tPointi T, int m, tPointd p );
char    InTri2D( tPointd Tp[3], tPointd pp );
int     AreaSign( tPointd q, tPointd b, tPointd c );
char    SegTriInt( tPointi Triangle, tPointd q, tPointd r, tPointd p );
char    InPlane( tPointi Triangle, int m, tPointd q, tPointd r, tPointd p);
double  VolumeSign( tPointd a, tPointd b, tPointd c, tPointd d );
char    SegTriCross( tPointi Triangle, tPointd q, tPointd r );
int  	InBox( tPointi q, tPointi bmin, tPointi bmax );
char 	BoxTest ( int n, tPointi a, tPointi b );
void 	PrintPoint( tPointi q );
};
#endif
