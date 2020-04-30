#include "aes.h"

int AES::getLeft4Bit(int num)
{
    int left = num & 0x000000f0;
    return left >> 4;
}

int AES::getRight4Bit(int num)
{
    return num & 0x0000000f;
}

int AES::getNumFromSBox(int index)
{
    int row = getLeft4Bit(index);
    int col = getRight4Bit(index);
    return S[row][col];
}

int AES::getIntFromChar(char c)
{
    int result = (int) c;
    return result & 0x000000ff;
}

void AES::convertToIntArray(char *str, int pa[4][4])
{
    int k = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) 
        {
            pa[j][i] = getIntFromChar(str[k]);
            k++;
        }

}

void AES::printArray(int a[4][4])
{
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            printf("a[%d][%d] = 0x%x ", i, j, a[i][j]);
        printf("\n");
    }
    printf("\n");
}

void AES::printASSCI(char *str, int len)
{
    for(int i = 0; i < len; i++)
        printf("0x%x ", getIntFromChar(str[i]));
    printf("\n");
}

int AES::getWordFromStr(char *str)
{
    int one = getIntFromChar(str[0]);
    one = one << 24;
    int two = getIntFromChar(str[1]);
    two = two << 16;
    int three = getIntFromChar(str[2]);
    three = three << 8;
    int four = getIntFromChar(str[3]);
    return one | two | three | four;
}

void AES::splitIntToArray(int num, int array[4])
{
    int one = num >> 24;
    array[0] = one & 0x000000ff;
    int two = num >> 16;
    array[1] = two & 0x000000ff;
    int three = num >> 8;
    array[2] = three & 0x000000ff;
    array[3] = num & 0x000000ff;
}

void AES::leftLoop4int(int array[4], int step)
{
    int temp[4];
    for(int i = 0; i < 4; i++)
        temp[i] = array[i];
    int index = step % 4 == 0 ? 0 : step % 4;
    for(int i = 0; i < 4; i++)
    {
        array[i] = temp[index];
        index++;
        index = index % 4;
    }

}

int AES::mergeArrayToInt(int array[4])
{
    int one = array[0] << 24;
    int two = array[1] << 16;
    int three = array[2] << 8;
    int four = array[3];
    return one | two | three | four;

}

int AES::T(int num, int round)
{
    
    int numArray[4];
    splitIntToArray(num, numArray);
    leftLoop4int(numArray, 1);
    for(int i = 0; i < 4; i++)
        numArray[i] = getNumFromSBox(numArray[i]);
    int result = mergeArrayToInt(numArray);
    return result ^ Rcon[round];
}

void AES::extendKey(char *key)
{
    for(int i = 0; i < 4; i++)
        w[i] = getWordFromStr(key + i * 4);
    for(int i = 4, j = 0; i < 44; i++) 
    {
        if( i % 4 == 0) {
            w[i] = w[i - 4] ^ T(w[i - 1], j);
            j++;
        }else 
        {
            w[i] = w[i - 4] ^ w[i - 1];
        }
    }
}

void AES::addRoundKey(int array[4][4], int round)
{
    
    int warray[4];
    for(int i = 0; i < 4; i++) 
    {
        splitIntToArray(w[ round * 4 + i], warray);
        for(int j = 0; j < 4; j++) {
            array[j][i] = array[j][i] ^ warray[j];
        }
    }

}

void AES::subBytes(int array[4][4])
{
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                array[i][j] = getNumFromSBox(array[i][j]);
}

void AES::shiftRows(int array[4][4])
{
    
    int rowTwo[4], rowThree[4], rowFour[4];
    for(int i = 0; i < 4; i++) 
    {
        rowTwo[i] = array[1][i];
        rowThree[i] = array[2][i];
        rowFour[i] = array[3][i];
    }
    leftLoop4int(rowTwo, 1);
    leftLoop4int(rowThree, 2);
    leftLoop4int(rowFour, 3);
    for(int i = 0; i < 4; i++) 
    {
        array[1][i] = rowTwo[i];
        array[2][i] = rowThree[i];
        array[3][i] = rowFour[i];
    }

}

int AES::GFMul2(int s)
{
    int result = s << 1;
    int a7 = result & 0x00000100;
    if(a7 != 0) 
    {
        result = result & 0x000000ff;
        result = result ^ 0x1b;
    }
    return result;
}

int AES::GFMul3(int s)
{
    return GFMul2(s) ^ s;
}

int AES::GFMul4(int s)
{
    return GFMul2(GFMul2(s));
}

int AES::GFMul8(int s)
{
    return GFMul2(GFMul4(s));
}

int AES::GFMul9(int s)
{
    return GFMul8(s) ^ s;
}

int AES::GFMul11(int s)
{
    return GFMul9(s) ^ GFMul2(s);
}

int AES::GFMul12(int s)
{
    return GFMul8(s) ^ GFMul4(s);
}

int AES::GFMul13(int s)
{
    return GFMul12(s) ^ s;
}

int AES::GFMul14(int s)
{
    return GFMul12(s) ^ GFMul2(s);
}

