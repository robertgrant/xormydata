xormydata
=========

Exclusive or (XOR) encryption takes your data at a binary level and combines it with a code file. If your data has a bit (0 or 1) with the same value as the corresponding bit from the code file, then the result is a 0. If they are different, the result is a 1. I intend this to be used as a one-time pad, which is to say that you use the code file once only, and it's paired with the input file on that occasion only. Provided that the code file is close enough to a random stream of 0s and 1s, it'll be impossible to decrypt. It wouldn't be a good idea to use something like a human-readable text file, for example, nor some format with predictable pockets of metadata, like a Word document. I think mp3s are a good option as they are large enough for most purposes, and you probably have lots of them sitting around. However, to be really secure what you should do is to record some static into a WAV sound file and normalise it (maximise the volume). You could use free software like Audacity for that, and plug a radio into your microphone socket.

XOR is reversible, so you can just apply the codefile to the encrypted file and get the original data back again. I imagine that Alice would encrypt the data, email it to Bob (because they work in some resource-poor place where they have to rely on email (and remember, emails are as good as published)), then call him and tell him which of their many shared files (starting at which byte number) to use as the code. Unless you think someone has hacked into your shared codefile library and is intercepting your emails and tapping your phone, this will do the biz.

XOR is commutative, which means that you can encrypt with codefile A, then apply codefile B on top of that. Then, in either order, apply them again and get the original back. This raises the possibility of triple-pass communication, where Alice and Bob do not share code files at all. Alice sends Bob data+A, Bob sends her back data+A+B, Alice sends him data+A+B-A = data+B, and he applies his codefile B to get the raw data again. There have been three communications, but none of them involved anything that could be decrypted. *Unfortunately*, if someone intercepts all the emails, they can use simple maths to get the raw data out. Also, a man-in-the-middle attack, where Charles intercepts the emails and pretends to be Bob, will obviously do the trick just fine. But you know what, if these are things that worry you, you have bigger problems than this can solve. Bottom line for everyone: do not use email, preferably ever (this is a light-hearted remark: because it destroys productivity), but at least not for sensitive data, even if it is encrypted.

Warning
-------

Possessing encryption software (which this repository contains) is a criminal offense in some jurisdictions, such as the United Arab Emirates. Because every MacBook and iPhone comes with openssl, they don't enforce this, but remember than changing planes at DXB with this repo cloned can in theory lead directly to the rest of your life in prison in the desert. You might also be breaking the law by leaving your own country with this in your possession. You have been warned. Remember the words of Jello Biafra: they'll bust your ....ing ass if they wanna.

Details
-------

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
