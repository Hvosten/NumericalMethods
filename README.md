# NumericalMethods
Numerical methods implemented in C++

## RealMatrix<br>
Program that allows to create square, real matrix (or to read it from txt file) and makes various operations on them like:
- counting determinant of matrix (using definition, LU and QR decompositon and Hessenberg matrix)
- determining the inverse matrix
- LU and QR decomposition
- QR deocmposition using Gram-Schmidt method
- solving system of equations (using QR, LU or LU with WEG methods)
- locating eigenvalues for symmetric matrix
- finding eigenvalues using QR method
- finding eigenvectors using Wielandt's algorithm
- using power iteration algorithm
- calcultating matrix norm's

## ComplexMatrix<br>
Most of listed above algortihms but for matrices with complex numbers

## InterpoacjaWielomianowa<br>
Program determines interpolation polynomial for a given set of data points. Coefficients of the polynomial are calculated using Newton's divided differences method. 
