#include "segmenttriangleintersection.h"

/*---------------------------------------------------------------------
    'p': The segment lies wholly within the plane.
    'q': The q endpoint is on the plane (but not 'p').
    'r': The r endpoint is on the plane (but not 'p').
    '0': The segment lies strictly to one side or the other of the plane.
    '1': The segement intersects the plane, and 'p' does not hold.
---------------------------------------------------------------------*/
char SegmentTriangleIntersection::SegPlaneInt( tPointi T, tPointd q, tPointd r, tPointd p, int *m)
{
    tPointd N; double D;
    tPointd rq;
    double num, denom, t;
    int i;

    *m = PlaneCoeff( T, N, &D );
    num = D - Dot( q, N );
    SubVec( r, q, rq );
    denom = Dot( rq, N );

    if ( denom == 0.0 ) {  /* Segment is parallel to plane. */
       if ( num == 0.0 )   /* q is on plane. */
           return 'p';
       else
           return '0';
    }
    else
       t = num / denom;

    for( i = 0; i < DIM; i++ )
       p[i] = q[i] + t * ( r[i] - q[i] );

    if ( (0.0 < t) && (t < 1.0) )
         return '1';
    else if ( num == 0.0 )   /* t == 0 */
         return 'q';
    else if ( num == denom ) /* t == 1 */
         return 'r';
    else return '0';
}
/*---------------------------------------------------------------------
Computes N & D and returns index m of largest component.
---------------------------------------------------------------------*/
int	SegmentTriangleIntersection::PlaneCoeff( tPointi T, tPointd N, double *D )
{
    int i;
    double t;              /* Temp storage */
    double biggest = 0.0;  /* Largest component of normal vector. */
    int m = 0;             /* Index of largest component. */

    NormalVec( Vertices[T[0]], Vertices[T[1]], Vertices[T[2]], N );
    *D = Dot( Vertices[T[0]], N );

    /* Find the largest component of N. */
    for ( i = 0; i < DIM; i++ ) {
      t = fabs( N[i] );
      if ( t > biggest ) {
        biggest = t;
        m = i;
      }
    }
    return m;
}


/*---------------------------------------------------------------------
a - b ==> c.
---------------------------------------------------------------------*/
void SegmentTriangleIntersection::SubVec( tPointd a, tPointd b, tPointd c )
{
   int i;

   for( i = 0; i < DIM; i++ )
      c[i] = a[i] - b[i];
}

/*---------------------------------------------------------------------
Returns the dot product of the two input vectors.
---------------------------------------------------------------------*/
double SegmentTriangleIntersection::Dot( tPointd a, tPointd b )
{
    int i;
    double sum = 0.0;

    for( i = 0; i < DIM; i++ )
       sum += a[i] * b[i];

    return  sum;
}

/*---------------------------------------------------------------------
Compute the cross product of (b-a)x(c-a) and place into N.
---------------------------------------------------------------------*/
void SegmentTriangleIntersection::NormalVec( tPointd a, tPointd b, tPointd c, tPointd N )
{
    N[X] = ( c[Z] - a[Z] ) * ( b[Y] - a[Y] ) -
           ( b[Z] - a[Z] ) * ( c[Y] - a[Y] );
    N[Y] = ( b[Z] - a[Z] ) * ( c[X] - a[X] ) -
           ( b[X] - a[X] ) * ( c[Z] - a[Z] );
    N[Z] = ( b[X] - a[X] ) * ( c[Y] - a[Y] ) -
           ( b[Y] - a[Y] ) * ( c[X] - a[X] );
}



/* Assumption: p lies in the plane containing T.
    Returns a char:
     'V': the query point p coincides with a Vertex of triangle T.
     'E': the query point p is in the relative interior of an Edge of triangle T.
     'F': the query point p is in the relative interior of a Face of triangle T.
     '0': the query point p does not intersect (misses) triangle T.
*/

char SegmentTriangleIntersection::InTri3D( tPointi T, int m, tPointd p )
{
   int i;           /* Index for X,Y,Z           */
   int j;           /* Index for X,Y             */
   int k;           /* Index for triangle vertex */
   tPointd pp;      /* projected p */
   tPointd Tp[3];   /* projected T: three new vertices */

   /* Project out coordinate m in both p and the triangular face */
   j = 0;
   for ( i = 0; i < DIM; i++ ) {
     if ( i != m ) {    /* skip largest coordinate */
       pp[j] = p[i];
       for ( k = 0; k < 3; k++ )
	Tp[k][j] = Vertices[T[k]][i];
       j++;
     }
   }
   return( InTri2D( Tp, pp ) );
}