int AES::GFMul(int n, int s)
{
    int result;
 
    if(n == 1)
        result = s;
    else if(n == 2)
        result = GFMul2(s);
    else if(n == 3)
        result = GFMul3(s);
    else if(n == 0x9)
        result = GFMul9(s);
    else if(n == 0xb)
        result = GFMul11(s);
    else if(n == 0xd)
        result = GFMul13(s);
    else if(n == 0xe)
        result = GFMul14(s);
    return result;
}

void AES::mixColumns(int array[4][4])
{
    int tempArray[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            tempArray[i][j] = array[i][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            array[i][j] = GFMul(colM[i][0],tempArray[0][j]) ^ GFMul(colM[i][1],tempArray[1][j]) 
                ^ GFMul(colM[i][2],tempArray[2][j]) ^ GFMul(colM[i][3], tempArray[3][j]);
        }
}

void AES::convertArrayToStr(int array[4][4], char *str)
{
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                *str++ = (char)array[j][i]; 
}

int AES::checkKeyLen(int len)
{
    
    if(len == 16)
        return 1;
    else
        return 0;
}

int AES::aes(char *p, int plen, char *key)
{
    int keylen = strlen(key);
    if(plen == 0 || plen % 16 != 0) {
        return -1;
    }
    if(!checkKeyLen(keylen)) {
        return -2;
    }
    extendKey(key);
    int pArray[4][4];
    for(int k = 0; k < plen; k += 16) 
    { 
        convertToIntArray(p + k, pArray);
        addRoundKey(pArray, 0);
        for(int i = 1; i < 10; i++)
        {
            subBytes(pArray);
            shiftRows(pArray);
            mixColumns(pArray);
            addRoundKey(pArray, i);
        }
        subBytes(pArray);
        shiftRows(pArray);
        addRoundKey(pArray, 10);
        convertArrayToStr(pArray, p + k);
    }
    return 0;
}

int AES::getNumFromS1Box(int index)
{
    int row = getLeft4Bit(index);
    int col = getRight4Bit(index);
    return S2[row][col];
}

void AES::deSubBytes(int array[4][4])
{
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                array[i][j] = getNumFromS1Box(array[i][j]);
}

void AES::rightLoop4int(int array[4], int step)
{
    int temp[4];
    for(int i = 0; i < 4; i++)
        temp[i] = array[i];
    int index = step % 4 == 0 ? 0 : step % 4;
    index = 3 - index;
    for(int i = 3; i >= 0; i--) 
    {
        array[i] = temp[index];
        index--;
        index = index == -1 ? 3 : index;
    }
}

void AES::deShiftRows(int array[4][4])
{
    int rowTwo[4], rowThree[4], rowFour[4];
    for(int i = 0; i < 4; i++) 
    {
        rowTwo[i] = array[1][i];
        rowThree[i] = array[2][i];
        rowFour[i] = array[3][i];
    }
    rightLoop4int(rowTwo, 1);
    rightLoop4int(rowThree, 2);
    rightLoop4int(rowFour, 3);
    for(int i = 0; i < 4; i++) 
    {
        array[1][i] = rowTwo[i];
        array[2][i] = rowThree[i];
        array[3][i] = rowFour[i];
    }
}

void AES::deMixColumns(int array[4][4])
{
    int tempArray[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            tempArray[i][j] = array[i][j];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            array[i][j] = GFMul(deColM[i][0],tempArray[0][j]) ^ GFMul(deColM[i][1],tempArray[1][j]) 
                ^ GFMul(deColM[i][2],tempArray[2][j]) ^ GFMul(deColM[i][3], tempArray[3][j]);
        }
}

void AES::addRoundTowArray(int aArray[4][4],int bArray[4][4])
{
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}

void AES::getArrayFrom4W(int i, int array[4][4])
{
    int index = i * 4;
    int colOne[4], colTwo[4], colThree[4], colFour[4];
    splitIntToArray(w[index], colOne);
    splitIntToArray(w[index + 1], colTwo);
    splitIntToArray(w[index + 2], colThree);
    splitIntToArray(w[index + 3], colFour);
    for(int i = 0; i < 4; i++) 
    {
        array[i][0] = colOne[i];
        array[i][1] = colTwo[i];
        array[i][2] = colThree[i];
        array[i][3] = colFour[i];
    }
}

int AES::deAes(char *c, int clen, char *key)
{
    
    int keylen = strlen(key);
    if(clen == 0 || clen % 16 != 0) {
        return -1;
    }
 
    if(!checkKeyLen(keylen)) {
        return -2;
    }
    extendKey(key);//扩展密钥
    int cArray[4][4];
    for(int k = 0; k < clen; k += 16) {
        convertToIntArray(c + k, cArray);
        addRoundKey(cArray, 10);
        int wArray[4][4];
        for(int i = 9; i >= 1; i--) 
        {
            deSubBytes(cArray);
            deShiftRows(cArray);
            deMixColumns(cArray);
            getArrayFrom4W(i, wArray);
            deMixColumns(wArray);
            addRoundTowArray(cArray, wArray);
        }
        deSubBytes(cArray);
        deShiftRows(cArray);
        addRoundKey(cArray, 0);
        convertArrayToStr(cArray, c + k);
    }
}