# Reversing Minesweeper

## Wtf

This project is currently on-going. The purpose of this is to reconstruct the full source code
of the original windows xp Minesweeper. (sha256: bcff89311d792f6428468e813ac6929a346a979f907071c302f418d128eaaf41)

The artifacts of the reverse engineering process:

- Design document explaining the full design and implementation of MineSweeper
- Full compilable source code of MineSweeper
- Finding bugs 

Most of the process is done using static analysis without using a decompiler. I wanted to read lots of assembly code.

## TODO

- Create different source files for different components
- Create documentation
- Test code 
- Check and validate unsigned/signed variables 

## Nt 4.0 Leak

As stated [here](https://tcrf.net/Minesweeper_(Windows,_1990)#Source_Code_Oddities), The source code of Minesweeper has already
been leaked - So we have a peek at the original source back then.

1) I did not know it was leaked when I started this
2) I was doing this just for fun and learning so probably I would have done it anyway
3) This is not the exact version I wanted to reverse engineer

After I finished the project, I compared the source code from my reversing to the leaked source, you can see it's almost identical,
so yay.

## Legal issues?

I don't think someone cares about it.. Anyway I don't know enough about the legal issues this might cause,
If someone sees any problem talk with me.
