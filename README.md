# Matrix Inverse

### Overall
This is a tool to calculate <a href="https://www.codecogs.com/eqnedit.php?latex=A^{-1}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A^{-1}" title="A^{-1}" /></a>. I use Gaussian Elimination to calculate the determinant and <a href="https://www.codecogs.com/eqnedit.php?latex=A^{-1}&space;=&space;\frac{(A^*)^T}{|A|}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?A^{-1}&space;=&space;\frac{(A^*)^T}{|A|}" title="A^{-1} = \frac{(A^*)^T}{|A|}" /></a> to calculate the answer. Please contact me by 272341890@qq.com if you find any bug(s).
use `g++ -o inv MatrixInverse.cpp -std=c++11`(or c++14, c++17) to compile.

You can type `num/den` or `-num/den` to input a fraction, or just type `c` on behalf of the fraction `c/1`.

The first line of the input should be the size "n" of the matrix, and the following "n" lines of the input should contain "n" fractions each line, which stand for each row of the matrix. 