# VirtualTuringMachine-Emulator
You can add as many lines as you want! Every line is a card(rule). Don't forget to add a new line at the end! Seperate the cases for reading 1 and 0 with a space. And don't forget to write the case for reading 1 before reading case for reading 0!
The left most bit the the value that will be written to the cell that the head is currenty on. The 2nd to left most bit is the direction the head will continue. 0 for left and 1 for rignth. The rest indicate the card that the machine will continue with.
For example a case may be 11011. In this situation the first two bits in the left meen the machine will replace the value with 1 then move rigth and then continue with the 6th card (rule) The maximum bits for a case is 16 bits. 
If you don't fill 16 bits the system will automatically count the missing ones to the left as 0!

For example

A(0) = {1, R, B}

A(1) = {1, L, B}

B(0) = {1, L, A}

B(1) = {1, R, HALT}

can be shown as

1001 1011

11 101

