### single instruction single data

Most Arm instructions are Single Instruction Single Data (SISD). Each instruction performs its specified operation on a single data source. Processing multiple data items therefore requires multiple instructions. For example, to perform four addition operations requires four instructions to add values from four pairs of registers

```
ADD w0, w0, w5
ADD w1, w1, w6
ADD w2, w2, w7
ADD w3, w3, w8
```

If the values you are dealing with are smaller than the maximum bit size, that extra potential bandwidth is wasted with SISD instructions. For example, when adding 8-bit values together, each 8-bit value needs to be loaded into a separate 64-bit register. Performing large numbers of individual operations on small data sizes does not use machine resources efficiently because processor, registers, and data path are all designed for 64-bit calculations.

### single instruction multiple data

perform the same operation simultaneously for multiple data items. These data items are packed as separate lanes in a larger register.

### registers, vectors, lanes and elements

| Letter | Meaning    | Bit Width |
| ------ | ---------- | --------- |
| **B**  | Byte       | 8-bit     |
| **H**  | Halfword   | 16-bit    |
| **S**  | Word       | 32-bit    |
| **D**  | Doubleword | 64-bit    |


The Neon register file is a collection of registers which can be accessed as 8-bit, 16-bit, 32-bit, 64-bit, or 128-bit registers.

The Neon registers contain vectors of elements of the same data type. The same element position in the input and output registers is referred to as a lane.

Usually each Neon instruction results in n operations occurring in parallel, where n is the number of lanes that the input vectors are divided into. Each operation is contained within the lane. There cannot be a carry or overflow from one lane to another.

The number of lanes in a Neon vector depends on the size of the vector and the data elements in the vector.

A 128-bit Neon vector can contain the following element sizes:

Sixteen 8-bit elements (operand suffix .16B, where B indicates byte)
Eight 16-bit elements (operand suffix .8H, where H indicates halfword)
Four 32-bit elements (operand suffix .4S, where S indicates word)
Two 64-bit elements (operand suffix .2D, where D indicates doubleword)
A 64-bit Neon vector can contain the following element sizes (with the upper 64 bits of the 128-bit register cleared to zero):

Eight 8-bit elements (operand suffix .8B, where B indicates byte)
Four 16-bit elements (operand suffix .4H, where H indicates halfword)
Two 32-bit elements (operand suffix .2S, where S indicates word)


```
MUL V0.4S, V2.4S, V3.S[2]
```
-> v0.4S = Vector of 4 x 32 bit  (128 bit)
-> v2.4S = vector of 4 x 32 bit ( 128 bit)
-> v3.S[2] = S denotes 32-bit, [2] denotes take the third index of the lane