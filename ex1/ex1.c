//Check if the machine is big or little endian
int is_big_endian() {
    //Store a 4 byte number
    int i = 0x01234567;
    //Get the bytes of the number as a char
    char * representation = (char*)&i;
    //Check the first byte of the representation, if the byte is equal to 01, than the machine uses big endian because
    //it stores the most significant byte at the lowest address, otherwise it uses little endian.
    if (0x01 == *representation) {
        return 1;
    }
    return 0;
}

unsigned long merge_bytes(unsigned long x, unsigned long y) {
    int halfLong = sizeof(unsigned long) / 2;
    //Move all of the bytes of x so that only the first half stays
    x = x >> (8 * halfLong);
    //Move all of the bytes of y so that only the second half stays
    y = y << (8 * halfLong);
    //Adjust all of the bytes of x and y to the correct half
    x = x << (8 * halfLong);
    y = y >> (8 * halfLong);
    //Calculate the addition of both halves
    return x | y;
}

unsigned long put_byte(unsigned long x, unsigned char b, int i) {
    //Get the bytes of the number as a char array
    char* representation = (char*)&x;
    //If the machine is little endian, the index should start from 7
    if (!is_big_endian()) {
        i = sizeof(unsigned long) - i - 1;
    }
    //Modify the i byte
    *(representation + i) = b;
    //Return the converted long
    return x;
}