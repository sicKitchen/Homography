# Homography

Name:		Spencer Kitchen
Email:		spencer.kitchen@wsu.edu

SUBMITTED ARCHIVE:
	README.txt
	LUdecomp.c
	LUdecomp.h
	homography.c
	hmap.c
	Makefile
	boxtop.in
	cheerios-small.ppm  	

DESCRIPTION:

	Package		- This package will read the input file, boxtops.in and set up 
			  the matrix for a homography transform using LU decomposition.
			  This is then piped into the provided program hmap.c to transform
			  the input picture ‘cheerios-small.ppm’ to a new picture outputted 
			  as face.ppm. face.ppm is the front of the cereal box.

	LUdecomp.c	- This file is what handles the creation of the matrix A and 
			  separates it into LU=A. LU is then replaces for A to generate
			  (LU)x=b. The program then forward and back solves to figure
			  out what x is and returns it.

	LUdecomp.h	- Header file for functions of LUdecomp.c. Provided by assignment

	homography.c	- This program takes the inputs from boxtops.in and maps them to
			  a transformation matrix composed of source points and target 
			  points. This then uses LU decomposition to solve for x in Ax =b 
			  and passes x on to the provided program hmap.c

	hmap.c		- provided program that takes cheerios-small.ppm and useing my 
			  x matrix from homography.c outputs the image face.ppm

	boxtop.in	- Provided input to homography.c

	cheerios-small.ppm - provided image

COMPILE: Compiles with included make file. Navigate to folder containing all these files.
	 From command line input ‘make’ and program should be built. To write out nine 
	 components on the homography matrix enter:

	 ‘./homography < boxtop.in’

	 To make face.ppm (image of face of cereal box) enter:

	 ‘./homography < boxtop.in | ./hmap cheerios-small.ppm 500 650 > face.ppm’

	 You can then open face.ppm to see the transformed image of the face of the cereal box.		