char SegmentTriangleIntersection::InTri2D( tPointd Tp[3], tPointd pp )
{
   int area0, area1, area2;

   /* compute three AreaSign() values for pp w.r.t. each edge of the face in 2D */
   area0 = AreaSign( pp, Tp[0], Tp[1] );
   area1 = AreaSign( pp, Tp[1], Tp[2] );
   area2 = AreaSign( pp, Tp[2], Tp[0] );

   if ( ( area0 == 0 ) && ( area1 > 0 ) && ( area2 > 0 ) ||
        ( area1 == 0 ) && ( area0 > 0 ) && ( area2 > 0 ) ||
        ( area2 == 0 ) && ( area0 > 0 ) && ( area1 > 0 ) )
     return 'E';

   if ( ( area0 == 0 ) && ( area1 < 0 ) && ( area2 < 0 ) ||
        ( area1 == 0 ) && ( area0 < 0 ) && ( area2 < 0 ) ||
        ( area2 == 0 ) && ( area0 < 0 ) && ( area1 < 0 ) )
     return 'E';

   if ( ( area0 >  0 ) && ( area1 > 0 ) && ( area2 > 0 ) ||
        ( area0 <  0 ) && ( area1 < 0 ) && ( area2 < 0 ) )
     return 'F';

   if ( ( area0 == 0 ) && ( area1 == 0 ) && ( area2 == 0 ) )
     fprintf( stderr, "Error in InTriD\n" ), exit(EXIT_FAILURE);

   if ( ( area0 == 0 ) && ( area1 == 0 ) ||
        ( area0 == 0 ) && ( area2 == 0 ) ||
        ( area1 == 0 ) && ( area2 == 0 ) )
     return 'V';

   else
     return '0';
}

int SegmentTriangleIntersection::AreaSign( tPointd a, tPointd b, tPointd c )
{
    double area2;

    area2 = ( b[0] - a[0] ) * (double)( c[1] - a[1] ) -
            ( c[0] - a[0] ) * (double)( b[1] - a[1] );

    /* The area should be an integer. */
    if      ( area2 >  0.5 ) return  1;
    else if ( area2 < -0.5 ) return -1;
    else                     return  0;
}

char SegmentTriangleIntersection::SegTriInt( tPointi T, tPointd q, tPointd r, tPointd p )
{
    int code = '?';
    int m = -1;

    code = SegPlaneInt( T, q, r, p, &m );

    if      ( code == '0')
       return '0';
    else if ( code == 'q')
       return InTri3D( T, m, q );
    else if ( code == 'r')
       return InTri3D( T, m, r );
    else if ( code == 'p' )
       return InPlane( T, m, q, r, p );
    else if ( code == '1' )
       return SegTriCross( T, q, r );
    else /* Error */
       return code;
}

char SegmentTriangleIntersection::InPlane( tPointi T, int m, tPointd q, tPointd r, tPointd p)
{
    /* NOT IMPLEMENTED */
    return 'p';
}

/*---------------------------------------------------------------------
The signed volumes of three tetrahedra are computed, determined
by the segment qr, and each edge of the triangle.
Returns a char:
   'v': the open segment includes a vertex of T.
   'e': the open segment includes a point in the relative interior of an edge
   of T.
   'f': the open segment includes a point in the relative interior of a face
   of T.
   '0': the open segment does not intersect triangle T.
---------------------------------------------------------------------*/

char SegmentTriangleIntersection::SegTriCross( tPointi T, tPointd q, tPointd r )
{
   double vol0, vol1, vol2;

   vol0 = VolumeSign( q, Vertices[ T[0] ], Vertices[ T[1] ], r );
   vol1 = VolumeSign( q, Vertices[ T[1] ], Vertices[ T[2] ], r );
   vol2 = VolumeSign( q, Vertices[ T[2] ], Vertices[ T[0] ], r );

   /* Same sign: segment intersects interior of triangle. */
   if ( ( ( vol0 > 0 ) && ( vol1 > 0 ) && ( vol2 > 0 ) ) ||
        ( ( vol0 < 0 ) && ( vol1 < 0 ) && ( vol2 < 0 ) ) )
      return 'f';

   /* Opposite sign: no intersection between segment and triangle */
   if ( ( ( vol0 > 0 ) || ( vol1 > 0 ) || ( vol2 > 0 ) ) &&
        ( ( vol0 < 0 ) || ( vol1 < 0 ) || ( vol2 < 0 ) ) )
      return '0';

   else if ( ( vol0 == 0 ) && ( vol1 == 0 ) && ( vol2 == 0 ) )
     fprintf( stderr, "Error 1 in SegTriCross\n" ), exit(EXIT_FAILURE);

   /* Two zeros: segment intersects vertex. */
   else if ( ( ( vol0 == 0 ) && ( vol1 == 0 ) ) ||
             ( ( vol0 == 0 ) && ( vol2 == 0 ) ) ||
             ( ( vol1 == 0 ) && ( vol2 == 0 ) ) )
      return 'v';

   /* One zero: segment intersects edge. */
   else if ( ( vol0 == 0 ) || ( vol1 == 0 ) || ( vol2 == 0 ) )
      return 'e';

   else
     fprintf( stderr, "Error 2 in SegTriCross\n" ), exit(EXIT_FAILURE);
}
#include <iostream>
double SegmentTriangleIntersection::VolumeSign( tPointd a, tPointd b, tPointd c, tPointd d )
{
   double vol;
   double ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz;
   double bxdx, bydy, bzdz, cxdx, cydy, czdz;

   ax = a[X];
   ay = a[Y];
   az = a[Z];
   bx = b[X];
   by = b[Y];
   bz = b[Z];
   cx = c[X];
   cy = c[Y];
   cz = c[Z];
   dx = d[X];
   dy = d[Y];
   dz = d[Z];

   bxdx=bx-dx;
   bydy=by-dy;
   bzdz=bz-dz;
   cxdx=cx-dx;
   cydy=cy-dy;
   czdz=cz-dz;
   vol =   (az-dz) * (bxdx*cydy - bydy*cxdx)
         + (ay-dy) * (bzdz*cxdx - bxdx*czdz)
         + (ax-dx) * (bydy*czdz - bzdz*cydy);

return vol;
}
