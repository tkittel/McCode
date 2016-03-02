// GENERATED CODE --- DO NOT EDIT ---
// Code is produced by sasmodels.gen from sasmodels/models/MODEL.c

#ifdef __OPENCL_VERSION__
# define USE_OPENCL
#endif

#define USE_KAHAN_SUMMATION 0

// If opencl is not available, then we are compiling a C function
// Note: if using a C++ compiler, then define kernel as extern "C"
#ifndef USE_OPENCL
#  ifdef __cplusplus
     #include <cstdio>
     #include <cmath>
     using namespace std;
     #if defined(_MSC_VER)
     #   define kernel extern "C" __declspec( dllexport )
         inline float trunc(float x) { return x>=0?floor(x):-floor(-x); }
	 inline float fmin(float x, float y) { return x>y ? y : x; }
	 inline float fmax(float x, float y) { return x<y ? y : x; }
     #else
     #   define kernel extern "C"
     #endif
     inline void SINCOS(float angle, float &svar, float &cvar) { svar=sin(angle); cvar=cos(angle); }
#  else
     #include <stdio.h>
     #include <tgmath.h> // C99 type-generic math, so sin(float) => sinf
     // MSVC doesn't support C99, so no need for dllexport on C99 branch
     #define kernel
     #define SINCOS(angle,svar,cvar) do {const float _t_=angle; svar=sin(_t_);cvar=cos(_t_);} while (0)
#  endif
#  define global
#  define local
#  define constant const
// OpenCL powr(a,b) = C99 pow(a,b), b >= 0
// OpenCL pown(a,b) = C99 pow(a,b), b integer
#  define powr(a,b) pow(a,b)
#  define pown(a,b) pow(a,b)
#else
#  ifdef USE_SINCOS
#    define SINCOS(angle,svar,cvar) svar=sincos(angle,&cvar)
#  else
#    define SINCOS(angle,svar,cvar) do {const float _t_=angle; svar=sin(_t_);cvar=cos(_t_);} while (0)
#  endif
#endif

// Standard mathematical constants:
//   M_E, M_LOG2E, M_LOG10E, M_LN2, M_LN10, M_PI, M_PI_2=pi/2, M_PI_4=pi/4,
//   M_1_PI=1/pi, M_2_PI=2/pi, M_2_SQRTPI=2/sqrt(pi), SQRT2, SQRT1_2=sqrt(1/2)
// OpenCL defines M_constant_F for float constants, and nothing if float
// is not enabled on the card, which is why these constants may be missing
#ifndef M_PI
#  define M_PI 3.141592653589793f
#endif
#ifndef M_PI_2
#  define M_PI_2 1.570796326794897f
#endif
#ifndef M_PI_4
#  define M_PI_4 0.7853981633974483f
#endif

// Non-standard pi/180, used for converting between degrees and radians
#ifndef M_PI_180
#  define M_PI_180 0.017453292519943295f
#endif


#define VOLUME_PARAMETERS effect_radius
#define VOLUME_WEIGHT_PRODUCT effect_radius_w
#define VOLUME_PARAMETER_DECLARATIONS float effect_radius
#define IQ_KERNEL_NAME stickyhardsphere_Iq
#define IQ_PARAMETERS effect_radius, volfraction, perturb, stickiness
#define IQ_FIXED_PARAMETER_DECLARATIONS const float scale, \
    const float background, \
    const float volfraction, \
    const float perturb, \
    const float stickiness
#define IQ_WEIGHT_PRODUCT effect_radius_w
#define IQ_DISPERSION_LENGTH_DECLARATIONS const int Neffect_radius
#define IQ_DISPERSION_LENGTH_SUM Neffect_radius
#define IQ_OPEN_LOOPS     for (int effect_radius_i=0; effect_radius_i < Neffect_radius; effect_radius_i++) { \
      const float effect_radius = loops[2*(effect_radius_i)]; \
      const float effect_radius_w = loops[2*(effect_radius_i)+1];
#define IQ_CLOSE_LOOPS     }
#define IQ_PARAMETER_DECLARATIONS float effect_radius, float volfraction, float perturb, float stickiness
#define IQXY_KERNEL_NAME stickyhardsphere_Iqxy
#define IQXY_PARAMETERS effect_radius, volfraction, perturb, stickiness
#define IQXY_FIXED_PARAMETER_DECLARATIONS const float scale, \
    const float background, \
    const float volfraction, \
    const float perturb, \
    const float stickiness
#define IQXY_WEIGHT_PRODUCT effect_radius_w
#define IQXY_DISPERSION_LENGTH_DECLARATIONS const int Neffect_radius
#define IQXY_DISPERSION_LENGTH_SUM Neffect_radius
#define IQXY_OPEN_LOOPS     for (int effect_radius_i=0; effect_radius_i < Neffect_radius; effect_radius_i++) { \
      const float effect_radius = loops[2*(effect_radius_i)]; \
      const float effect_radius_w = loops[2*(effect_radius_i)+1];
