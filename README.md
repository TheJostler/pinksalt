# pinksalt

This is a demonstration of a password salter + hasher, only this is a very special kind of salt, hence the name!

It is a simple program that is the result of a thought experiment I had, it tests the idea of storing simple information into a password hash. DON'T ACTUALLY USE THIS IN ANY AUTHENTICATION SYSTEM🤣

Many developers use Salted passwords to stop hackers trying to bruteforce passwords, with known password hashes.
A salt is a fixed length random integer appended to the end of the password before it's hashed. I figured why does the salt have to be random.

If the integer at the end of the password could store useful information, this information would be stored/transported securely as the only way to retrieve the information is to know the password and to spend time bruteforcing the information!

This could be used to make information even more private and secure as the information is not really being stored
in a way that can be decrypted. 

The information must to attained through a brute force password attack.

## How to use

This program simply takes a string and a 5 digit hexadecimal number and hashes them. 

Or it can take hashes either from the user or by reading a file and bruteforce the information with a given string.

It's up to you what your 5 digit number signifies.

## Is 5 digits enough?

Did you know the majority of English words are 4 characters long. You don't need a lot of storage to record alot of information.

I chose to use a 20-bit integer meaning there are a total of 1,048,575 unique possible combinations. Which depending on the use case might or might not be enough.

It's a trade off between storage capacity and time it takes to retrieve the information, as you add bits to the salt the number of combinations grows exponentially; making retrieval time longer!

If you want to you can change the value of SALT_CAP in pinksalt.c(line:13) to increase/decrease the total range of salts that you will use.
