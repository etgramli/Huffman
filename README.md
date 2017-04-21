# Huffman Encoder and Decoder
## Huffman Encoder
This is a program that encodes a text file to Huffman code.
It creates a huffman code for all distinct characters and writes both to
an encoding table file and the huffman codes of the message characters
to a binary file.

### What it does
For all printable characters the encoder creates a leaf node with the
character's frequency. Then it takes recursively the two characters with
the lowest frequencies and creates a Connection node with the previous
nodes as children. Then it removes the children from the list and adds
the Connection node.

After the tree is constructed, the tree will be passed through to
collect all Huffman codes for all the characters. The codes are stored
in the encodingTable of the HuffmanEncoder.

Then, in the 2nd pass, the text file will be read again, character by
character, and the Huffman codes for the character will be written to
the output file.

## Huffman Decoder
The decoder needs the file with the encoding table and the encoded
message file (ending with .out).
It reads the bits of the message file and replaces them with the fitting
characters to the found huffman code (does not build the huffman code
tree, only constructs a map of huffman code to char).

### Important note
If decoding, both -i and -c parameters must be passed.


# Usage

## Compilation

### make huffman
Creates an executable with debugging symbols (-g). Should only be used
for testing.

### make huffmanO3
Creates an executable with strongest optimizations. Can be used for
creating the final exectuable for normal usage.

### make huffmanOs
Creates an executable optimized for size. Can be used for creating the
final exectuable for normal usage.

### make huffmanClang
Additional target that was used to print additional warnings and errors
from the clang compiler, to find more errors (useful to find UB).

### make all
Makes all targets above.


## Programm call
The program takes following parameters:
### Parameters:
- -h
Print help.

- -i <file>
The file to create a Huffman Code for

- -c <file>
The file with the Huffman Code for the input file; results in only the 2nd pass

- -o <file>
The file to to save the Huffman Code in

- -s
Silent; do not create a Huffman code file



# Hints
- Only text files supported for endcoding
- Decoded text file is exactly the same as the original file (tested using diff)
- Own binary format
