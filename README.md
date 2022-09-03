# Shamir Secret Sharing Algorithm
Implementation of the shamir secret sharing algorithm used in cryptology using galois field 256.

### Input format:
1. 32 space separated integers, this will be our secret.
2. In the next line, 2 space separated integers, these are the share numbers we use for finding the secret.

### Improvements that can be made: 
1. Make the code more extensible. For eg currently it is taking a hard coded values like limit of 32 as the number of elements in secrets, the number of shares (i.e  4 here) and number of shares needed for decrypting (2 in our case). It will be much more useable if we can take all of these values as dynamic input from the user.
2. Writing tests to check the correctness of our algorithm.
3. Lagrange function has been simplified to use the value of 2 (as in our case). It can be made generalised.

### Resources used:
1. https://www.youtube.com/watch?v=kkMps3X_tEE (built understanding and intuition for the algorithm)
2. https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing (used preparation section for generating the shares)
