#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double real_type;

static inline real_type to_radians(real_type d)
{
  return d * M_PI / 180;
}


// references
// . potential kinetic energy
// http://montblancsciences.free.fr/premiere/physique/cours/p07.htm
// . potential elastic energy
// http://en.wikipedia.org/wiki/Potential_energy#Elastic_potential_energy

static real_type CONFIG_K; // spring constant, in newton/m-1. the more the stiffer.
static real_type CONFIG_X; // spring displacement in meters
static real_type CONFIG_M; // mass in newtons. 10 newtons ~= 1kg
static real_type CONFIG_H; // height in meters
static real_type CONFIG_A; // angle in radians 

static void setup
(real_type k, real_type x, real_type m, real_type h, real_type a)
{
  CONFIG_K = k;
  CONFIG_X = x;
  CONFIG_M = m;
  CONFIG_H = h;
  CONFIG_A = a;
}

static inline real_type compute_v(void)
{
  // compute the velocity based on elasticity kinetic energy equivalence
  static const real_type xx = CONFIG_X * CONFIG_X;
  const real_type v = ::sqrt(CONFIG_K * xx / CONFIG_M);
  // printf("v: %lf\n", v);
  // return v;
  return v * 75 / 16;
}

static inline real_type compute_vh(real_type v)
{
  return v * ::cos(CONFIG_A);
}

static inline real_type compute_vv(real_type v)
{
  return v * ::sin(CONFIG_A);
}

static inline real_type compute_delta(void)
{
  const real_type vv = compute_vv(compute_v());
  return vv * vv + 19.6 * CONFIG_H;
}

static inline real_type compute_t(void)
{
  const real_type delta = compute_delta();
  if (delta < 0)
  {
    printf("the eq. has no solution\n");
    return delta;
  }

  // printf("delta: %lf, %lf\n", delta, compute_vv(compute_v()));

  return (compute_vv(compute_v()) * -1 - ::sqrt(delta)) / (-9.8);
}

static inline real_type compute_d(void)
{
  return compute_t() * compute_vh(compute_v());
}

static void plot_curve(void)
{
  static const real_type dt = 0.01;
  const real_type max_t = compute_t();
  const real_type v = compute_v();
  const real_type vh = compute_vh(v);
  const real_type vv = compute_vv(v);

  // for (real_type t = 0; t < max_t + 10.9; t += dt)
  for (real_type t = 0; t < max_t; t += dt)
  {
    const real_type x = t * vh;
    const real_type y = CONFIG_H + vv * t - (4.9 * t * t);
    printf("%lf %lf\n", x, y);
  }
}

int main(int ac, char** av)
{
  // printf("%lf\n", compute_d());
  // setup(10, 80, 10, 100, to_radians(atoi(av[1])));
  // setup(17.6, 25e-3, 0.1, 80e-3, to_radians(atoi(av[1])));
  setup(475, 30e-3, 0.3, 90e-3, to_radians(atoi(av[1])));
  // printf("%lf\n", compute_t());
  plot_curve();

  return 0;
}
