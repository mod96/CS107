/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "bovik_",              /* Team name */

    "Harry Q. Bovik",     /* First member full name */
    "bovik@nowhere.edu",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
	    	dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
			}
		}
}

char rotate_descr_1[] = "rotate_1_only unroll";
void rotate_1(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i+=2) {
			for (j = 0; j < dim; j+=2) {
	    	dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
				dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
				dst[RIDX(dim-2-j, i, dim)] = src[RIDX(i, j+1, dim)];
				dst[RIDX(dim-2-j, i+1, dim)] = src[RIDX(i+1, j+1, dim)];
			}
		}
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr_1_[] = "rotate_1_unroll_and_param_optim";
void rotate_1_(int dim, pixel *src, pixel *dst) 
{
    int i, j;
		int t1, t2;
		int p1, p2;

    for (i = 0; i < dim; i+=2) {
			for (j = 0; j < dim; j+=2) {
				t2 = (dim-2-j)*dim+i;
				t1 = t2 + dim;
				p1 = i*dim+j;
				p2 = p1+dim;
				dst[t1] = src[p1];
				dst[t1+1] = src[p2];
				dst[t2] = src[p1+1];
				dst[t2+1] = src[p2+1];
			}
		}
}

char rotate_descr_2[] = "rotate_2_only unroll_4x4";
void rotate_2(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i+=4) {
			for (j = 0; j < dim; j+=4) {
	    	dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
				dst[RIDX(dim-1-j, i+1, dim)] = src[RIDX(i+1, j, dim)];
				dst[RIDX(dim-1-j, i+2, dim)] = src[RIDX(i+2, j, dim)];
				dst[RIDX(dim-1-j, i+3, dim)] = src[RIDX(i+3, j, dim)];
				dst[RIDX(dim-2-j, i, dim)] = src[RIDX(i, j+1, dim)];
				dst[RIDX(dim-2-j, i+1, dim)] = src[RIDX(i+1, j+1, dim)];
				dst[RIDX(dim-2-j, i+2, dim)] = src[RIDX(i+2, j+1, dim)];
				dst[RIDX(dim-2-j, i+3, dim)] = src[RIDX(i+3, j+1, dim)];
				dst[RIDX(dim-3-j, i, dim)] = src[RIDX(i, j+2, dim)];
				dst[RIDX(dim-3-j, i+1, dim)] = src[RIDX(i+1, j+2, dim)];
				dst[RIDX(dim-3-j, i+2, dim)] = src[RIDX(i+2, j+2, dim)];
				dst[RIDX(dim-3-j, i+3, dim)] = src[RIDX(i+3, j+2, dim)];
				dst[RIDX(dim-4-j, i, dim)] = src[RIDX(i, j+3, dim)];
				dst[RIDX(dim-4-j, i+1, dim)] = src[RIDX(i+1, j+3, dim)];
				dst[RIDX(dim-4-j, i+2, dim)] = src[RIDX(i+2, j+3, dim)];
				dst[RIDX(dim-4-j, i+3, dim)] = src[RIDX(i+3, j+3, dim)];
			}
		}
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr_2_[] = "rotate_2_unroll_and_param_optim";
void rotate_2_(int dim, pixel *src, pixel *dst) 
{
    int i, j;
		int t1, t2, t3, t4;
		int p1, p2, p3, p4;

    for (i = 0; i < dim; i+=4) {
			for (j = 0; j < dim; j+=4) {
				t4 = (dim-4-j)*dim+i;
				t3 = t4 + dim;
				t2 = t3 + dim;
				t1 = t2 + dim;
				p1 = i*dim+j;
				p2 = p1 + dim;
				p3 = p2 + dim;
				p4 = p3 + dim;

	    	dst[t1] = src[p1];
				dst[t1+1] = src[p2];
				dst[t1+2] = src[p3];
				dst[t1+3] = src[p4];
				dst[t2] = src[p1+1];
				dst[t2+1] = src[p2+1];
				dst[t2+2] = src[p3+1];
				dst[t2+3] = src[p4+1];
				dst[t3] = src[p1+2];
				dst[t3+1] = src[p2+2];
				dst[t3+2] = src[p3+2];
				dst[t3+3] = src[p4+2];
				dst[t4] = src[p1+3];
				dst[t4+1] = src[p2+3];
				dst[t4+2] = src[p3+3];
				dst[t4+3] = src[p4+3];
			}
		}
}

char rotate_descr[] = "rotate: current";
void rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;
		int t1, t2, t3, t4;
		int p1, p2, p3, p4;
		int base=0, dim_4_dim=(dim-4)*dim;

    for (i = 0; i < dim; i+=4) {
			t4 = dim_4_dim+i;
			for (j = 0; j < dim; j+=4) {
				t3 = t4 + dim;
				t2 = t3 + dim;
				t1 = t2 + dim;
				p1 = base+j;
				p2 = p1 + dim;
				p3 = p2 + dim;
				p4 = p3 + dim;

	    	dst[t1] = src[p1];
				dst[t1+1] = src[p2];
				dst[t1+2] = src[p3];
				dst[t1+3] = src[p4];
				dst[t2] = src[p1+1];
				dst[t2+1] = src[p2+1];
				dst[t2+2] = src[p3+1];
				dst[t2+3] = src[p4+1];
				dst[t3] = src[p1+2];
				dst[t3+1] = src[p2+2];
				dst[t3+2] = src[p3+2];
				dst[t3+3] = src[p4+2];
				dst[t4] = src[p1+3];
				dst[t4+1] = src[p2+3];
				dst[t4+2] = src[p3+3];
				dst[t4+3] = src[p4+3];

				t4 -= 4*dim;
			}
			base += 4*dim;
		}
}
/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);  
		add_rotate_function(&rotate_1, rotate_descr_1);  
		add_rotate_function(&rotate_1_, rotate_descr_1_);   
    add_rotate_function(&rotate_2, rotate_descr_2);  
		add_rotate_function(&rotate_2_, rotate_descr_2_); 
		add_rotate_function(&rotate, rotate_descr); }


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
			for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    	accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}


