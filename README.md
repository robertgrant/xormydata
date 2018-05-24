**xorit** is a test program that shows you the first 8-bit character of the first argument XOR the first 8-bit character of the second argument
```
$ ./xorit g 4
g (103) XOR 4 (52) = S (83)
$ ./xorit S 4
S(83) XOR 4 (52) = g (103)
```

**xormydata** has the following arguments in this order:

* the name of the input file to be encrypted
* the name of the code file to be XOR'd with the input file
* the name of the output encrypted file that you want xormydata to save (none of these names should contain spaces: we're grown-ups here)
* the location in bytes (zero-indexed) from which to start using the code file (default 0); the length of the code file after this point must exceed the length of the input file or you will get an error message

You might type something like this:
```
$ ./xormydata secret-customer-data.xls Eleanor_Rigby.mp3 data-for-Geoff.xor 28191
```