#define IQXY_CLOSE_LOOPS     }
#define IQXY_PARAMETER_DECLARATIONS float effect_radius, float volfraction, float perturb, float stickiness

float form_volume(VOLUME_PARAMETER_DECLARATIONS);
float form_volume(VOLUME_PARAMETER_DECLARATIONS) {
    
    return 1.0f;
    
}


float Iq(float q, IQ_PARAMETER_DECLARATIONS);
float Iq(float q, IQ_PARAMETER_DECLARATIONS) {
    
    float onemineps,eta;
    float sig,aa,etam1,etam1sq,qa,qb,qc,radic;
    float lam,lam2,test,mu,alpha,beta;
    float kk,k2,k3,ds,dc,aq1,aq2,aq3,aq,bq1,bq2,bq3,bq,sq;

    onemineps = 1.0f-perturb;
    eta = volfraction/onemineps/onemineps/onemineps;

    sig = 2.0f * effect_radius;
    aa = sig/onemineps;
    etam1 = 1.0f - eta;
    etam1sq=etam1*etam1;
    //C
    //C  SOLVE QUADRATIC FOR LAMBDA
    //C
    qa = eta/12.0f;
    qb = -1.0f*(stickiness + eta/etam1);
    qc = (1.0f + eta/2.0f)/etam1sq;
    radic = qb*qb - 4.0f*qa*qc;
    if(radic<0) {
        //if(x>0.01f && x<0.015f)
        //    Print "Lambda unphysical - both roots imaginary"
        //endif
        return(-1.0f);
    }
    //C   KEEP THE SMALLER ROOT, THE LARGER ONE IS UNPHYSICAL
    lam = (-1.0f*qb-sqrt(radic))/(2.0f*qa);
    lam2 = (-1.0f*qb+sqrt(radic))/(2.0f*qa);
    if(lam2<lam) {
        lam = lam2;
    }
    test = 1.0f + 2.0f*eta;
    mu = lam*eta*etam1;
    if(mu>test) {
        //if(x>0.01f && x<0.015f)
        // Print "Lambda unphysical mu>test"
        //endif
        return(-1.0f);
    }
    alpha = (1.0f + 2.0f*eta - mu)/etam1sq;
    beta = (mu - 3.0f*eta)/(2.0f*etam1sq);
    //C
    //C   CALCULATE THE STRUCTURE FACTOR
    //C
    kk = q*aa;
    k2 = kk*kk;
    k3 = kk*k2;
    SINCOS(kk,ds,dc);
    //ds = sin(kk);
    //dc = cos(kk);
    aq1 = ((ds - kk*dc)*alpha)/k3;
    aq2 = (beta*(1.0f-dc))/k2;
    aq3 = (lam*ds)/(12.0f*kk);
    aq = 1.0f + 12.0f*eta*(aq1+aq2-aq3);
    //
    bq1 = alpha*(0.5f/kk - ds/k2 + (1.0f - dc)/k3);
    bq2 = beta*(1.0f/kk - ds/k2);
    bq3 = (lam/12.0f)*((1.0f - dc)/kk);
    bq = 12.0f*eta*(bq1+bq2-bq3);
    //
    sq = 1.0f/(aq*aq +bq*bq);

    return(sq);

}


float Iqxy(float qx, float qy, IQXY_PARAMETER_DECLARATIONS);
float Iqxy(float qx, float qy, IQXY_PARAMETER_DECLARATIONS) {
    
    return Iq(sqrt(qx*qx+qy*qy), IQ_PARAMETERS);
    
}


/*
    ##########################################################
    #                                                        #
    #   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   #
    #   !!                                              !!   #
    #   !!  KEEP THIS CODE CONSISTENT WITH KERNELPY.PY  !!   #
    #   !!                                              !!   #
    #   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   #
    #                                                        #
    ##########################################################
*/

