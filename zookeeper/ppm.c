#include <stdio.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef float f32;

#define min(a, b) ((a) < (b) ? (a) : (b))

int
fputppm(FILE* f, f32* px, u16 w, u16 h)
{
u32 i;

if (fprintf(f, "P6 %u %u 255\n", w, h) <= 0) {
return -1;
}

for (i = 0; i < (u32)w * (u32)h; ++i)
{
u8 color[3];

color[0] = (u8)(min(1.f, px[0]) * 255.f);
color[1] = (u8)(min(1.f, px[1]) * 255.f);
color[2] = (u8)(min(1.f, px[2]) * 255.f);

if (fwrite(color, 1, 3, f) != 3) {
return -2;
}

px += 3;
}

return 0;
}

#define NCELLS 8
#define CELL_W 32
#define W (NCELLS * CELL_W)

int
main(int argc, char* argv[])
{
/* generate a checkerboard */
f32 px[W * W * 3];

f32* p = px;

u16 i, j;
int e;

for (j = 0; j < W; ++j)
{
for (i = 0; i < W; ++i)
{
u16 xodd = (i / CELL_W) & 1;
u16 yodd = (j / CELL_W) & 1;

p[0] = p[2] = 1.f;

if (xodd ^ yodd) {
p[1] = 1.f;
}

p += 3;
}
}

/* output ppm to stdout */
e = fputppm(stdout, px, W, W);
if (e) {
fprintf(stderr, "fputppm failed with error %d\n", e);
return 1;
}

return 0;
}
