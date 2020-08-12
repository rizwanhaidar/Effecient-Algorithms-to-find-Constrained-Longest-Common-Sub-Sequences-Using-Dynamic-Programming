# Effecient-Algorithms-to-find-Constrained-Longest-Common-Sub-Sequences-Using-Dynamic-Programming
My 4th Semester project of course "Design and Analysis of Algorithms" 

Programming Language : C/C++

Environment used : Linux & Windows 

Tools : Visual Studio 

                                                                  Dynamic Programming for Longest Common Subsequence 

In order to find out the complexity of brute force approach, we need to first know the number of possible different subsequences of a string with length n, i.e., find the number of subsequences with lengths ranging from 1,2,..n-1. Recall from theory of permutation and combination that number of combinations with 1 element are nC1. Number of combinations with 2 elements are nC2 and so forth and so on. We know that nC0 + nC1 + nC2 + … nCn = 2n. So a string of length n has 2n-1 different possible subsequences since we do not consider the subsequence with length 0. This implies that the time complexity of the brute force approach will be O(n * 2n). Note that it takes O(n) time to check if a subsequence is common to both the strings. This time complexity can be improved using dynamic programming. It is a classic computer science problem, the basis of diff (a file comparison program that outputs the differences between two files), and has applications in bioinformatics.