#ifdef IQ_KERNEL_NAME
kernel void IQ_KERNEL_NAME(
    global const float *q,
    global float *result,
    const int Nq,
#ifdef IQ_OPEN_LOOPS
  #ifdef USE_OPENCL
    global float *loops_g,
  #endif
    local float *loops,
    const float cutoff,
    IQ_DISPERSION_LENGTH_DECLARATIONS,
#endif
    IQ_FIXED_PARAMETER_DECLARATIONS
    )
{
#ifdef USE_OPENCL
  #ifdef IQ_OPEN_LOOPS
  // copy loops info to local memory
  event_t e = async_work_group_copy(loops, loops_g, (IQ_DISPERSION_LENGTH_SUM)*2, 0);
  wait_group_events(1, &e);
  #endif

  int i = get_global_id(0);
  if (i < Nq)
#else
  #pragma omp parallel for
  for (int i=0; i < Nq; i++)
#endif
  {
    const float qi = q[i];
#ifdef IQ_OPEN_LOOPS
    float ret=0.0f, norm=0.0f;
  #ifdef VOLUME_PARAMETERS
    float vol=0.0f, norm_vol=0.0f;
  #endif
    IQ_OPEN_LOOPS
    //for (int radius_i=0; radius_i < Nradius; radius_i++) {
    //  const float radius = loops[2*(radius_i)];
    //  const float radius_w = loops[2*(radius_i)+1];

    const float weight = IQ_WEIGHT_PRODUCT;
    if (weight > cutoff) {
      const float scattering = Iq(qi, IQ_PARAMETERS);
      // allow kernels to exclude invalid regions by returning NaN
      if (!isnan(scattering)) {
        ret += weight*scattering;
        norm += weight;
      #ifdef VOLUME_PARAMETERS
        const float vol_weight = VOLUME_WEIGHT_PRODUCT;
        vol += vol_weight*form_volume(VOLUME_PARAMETERS);
        norm_vol += vol_weight;
      #endif
      }
    //else { printf("exclude qx,qy,I:%g,%g,%g\n",qi,scattering); }
    }
    IQ_CLOSE_LOOPS
  #ifdef VOLUME_PARAMETERS
    if (vol*norm_vol != 0.0f) {
      ret *= norm_vol/vol;
    }
  #endif
    result[i] = scale*ret/norm+background;
#else
    result[i] = scale*Iq(qi, IQ_PARAMETERS) + background;
#endif
  }
}
#endif


#ifdef IQXY_KERNEL_NAME
kernel void IQXY_KERNEL_NAME(
    global const float *qx,
    global const float *qy,
    global float *result,
    const int Nq,
#ifdef IQXY_OPEN_LOOPS
  #ifdef USE_OPENCL
    global float *loops_g,
  #endif
    local float *loops,
    const float cutoff,
    IQXY_DISPERSION_LENGTH_DECLARATIONS,
#endif
    IQXY_FIXED_PARAMETER_DECLARATIONS
    )
{
#ifdef USE_OPENCL
  #ifdef IQXY_OPEN_LOOPS
  // copy loops info to local memory
  event_t e = async_work_group_copy(loops, loops_g, (IQXY_DISPERSION_LENGTH_SUM)*2, 0);
  wait_group_events(1, &e);
  #endif

  int i = get_global_id(0);
  if (i < Nq)
#else
  #pragma omp parallel for
  for (int i=0; i < Nq; i++)
#endif
  {
    const float qxi = qx[i];
    const float qyi = qy[i];
    #if USE_KAHAN_SUMMATION
    float accumulated_error = 0.0f;
    #endif
#ifdef IQXY_OPEN_LOOPS
    float ret=0.0f, norm=0.0f;
    #ifdef VOLUME_PARAMETERS
    float vol=0.0f, norm_vol=0.0f;
    #endif
    IQXY_OPEN_LOOPS
    //for (int radius_i=0; radius_i < Nradius; radius_i++) {
    //  const float radius = loops[2*(radius_i)];
    //  const float radius_w = loops[2*(radius_i)+1];

    const float weight = IQXY_WEIGHT_PRODUCT;
    if (weight > cutoff) {

      const float scattering = Iqxy(qxi, qyi, IQXY_PARAMETERS);
      if (!isnan(scattering)) { // if scattering is bad, exclude it from sum
      //if (scattering >= 0.0f) { // scattering cannot be negative
        // TODO: use correct angle for spherical correction
        // Definition of theta and phi are probably reversed relative to the
        // equation which gave rise to this correction, leading to an
        // attenuation of the pattern as theta moves through pi/2.f  Either
        // reverse the meanings of phi and theta in the forms, or use phi
        // rather than theta in this correction.  Current code uses cos(theta)
        // so that values match those of sasview.
      #if defined(IQXY_HAS_THETA) // && 0
        const float spherical_correction
          = (Ntheta>1 ? fabs(cos(M_PI_180*theta))*M_PI_2:1.0f);
        const float next = spherical_correction * weight * scattering;
      #else
        const float next = weight * scattering;
      #endif
      #if USE_KAHAN_SUMMATION
        const float y = next - accumulated_error;
        const float t = ret + y;
        accumulated_error = (t - ret) - y;
        ret = t;
      #else
        ret += next;
      #endif
        norm += weight;
      #ifdef VOLUME_PARAMETERS
        const float vol_weight = VOLUME_WEIGHT_PRODUCT;
        vol += vol_weight*form_volume(VOLUME_PARAMETERS);
      #endif
        norm_vol += vol_weight;
      }
      //else { printf("exclude qx,qy,I:%g,%g,%g\n",qi,scattering); }
    }
    IQXY_CLOSE_LOOPS
  #ifdef VOLUME_PARAMETERS
    if (vol*norm_vol != 0.0f) {
      ret *= norm_vol/vol;
    }
  #endif
    result[i] = scale*ret/norm+background;
#else
    result[i] = scale*Iqxy(qxi, qyi, IQXY_PARAMETERS) + background;
#endif
  }
}
#endif