/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
	    	dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
			}
		}
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;
		int t;
		int limit;
		
		/* vertices */
		t=0;
    dst[t].red = (src[t].red+src[t+1].red+src[t+dim].red+src[t+dim+1].red)/4;
    dst[t].green  = (src[t].green +src[t+1].green +src[t+dim].green +src[t+dim+1].green )/4;
    dst[t].blue = (src[t].blue+src[t+1].blue+src[t+dim].blue+src[t+dim+1].blue)/4;
		t=dim-1;
		dst[t].red = (src[t].red+src[t-1].red+src[t+dim].red+src[t+dim-1].red)/4;
		dst[t].green  = (src[t].green +src[t-1].green +src[t+dim].green +src[t+dim-1].green )/4;
		dst[t].blue = (src[t].blue+src[t-1].blue+src[t+dim].blue+src[t+dim-1].blue)/4;
		t=dim*dim-1;
		dst[t].red = (src[t].red+src[t-1].red+src[t-dim].red+src[t-dim-1].red)/4;
		dst[t].green  = (src[t].green +src[t-1].green +src[t-dim].green +src[t-dim-1].green )/4;
		dst[t].blue = (src[t].blue+src[t-1].blue+src[t-dim].blue+src[t-dim-1].blue)/4;
		t=dim*dim-dim;
		dst[t].red = (src[t].red+src[t+1].red+src[t-dim].red+src[t-dim+1].red)/4;
		dst[t].green  = (src[t].green +src[t+1].green +src[t-dim].green +src[t-dim+1].green )/4;
		dst[t].blue = (src[t].blue+src[t+1].blue+src[t-dim].blue+src[t-dim+1].blue)/4;

		/* sides */
		limit = dim * dim - 1; /* bottom */
		for (i = limit - dim + 2; i < limit; i++) {
			dst[i].red = ((src[i-1].red+src[i].red)+(src[i+1].red+src[i-dim-1].red)+(src[i-dim].red+src[i-dim+1].red))/6;
			dst[i].green  = ((src[i-1].green +src[i].green )+(src[i+1].green +src[i-dim-1].green )+(src[i-dim].green +src[i-dim+1].green ))/6;
			dst[i].blue = ((src[i-1].blue+src[i].blue)+(src[i+1].blue+src[i-dim-1].blue)+(src[i-dim].blue+src[i-dim+1].blue))/6;
		}
		limit = dim * dim - dim; /* left */
		for (i = dim; i < limit; i+=dim) {
			dst[i].red = ((src[i-dim].red+src[i-dim+1].red)+(src[i].red+src[i+1].red)+(src[i+dim].red+src[i+dim+1].red))/6;
			dst[i].green  = ((src[i-dim].green +src[i-dim+1].green )+(src[i].green +src[i+1].green )+(src[i+dim].green +src[i+dim+1].green ))/6;
			dst[i].blue = ((src[i-dim].blue+src[i-dim+1].blue)+(src[i].blue+src[i+1].blue)+(src[i+dim].blue+src[i+dim+1].blue))/6;
		}
		for (i = (dim << 1) - 1; i < limit; i+=dim) { /* right */
			dst[i].red = ((src[i-dim-1].red+src[i-dim].red)+(src[i-1].red+src[i].red)+(src[i+dim-1].red+src[i+dim].red))/6;
			dst[i].green  = ((src[i-dim-1].green +src[i-dim].green )+(src[i-1].green +src[i].green )+(src[i+dim-1].green +src[i+dim].green ))/6;
			dst[i].blue = ((src[i-dim-1].blue+src[i-dim].blue)+(src[i-1].blue+src[i].blue)+(src[i+dim-1].blue+src[i+dim].blue))/6;
		}
		limit = dim - 1; /* top */
		for (i = 1; i < limit; i++) {
			dst[i].red = ((src[i-1].red+src[i].red)+(src[i+1].red+src[i+limit].red)+(src[i+dim].red+src[i+dim+1].red))/6;
			dst[i].green  = ((src[i-1].green +src[i].green )+(src[i+1].green +src[i+limit].green )+(src[i+dim].green +src[i+dim+1].green ))/6;
			dst[i].blue = ((src[i-1].blue+src[i].blue)+(src[i+1].blue+src[i+limit].blue)+(src[i+dim].blue+src[i+dim+1].blue))/6;
		}

		/* main loop */
		for (i = 1; i < limit; i++) {
			for (j = 1; j < limit; j++) {
				t = i*dim + j;
	    	dst[t].red = (((src[t-dim-1].red+src[t-dim].red)+(src[t-dim+1].red+src[t-1].red))+((src[t].red+src[t+1].red)+(src[t+dim-1].red+src[t+dim].red))+src[t+dim+1].red)/9;		
	    	dst[t].green  = (((src[t-dim-1].green +src[t-dim].green )+(src[t-dim+1].green +src[t-1].green ))+((src[t].green +src[t+1].green )+(src[t+dim-1].green +src[t+dim].green ))+src[t+dim+1].green )/9;		
	    	dst[t].blue = (((src[t-dim-1].blue+src[t-dim].blue)+(src[t-dim+1].blue+src[t-1].blue))+((src[t].blue+src[t+1].blue)+(src[t+dim-1].blue+src[t+dim].blue))+src[t+dim+1].blue)/9;		
			}
		}
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

