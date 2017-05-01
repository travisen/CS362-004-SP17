/*
	How I tested randomstring.c
	I was a little confused out first about what I was suppose
	to do with the testme.c file; however, inspecting the code
	and reading some discussions on piazza, crystalized what I had to do.

	Using randomly generated input, my goal is to make the testme function
	print an error. I noticed that the loop within test me runs forever
	and that some parameters had to be meet in order to print "error ".

	I noticed that srand() was called in main. I then decided that I would 
	generate a random char in the inputchar function and a random string in the
	random string function. To print "error " string s must contain the
	following, recall that a string in c is an array of chars: reset\0.
	Including the null character this is a string of length 6, so I decided
	to randomly generate strings of length 5 and append on a \0.

	randomChar generates a random character and works as follows. Remembering
	that in c chars can be represented as numbers which correspond to values
	in the ASCII table, I take the mod of 96 and add 32 as I need to get each 
	of the nesscary chars to eventually increment state to 9. Modding by 96 and
	adding 32 accesses the range of ASCII values needed.

	Initially,I had randomStr generate a random string consisting of chars
	from a to z. When I did all chars from a to z it took 6138383 iterations.
	I also could have just generated random chars from e to t which could
	possibly make the test run faster by meeting the conditions quicker.

*/
